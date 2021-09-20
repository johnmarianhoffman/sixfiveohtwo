#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"

#include <processor.h>

// Override base class with your custom functionality
class Visual6502 : public olc::PixelGameEngine
{
public:
	Visual6502()
	{
		// Name your application
		sAppName = "Visual6502";
	}

public:
	bool OnUserCreate() override
	{
		// Called once at the start, so create things here
		return true;
	}

	bool OnUserUpdate(float fElapsedTime) override
	{
		// Called once per frame, draws random coloured pixels
		for (int x = 0; x < ScreenWidth(); x++)
			for (int y = 0; y < ScreenHeight(); y++)
				Draw(x, y, olc::Pixel(rand() % 256, rand() % 256, rand() % 256));
		return true;
	}
};

int main()
{
	Visual6502 process;
	if (process.Construct(256, 240, 2, 2))
		process.Start();
	return 0;
}