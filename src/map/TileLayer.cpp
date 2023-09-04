/* #include "TileLayer.h"

TileLayer::TileLayer(int tile_size, int row_count, int col_count, TileMap tile_map, TilesetList tileset) :
    m_tile_size(tile_size), m_row_count(row_count), m_col_count(col_count), m_tile_map(tile_map), m_tileset(tileset)
{
    for(unsigned int i = 0; i<m_tileset.size(); i++)
    {
        TextureManager::get_instance()->load(m_tileset[i]->name, "assets/maps/" + m_tileset[i]->source);
    }
}

void TileLayer::render()
{
    for(int i = 0; i<m_row_count; i++)
    {
        for(int j = 0; j<m_col_count; i++)
        {
            int tile_id = m_tile_map[i][j];

            if(tile_id == 0)
            {
                continue;
            }
            else
            {
                int index;
                if(m_tileset.size() > 1)
                {
                    for(unsigned int k = 1; k < m_tileset.size(); k++)
                    {
                        if(tile_id > m_tileset[k]->first_id && tile_id < m_tileset[k]->last_id)
                        {
                            tile_id = tile_id + m_tileset[k]->tile_count - m_tileset[k]->last_id;
                            index = k;
                            break;
                        }
                    }
                }
                Tileset* tileset = m_tileset[index];
                int tile_row = tile_id / tileset->col_count;
                int tile_col = tile_id - tile_row * tileset->col_count -1;

                if(tile_id % tileset->col_count == 0)
                {
                    tile_row--;
                    tile_col = tileset->col_count - 1;
                }

                TextureManager::get_instance()->draw_tile(tileset->name, tileset->tile_size, i*tileset->tile_size, j*tileset->tile_size, tileset->row_count, tileset->col_count);
            }
        }
    }
}

void TileLayer::update()
{

}

*/
