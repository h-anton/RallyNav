#ifndef WIDGETS_OSMSCOUT_GFX_PAINTER_HPP_
#define WIDGETS_OSMSCOUT_GFX_PAINTER_HPP_
#define _USE_MATH_DEFINES

#include <osmscoutmap/MapPainter.h>
#include <touchgfx/hal/HAL.hpp>
#include <touchgfx/widgets/canvas/Canvas.hpp>


using namespace osmscout;

class TouchGFXMapPainter : public osmscout::MapPainter {
    touchgfx::Canvas *canvas;
public:
    explicit TouchGFXMapPainter(StyleConfigRef styleConfig);

    void DrawCanvas(touchgfx::Canvas& canvas,
                    const touchgfx::Rect& invalidatedArea,
                    const Projection& projection,
                    const MapParameter& parameter,
                    const MapData& data);

protected:
    void RegisterRegularLabel(const Projection& projection,
                              const MapParameter& parameter,
                              const std::vector<LabelData>& labels,
                              const Vertex2D& position,
                              double objectWidth) override;

    void RegisterContourLabel(const Projection& projection,
                              const MapParameter& parameter,
                              const PathLabelData& label,
                              const LabelPath& labelPath) override;
    
    bool HasIcon(const StyleConfig& styleConfig,
                 const Projection& projection,
                 const MapParameter& parameter,
                 IconStyle& style) override;

    double GetFontHeight(const Projection& projection,
                       const MapParameter& parameter,
                       double fontSize) override;

    void DrawGround(const Projection& projection,
                    const MapParameter& parameter,
                    const FillStyle& style) override;

    void DrawLabels(const Projection& projection,
                    const MapParameter& parameter,
                    const MapData& data) override;

    void DrawSymbol(const Projection& projection,
                    const MapParameter& parameter,
                    const Symbol& symbol,
                    const Vertex2D& screenPos,
                    double scaleFactor) override;

    void DrawIcon(const IconStyle* style,
                  const Vertex2D& centerPos,
                  double width, double height) override;

    void DrawPath(const Projection& projection,
                  const MapParameter& parameter,
                  const osmscout::Color& color,
                  double width,
                  const std::vector<double>& dash,
                  LineStyle::CapStyle startCap,
                  LineStyle::CapStyle endCap,
                  const CoordBufferRange& coordRange) override;

    void DrawContourSymbol(const Projection& projection,
                           const MapParameter& parameter,
                           const Symbol& symbol,
                           const ContourSymbolData& data) override;

    void DrawArea(const Projection& projection,
                  const MapParameter& parameter,
                  const AreaData& area) override;
};


#endif /* WIDGETS_OSMSCOUT_GFX_PAINTER_HPP_ */
