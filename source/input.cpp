#include "SDL.h"
#include "igc.h"
#include "input.h"
#include <iostream>
#include <string>
#include <vector>


namespace IGC
{
	namespace Engine
	{
		namespace SDL
		{
			namespace Input
			{
				gamepad_status g_gamepad_status[GAMEPAD_STATUS_MAX]{};
				int Init()
				{
					return Engine::RETURN_SUCCESS;
				}

				int Update(SDL_Event& event)
				{
					switch (event.type)
					{
						//If a key was pressed
						case SDL_KEYDOWN:
						{
							switch (event.key.keysym.sym)
							{
							case SDLK_ESCAPE:
								PressButton(PLAYER_1, BUTTON_GUIDE);
								break;
							case SDLK_UP:
								PressButton(PLAYER_1, BUTTON_DPAD_UP);
								break;
							case SDLK_DOWN:
								PressButton(PLAYER_1, BUTTON_DPAD_DOWN);
								break;
							case SDLK_LEFT:
								PressButton(PLAYER_1, BUTTON_DPAD_LEFT);
								break;
							case SDLK_RIGHT:
								PressButton(PLAYER_1, BUTTON_DPAD_RIGHT);
								break;
							case SDLK_RETURN:
								PressButton(PLAYER_1, BUTTON_START);
								break;
							case SDLK_f:
								PressButton(PLAYER_1, BUTTON_B);
								break;
							case SDLK_d:
								PressButton(PLAYER_1, BUTTON_A);
								break;
							default://unhandled key press 
								break;
							}
							return Input::EVENT_PROCESSED;
						}

						//If a key was released
						case SDL_KEYUP:
						{
							switch (event.key.keysym.sym)
							{
							case SDLK_ESCAPE:
								ReleaseButton(PLAYER_1, BUTTON_GUIDE);
								break;
							case SDLK_UP:
								ReleaseButton(PLAYER_1, BUTTON_DPAD_UP);
								break;
							case SDLK_DOWN:
								ReleaseButton(PLAYER_1, BUTTON_DPAD_DOWN);
								break;
							case SDLK_LEFT:
								ReleaseButton(PLAYER_1, BUTTON_DPAD_LEFT);
								break;
							case SDLK_RIGHT:
								ReleaseButton(PLAYER_1, BUTTON_DPAD_RIGHT);
								break;
							case SDLK_RETURN:
								ReleaseButton(PLAYER_1, BUTTON_START);
								break;
							case SDLK_f:
								ReleaseButton(PLAYER_1, BUTTON_B);
								break;
							case SDLK_d:
								ReleaseButton(PLAYER_1, BUTTON_A);
								break;
							default://unhandled key press 
								break;
							}
							return Input::EVENT_PROCESSED;
						}
					}
					return Input::EVENT_UNPROCESSED;
				}
				void PressButton(GAMEPAD_PLAYERS gamepad, uint16_t button)
				{
					g_gamepad_status[gamepad].buttons |= button;
				}
				void ReleaseButton(GAMEPAD_PLAYERS gamepad, uint16_t button)
				{
					g_gamepad_status[gamepad].buttons &= ~button;
				}
				bool IsPressed(GAMEPAD_PLAYERS gamepad, uint16_t button)
				{
					return (g_gamepad_status[gamepad].buttons & button) == button;
				}
			}
		}
	}
}
