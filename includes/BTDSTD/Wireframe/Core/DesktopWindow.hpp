#pragma once

//defines a desktop window

#include <BTDSTD/Logger.hpp>

#include <BTDSTD/Wireframe/vk_types.h>

#include <SDL_video.h>
#include <SDL_syswm.h>

namespace Wireframe::Window
{
	//defines a desktop window create info
	struct DesktopWindow_CreateInfo
	{
		VkExtent2D size = { 500, 800 };
		const char* title = "Wireframe App";
	};

	//defines a desktop window
	struct DesktopWindow
	{
		bool isRunning = false;
		bool isMinimized = false;
		bool hasBeenResized = false;

		VkExtent2D _windowExtent{ 1700 , 900 };
		SDL_SysWMinfo systemInfo; //low level system info about the window
		struct SDL_Window* _window{ nullptr };
		VkSurfaceKHR _surface;

		//creates a window
		bool Create(const DesktopWindow_CreateInfo& info);
		//destroys a window
		void Destroy();

		//creates a surface
		void CreateSurface(VkInstance& instance);
		//destroys a surface
		void DestroySurface(VkInstance& instance);

		//resizes a window
	};
}