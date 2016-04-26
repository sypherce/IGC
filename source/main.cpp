#include <iostream>
#include "igc.h"
#include "input.h"
#include "audio.h"
#include "animation.h"

using namespace IGC;
using namespace IGC::Engine;
using namespace IGC::Engine::SDL;
using namespace IGC::Engine::SDL::Video;

//this is a simple testing function
int SimpleScene()
{
	int function_result{};

	//setup sprite, all the sprite stuff is static
	static x2D::Animation* s_sprite{};
	static int s_sprite_x = 15;
	static int s_sprite_y = 15;
	static int s_sprite_speed = 1;
	//setup frames and animation status
	static int s_current_frame = 0;
	static int s_current_animation = 0;
	//load animation if we haven't already
	if (s_sprite == nullptr)
		s_sprite = new x2D::Animation("Data\\sample.png");

	//setup picture
	const std::string TEXTURE_FILENAME = "Data\\sample2.png";
	SDL_Texture* texture{};
	//Load Texture from file
	function_result += Video::x2D::LoadTextureByFilename(texture, TEXTURE_FILENAME);

	//draw pictures
	function_result += x2D::DrawTexture(texture, { 0, 0, x2D::FULL_TEXTURE_WIDTH, x2D::FULL_TEXTURE_HEIGHT });
	function_result += x2D::DrawTexture(texture, { 25, 25, 26, 26 });

	//draw rectangle
	function_result += x2D::FillRect(
								{ 0xFF, 0x00, 0xFF, SDL_ALPHA_OPAQUE }, //color
								{ 0, 45, 46, 46 }						//rectangle
									);

	//Draw Message
	SDL_Texture *message = x2D::RenderText("Hello Simple Scene!", "Data\\sample.ttf", { 0, 0, 0, SDL_ALPHA_OPAQUE }, 48);
	function_result += x2D::DrawTexture(message, { 0, 0, x2D::FULL_TEXTURE_WIDTH, x2D::FULL_TEXTURE_HEIGHT });
	SDL_DestroyTexture(message);

	//change animation depending on dpad status, also move
	if (Input::IsPressed(Input::PLAYER_1, Input::BUTTON_DPAD_UP))
	{
		s_current_animation = x2D::ANIMATION_NORTH;
		s_sprite_y -= s_sprite_speed;
	}
	if (Input::IsPressed(Input::PLAYER_1, Input::BUTTON_DPAD_DOWN))
	{
		s_current_animation = x2D::ANIMATION_SOUTH;
		s_sprite_y += s_sprite_speed;
	}
	if (Input::IsPressed(Input::PLAYER_1, Input::BUTTON_DPAD_LEFT))
	{
		s_current_animation = x2D::ANIMATION_WEST;
		s_sprite_x -= s_sprite_speed;
	}
	if (Input::IsPressed(Input::PLAYER_1, Input::BUTTON_DPAD_RIGHT))
	{
		s_current_animation = x2D::ANIMATION_EAST;
		s_sprite_x += s_sprite_speed;
	}
	
	//play sound
	if (Input::IsPressed(Input::PLAYER_1, Input::BUTTON_A))
	{
		Audio::PlaySound("Data\\sample.wav");
	}
	//reset position
	if (Input::IsPressed(Input::PLAYER_1, Input::BUTTON_START))
	{
		s_current_animation = 0;
		s_sprite_x = s_sprite_y = 15;
	}

	//exit
	if (Input::IsPressed(Input::PLAYER_1, Input::BUTTON_GUIDE))
	{
		SDL::DeInit();
	}

	//draw sprite
	s_sprite->Draw(s_sprite_x, s_sprite_y, s_current_animation, s_current_frame);

	//this checks if any direction is currently pressed
	bool is_dpad_pressed =
		Input::IsPressed(Input::PLAYER_1, Input::BUTTON_DPAD_UP) ||
			Input::IsPressed(Input::PLAYER_1, Input::BUTTON_DPAD_DOWN) ||
			Input::IsPressed(Input::PLAYER_1, Input::BUTTON_DPAD_LEFT) ||
			Input::IsPressed(Input::PLAYER_1, Input::BUTTON_DPAD_RIGHT);

	//if dpad is pressed we animate
	if (is_dpad_pressed)
		s_current_frame++;
	if (s_current_frame >= 4)
		s_current_frame = 0;

	//Clear Texture By Filename, this isn't productive, it's for testing
	function_result += Video::x2D::UnloadTextureByFilename(TEXTURE_FILENAME);

	return function_result;
}

int main(int argc, char* argv[])
{
	//Initialize Engine
	int engine_status = IGC::Engine::Init();
	if(engine_status == IGC::Engine::VALUE_SUCCESS)
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
		if (IGC::Engine::SDL::Video::Update() < IGC::Engine::VALUE_SUCCESS) {
			engine_status = IGC::Engine::VALUE_FAILURE;
			break;
		}
		if (SimpleScene() < IGC::Engine::VALUE_SUCCESS) {
			engine_status = IGC::Engine::VALUE_FAILURE;
			break;
		}
		IGC::Engine::Sleep(100);
		IGC::Engine::SDL::Update();
	}

	IGC::Engine::DeInit();

	return engine_status;
}
