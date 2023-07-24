/*
 * MapWidget.cpp
 *
 *  Created on: Jul 24, 2023
 *      Author: ewoud
 */


#include "gui/widgets/MapWidget.hpp"

void MapWidget::draw(const touchgfx::Rect& invalidatedArea) const
{
}

touchgfx::Rect MapWidget::getSolidRect() const
{
    return touchgfx::Rect(0, 0, getWidth(), getHeight());
}
