#include "MapHandler.h"

#include <iostream>

MapParser* MapParser::s_instance = nullptr;

TileLayer::TileLayer(int tile_size, int row_count, int col_count, TileMap tile_map, TilesetList tilesets) :
    m_tile_size(tile_size), m_row_count(row_count), m_col_count(col_count), m_tile_map(tile_map), m_tilesets(tilesets)
{
    std::cout << "m_tilesets.size() : " << m_tilesets.size() << std::endl;
    std::cout << "m_row_count : " << m_row_count << std::endl;
    std::cout << "m_col_count : " << m_col_count << std::endl;
    for(unsigned int i = 0; i < m_tilesets.size(); i++)
    {
        TextureManager::GetInstance()->Load(m_tilesets[i].name, m_tilesets[i].source);
    }
} // used in parse_tile_layer

void TileLayer::render()
{
    for(int i = 0; i < m_row_count; i++)
    {
        for(int j = 0; j < m_col_count; j++)
        {
            int tile_id = m_tile_map[i][j];

            if(tile_id == 0)
            {
                continue;
            }
            else
            {
                int index = 0;

                /* if(m_tilesets.size() > 1)
                {
                    for(unsigned int k = 1; k <= m_tilesets.size(); k++)
                    {
                        if(tile_id > m_tilesets[k].first_id && tile_id < m_tilesets[k].last_id)
                        {
                            tile_id = tile_id + m_tilesets[k].tile_count - m_tilesets[k].last_id;
                            index = k;
                            break;
                        }
                    }
                } */

                Tileset tileset = m_tilesets[index];

                int tile_row = tile_id / tileset.col_count;
                int tile_col = tile_id - tile_row * tileset.col_count - 1;

                // std::cout << tile_row << " " << tile_col << std::endl;

                if(tile_id % tileset.col_count == 0)
                {
                    tile_row--;
                    tile_col = tileset.col_count - 1;
                }

                TextureManager::GetInstance()->DrawTile(tileset.name, tileset.tile_size, j * tileset.tile_size, i * tileset.tile_size, tile_row, tile_col);
            }
        }
    }
}

void TileLayer::update()
{

}

MapParser::MapParser()
{
    //ctor
}

bool MapParser::load()
{
    if(!parse("level_1", "map.tmx"))
    {
        return false;
    }
    return true;
}

bool MapParser::parse(std::string id, std::string source)
{
    TiXmlDocument xml;
    xml.LoadFile(source);

    if(xml.Error())
    {
        std::cerr << "failed to load : " << source << std::endl;
        return false;
    }

    TiXmlElement* root = xml.RootElement();
    int row_count, col_count, tile_size = 0;

    root->Attribute("width", &row_count);
    root->Attribute("height", &col_count);
    root->Attribute("tilewidth", &tile_size);

    TilesetList tileset;
    for(TiXmlElement* e = root->FirstChildElement(); e != nullptr; e = e->NextSiblingElement())
    {
        if(e->Value() == std::string("tileset"))
        {
            tileset.push_back(parse_tileset(e));
            break; // Load only one tileset
        }
    }

    GameMap* game_map = new GameMap();
    for(TiXmlElement* e = root->FirstChildElement(); e != nullptr; e = e->NextSiblingElement())
    {
        if(e->Value() == std::string("layer"))
        {
            TileLayer* tile_layer = parse_tile_layer(e, tileset, tile_size, col_count, row_count);
            game_map->m_map_layers.push_back(tile_layer);
        }
    }

    m_map[id] = game_map;

    return true;
}

Tileset MapParser::parse_tileset(TiXmlElement* xml_tileset)
{
    Tileset tileset;

    tileset.name = xml_tileset->Attribute("name");

    xml_tileset->Attribute("firstgid", &tileset.first_id);
    xml_tileset->Attribute("tilecount", &tileset.tile_count);

    tileset.last_id = (tileset.first_id + tileset.tile_count) - 1;

    xml_tileset->Attribute("columns", &tileset.col_count);

    tileset.row_count = tileset.tile_count / tileset.col_count;

    xml_tileset->Attribute("tilewidth", &tileset.tile_size);

    TiXmlElement* image = xml_tileset->FirstChildElement();
    tileset.source = image->Attribute("source");

    std::cout << "source : " << tileset.source << ", first_id : " << tileset.first_id << ", name : " << tileset.name
              << ", size : " << tileset.tile_size << ", tile_count : " << tileset.tile_count << ", col_count : " << tileset.col_count
              << ", row_count : " << tileset.row_count << ", last_id : " << tileset.last_id << std::endl;

    return tileset;
}

TileLayer* MapParser::parse_tile_layer(TiXmlElement* xml_layer, TilesetList tilesets, int tile_size, int row_count, int col_count)
{
    TiXmlElement* data;

    std::cout << tile_size << " " << row_count << " " << col_count << " " << std::endl;

    for(TiXmlElement* e = xml_layer->FirstChildElement(); e != nullptr; e = e->NextSiblingElement())
    {
        if(e->Value() == std::string("data"))
        {
            data = e;
            break;
        }
    }

    std::string matrix(data->GetText()); // the matrix is the big text of number and ',' between <data encoding="csv"> and </data>
    // std::cout << "matrix : " << matrix << std::endl;
    std::istringstream iss(matrix);

    std::string id;

    int cnt = 0;

    TileMap tile_map(row_count, std::vector<int>(col_count, 0)); // fill the map with zeros

    for(int row = 0; row < row_count; row++)
    {
        for(int col = 0; col < col_count; col++)
        {
            getline(iss, id, ',');

            cnt++;

            std::stringstream convertor(id);
            convertor >> tile_map[row][col];

            std::cout << tile_map[row][col] << " ";

            if(!iss.good())
            {
                break;
            }
        }
    }

    std::cout << "cnt : " << cnt << std::endl;

    return (new TileLayer(tile_size, row_count, col_count, tile_map, tilesets));
}

void MapParser::clean()
{
    std::map <std::string, GameMap*>::iterator it;
    for(it = m_map.begin(); it != m_map.end(); it++)
    {
        it->second = nullptr;
    }

    m_map.clear();
}
