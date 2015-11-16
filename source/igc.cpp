/*RPG
	Dialogue
	Menus
	Overworld
	Battles
	Mini Games*/

#include <iostream>
#include <string>
#include <vector>
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include "igc.h"
#include "input.h"


namespace IGC
{
	namespace Engine
	{
		int Init()
		{
			if (SDL::Init() != Engine::RETURN_SUCCESS)
			{
				return Engine::RETURN_HALT;
			}
			if (SDL::LoadMedia() != Engine::RETURN_SUCCESS)
			{
				return Engine::RETURN_HALT;
			}

			return Engine::RETURN_SUCCESS;
		}
		void Sleep(unsigned int milliseconds)
		{
			SDL_Delay(milliseconds);
		}
		void DeInit()
		{
			SDL::DeInit();
			SDL::Video::DeInit();
		}
		namespace SDL
		{
			int g_status = SDL::STATUS_OFF;
			int Init()
			{
				g_status = SDL::STATUS_STARTING;
				//Initialize SDL
				if (SDL_Init(SDL_INIT_EVERYTHING) < SDL::INIT_SUCCESS) {//reminder: perhaps change `SDL_INIT_EVERYTHING` later on 
					printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
					DeInit();
					return Engine::RETURN_HALT;
				}
				else
				{
					//Initialize sub-systems
					int video_result = SDL::Video::Init();
					int audio_result = SDL::Audio::Init();
					int input_result = SDL::Input::Init();
					int scripting_result = Scripting::Init();

					if ((video_result == Engine::RETURN_SUCCESS) &&
						(video_result == Engine::RETURN_SUCCESS) &&
						(video_result == Engine::RETURN_SUCCESS) &&
						(video_result == Engine::RETURN_SUCCESS))
					{
						g_status = SDL::STATUS_RUNNING;
						return Engine::RETURN_SUCCESS;
					}
					else
					{
						DeInit();
						return Engine::RETURN_HALT;
					}
				}
			}

			void DeInit()
			{
				g_status = SDL::STATUS_EXITING;
				TTF_Quit();
				SDL_Quit();
				g_status = SDL::STATUS_OFF;
			}

			int LoadMedia()
			{
				return Engine::RETURN_SUCCESS;
			}
			void Update()
			{
				static SDL_Event s_events;//temporary
				//Handle events on queue

				//Reset Input Status
				//Input::g_player1_gamepad_status.buttons |= Input::DPAD_NONE;

				while (SDL_PollEvent(&s_events) != 0)
				{
					switch (s_events.type)
					{
						//User requests quit
						case SDL_QUIT:
							DeInit();
							break;

						//If a key was pressed
						case SDL_KEYDOWN:
						{
							switch (s_events.key.keysym.sym)
							{
								case SDLK_UP:
									Input::g_player1_gamepad_status.buttons |= Input::DPAD_UP;
									break;
								case SDLK_DOWN:
									Input::g_player1_gamepad_status.buttons |= Input::DPAD_DOWN;
									break;
								case SDLK_LEFT:
									Input::g_player1_gamepad_status.buttons |= Input::DPAD_LEFT;
									break;
								case SDLK_RIGHT:
									Input::g_player1_gamepad_status.buttons |= Input::DPAD_RIGHT;
									break;
								default://unhandled key press 
									break;
							}
							break;
						}

						//If a key was released
						case SDL_KEYUP:
						{
							switch (s_events.key.keysym.sym)
							{
								case SDLK_UP:
									Input::g_player1_gamepad_status.buttons &= ~Input::DPAD_UP;
									break;
								case SDLK_DOWN:
									Input::g_player1_gamepad_status.buttons &= ~Input::DPAD_DOWN;
									break;
								case SDLK_LEFT:
									Input::g_player1_gamepad_status.buttons &= ~Input::DPAD_LEFT;
									break;
								case SDLK_RIGHT:
									Input::g_player1_gamepad_status.buttons &= ~Input::DPAD_RIGHT;
									break;
								default://unhandled key press 
									break;
							}
							break;
						}

						//unhandled event
						default:
							break;
					}
				}
			}
			namespace Video
			{
				SDL_Window* g_window{};
				SDL_Renderer* g_renderer{};
				unsigned int g_width = 640;
				unsigned int g_height = 480;

				int Init()
				{
					//Initialize SDL
					if (SDL_Init(SDL_INIT_VIDEO) < SDL::INIT_SUCCESS)
					{
						printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());

						return Engine::RETURN_HALT;
					}

					//Initialize SDL TTF Support
					if (TTF_Init() < SDL::INIT_SUCCESS)
					{
						printf("SDL could not initialize TTF Support! SDL_Error: %s\n", SDL_GetError());

						return Engine::RETURN_HALT;
					}

					//Create window
					Video::g_window = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SDL::Video::g_width, SDL::Video::g_height, SDL_WINDOW_SHOWN);
					if (Video::g_window == nullptr)
					{
						printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());

						return Engine::RETURN_HALT;
					}

					//Assign renderer to pointer
					Video::g_renderer = SDL_CreateRenderer(Video::g_window, -1, 0);
					if (Video::g_renderer == nullptr)
					{
						printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());

						return Engine::RETURN_HALT;
					}

					//Clear screen
					if(x2D::ClearScreen() == SDL::DRAW_FAILURE)
					{
						return Engine::RETURN_HALT;
					}

					return Engine::RETURN_SUCCESS;
				}
				/*This destroys the window. It also frees any surface created by
				it. So we don't have to. And definately shouldn't try to.*/
				void DeInit()
				{
					SDL_DestroyWindow(Video::g_window);
				}

				int Update()
				{
					int function_result{};
					//Update screen
					SDL_RenderPresent(Video::g_renderer);

					//Clear screen
					function_result += x2D::ClearScreen();

					return function_result;
				}
				namespace x2D
				{
					TextureContainer::TextureContainer(std::string Filename)
					{
						m_filename = Filename;
						m_texture = LoadTexture(m_filename);
						if (m_texture != nullptr)
						{
							m_instance_counter = 1;
						}
						else
						{
							m_instance_counter = 0;
						}
					}
					TextureContainer::~TextureContainer()
					{
						if (m_texture != nullptr)
						{
							SDL_DestroyTexture(m_texture);
						}
					}
					SDL_Texture* TextureContainer::CompareFilename(std::string filename)
					{
						if (m_filename.compare(filename) == 0)//filenames match
						{
							return m_texture;
						}
						else
						{
							return nullptr;
						}
					}
					
					std::vector<x2D::TextureContainer*> TextureContainerVector;
					int LoadTextureByFilename(SDL_Texture*& texture, std::string filename)
					{
						//if we already have a working texture, no need to waste cpu cycles
						//if (texture != nullptr)
						//	return DRAW_SUCCESS;
						//look through the container for `Filename` and see if we've already loaded it
						for (std::vector<x2D::TextureContainer*>::iterator it = TextureContainerVector.begin(); it != TextureContainerVector.end(); ++it)
						{
							texture = (*it)->CompareFilename(filename);
							//return the `Texture` if we found a match
							if (texture != nullptr)
							{
								return DRAW_SUCCESS;
							}
						}

						//if there was no match, try loading `Filename`
						TextureContainer* container_pointer = new TextureContainer(filename);
						texture = container_pointer->m_texture;	//set the texture
						
						//if the image fails to load
						if (container_pointer->m_texture == nullptr)
						{
							delete container_pointer;	//we clear out the empty container
							return DRAW_FAILURE;		//and return with failure
						}

						//otherwise we add it to our list
						TextureContainerVector.push_back(container_pointer);

						return DRAW_SUCCESS;
					}

					int UnloadTextureByFilename(std::string filename)
					{
						//look through the container for `Filename` and see if it's loaded
						for (std::vector<x2D::TextureContainer*>::iterator it = TextureContainerVector.begin(); it != TextureContainerVector.end(); ++it)
						{
							SDL_Texture* texture = (*it)->CompareFilename(filename);
							if (texture != nullptr)
							{
								TextureContainer* container_pointer = (*it);
								TextureContainerVector.erase(it);//remove if we find it
								delete container_pointer;
								return DRAW_SUCCESS;
							}
						}
						return DRAW_FAILURE;
					}

					SDL_Texture* LoadTexture(std::string filename) {
						//The final texture
						SDL_Texture* new_texture{};

						//Load image at specified path
						SDL_Surface* temporary_surface = IMG_Load(filename.c_str());
						if (temporary_surface == nullptr)
						{
							printf("Unable to load image %s! SDL_image Error: %s\n", filename.c_str(), IMG_GetError());
							return nullptr;
						}

						//Create texture from surface pixels
						new_texture = SDL_CreateTextureFromSurface(Video::g_renderer, temporary_surface);
						if (new_texture == nullptr)
						{
							printf("Unable to create texture from %s! SDL Error: %s\n", filename.c_str(), SDL_GetError());
						}

						//Get rid of temporary_surface
						SDL_FreeSurface(temporary_surface);

						return new_texture;
					}

					int SetDrawColor(SDL_Color color)
					{
						int function_result = SDL_SetRenderDrawColor(Video::g_renderer, color.r, color.g, color.b, color.a);
						if (function_result < SDL::DRAW_SUCCESS)
						{
							printf("Set Render Draw Color failed! SDL_Error: %s\n", SDL_GetError());

							return SDL::DRAW_FAILURE;
						}
						return function_result;
					}

					int FillRect(SDL_Color color, SDL_Rect destination_rectangle)
					{
						int function_result = SetDrawColor(color);
						if (function_result < SDL::DRAW_SUCCESS)
							return SDL::DRAW_FAILURE;

						function_result = SDL_RenderFillRect(Video::g_renderer, &destination_rectangle);
						if (function_result < SDL::DRAW_SUCCESS)
						{
							printf("Could not fill rectangle! SDL_Error: %s\n", SDL_GetError());

							return SDL::DRAW_FAILURE;
						}

						return SDL::DRAW_SUCCESS;
					}

					SDL_Texture* RenderText(const std::string &message, const std::string &font_filename, SDL_Color color, int font_size)
					{
						//Open a font
						TTF_Font *temporary_font = TTF_OpenFont(font_filename.c_str(), font_size);
						if (temporary_font == nullptr)
						{
							printf("SDL could not open font \"%s\" for message \"%s\"! SDL_Error: %s\n", font_filename.c_str(), message.c_str(), SDL_GetError());
							
							return nullptr;
						}

						//Render a surface
						SDL_Surface *temporary_surface = TTF_RenderText_Blended(temporary_font, message.c_str(), color);
						if (temporary_surface == nullptr)
						{
							printf("SDL could not create message surface \"%s\"! SDL_Error: %s\n", message.c_str(), SDL_GetError());
							
							//Clean up the font
							TTF_CloseFont(temporary_font);

							return nullptr;
						}

						//Convert to texture
						SDL_Texture *return_texture = SDL_CreateTextureFromSurface(g_renderer, temporary_surface);
						if (return_texture == nullptr)
						{
							printf("SDL could not create message texture \"%s\"! SDL_Error: %s\n", message.c_str(), SDL_GetError());
							
							//Clean up the surface and font
							SDL_FreeSurface(temporary_surface);
							TTF_CloseFont(temporary_font);

							return nullptr;
						}

						//Clean up the surface and font
						SDL_FreeSurface(temporary_surface);
						TTF_CloseFont(temporary_font);

						return return_texture;
					}

					int ClearScreen()
					{
						x2D::SetDrawColor({ 0xFF, 0xFF, 0xFF, SDL_ALPHA_OPAQUE });//TODO: Change to black
						int function_result = SDL_RenderClear(Video::g_renderer);
						if (function_result < SDL::DRAW_SUCCESS)
						{
							printf("SDL could not clear window renderer! SDL_Error: %s\n", SDL_GetError());
							return SDL::DRAW_FAILURE;
						}
						return function_result;
					}

					int DrawTexture(SDL_Texture* texture, SDL_Rect destination_rectangle)
					{
						if (texture == nullptr)
						{
							printf("Texture not initialized!\n");
							return SDL::DRAW_FAILURE;
						}
						if (destination_rectangle.w == FULL_TEXTURE_WIDTH || destination_rectangle.h == FULL_TEXTURE_HEIGHT)
							SDL_QueryTexture(texture, NULL, NULL, &destination_rectangle.w, &destination_rectangle.h);

						int function_result = SDL_RenderCopy(Video::g_renderer, texture, NULL, &destination_rectangle);
						if (function_result < SDL::DRAW_SUCCESS)
						{
							printf("SDL could not copy texture to renderer! SDL_Error: %s\n", SDL_GetError());
							return SDL::DRAW_FAILURE;
						}
						return function_result;
					}

					int DrawTexture(SDL_Texture* texture, SDL_Rect source_rectangle, SDL_Rect destination_rectangle)
					{
						if (texture == nullptr)
						{
							printf("Texture not initialized!\n");
							return SDL::DRAW_FAILURE;
						}
						if (destination_rectangle.w == FULL_TEXTURE_WIDTH || destination_rectangle.h == FULL_TEXTURE_HEIGHT)
							SDL_QueryTexture(texture, NULL, NULL, &destination_rectangle.w, &destination_rectangle.h);

						int function_result = SDL_RenderCopy(Video::g_renderer, texture, &source_rectangle, &destination_rectangle);
						if (function_result < SDL::DRAW_SUCCESS)
						{
							printf("SDL could not copy texture to renderer! SDL_Error: %s\n", SDL_GetError());
							return SDL::DRAW_FAILURE;
						}
						return function_result;
					}
				}
			}

			namespace Audio
			{
				int Init()
				{
					return Engine::RETURN_SUCCESS;
				}
			}

		}
		namespace Scripting
		{
			int Init()
			{
				return Engine::RETURN_SUCCESS;
			}
		}
	}
}
