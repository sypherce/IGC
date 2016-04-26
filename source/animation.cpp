#include <string>
#include "SDL.h"
#include "animation.h"

namespace IGC {namespace Engine {namespace SDL {namespace Video {namespace x2D {
const Uint8 DEFAULT_FRAME_COUNT = 4;
const Uint8 DEFAULT_ANIMATION_COUNT = 4;
Animation::Animation(std::string filename)
{
	m_filename = filename;
	m_layout = LAYOUT_TOP_BOTTOM_LEFT_RIGHT;
	if (LoadTextureByFilename(m_texture, m_filename) == VALUE_FAILURE)
	{
		printf("Failed to initialize texture\n");
		return;
	}

	SDL_QueryTexture(m_texture, NULL, NULL, &m_frame_dimensions.w, &m_frame_dimensions.h);
						
	m_frame_dimensions.w /= DEFAULT_FRAME_COUNT;
	m_frame_dimensions.h /= DEFAULT_ANIMATION_COUNT;

}
Animation::Animation(std::string filename, ANIMATION_LAYOUT layout, SDL_Rect frame_dimensions)
{
	m_filename = filename;
	m_layout = layout;
	m_frame_dimensions = frame_dimensions;
	if (LoadTextureByFilename(m_texture, m_filename) == VALUE_FAILURE)
	{
		printf("Failed to initialize texture\n");
	}
}

Animation::Animation(std::string filename, ANIMATION_LAYOUT layout, Sint8 animation_count, Sint8 frame_count)
{
	if (animation_count == 0)
		animation_count = DEFAULT_ANIMATION_COUNT;
	if (frame_count == 0)
		frame_count = DEFAULT_FRAME_COUNT;
	m_filename = filename;
	m_layout = layout;
	if (LoadTextureByFilename(m_texture, m_filename) == VALUE_FAILURE)
	{
		printf("Failed to initialize texture\n");
		return;
	}

	SDL_QueryTexture(m_texture, NULL, NULL, &m_frame_dimensions.w, &m_frame_dimensions.h);
						
	m_frame_dimensions.w /= frame_count;
	m_frame_dimensions.h /= animation_count;
}
Animation::~Animation()
{

}
int Animation::Draw(int x, int y, Uint8 animation, Uint8 frame)
	{
		SDL_Rect destination_rectangle = {
			x,
			y,
			m_frame_dimensions.w,
			m_frame_dimensions.h
		};

		SDL_Rect source_rectangle = {
			m_frame_dimensions.w * frame,
			m_frame_dimensions.h * animation,
			m_frame_dimensions.w,
			m_frame_dimensions.h
		};

		return DrawTexture(m_texture, source_rectangle, destination_rectangle);
	}
}}}}}//namespace IGC::Engine::SDL::Video::x2D
