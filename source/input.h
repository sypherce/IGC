#pragma once

#include <string>
#include "SDL.h"

namespace IGC { namespace Engine { namespace SDL { namespace Input { //xinput by default
enum GAMEPAD_STATUS_BUTTONS : uint16_t
{
	BUTTON_DPAD_UP			= 0x0001,
	BUTTON_DPAD_DOWN		= 0x0002,
	BUTTON_DPAD_LEFT		= 0x0004,
	BUTTON_DPAD_RIGHT		= 0x0008,
	BUTTON_START			= 0x0010,
	BUTTON_BACK				= 0x0020,
	BUTTON_LEFT_THUMB		= 0x0040,
	BUTTON_RIGHT_THUMB		= 0x0080,
	BUTTON_LEFT_SHOULDER	= 0x0100,
	BUTTON_RIGHT_SHOULDER	= 0x0200,
	BUTTON_GUIDE			= 0x0400,
	BUTTON_A				= 0x1000,
	BUTTON_B				= 0x2000,
	BUTTON_X				= 0x4000,
	BUTTON_Y				= 0x8000
};

//a data structure modeled after xinput
struct gamepad_status {
	uint16_t	buttons;//refer to enum GAMEPAD_STATUS_BUTTONS
	uint8_t		left_trigger;
	uint8_t		right_Trigger;
	int16_t		left_analog_x;
	int16_t		left_analog_y;
	int16_t		right_analog_x;
	int16_t		right_analog_y;
};
enum GAMEPAD_PLAYERS
{
	PLAYER_1 = 0,
	PLAYER_2,
	PLAYER_3,
	PLAYER_4,
	GAMEPAD_STATUS_MAX
};
extern gamepad_status g_gamepad_status[GAMEPAD_STATUS_MAX];

// Setup everything input related, load setting for default options, etc.
//
// Returns:
//	`Engine::VALUE_SUCCESS` or `Engine::VALUE_FAILURE`
extern int Init();
				
enum INPUT_UPDATE : int
{
	EVENT_PROCESSED,
	EVENT_UNPROCESSED
};
// Update everything input related
//
// Parameters:
//	`event` General event structure
//
// Returns:
//	`EVENT_PROCESSED` if `event.type` is handled,
//	`EVENT_UNPROCESSED` otherwise.
extern int Update(SDL_Event& event);

//TODO: rewrite description
//TODO: `gamepad` should be a enum of 1-4
// Set `button` in `gamepad.buttons` to a pressed state
//
// Parameters:
//	`gamepad` gamepad 1-4 to manipulate
//	`button` button to manipulate
extern void PressButton(GAMEPAD_PLAYERS gamepad, uint16_t button);

//TODO: rewrite description
//TODO: `gamepad` should be a enum of 1-4
// Set `button` in `gamepad.buttons` to a released state
//
// Parameters:
//	`gamepad` gamepad 1-4 to manipulate
//	`button` button to manipulate
extern void ReleaseButton(GAMEPAD_PLAYERS gamepad, uint16_t button);

// Check if a `button` is pressed on `gamepad`
//
// Parameters:
//	`gamepad` Which player to check. Refer to `enum GAMEPAD_PLAYERS`
//	`button` Which button to check. Refer to `enum GAMEPAD_STATUS_BUTTONS`
//
// Returns:
//	`true` if pressed, `false` if not
extern bool IsPressed(GAMEPAD_PLAYERS gamepad, uint16_t button);

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
}}}}//namespace IGC::Engine::SDL::Input
