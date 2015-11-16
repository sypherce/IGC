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
				gamepad_status g_player1_gamepad_status{};
				gamepad_status g_player2_gamepad_status{};
				gamepad_status g_player3_gamepad_status{};
				gamepad_status g_player4_gamepad_status{};
				int Init()
				{
					return Engine::RETURN_SUCCESS;
				}
			}
		}
	}
}
