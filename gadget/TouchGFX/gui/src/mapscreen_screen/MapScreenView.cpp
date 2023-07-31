#include <gui/mapscreen_screen/MapScreenView.hpp>

MapScreenView::MapScreenView()
{
	mapWidget.setWidth(this->getScreenWidth());
	mapWidget.setHeight(this->getScreenHeight());
	mapWidget.setXY(0, 0);
	add(mapWidget);
}

void MapScreenView::setupMap(StyleConfigRef styleConfig, MapDataRef mapData, Projection* mapProjection)
{
	mapWidget.setup(styleConfig, mapData, mapProjection);
}

void MapScreenView::setupScreen()
{
	MapScreenViewBase::setupScreen();
}

void MapScreenView::tearDownScreen()
{
	MapScreenViewBase::tearDownScreen();
}
