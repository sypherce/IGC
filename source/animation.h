#pragma once

#include <string>
#include "SDL.h"
#include "igc.h"

namespace IGC {namespace Engine {namespace SDL {namespace Video {namespace x2D {
enum ANIMATION_LAYOUT {
	LAYOUT_HORIZONTLE,
	LAYOUT_VERTICAL,
	LAYOUT_TOP_BOTTOM_LEFT_RIGHT,
	LAYOUT_BOTTOM_TOP_LEFT_RIGHT,
	LAYOUT_TOP_BOTTOM_RIGHT_LEFT,
	LAYOUT_BOTTOM_TOP_RIGHT_LEFT
};
enum ANIMATION_TYPE {
	ANIMATION_SOUTH = 0,
	ANIMATION_WEST,
	ANIMATION_EAST,
	ANIMATION_NORTH
};

//defaults
//
//each animation is left to right, top to bottom
//each image has 4 animations
//each animation has 4 frame
//
//1 2 3 4
//a b c d
//6 7 8 9
//w x y z
//


//TODO: Class description
class Animation
{
private:
//	unsigned int m_instance_counter;	//Amount of active instances
	std::string m_filename;				//Filename and ID
	ANIMATION_LAYOUT m_layout;
	SDL_Rect m_frame_dimensions;
	SDL_Texture* m_texture;				//Loaded Texture
public:
	Animation(std::string filename);
	Animation(std::string filename, ANIMATION_LAYOUT layout, SDL_Rect frame_dimensions);
	Animation(std::string filename, ANIMATION_LAYOUT layout, Sint8 animation_count, Sint8 frame_count);
	~Animation();
	//TODO: Function description
	int Draw(int x, int y, Uint8 animation, Uint8 frame);
};
}}}}}//namespace IGC::Engine::SDL::Video::x2D
