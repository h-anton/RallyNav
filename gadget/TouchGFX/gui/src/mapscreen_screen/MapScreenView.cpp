#include <gui/mapscreen_screen/MapScreenView.hpp>

MapScreenView::MapScreenView()
{
	map.setWidth(this->getScreenWidth());
	map.setHeight(this->getScreenHeight());
	map.setXY(0, 0);
	add(map);
}

void MapScreenView::setupScreen()
{
    MapScreenViewBase::setupScreen();
}

void MapScreenView::tearDownScreen()
{
    MapScreenViewBase::tearDownScreen();
}
