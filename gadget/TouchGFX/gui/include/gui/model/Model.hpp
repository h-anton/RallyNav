#ifndef MODEL_HPP
#define MODEL_HPP
#define _USE_MATH_DEFINES

#include <osmscout/db/Database.h>
#include <osmscoutmap/MapService.h>

class ModelListener;

class Model
{
public:
    Model();

    void bind(ModelListener* listener)
    {
        modelListener = listener;
    }

    void tick();

    void updateData(osmscout::MapDataRef mapData, const osmscout::Projection& projection);

protected:
    ModelListener* modelListener;
private:
    uint8_t _mapDatabase[sizeof(osmscout::Database)];
    uint8_t _mapService[sizeof(osmscout::MapService)];
    uint8_t _styleConfig[sizeof(osmscout::StyleConfig)];
    std::list<osmscout::TileRef> tiles;
public:
    osmscout::DatabaseRef mapDatabase;
    osmscout::MapServiceRef mapService;
    osmscout::StyleConfigRef styleConfig;
};

#endif // MODEL_HPP
