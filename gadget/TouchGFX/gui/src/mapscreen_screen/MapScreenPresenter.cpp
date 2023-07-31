#include <gui/mapscreen_screen/MapScreenView.hpp>
#include <gui/mapscreen_screen/MapScreenPresenter.hpp>

MapScreenPresenter::MapScreenPresenter(MapScreenView& v)
    : view(v), mapData(new osmscout::MapData())
{

}

void MapScreenPresenter::activate()
{
    osmscout::Magnification magnification;
    magnification.SetLevel(Magnification::magClose);
    projection.Set(osmscout::GeoCoord(50.99625895810891, 4.25410786064287), magnification, view.getScreenWidth(), view.getScreenHeight());
    model->updateData(mapData, projection);

    view.setupMap(model->styleConfig, mapData, &projection);
}

void MapScreenPresenter::deactivate()
{

}
