#pragma once

//gets the state of key presses

#include <SDL_events.h>

#include <cstdio>

namespace BTD::Input
{
	//stores the data of key presses
	struct KeyInput
	{
		Uint8 lastFrame[SDL_NUM_SCANCODES];
		Uint8 currentFrame[SDL_NUM_SCANCODES];

		//updates the inpur frame data
		inline void UpdateInputData()
		{
			const Uint8* state = SDL_GetKeyboardState(NULL);
			const size_t memSize = sizeof(lastFrame);
			memcpy(lastFrame, currentFrame, memSize);
			memcpy(currentFrame, state, memSize);
		}

		//was a key pressed

		//was a key released

		//is a key held
		inline bool IsKeyHeld(const SDL_Scancode& key)
		{
			if (lastFrame[key] && currentFrame[key])
				return true;

			return false;
		}

		//is a key released
	};
}