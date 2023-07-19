#include <gui/graph_screen/graph_widget/PainterVerticalAlpha.hpp>
#include <touchgfx/Color.hpp>

using namespace touchgfx;

PainterVerticalAlpha::PainterVerticalAlpha(colortype color /*= 0*/, int alpha0atY /*= 100*/)
{
    setColor(color, alpha0atY);
}

void PainterVerticalAlpha::setColor(colortype color, int alphaZeroAt)
{
#if USE_BPP==4
    painterGray = LCD4bpp::getNativeColor(color);
#elif USE_BPP==2
    painterGray = LCD2bpp::getNativeColor(color);
#else
    painterRed = Color::getRed(color);
    painterGreen = Color::getGreen(color);
    painterBlue = Color::getBlue(color);
#endif
    alpha0atY = alphaZeroAt;
}

void PainterVerticalAlpha::paint(uint8_t* destination, int16_t offset, int16_t widgetX, int16_t widgetY, int16_t count, uint8_t alpha) const
{
    framebufferToDisplay(widgetX, widgetY);
    const uint8_t combinedAlpha = widgetY < 0 ? alpha : (widgetY >= alpha0atY ? 0 : LCD::div255(alpha * (255 - (widgetY * 255 / alpha0atY))));
    const uint8_t inverseAlpha = 255 - combinedAlpha;
#if !defined(USE_BPP) || USE_BPP==16
    uint16_t* RESTRICT framebuffer = reinterpret_cast<uint16_t*>(destination) + offset;
    const uint16_t* const lineEnd = framebuffer + count;
    do
    {
#define fastrand(g_seed) ((214013 * (uint32_t)(g_seed) + 2531011) >> 16)
        const uint8_t rand = fastrand((widgetX + *framebuffer) * (widgetY + *framebuffer));
        widgetX++;

        const uint8_t p_red = (*framebuffer & RMASK) >> 8;
        const uint8_t p_green = (*framebuffer & GMASK) >> 3;
        const uint8_t p_blue = (*framebuffer & BMASK) << 3;

        uint8_t pixelRed = LCD::div255(painterRed * combinedAlpha + p_red * inverseAlpha);
        uint8_t pixelGreen = LCD::div255(painterGreen * combinedAlpha + p_green * inverseAlpha);
        uint8_t pixelBlue = LCD::div255(painterBlue * combinedAlpha + p_blue * inverseAlpha);

        if (pixelRed < 0xF8)
        {
            pixelRed += (rand >> 5); // Add bit 7-5 of rand to red to get rounding
        }
        if (pixelGreen < 0xFC)
        {
            pixelGreen += (rand >> 3) & 0x3; // Add bit 4-3 of rand to green to get rounding
        }
        if (pixelBlue < 0xF8)
        {
            pixelBlue += (rand) & 0x7; // Add bit 2-0 of rand to blue to get rounding
        }
        *framebuffer = LCD16bpp::getNativeColorFromRGB(pixelRed, pixelGreen, pixelBlue);
    } while (++framebuffer < lineEnd);
#elif USE_BPP==24
    uint8_t* RESTRICT framebuffer = destination + offset * 3;
    const uint8_t* const lineEnd = framebuffer + count * 3;
    do
    {
        *framebuffer = LCD::div255(painterBlue * combinedAlpha + *framebuffer * inverseAlpha);
        framebuffer++;
        *framebuffer = LCD::div255(painterGreen * combinedAlpha + *framebuffer * inverseAlpha);
        framebuffer++;
        *framebuffer = LCD::div255(painterRed * combinedAlpha + *framebuffer * inverseAlpha);
        framebuffer++;
    } while (framebuffer < lineEnd);
#elif defined(LCD8BPP_ABGR2222) || defined(LCD8BPP_RGBA2222) || defined(LCD8BPP_BGRA2222) || defined(LCD8BPP_ARGB2222) || USE_BPP==8
    uint8_t* RESTRICT framebuffer = destination + offset;
    const uint8_t* const lineEnd = framebuffer + count;
    do
    {
#define fastrand(g_seed) ((g_seed * 1103515245U + 12345U) & 0x7fffffffU)
        const uint8_t rand = fastrand((widgetX + *framebuffer) * (widgetY + *framebuffer));
        widgetX++;

#if defined(LCD8BPP_ABGR2222)
        const uint8_t p_red = LCD8bpp_ABGR2222::getRedFromNativeColor(*framebuffer);
        const uint8_t p_green = LCD8bpp_ABGR2222::getGreenFromNativeColor(*framebuffer);
        const uint8_t p_blue = LCD8bpp_ABGR2222::getBlueFromNativeColor(*framebuffer);
#elif defined(LCD8BPP_RGBA2222)
        const uint8_t p_red = LCD8bpp_RGBA2222::getRedFromNativeColor(*framebuffer);
        const uint8_t p_green = LCD8bpp_RGBA2222::getGreenFromNativeColor(*framebuffer);
        const uint8_t p_blue = LCD8bpp_RGBA2222::getBlueFromNativeColor(*framebuffer);
#elif defined(LCD8BPP_BGRA2222)
        const uint8_t p_red = LCD8bpp_BGRA2222::getRedFromNativeColor(*framebuffer);
        const uint8_t p_green = LCD8bpp_BGRA2222::getGreenFromNativeColor(*framebuffer);
        const uint8_t p_blue = LCD8bpp_BGRA2222::getBlueFromNativeColor(*framebuffer);
#else // defined(LCD8BPP_ARGB2222) || USE_BPP == 8
        const uint8_t p_red = LCD8bpp_ARGB2222::getRedFromNativeColor(*framebuffer);
        const uint8_t p_green = LCD8bpp_ARGB2222::getGreenFromNativeColor(*framebuffer);
        const uint8_t p_blue = LCD8bpp_ARGB2222::getBlueFromNativeColor(*framebuffer);
#endif
        uint8_t pixelRed = LCD::div255(painterRed * combinedAlpha + p_red * inverseAlpha);
        uint8_t pixelGreen = LCD::div255(painterGreen * combinedAlpha + p_green * inverseAlpha);
        uint8_t pixelBlue = LCD::div255(painterBlue * combinedAlpha + p_blue * inverseAlpha);

        if (pixelRed < 0xC0)
        {
            pixelRed += (rand >> 0) & 0x3F;
        }
        if (pixelGreen < 0xC0)
        {
            pixelGreen += (rand >> 1) & 0x3F;
        }
        if (pixelBlue < 0xC0)
        {
            pixelBlue += (rand >> 2) & 0x3F;
        }
#if defined(LCD8BPP_ABGR2222)
        *framebuffer = LCD8bpp_ABGR2222::getNativeColorFromRGB(pixelRed, pixelGreen, pixelBlue);
#elif defined(LCD8BPP_RGBA2222)
        *framebuffer = LCD8bpp_RGBA2222::getNativeColorFromRGB(pixelRed, pixelGreen, pixelBlue);
#elif defined(LCD8BPP_BGRA2222)
        *framebuffer = LCD8bpp_BGRA2222::getNativeColorFromRGB(pixelRed, pixelGreen, pixelBlue);
#else // defined(LCD8BPP_ARGB2222) || USE_BPP == 8
        *framebuffer = LCD8bpp_ARGB2222::getNativeColorFromRGB(pixelRed, pixelGreen, pixelBlue);
#endif
    } while (++framebuffer < lineEnd);
#elif USE_BPP==4
    do
    {
        const uint8_t framebufferGray = LCD4bpp::getPixel(destination, offset) * 0x11;
#define fastrand(g_seed) ((g_seed * 1103515245U + 12345U) & 0x7fffffffU)
        const uint8_t rand = fastrand((widgetX + framebufferGray) * (widgetY + framebufferGray));
        widgetX++;
        uint8_t pixelGray = LCD::div255(painterGray * combinedAlpha + framebufferGray * inverseAlpha);
        if (pixelGray < 0xF0)
        {
            pixelGray += rand & 0x0F;
        }
        LCD4bpp::setPixel(destination, offset, pixelGray >> 4);
        offset++;
    } while (--count != 0);
#elif USE_BPP==2
    do
    {
        const uint8_t framebufferGray = LCD2bpp::getPixel(destination, offset) * 0x55;
#define fastrand(g_seed) ((g_seed * 1103515245U + 12345U) & 0x7fffffffU)
        const uint8_t rand = fastrand((widgetX + framebufferGray) * (widgetY + framebufferGray));
        widgetX++;
        uint8_t pixelGray = LCD::div255(painterGray * combinedAlpha + framebufferGray * inverseAlpha);
        if (pixelGray < 0xC0)
        {
            pixelGray += rand & 0x3F;
        }
        LCD2bpp::setPixel(destination, offset, pixelGray >> 6);
        offset++;
    } while (--count != 0);
#else
#error Unknown USE_BPP
#endif
}
