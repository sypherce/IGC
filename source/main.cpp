#include <iostream>
#include "igc.h"
#include "input.h"
#include "animation.h"

using namespace IGC;
using namespace IGC::Engine;
using namespace IGC::Engine::SDL;
using namespace IGC::Engine::SDL::Video;

//this is a simple testing function
int SimpleScene()
{
	static x2D::Animation* constant_sprite{};

	if (constant_sprite == nullptr)
		constant_sprite = new x2D::Animation("..\\Data\\sample.png");
	const std::string TEXTURE_FILENAME = "..\\Data\\gba.png";
	SDL_Texture* texture{};

	int function_result{};
	//Load Texture from file
	function_result += Video::x2D::LoadTextureByFilename(texture, TEXTURE_FILENAME);

	//Draw stuff
	function_result += x2D::DrawTexture(texture, { 0, 0, x2D::FULL_TEXTURE_WIDTH, x2D::FULL_TEXTURE_HEIGHT });
	function_result += x2D::DrawTexture(texture, { 25, 25, 26, 26 });
	function_result += x2D::FillRect(
								{ 0xFF, 0x00, 0xFF, SDL_ALPHA_OPAQUE }, //color
								{ 0, 45, 46, 46 }						//rectangle
									);

	//Draw Message
	SDL_Texture *message = x2D::RenderText("Hello Simple Scene!", "..\\Data\\sample.ttf", { 0, 0, 0, SDL_ALPHA_OPAQUE }, 48);
	function_result += x2D::DrawTexture(message, { 0, 0, x2D::FULL_TEXTURE_WIDTH, x2D::FULL_TEXTURE_HEIGHT });
	SDL_DestroyTexture(message);

	//setup frames and animation status, status is static
	static int current_frame = 0;
	static int current_animation = 0;

	//this checks if any direction is currently pressed
	bool is_dpad_pressed =
		((Input::g_player1_gamepad_status.buttons & Input::DPAD_UP) +
			(Input::g_player1_gamepad_status.buttons & Input::DPAD_DOWN) +
			(Input::g_player1_gamepad_status.buttons & Input::DPAD_LEFT) +
			(Input::g_player1_gamepad_status.buttons & Input::DPAD_RIGHT));

	//change animation depending on dpad status
	if (Input::g_player1_gamepad_status.buttons & Input::DPAD_UP)
	{
		current_animation = 3;
	}
	if (Input::g_player1_gamepad_status.buttons & Input::DPAD_DOWN)
	{
		current_animation = 0;
	}
	if (Input::g_player1_gamepad_status.buttons & Input::DPAD_LEFT)
	{
		current_animation = 1;
	}
	if (Input::g_player1_gamepad_status.buttons & Input::DPAD_RIGHT)
	{
		current_animation = 2;
	}

	//draw sprite
	constant_sprite->Draw(15, 55, current_animation, current_frame);

	//if dpad is pressed we animate
	if (is_dpad_pressed)
		current_frame++;
	if (current_frame >= 4)
		current_frame = 0;

	//Clear Texture By Filename
	function_result += Video::x2D::UnloadTextureByFilename(TEXTURE_FILENAME);

	return function_result;
}

int main(int argc, char* argv[])
{
	//Initialize Engine
	int engine_status = IGC::Engine::Init();
	if(engine_status == IGC::Engine::RETURN_SUCCESS)
	{
		std::cout << "Engine loaded properly" << std::endl;
	}
	else // failure
	{
		std::cout << "Engine failed to load properly" << std::endl;
		getchar();

		return engine_status;
	}
	
	//this is just dummy code for now
	std::cout << "Hello World!" << std::endl;

	while(IGC::Engine::SDL::g_status == IGC::Engine::SDL::STATUS_RUNNING)
	{
		if (IGC::Engine::SDL::Video::Update() < IGC::Engine::SDL::DRAW_SUCCESS) {
			engine_status = IGC::Engine::RETURN_VIDEO_FAILURE;
			break;
		}
		if (SimpleScene() < IGC::Engine::SDL::DRAW_SUCCESS) {
			engine_status = IGC::Engine::RETURN_VIDEO_FAILURE;
			break;
		}
		IGC::Engine::Sleep(100);
		IGC::Engine::SDL::Update();
	}

	IGC::Engine::DeInit();

	return engine_status;
}
