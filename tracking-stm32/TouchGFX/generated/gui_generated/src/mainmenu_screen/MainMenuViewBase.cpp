/*********************************************************************************/
/********** THIS FILE IS GENERATED BY TOUCHGFX DESIGNER, DO NOT MODIFY ***********/
/*********************************************************************************/
#include <gui_generated/mainmenu_screen/MainMenuViewBase.hpp>
#include <touchgfx/Color.hpp>
#include <images/BitmapDatabase.hpp>

MainMenuViewBase::MainMenuViewBase() :
    buttonCallback(this, &MainMenuViewBase::buttonCallbackHandler)
{
    __background.setPosition(0, 0, 32, 32);
    __background.setColor(touchgfx::Color::getColorFromRGB(0, 0, 0));
    add(__background);

    backgroundLeft.setXY(0, 0);
    backgroundLeft.setBitmap(touchgfx::Bitmap(BITMAP_MENU_STAGE_STRETCH_LEFT_SIDE_ID));
    add(backgroundLeft);

    backgroundRight.setXY(430, 0);
    backgroundRight.setBitmap(touchgfx::Bitmap(BITMAP_MENU_STAGE_STRETCH_RIGHT_SIDE_ID));
    add(backgroundRight);

    demoScreensContainer00.setPosition(0, 0, 480, 272);
    demoScreenBackground00.setXY(0, 0);
    demoScreenBackground00.setBitmap(touchgfx::Bitmap(BITMAP_MENU_DEMO_SCREEN_02_ID));
    demoScreensContainer00.add(demoScreenBackground00);

    demoScreenButton00.setXY(318, 137);
    demoScreenButton00.setBitmaps(touchgfx::Bitmap(BITMAP_DEMO_BUTTON_02_03_ID), touchgfx::Bitmap(BITMAP_DEMO_BUTTON_02_03_PRESSED_ID));
    demoScreenButton00.setAction(buttonCallback);
    demoScreensContainer00.add(demoScreenButton00);

    add(demoScreensContainer00);

    demoScreensContainer01.setPosition(0, 0, 480, 272);
    demoScreenBackground01.setXY(0, 0);
    demoScreenBackground01.setBitmap(touchgfx::Bitmap(BITMAP_MENU_DEMO_SCREEN_03_ID));
    demoScreensContainer01.add(demoScreenBackground01);

    demoScreenButton01.setXY(318, 137);
    demoScreenButton01.setBitmaps(touchgfx::Bitmap(BITMAP_DEMO_BUTTON_02_03_ID), touchgfx::Bitmap(BITMAP_DEMO_BUTTON_02_03_PRESSED_ID));
    demoScreenButton01.setAction(buttonCallback);
    demoScreensContainer01.add(demoScreenButton01);

    add(demoScreensContainer01);

    demoScreensContainer02.setPosition(0, 0, 480, 272);
    demoScreenBackground02.setXY(0, 0);
    demoScreenBackground02.setBitmap(touchgfx::Bitmap(BITMAP_MENU_DEMO_SCREEN_04_ID));
    demoScreensContainer02.add(demoScreenBackground02);

    demoScreenButton02.setXY(318, 137);
    demoScreenButton02.setBitmaps(touchgfx::Bitmap(BITMAP_DEMO_BUTTON_04_ID), touchgfx::Bitmap(BITMAP_DEMO_BUTTON_04_PRESSED_ID));
    demoScreenButton02.setAction(buttonCallback);
    demoScreensContainer02.add(demoScreenButton02);

    add(demoScreensContainer02);

    demoScreensContainer03.setPosition(0, 0, 480, 272);
    demoScreenBackground03.setXY(0, 0);
    demoScreenBackground03.setBitmap(touchgfx::Bitmap(BITMAP_MENU_DEMO_SCREEN_05_ID));
    demoScreensContainer03.add(demoScreenBackground03);

    demoScreenButton03.setXY(318, 137);
    demoScreenButton03.setBitmaps(touchgfx::Bitmap(BITMAP_DEMO_BUTTON_05_06_ID), touchgfx::Bitmap(BITMAP_DEMO_BUTTON_05_06_PRESSED_ID));
    demoScreenButton03.setAction(buttonCallback);
    demoScreensContainer03.add(demoScreenButton03);

    add(demoScreensContainer03);

    mcuLoad.setXY(370, 10);
    add(mcuLoad);
}

MainMenuViewBase::~MainMenuViewBase()
{

}

void MainMenuViewBase::setupScreen()
{
    mcuLoad.initialize();
}

void MainMenuViewBase::buttonCallbackHandler(const touchgfx::AbstractButton& src)
{
    if (&src == &demoScreenButton00)
    {
        //demoScreenButton00Clicked
        //When demoScreenButton00 clicked change screen to CustomControls
        //Go to CustomControls with screen transition towards South
        application().gotoCustomControlsScreenSlideTransitionSouth();
    }
    if (&src == &demoScreenButton01)
    {
        //demoScreenButton01Clicked
        //When demoScreenButton01 clicked change screen to EasingEquation
        //Go to EasingEquation with screen transition towards South
        application().gotoEasingEquationScreenSlideTransitionSouth();
    }
    if (&src == &demoScreenButton02)
    {
        //demoScreenButton02Clicked
        //When demoScreenButton02 clicked change screen to ProductPresenter
        //Go to ProductPresenter with screen transition towards South
        application().gotoProductPresenterScreenSlideTransitionSouth();
    }
    if (&src == &demoScreenButton03)
    {
        //demoScreenButton03Clicked
        //When demoScreenButton03 clicked change screen to Graph
        //Go to Graph with screen transition towards South
        application().gotoGraphScreenSlideTransitionSouth();
    }
}