#pragma once

//defines File Dialogs

#include <BTDSTD/Wireframe/Core/DesktopWindow.hpp>

#include <BTDSTD/Build/tinyfiledialogs.h>

#include <string>

namespace BTD::IO
{
	//opens a save file dialog
	std::string SaveFileDialog(char* fileTypeFilter, Wireframe::Window::DesktopWindow* window);
	
	//opens a open file dialog
	std::string OpenFileDialog(const char* windowTitle);
	
	//opens a directory select dialog
	std::string DirectorySelectDialog(const char* windowTitle);
}