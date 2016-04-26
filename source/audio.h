#pragma once

#include <string>
#include "SDL.h"

namespace IGC {namespace Engine {namespace SDL {namespace Audio {
// Setup everything audio related.
//
// Returns:
//	`Engine::VALUE_SUCCESS` or `Engine::VALUE_FAILURE`
extern int Init();
/*
namespace Midi
{
					
}
namespace Raw
{
					
}
namespace Music
{
					
}
namespace SoundEffects
{
					
}
namespace Microphone
{
					
}
*/
//TODO: write description
int PlaySound(std::string filename);
}}}}//namespace IGC::Engine::SDL::Audio
