#ifndef MAPHANDLER_H
#define MAPHANDLER_H

#include <string>
#include <vector>
#include <map>

#include "Layers.h"
#include "GameMap.h"
#include "tinyxml.h"
#include "TextureManager.h"


struct Tileset
{
    int first_id, last_id;
    int row_count, col_count;
    int tile_count, tile_size;
    std::string name, source;
};

using TilesetList = std::vector<Tileset>; // list of all tilesets
using TileMap = std::vector<std::vector<int>>; // coords  x and y of a tile

class TileLayer : public Layers
{
    public:
        TileLayer(int tile_size, int row_count, int col_count, TileMap tile_map, TilesetList tile_set);

        void render();
        void update();

    public:
        inline TileMap get_tile_map(){return m_tile_map;}

    private:
        int m_tile_size;
        int m_row_count, m_col_count;

        TileMap m_tile_map;

        TilesetList m_tilesets;

        friend class MapParser;
};

class MapParser
{
    public:
        inline static MapParser* get_instance()
        {return s_instance = (s_instance != nullptr)? s_instance : new MapParser();}

        bool load();
        void clean();

        inline GameMap* get_map(std::string id){return m_map[id];}

    public:
        bool parse(std::string id, std::string source);

        Tileset parse_tileset(TiXmlElement* xml_tileset);
        TileLayer* parse_tile_layer(TiXmlElement* xml_layer, TilesetList tile_set, int tile_size, int row_count, int col_count);

    private:
        static MapParser* s_instance;
        MapParser();

        std::map <std::string, GameMap*> m_map;
};

#endif // MAPHANDLER_H
