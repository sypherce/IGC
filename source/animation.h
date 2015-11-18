#ifndef __ANIMATION_H__
#define __ANIMATION_H__

#include <string>
#include "SDL.h"
#include "igc.h"

namespace IGC
{
	namespace Engine
	{
		namespace SDL
		{
			namespace Video
			{
				namespace x2D
				{
					enum animation_layout {
						layout_horizontle,
						layout_vertical,
						layout_top_bottom_left_right,
						layout_bottom_top_left_right,
						layout_top_bottom_right_left,
						layout_bottom_top_right_left
					};
<<<<<<< HEAD
					enum animation_type {
						animation_south = 0,
						animation_west,
						animation_east,
						animation_north
					};
=======
>>>>>>> refs/remotes/origin/master

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
						animation_layout m_layout;
						SDL_Rect m_frame_dimensions;
						SDL_Texture* m_texture;				//Loaded Texture
					public:
						Animation(std::string filename);
						Animation(std::string filename, animation_layout layout, SDL_Rect frame_dimensions);
						Animation(std::string filename, animation_layout layout, Sint8 animation_count, Sint8 frame_count);
						~Animation();
						//TODO: Function description
						int Draw(int x, int y, Uint8 animation, Uint8 frame);
					};				
				}
			}
		}
	}
}

#endif//__ANIMATION_H__
