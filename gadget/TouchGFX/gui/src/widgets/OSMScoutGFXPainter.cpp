#include <touchgfx/hal/HAL.hpp>
#include "gui/widgets/OSMScoutGFXPainter.hpp"

const touchgfx::colortype color = 0x964B00;

TouchGFXMapPainter::TouchGFXMapPainter(StyleConfigRef styleConfig) : MapPainter(styleConfig)
{
}

void TouchGFXMapPainter::DrawCanvas(
    touchgfx::Canvas &canvas,
    const touchgfx::Rect &invalidatedArea,
    const Projection &projection,
    const MapParameter &parameter,
    const MapData &data)
{
    this->canvas = &canvas;
    //TODO change projection based on invalidated
    this->Draw(projection, parameter, data);
}

void TouchGFXMapPainter::RegisterRegularLabel(
    const Projection &projection,
    const MapParameter &parameter,
    const std::vector<LabelData> &labels,
    const Vertex2D &position,
    double objectWidth)
{
}

void TouchGFXMapPainter::RegisterContourLabel(
    const Projection &projection,
    const MapParameter &parameter,
    const PathLabelData &label,
    const LabelPath &labelPath)
{
}

double TouchGFXMapPainter::GetFontHeight(const Projection &projection, const MapParameter &parameter, double fontSize)
{
    return 10.0;
}

bool TouchGFXMapPainter::HasIcon(
    const StyleConfig &styleConfig,
    const Projection &projection,
    const MapParameter &parameter,
    IconStyle &style)
{
    return false;
}

void TouchGFXMapPainter::DrawGround(const Projection &projection, const MapParameter &parameter, const FillStyle &style)
{
    auto box = projection.GetScreenBox();
    touchgfx::Rect rect(box.GetMinX(), box.GetMinY(), box.GetWidth(), box.GetHeight());
    touchgfx::HAL::lcd().fillRect(rect, color);
}

void TouchGFXMapPainter::DrawLabels(
    const Projection &projection,
    const MapParameter &parameter,
    const MapData &data)
{
}

void TouchGFXMapPainter::DrawSymbol(
    const Projection &projection,
    const MapParameter &parameter,
    const Symbol &symbol,
    const Vertex2D &screenPos,
    double scaleFactor)
{
}

void TouchGFXMapPainter::DrawIcon(
    const IconStyle *style,
    const Vertex2D &centerPos,
    double width, double height)
{
}

void TouchGFXMapPainter::DrawPath(
    const Projection &projection,
    const MapParameter &parameter,
    const osmscout::Color &color,
    double width,
    const std::vector<double> &dash,
    LineStyle::CapStyle startCap,
    LineStyle::CapStyle endCap,
    const CoordBufferRange &coordRange)
{
    double hWidth = width / 2.0;

    canvas->moveTo(coordRange.GetFirst().GetX() + hWidth, coordRange.GetFirst().GetY() + hWidth);
    for (size_t i = coordRange.GetStart()+1; i <=coordRange.GetEnd(); i++) {
        canvas->lineTo(coordRange.Get(i).GetX() + hWidth, coordRange.Get(i).GetY() + hWidth);
    }
    for (size_t i = coordRange.GetEnd(); i >= coordRange.GetStart(); i--) {
        canvas->lineTo(coordRange.Get(i).GetX() - hWidth, coordRange.Get(i).GetY() - hWidth);
    }
    canvas->lineTo(coordRange.GetFirst().GetX() + hWidth, coordRange.GetFirst().GetY() + hWidth);
}

void TouchGFXMapPainter::DrawContourSymbol(
    const Projection &projection,
    const MapParameter &parameter,
    const Symbol &symbol,
    const ContourSymbolData &data)
{
}

void TouchGFXMapPainter::DrawArea(
    const Projection &projection,
    const MapParameter &parameter,
    const AreaData &area)
{
}