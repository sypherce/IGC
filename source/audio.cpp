#include <iostream>
#include <string>
#include <vector>
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include "SDL_mixer.h"
#include "igc.h"
#include "input.h"


namespace IGC
{
	namespace Engine
	{
		namespace SDL
		{
			namespace Audio
			{
				int Init()
				{
					//Initialize SDL_mixer
					if (Mix_Init(MIX_INIT_MP3) < Engine::VALUE_SUCCESS)
					{
						printf("SDL_mixer failed to initialize! Mix_GetError: %s\n", Mix_GetError());
						return Engine::VALUE_FAILURE;
					}
					//Open sound mixer
					if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096) < Engine::VALUE_SUCCESS)
					{
						printf("SDL_mixer failed to open sound mixer! Mix_GetError: %s\n", Mix_GetError());
						return Engine::VALUE_FAILURE;
					}
					return Engine::VALUE_SUCCESS;
				}
				int PlaySound(std::string filename)
				{
					//this is temporary. static for the time being too.
					static Mix_Chunk *audio_chunk{};
					if (audio_chunk == nullptr)//we haven't loaded YET!
					{
						audio_chunk = Mix_LoadWAV(filename.c_str());
					}
					if (audio_chunk == nullptr)//we failed to load
					{
						printf("SDL_mixer failed to load audio file %s! Mix_GetError: %s\n", filename.c_str(), Mix_GetError());
						return Engine::VALUE_FAILURE;
					}
                    if( Mix_PlayChannel( -1, audio_chunk, 0 ) < Engine::VALUE_SUCCESS)
                    {
						printf("SDL_mixer failed to play audio file %s! Mix_GetError: %s\n", filename.c_str(), Mix_GetError());
						return Engine::VALUE_FAILURE;
                    }
					return Engine::VALUE_SUCCESS;
				}
			}

		}
	}
}
