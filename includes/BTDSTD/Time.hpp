#pragma once

//handles time and delta time

#include <SDL_timer.h>

namespace BTD::Time
{
	struct Time
	{
	public:
		Time(float targetFPS)
			: m_FixedDeltaTime(1.0f / targetFPS), m_Accumulator(0.0f),
			m_CurrentTime(static_cast<float>(SDL_GetTicks()) / 1000.0f),
			m_DeltaTime(0.0f) {}

		void Update() {
			float newTime = static_cast<float>(SDL_GetTicks()) / 1000.0f;
			m_DeltaTime = newTime - m_CurrentTime;
			m_CurrentTime = newTime;

			m_Accumulator += m_DeltaTime;
		}

		bool ShouldUpdate() const {
			return m_Accumulator >= m_FixedDeltaTime;
		}

		void ConsumeAccumulator() {
			m_Accumulator -= m_FixedDeltaTime;
		}

		float GetFixedDeltaTime() const {
			return m_FixedDeltaTime;
		}

		float GetDeltaTime() const {
			return m_DeltaTime;
		}

		float GetAlpha() const {
			return m_Accumulator / m_FixedDeltaTime;
		}

	private:
		float m_FixedDeltaTime;   // Fixed timestep duration (e.g., 1/60th of a second)
		float m_Accumulator;      // Accumulated time since last physics update
		float m_CurrentTime;      // The current time in seconds
		float m_DeltaTime;        // Time between the last two frames
	};

	//defines a Time
	/*struct Time
	{
		static double deltaTime;
		static double fixedDeltaTime;

		static Uint64 lastFrame;
		static Uint64 currentFrame;

		static Uint64 currentFrameCount;
		static Uint64 maxFrameCount;

		//calculates the delta time
		inline static double CalDeltaTime()
		{
			lastFrame = currentFrame;
			currentFrame = SDL_GetPerformanceCounter();
			Uint64 elapsedTicks = currentFrame - lastFrame;

			Uint64 frequency = SDL_GetPerformanceFrequency();
			deltaTime = static_cast<double>(elapsedTicks) / static_cast<double>(frequency);

			//lastFrame = currentFrame;
			//currentFrame = SDL_GetPerformanceCounter();
			//
			//deltaTime = (double)((currentFrame - lastFrame) * 1000 / (double)SDL_GetPerformanceFrequency());
			return deltaTime;
		}

		//calculates the fixed delta time
		inline static double CalFixedDeltaTime()
		{
			if (currentFrameCount >= maxFrameCount)
			{
				fixedDeltaTime = deltaTime;
				currentFrameCount = 0;
			}
			else
			{
				currentFrameCount++;
				fixedDeltaTime = 0.0f;
			}

			return fixedDeltaTime;
		}

	};*/
}