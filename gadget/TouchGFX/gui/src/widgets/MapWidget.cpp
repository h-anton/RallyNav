/*
 * MapWidget.cpp
 *
 *  Created on: Jul 24, 2023
 *      Author: ewoud
 */


#include "gui/widgets/MapWidget.hpp"
#include <touchgfx/hal/HAL.hpp>

void MapWidget::draw(const touchgfx::Rect& invalidatedArea) const
{
    auto hal = touchgfx::HAL::getInstance();
    const MapParameter params;
    const MapData myData = *data;
    const Projection &myProjection = projection;

    hal->lockFrameBuffer();
    const_cast<TouchGFXMapPainter*>(&this->painter)->Draw(myProjection, params, myData);
    hal->unlockFrameBuffer();
}

touchgfx::Rect MapWidget::getSolidRect() const
{
    return touchgfx::Rect(0, 0, getWidth(), getHeight());
}
