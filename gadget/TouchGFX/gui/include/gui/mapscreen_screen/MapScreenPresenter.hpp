#ifndef MAPSCREENPRESENTER_HPP
#define MAPSCREENPRESENTER_HPP
#define _USE_MATH_DEFINES

#include <osmscout/projection/MercatorProjection.h>
#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>

using namespace touchgfx;

class MapScreenView;

class MapScreenPresenter : public touchgfx::Presenter, public ModelListener
{
public:
    MapScreenPresenter(MapScreenView& v);

    /**
     * The activate function is called automatically when this screen is "switched in"
     * (ie. made active). Initialization logic can be placed here.
     */
    virtual void activate();

    /**
     * The deactivate function is called automatically when this screen is "switched out"
     * (ie. made inactive). Teardown functionality can be placed here.
     */
    virtual void deactivate();

    virtual ~MapScreenPresenter() {}

private:
    MapScreenPresenter();

    MapScreenView& view;
    osmscout::MapDataRef mapData;
    osmscout::MercatorProjection projection;
};

#endif // MAPSCREENPRESENTER_HPP
