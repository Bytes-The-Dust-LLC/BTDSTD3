#pragma once

//defines various file operations

#include <BTDSTD/Logger.hpp>
#include <BTDSTD/IO/FileErrors.hpp>

#include <BTDSTD/Build/whereami.h>
#include <filesystem>

namespace BTD::IO
{
	//gets the path to the exe
	inline std::string GetExePath()
	{
		//gets file path
		int dirLength = 0;
		const int pathLength = wai_getExecutablePath(NULL, 0, &dirLength);
		char* path = (char*)malloc(pathLength + 1);
		wai_getExecutablePath(path, pathLength, &dirLength);
		path[pathLength] = '\0';
		
		//convert to string and clean C-string
		std::string p = std::string(path);
		free(path);

		return p;
	}

	/*
	In the BTDSTD, the most common way of writing custom files is separating them out to the directory, filename, and extension
	This enforcing a specific convention for our functions so everything stays in sync
	As such, a struct storing FileInfo is created for storing all theses specific data bits accros platforms
	This normally wraps around a C++17 Filesystem object and makes calls into it.

	- Anytime this struct refers to a filename, this is JUST the FILE NAME, anything after the . or parsed a extension is ignored
	*/
	struct FileInfo
	{
		std::filesystem::path path;

		std::string name = "", //the file name of this file, minus the extension
			extension = "", //the file extension of this file
			fullname = ""; //the full name of this extension including any extentions parsed

		//updates the full filepath and updates all the internal data
		inline void SetFullFilePath(const std::string& filepath)
		{
			path = std::filesystem::path(filepath);

			//splits the full name off
			fullname = path.filename().string();
			name = path.filename().stem().string();

			//splits the . from the extension
			extension = path.filename().extension().string();
			if (extension.size() > 1 && extension[0] == '.')
				extension.erase(extension.begin());
		}

		//Constructor
		FileInfo() {}
		
		//Constructor
		FileInfo(const std::string& filepath) { SetFullFilePath(filepath); }

		//gets the path string
		inline std::string GetPathStr() const { return path.string(); }

		//returns if the file exists
		inline bool Exists() const { return std::filesystem::exists(path); }

		//checks if the file extension of this file, matches the desired one
		inline bool IsFileExtension(const std::string& desiredExtension) const { return (extension == desiredExtension); }

		//adds a extension to the file path, factors in the . at the end of the file
		inline void AppendFileExtension(const std::string& newExtension)
		{
			//if we need a period
			const std::string p = GetPathStr();
			if (p[p.size() - 1] != '.')
				SetFullFilePath(p + "." + newExtension);
			else
				SetFullFilePath(p + newExtension);
		}
	};
}