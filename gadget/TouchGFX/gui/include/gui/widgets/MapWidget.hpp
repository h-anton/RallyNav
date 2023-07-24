/*
 * map_widget.hpp
 *
 *  Created on: Jul 24, 2023
 *      Author: ewoud
 */

#ifndef APPLICATION_USER_GUI_WIDGETS_MAPWIDGET_HPP_
#define APPLICATION_USER_GUI_WIDGETS_MAPWIDGET_HPP_

#include <touchgfx/widgets/Widget.hpp>

class MapWidget : public touchgfx::Widget {
	virtual void draw(const touchgfx::Rect& invalidatedArea) const;
	virtual touchgfx::Rect getSolidRect() const;
};


#endif /* APPLICATION_USER_GUI_WIDGETS_MAPWIDGET_HPP_ */
