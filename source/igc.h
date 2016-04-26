#pragma once

#include <string>
#include "SDL.h"

//Contains everything to do with IGC. Engine & the Editor
namespace IGC {namespace Editor {
extern int Init();
namespace WX {
extern int Init();
}
}
//Contains everything to do with Engine half of IGC
namespace Engine
{
// Values are adopted from SDL Documentation.
enum G_RETURN_VALUES: int
{
	VALUE_FAILURE = -1,	// Only use this to assign failure, not to check
	VALUE_SUCCESS = 0	// SDL Documentation specifys 0 as success, < 0 as failure
};

// Setup super low-level stuff. Anything that has
// to be setup before any other engine stuff. Video,
// Sound, Input is all later. We will be reading files
// here and figuring out what OS we are working with
// 
// Returns:
//	`Engine::VALUE_SUCCESS` or `Engine::VALUE_FAILURE`
extern int Init();
		
//Wait a specified number of milliseconds before returning.
void Sleep(unsigned int milliseconds);

// Shut everything down and check for errors.
extern void DeInit();
namespace SDL {
// g_status is considered read-only outside of the engine
extern int g_status;
enum G_STATUS : int
{
STATUS_OFF = 0,		// Nothing is initiated at all
STATUS_STARTING = 1,// We are setting up still
STATUS_RUNNING = 2,	// Everything is `running`
STATUS_EXITING = 3	// We are shutting down
};


// This will setup most of our engine. SDL is used for everything but
// scripting. However, running sub-SDL init functions must be done before
// using sub-functions.
//
// Returns:
//	`Engine::VALUE_SUCCESS` or `Engine::VALUE_FAILURE`
extern int Init();
// Clean up all SDL functions, including any lingering video, audio, or input.
extern void DeInit();

//Loads all media, audio files, graphics, etc. Return values may need changed
extern int LoadMedia();
//Updates input, events, etc, no drawing or audio, just logic
extern void Update();
namespace Video{ //focus on 2d
//The `GUI Window` object our program will be using
extern SDL_Window* g_window;

//The `Drawing Surface` contained by the `GUI Window`
extern SDL_Renderer* g_renderer;

//Width of Window/Drawing Area
extern unsigned int g_width;

//Height of Window/Drawing Area
extern unsigned int g_height;

// Setup everything graphic related, resolution,
// orientation, etc.
//
// Returns:
// 	`Engine::VALUE_SUCCESS` or `Engine::VALUE_FAILURE`
extern int Init();

// Clean up everything graphic related.
// Solely called by `SDL::DeInit`
//
// Returns:
//	`Engine::VALUE_SUCCESS` or `Engine::VALUE_FAILURE`
extern void DeInit();

// Draw everything on screen. Text, sprites, backgrounds, 3d or 2d.
// Note: does NOT update objects or coordinates.
//
//Returns:
//	`Engine::VALUE_SUCCESS` or `Engine::VALUE_FAILURE`
extern int Update();
namespace x2D {	
//TODO: Class description
class TextureContainer
{
private:
	unsigned int m_instance_counter;	//Amount of active instances
	std::string m_filename;				//Filename and ID
public:
	SDL_Texture* m_texture;				//Loaded Texture
	TextureContainer(std::string Filename);
	~TextureContainer();
	SDL_Texture* CompareFilename(std::string Filename);
};

//TODO: Function description
extern int LoadTextureByFilename(SDL_Texture*& texture, std::string filename);
//TODO: Function description
extern int UnloadTextureByFilename(std::string filename);

// Loads `filename` into a texture
//
// Returns:
//	A `SDL_Texture*` containing an image on success 
//	`nullptr` on failure
extern SDL_Texture* LoadTexture(std::string filename);

// Fills a rectangle with a solid color
//
// `color` An RGBA value. Example: opaque green {0x00, 0xFF, 0x00, SDL_ALPHA_OPAQUE}
// `destination_rectangle` Demensions of the rectangle. w, h are relative to x, y
extern int FillRect(SDL_Color color, SDL_Rect destination_rectangle);

// Renders a ttf `message`
//
// Parameters:
//	`message` The message to display
//	`font_filename` The font we want to render the text
//	`color` The color the text will be
//	`font_size` The size the font will be
//
// Returns:
//	A `SDL_Texture*` containing message on success 
//	or `nullptr` on failure
extern SDL_Texture* RenderText(const std::string &message, const std::string &font_filename, SDL_Color color, int font_size);

//Clears entire screen with `black`
extern int ClearScreen();

const int FULL_TEXTURE_WIDTH = 0;
const int FULL_TEXTURE_HEIGHT = 0;

//Draws an already loaded texture
extern int DrawTexture(SDL_Texture* texture, SDL_Rect destination_rectangle);
//Draws an already loaded texture
extern int DrawTexture(SDL_Texture* texture, SDL_Rect source_rectangle, SDL_Rect destination_rectangle);

//Sets color for other drawing functions
extern int SetDrawColor(SDL_Color color);

/*
namespace sprites {

}
namespace maps {

}
namespace images {

}
*/
}
/*
namespace x3D {
namespace objects {

}
namespace terrain {

}
namespace shaders {

}
}
*/
}
}
namespace Scripting {

// Function: Scripting Init
// 	This will setup our Lua environment and and external libraries and
// 	scripts needed.
//
// Parameters:
//	NULL - ...
//
// Returns:
//	`Engine::VALUE_SUCCESS` or `Engine::VALUE_FAILURE`
//
// See Also:
//	...
extern int Init();
namespace lua {

}
}
}
}//namespace IGC
