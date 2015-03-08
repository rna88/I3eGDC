#include <iostream>
#include <irrlicht.h>
#include <irrKlang.h>

using namespace std;
using namespace irr;
using namespace irrklang;

#pragma comment(lib, "Irrlicht.lib")
#pragma comment(lib, "IrrKlang.lib")


//f32 bally = 400;
//f32 ballx = 400;
//core::vector2d<f32>(ballx, bally);
core::vector2d<s32> ballPosition(0.0f, 0.0f);
core::vector2d<s32> ballDirection(1.0f,1.0f);


int main()
{
	cout << "hello world\n";

	IrrlichtDevice* device = createDevice(video::EDT_OPENGL,
											core::dimension2d<u32>(800,600),
											32,
											0,
											0,
											0,
											0);

	//
	irrklang::ISoundEngine* soundEngine = irrklang::createIrrKlangDevice();

	video::IVideoDriver* driver = device->getVideoDriver();
	scene::ISceneManager* sceneManager = device->getSceneManager();
	gui::IGUIEnvironment* guiENV = device->getGUIEnvironment();
	gui::IGUIFont* fpsFont = guiENV->getFont("bigfont.png");
	gui::IGUIFont* deltaTimeFont = guiENV->getFont("bigfont.png");
	//guiENV->addFont("bigfont.png",)
	double FPS = driver->getFPS();
	
	//soundEngine->play2D("/../../../irrlicht 1.8/media/IrrlichtTheme.ogg");
	ISound* ITheme = soundEngine->play2D("IrrlichtTheme.ogg", 0, 0, 0, ESM_AUTO_DETECT, 1);

	ISoundEffectControl* soundFX = ITheme->getSoundEffectControl();
	//ISound* ball = soundEngine->play2D("impact.wav", 1, 0, 0, ESM_AUTO_DETECT, 1);
	soundFX->enableEchoSoundEffect();
	//ISound* ball = soundEngine->play2D("impact.wav", 1, 0, 0, ESM_AUTO_DETECT, 1);

	video::ITexture* ball = driver->getTexture("fireball.bmp");
	//ball->getSize();



	// The time when the frame starts
	f32 now = device->getTimer()->getTime();
	f32 then = 0;
	f32 deltaTime = 0;
	f32 fpsFromDeltaTime = 0;

	while (device->run())
	{
		then = device->getTimer()->getTime();
		deltaTime = then - now;
		fpsFromDeltaTime = (1000.0f / (deltaTime));
		
		now = then;
		
	

		// physics code
		// ai code -> whatever
		driver->beginScene(1,1,video::SColor(255,100,100,100));

		//x = x + (speed*dt)*direction.X
		ballPosition.X += (0.2f * deltaTime)*ballDirection.X;
		if (ballPosition.X > 700 || ballPosition.X < 0) ballDirection.X *= -1;

		ballPosition.Y += (0.2f * deltaTime)*ballDirection.Y;
		if (ballPosition.Y > 500 || ballPosition.Y < 0) ballDirection.Y *= -1;

		driver->draw2DImage(ball, ballPosition);
		fpsFont->draw((core::stringw)(driver->getFPS()), core::rect<s32>(10, 10, 100, 100), video::SColor(255, 30, 30, 255));
		deltaTimeFont->draw((core::stringw)(fpsFromDeltaTime), core::rect<s32>(10, 40, 100, 100), video::SColor(255, 255, 30, 30));


		driver->endScene();
	
		device->setWindowCaption(L"First Example");
	}
	return 0;
}