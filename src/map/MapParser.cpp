/* #include "MapParser.h"

MapParser* MapParser::s_instance = nullptr;

MapParser::MapParser()
{
    //ctor
}

bool MapParser::load()
{
    return parse("level_1", "assets/maps/map.tmx");
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
    for(TiXmlElement* e=root->FirstChildElement(); e!= nullptr; e=e->NextSiblingElement())
    {
        if(e->Value() == std::string("tileset"))
        {
            // tileset.push_back(new Tileset(parse_tileset(e)));
        }
    }

    GameMap* game_map = new GameMap();
    for(TiXmlElement* e=root->FirstChildElement(); e!= nullptr; e=e->NextSiblingElement())
    {
        if(e->Value() == std::string("layer"))
        {
            TileLayer* tile_layer = parse_tile_layer(e, tileset, tile_size, row_count, col_count);
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
    tileset.row_count = tileset.tile_count/ tileset.col_count;

    xml_tileset->Attribute("tilewidth", &tileset.tile_size);

    TiXmlElement* image = xml_tileset->FirstChildElement(); // image is another child element to the tileset -> access tinyImage

    tileset.source = image->Attribute("source");

    return tileset;
}

TileLayer* MapParser::parse_tile_layer(TiXmlElement* xml_layer, TilesetList tileset, int tile_size, int row_count, int col_count)
{
    TiXmlElement* data;

    for(TiXmlElement* e = xml_layer->FirstChildElement(); e != nullptr; e = e->NextSiblingElement())
    {
        if(e->Value() == std::string("data"))
        {
            data = e;
            break;
        }
    }

    std::string matrix(data->GetText()); // the matrix is the big text of number which define the map
    std::istringstream iss(matrix);
    std::string id;
    TileMap tile_map(row_count, std::vector<int>(col_count, 0)); // fill the map with zeros

    for(int row = 0; row < row_count; row++)
    {
        for(int col = 0; col < col_count; col++)
        {
            getline(iss, id, ','); // separate with ',', we put it inside id
            std::stringstream convertor(id); // convert id
            convertor >> tile_map[row][col];

            if(iss.good())
            {
                break;
            }
        }
    }

    return (new TileLayer(tile_size, row_count, col_count, tile_map, tileset));
}

void MapParser::clean()
{
    std::map <std::string, GameMap*>::iterator it;
    for(it = m_map.begin(); it != m_map.end(); it++)
    {
        it->second = nullptr;
    }

    m_map.clear();
} */
