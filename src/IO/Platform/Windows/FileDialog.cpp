#include <BTDSTD/IO/FileDialog.hpp>

#include <BTDSTD/String.hpp>

#ifdef Window_Build
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <commdlg.h>
#endif

#include <SDL_video.h>

//gets a file
std::string BTD::IO::OpenFileDialog(const char* windowTitle)
{
	//gets a file dialogue
	return tinyfd_openFileDialog(
		windowTitle,              // Title
		"",                       // Default path
		0,                        // Number of filters
		nullptr,                  // Filter patterns
		nullptr,                  // Filter description
		0                         // Allow multiple selection
	);
}

//opens a directory select dialog
std::string BTD::IO::DirectorySelectDialog(const char* windowTitle)
{
	return tinyfd_selectFolderDialog(windowTitle, "");
}

#ifdef Window_Build
//opens a save file dialog
std::string BTD::IO::SaveFileDialog(char* fileTypeFilter, Wireframe::Window::DesktopWindow* window)
{
	//common dialog box struture
	OPENFILENAMEA ofn;
	CHAR szFile[260] = { 0 };

	//initalize Open Filename
	ZeroMemory(&ofn, sizeof(OPENFILENAMEA));
	ofn.lStructSize = sizeof(OPENFILENAMEA);
	ofn.hwndOwner = window->systemInfo.info.win.window; //gets the native window handle
	ofn.lpstrFile = szFile;
	ofn.nMaxFile = sizeof(szFile);
	ofn.lpstrFilter = fileTypeFilter;
	ofn.nFilterIndex = 1;

	//sets flags and opens
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_NOCHANGEDIR;
	return (GetSaveFileNameA(&ofn) == TRUE ? ofn.lpstrFile : std::string());
}

////opens a load file dialog
//std::string BTD::IO::OpenFileDialog(char* fileTypeFilter, Wireframe::Window::DesktopWindow* window)
//{
//	//common dialog box struture
//	OPENFILENAMEA ofn;
//	CHAR szFile[260] = { 0 };
//
//	//initalize Open Filename
//	ZeroMemory(&ofn, sizeof(OPENFILENAMEA));
//	ofn.lStructSize = sizeof(OPENFILENAMEA);
//	ofn.hwndOwner = window->systemInfo.info.win.window; //gets the native window handle
//	ofn.lpstrFile = szFile;
//	ofn.nMaxFile = sizeof(szFile);
//	ofn.lpstrFilter = fileTypeFilter;
//	ofn.nFilterIndex = 1;
//
//	//sets flags and opens
//	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_NOCHANGEDIR;
//	return (GetOpenFileNameA(&ofn) == TRUE ? ofn.lpstrFile : std::string());
//}

////opens a directory select dialog
//std::string BTD::IO::DirectorySelectDialog(const char* fileTypeFilter, Wireframe::Window::DesktopWindow* window)
//{
//	//gets a file dialogue
//	return tinyfd_openFileDialog(
//		"Open File",              // Title
//		"",                       // Default path
//		0,                        // Number of filters
//		nullptr,                  // Filter patterns
//		nullptr,                  // Filter description
//		0                         // Allow multiple selection
//	);
//
//
//	////common dialog box struture
//	//OPENFILENAMEA ofn;
//	//CHAR szFile[260] = { 0 };
//
//	////initalize Open Filename
//	//ZeroMemory(&ofn, sizeof(OPENFILENAMEA));
//	//ofn.lStructSize = sizeof(OPENFILENAMEA);
//	//ofn.hwndOwner = window->systemInfo.info.win.window; //gets the native window handle
//	//ofn.lpstrFile = szFile;
//	//ofn.nMaxFile = sizeof(szFile);
//	//ofn.lpstrFilter = fileTypeFilter;
//	//ofn.nFilterIndex = 1;
//
//	////sets flags and opens
//	//ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_NOCHANGEDIR;
//	//if (GetSaveFileNameA(&ofn) == TRUE)
//	//{
//	//	//gets the directory
//	//	std::string dir = "";
//	//	std::vector<std::string> strs = BTD::String::SplitStrIntoArrayByDelimiter(ofn.lpstrFile, '\\');
//	//	dir = "";
//	//	for (size_t i = 0; i < strs.size() - 1; ++i)
//	//	{
//	//		dir += strs[i];
//	//		dir += '/';
//	//	}
//	//	
//	//	return dir;
//	//}
//
//	//return std::string();
//}
#endif