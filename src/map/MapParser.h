/* #ifndef MAPPARSER_H
#define MAPPARSER_H

#include <string>
#include <map>

#include "Layers.h"
#include "GameMap.h"
#include "TileLayer.h"

#include <tinyxml.h>

struct Tileset2
{
    int first_id, last_id;
    int row_count, col_count;
    int tile_count, tile_size;
    std::string name, source;
};

class MapParser
{
    public:
        inline static MapParser* get_instance()
        {return s_instance = (s_instance != nullptr)? s_instance : new MapParser();}

        bool load();
        void clean();

        inline GameMap* get_map(std::string id){return m_map[id];}

    private:
        bool parse(std::string id, std::string source);

        Tileset parse_tileset(TiXmlElement* xml_tileset);
        TileLayer* parse_tile_layer(TiXmlElement* xml_layer, TilesetList tile_set, int tile_size, int row_count, int col_count);

    private:
        MapParser();
        static MapParser* s_instance;

        std::map <std::string, GameMap*> m_map;
};

#endif */ // MAPPARSER_H
