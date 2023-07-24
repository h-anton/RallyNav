/*********************************************************************************/
/********** THIS FILE IS GENERATED BY TOUCHGFX DESIGNER, DO NOT MODIFY ***********/
/*********************************************************************************/
#include <simulator/mainBase.hpp>
#include <platform/hal/simulator/sdl2/HALSDL2.hpp>
#include <common/TouchGFXInit.hpp>
#include <platform/driver/lcd/LCD24bpp.hpp>
#include <touchgfx/widgets/canvas/CWRVectorRenderer.hpp>
#include <touchgfx/widgets/canvas/PainterRGB888.hpp>
#include <touchgfx/canvas_widget_renderer/CanvasWidgetRenderer.hpp>
#include <string.h>

#ifdef __GNUC__
#define fopen_s(pFile, filename, mode) (((*(pFile)) = fopen((filename), (mode))) == NULL)
#endif
touchgfx::LCD24bpp lcd;

namespace touchgfx
{
    VectorRenderer* VectorRenderer::getInstance()
    {
        static CWRVectorRendererRGB888 renderer;
        return &renderer;
    }
}

void setupSimulator(int argc, char** argv, touchgfx::HAL& hal)
{
    // Simulate hardware running at 60Hz generating a vsync every 16.6667 ms
    static_cast<touchgfx::HALSDL2&>(hal).setVsyncInterval(16.6667f);
    static_cast<touchgfx::HALSDL2&>(hal).setWindowTitle("gadget");

    // Initialize SDL
    bool sdl_init_result = static_cast<touchgfx::HALSDL2&>(hal).sdl_init(argc, argv);
    assert(sdl_init_result && "Error during SDL initialization");
}

touchgfx::LCD& setupLCD()
{
    return lcd;
}