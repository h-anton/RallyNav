#ifndef APPLICATION_USER_GUI_WIDGETS_MAPWIDGET_HPP_
#define APPLICATION_USER_GUI_WIDGETS_MAPWIDGET_HPP_
#define _USE_MATH_DEFINES

#include <touchgfx/widgets/canvas/CanvasWidget.hpp>
#include <osmscout/db/Database.h>
#include <osmscoutmap/MapService.h>

#include "gui/widgets/OSMScoutGFXPainter.hpp"

class MapWidget : public touchgfx::CanvasWidget {
public:
	MapWidget();

	void setup(StyleConfigRef styleConfig, MapDataRef mapData, Projection* projection);
	inline TouchGFXMapPainter const* getPainter() const;

	virtual bool drawCanvasWidget(const touchgfx::Rect& invalidatedArea) const override;
private:
	MapDataRef data;
	Projection* projection;
	//We initialize this later, but the way TouchGFX works, we need to have it already allocated
	uint8_t _painter[sizeof(TouchGFXMapPainter)];
};

#endif /* APPLICATION_USER_GUI_WIDGETS_MAPWIDGET_HPP_ */
