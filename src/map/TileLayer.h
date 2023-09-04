/* #ifndef TILELAYER_H
#define TILELAYER_H

#include <string>
#include <vector>

#include "Layers.h"
#include "TextureManager.h"

struct Tileset
{
    int first_id, last_id;
    int row_count, col_count;
    int tile_count, tile_size;
    std::string name, source;
};

using TilesetList = std::vector<Tileset*>;
using TileMap = std::vector<std::vector<int>>;


class TileLayer : public Layers
{
    public:
        TileLayer(int tile_size, int row_count, int col_count, TileMap tile_map, TilesetList tile_set);

        void render();
        void update();

        inline TileMap get_tile_map(){return m_tile_map;}

    private:
        int m_tile_size;
        int m_row_count, m_col_count;

        TileMap m_tile_map;
        TilesetList m_tileset;

        friend class MapParser;
};

#endif */ // TILELAYER_H
