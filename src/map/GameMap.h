#ifndef GAMEMAP_H
#define GAMEMAP_H

#include "Layers.h"
#include <vector>


class GameMap
{
    public:
        void render()
        {
            for(unsigned int i=0; i<m_mapLayers.size(); i++)
            {
                m_mapLayers[i]->render();
            }
        }

        void update()
        {
            for(unsigned int i=0; i<m_mapLayers.size(); i++)
            {
                m_mapLayers[i]->update();
            }
        }

        std::vector<Layers*> GetMapLayers(){return m_mapLayers;}

    private:
        friend class MapParser;
        std::vector<Layers*> m_mapLayers;
};

#endif // GAMEMAP_H
