#ifndef MAPSCREENVIEW_HPP
#define MAPSCREENVIEW_HPP

#include <gui_generated/mapscreen_screen/MapScreenViewBase.hpp>
#include <gui/mapscreen_screen/MapScreenPresenter.hpp>
#include <gui/widgets/MapWidget.hpp>

class MapScreenView : public MapScreenViewBase
{
public:
    MapScreenView();
    virtual ~MapScreenView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
protected:
    MapWidget map;
};

#endif // MAPSCREENVIEW_HPP
