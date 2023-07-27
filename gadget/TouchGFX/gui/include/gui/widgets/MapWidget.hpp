#ifndef APPLICATION_USER_GUI_WIDGETS_MAPWIDGET_HPP_
#define APPLICATION_USER_GUI_WIDGETS_MAPWIDGET_HPP_
#define _USE_MATH_DEFINES

#include <touchgfx/widgets/Widget.hpp>
#include <osmscout/db/Database.h>
#include <osmscoutmap/MapService.h>
#include <osmscout/projection/MercatorProjection.h>

#include "gui/widgets/OSMScoutGFXPainter.hpp"

class MapWidget : public touchgfx::Widget {
public:
	MapWidget() : Widget(), data(nullptr) {}

	virtual void draw(const touchgfx::Rect& invalidatedArea) const override;
	virtual touchgfx::Rect getSolidRect() const override;
private:
	osmscout::MapDataRef data;
	TouchGFXMapPainter painter;
	osmscout::MercatorProjection projection;
};

#endif /* APPLICATION_USER_GUI_WIDGETS_MAPWIDGET_HPP_ */
