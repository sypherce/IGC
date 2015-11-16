#ifndef __INPUT_H__
#define __INPUT_H__

#include <string>
#include "SDL.h"

namespace IGC
{
	namespace Engine
	{
		namespace SDL
		{
			namespace Input //xinput by default
			{
				enum GAMEPAD : uint16_t
				{
					DPAD_UP			= 0x0001,
					DPAD_DOWN		= 0x0002,
					DPAD_LEFT		= 0x0004,
					DPAD_RIGHT		= 0x0008,
					START			= 0x0010,
					BACK			= 0x0020,
					LEFT_THUMB		= 0x0040,
					RIGHT_THUMB		= 0x0080,
					LEFT_SHOULDER	= 0x0100,
					RIGHT_SHOULDER	= 0x0200,
					A				= 0x1000,
					B				= 0x2000,
					X				= 0x4000,
					Y				= 0x8000
				};

				//a data structure modeled after xinput
				typedef struct gamepad_status {
					uint16_t	buttons;
					uint8_t		left_trigger;
					uint8_t		right_Trigger;
					int16_t		left_analog_x;
					int16_t		left_analog_y;
					int16_t		right_analog_x;
					int16_t		right_analog_y;
				};
				extern gamepad_status g_player1_gamepad_status;
				extern gamepad_status g_player2_gamepad_status;
				extern gamepad_status g_player3_gamepad_status;
				extern gamepad_status g_player4_gamepad_status;

				// Setup everything input related, load setting for default options, etc.
				//
				// Returns:
				//	Returns `Engine::RETURN_SUCCESS` or `Engine::RETURN_HALT`
				extern int Init();
				/*
				namespace Keyboard
				{
					
				}
				namespace Mouse
				{
					
				}
				namespace Touch
				{
					
				}
				namespace Gamepad
				{
					namespace Windows
					{
						namespace DInput
						{
							
						}
						namespace XInput
						{
							
						}
					}
					namespace Android_IOS
					{
						namespace Bluetooth
						{
							
						}
						namespace iCade
						{
							
						}
						namespace Keyboard
						{
							
						}
					}
				}
				*/
			}
		}
	}
}

#endif//__INPUT_H__
