#include <gui/model/Model.hpp>
#include <gui/model/ModelListener.hpp>


Model::Model() : modelListener(0),
                 mapDatabase((osmscout::Database *) (&_mapDatabase)),
                 mapService((osmscout::MapService *) (&_mapService)),
                 styleConfig((osmscout::StyleConfig *) (&_styleConfig))
{
    new (&_mapDatabase) osmscout::Database(osmscout::DatabaseParameter());
    mapDatabase->Open("../../simulator/map/out"); // We are running at build/bin if simulator

    new (&_mapService) osmscout::MapService(mapDatabase);

    new (&_styleConfig) osmscout::StyleConfig(mapDatabase->GetTypeConfig());
    //styleConfig->Load("../../simulator/map/standard.oss");
}

void Model::updateData(osmscout::MapDataRef data, const osmscout::Projection &projection)
{
    osmscout::AreaSearchParameter searchParameter;
    searchParameter.SetUseLowZoomOptimization(true);

    data->ClearDBData();

    mapService->LookupTiles(projection, tiles);
    mapService->LoadMissingTileData(searchParameter, *styleConfig, tiles);
    mapService->AddTileDataToMapData(tiles, *data);
    mapService->GetGroundTiles(projection, data->groundTiles);
}

void Model::tick()
{
}
