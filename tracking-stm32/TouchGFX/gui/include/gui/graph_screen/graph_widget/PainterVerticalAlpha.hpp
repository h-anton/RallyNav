#ifndef PAINTERVERTICALALPHA_HPP
#define PAINTERVERTICALALPHA_HPP

#include <touchgfx/hal/Types.hpp>
#include <stdint.h>
#if !defined(USE_BPP) || USE_BPP==16
#include <touchgfx/widgets/canvas/AbstractPainterRGB565.hpp>
#include <platform/driver/lcd/LCD16bpp.hpp>
#elif USE_BPP == 24
#include <touchgfx/widgets/canvas/AbstractPainterRGB888.hpp>
#elif defined(LCD8BPP_ABGR2222)
#include <touchgfx/widgets/canvas/AbstractPainterABGR2222.hpp>
#elif defined(LCD8BPP_RGBA2222)
#include <touchgfx/widgets/canvas/AbstractPainterRGBA2222.hpp>
#elif defined(LCD8BPP_BGRA2222)
#include <touchgfx/widgets/canvas/AbstractPainterBGRA2222.hpp>
#elif defined(LCD8BPP_ARGB2222) || USE_BPP==8
#include <touchgfx/widgets/canvas/AbstractPainterARGB2222.hpp>
#elif USE_BPP==4
#include <touchgfx/widgets/canvas/AbstractPainterGRAY4.hpp>
#include <platform/driver/lcd/LCD4bpp.hpp>
#elif USE_BPP==2
#include <touchgfx/widgets/canvas/AbstractPainterGRAY2.hpp>
#include <platform/driver/lcd/LCD2bpp.hpp>
#else
#error Unknown USE_BPP
#endif

using namespace touchgfx;

/**
 * @class PainterVerticalAlpha PainterVerticalAlpha.hpp
 *
 * @brief A Painter that will paint using a fading color.
 *
 *        PainterVerticalAlpha will paint using the given color at y coordinate 0 fading
 *        the color to invisible at the given y coordinate.
 *
 * @see AbstractPainter
 */
class PainterVerticalAlpha :
#if !defined(USE_BPP) || USE_BPP==16
    public AbstractPainterRGB565
#elif USE_BPP==24
    public AbstractPainterRGB888
#elif defined(LCD8BPP_ABGR2222)
    public AbstractPainterABGR2222
#elif defined(LCD8BPP_RGBA2222)
    public AbstractPainterRGBA2222
#elif defined(LCD8BPP_BGRA2222)
    public AbstractPainterBGRA2222
#elif defined(LCD8BPP_ARGB2222) || USE_BPP==8
    public AbstractPainterARGB2222
#elif USE_BPP==4
    public AbstractPainterGRAY4
#elif USE_BPP==2
    public AbstractPainterGRAY2
#else
#error Unknown USE_BPP
#endif
{
public:

    /**
     * @fn PainterVerticalAlpha::PainterVerticalAlpha(colortype color = 0, int alpha0atY = 100);
     *
     * @brief Constructor.
     *
     *        Constructor.
     *
     * @param color     The color.
     * @param alpha0atY The y coordinate where alpha has faded to 0.
     */
    PainterVerticalAlpha(colortype color = 0, int alpha0atY = 100);

    /**
     * @fn void PainterVerticalAlpha::setColor(colortype color, int alphaZeroAt);
     *
     * @brief Sets color and alpha to use when drawing the CanvasWidget.
     *
     *        Sets color and alpha to use when drawing the CanvasWidget.
     *
     * @param color       The color.
     * @param alphaZeroAt The y coordinate where alpha has faded to 0.
     */
    void setColor(colortype color, int alphaZeroAt);

    virtual void paint(uint8_t* destination, int16_t offset, int16_t widgetX, int16_t widgetY, int16_t count, uint8_t alpha) const;

protected:
#if USE_BPP == 4 || USE_BPP == 2
    uint8_t painterGray; ///< The gray color
#else
    uint8_t painterRed;   ///< The red part of the color
    uint8_t painterGreen; ///< The green part of the color
    uint8_t painterBlue;  ///< The blue part of the color
#endif

    uint8_t painterAlpha; ///< Current alpha for the scan line
    int alpha0atY;        ///< The Y coordinate where alpha has faded to 0
};                        // class PainterVerticalAlpha

#endif /* PAINTERVERTICALALPHA_HPP */
