#pragma once

//defines File Dialogs

#include <BTDSTD/Wireframe/Core/DesktopWindow.hpp>

#include <string>

namespace BTD::IO
{
	//opens a save file dialog
	std::string SaveFileDialog(char* fileTypeFilter, Wireframe::Window::DesktopWindow* window);
	
	//opens a load file dialog
	std::string OpenFileDialog(char* fileTypeFilter, Wireframe::Window::DesktopWindow* window);
	
	//opens a directory select dialog
	std::string DirectorySelectDialog(const char* fileTypeFilter, Wireframe::Window::DesktopWindow* window);
}