#ifndef GAMEMAP_H
#define GAMEMAP_H

#include "Layers.h"
#include <vector>


class GameMap
{
    public:
        void render()
        {
            for(unsigned int i=0; i<m_map_layers.size(); i++)
            {
                m_map_layers[i]->render();
            }
        }

        void update()
        {
            for(unsigned int i=0; i<m_map_layers.size(); i++)
            {
                m_map_layers[i]->update();
            }
        }

        std::vector<Layers*> get_map_layers(){return m_map_layers;}

    private:
        friend class MapParser;
        std::vector<Layers*> m_map_layers;
};

#endif // GAMEMAP_H
