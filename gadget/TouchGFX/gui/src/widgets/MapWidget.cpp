/*
 * MapWidget.cpp
 *
 *  Created on: Jul 24, 2023
 *      Author: ewoud
 */

#include "gui/widgets/MapWidget.hpp"
#include <touchgfx/widgets/canvas/Canvas.hpp>
#include <touchgfx/hal/HAL.hpp>

MapWidget::MapWidget() : CanvasWidget(), projection(nullptr)
{
}

inline TouchGFXMapPainter const *MapWidget::getPainter() const
{
    return (TouchGFXMapPainter const *)&_painter;
}

void MapWidget::setup(StyleConfigRef styleConfig, MapDataRef mapData, Projection *mapProjection)
{
    data = mapData;
    new (&_painter) TouchGFXMapPainter(styleConfig);
    projection = mapProjection;
}

bool MapWidget::drawCanvasWidget(const touchgfx::Rect &invalidatedArea) const
{
    // auto hal = touchgfx::HAL::getInstance();
    const MapParameter params;
    touchgfx::Canvas canvas(this, invalidatedArea);

    // hal->lockFrameBuffer();
    const_cast<TouchGFXMapPainter *>(this->getPainter())->DrawCanvas(canvas, invalidatedArea, *projection, params, *data);
    // hal->unlockFrameBuffer();

    return canvas.render();
}