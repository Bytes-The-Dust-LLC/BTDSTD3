#pragma once

//defines various file operations

#include <BTDSTD/Logger.hpp>
#include <BTDSTD/IO/FileErrors.hpp>

#include <filesystem>

namespace BTD::IO
{
	/*
	In the BTDSTD, the most common way of writing custom files is separating them out to the directory, filename, and extension
	This enforcing a specific convention for our functions so everything stays in sync
	As such, a struct storing FileInfo is created for storing all theses specific data bits accros platforms
	This normally wraps around a C++17 Filesystem object and makes calls into it.

	- Anytime this struct refers to a filename, this is JUST the FILE NAME, anything after the . or parsed a extension is ignored
	*/
	struct FileInfo
	{
		std::string dir = "", //the directory this file exists in

		name = "", //the file name of this file, minus the extension
		extension = "", //the file extension of this file
		fullname = "", //the full name of this extension including any extentions parsed

		absolutePath = ""; //the full path of the file

		FileInfo() {}
		
		FileInfo(const std::string& filepath)
		{
			//gets the absolute path
			std::filesystem::path p = std::filesystem::absolute(filepath);
			absolutePath = p.string();

			//stores the directory
			dir = p.parent_path().string();

			//splits the full name off
			fullname = p.filename().string();
			name = p.filename().stem().string();

			//splits the . from the extension
			extension = p.filename().extension().string();
			if (extension.size() > 1 && extension[0] == '.')
				extension.erase(extension.begin());
		}

		//returns if the file exists
		inline bool Exists() const { return std::filesystem::exists(absolutePath); }

		//creates the file
		inline FileError Create(bool nukeIfAlreadyExists)
		{
			//checks if it already exits
			if (Exists() && !nukeIfAlreadyExists)
			{
				fmt::print("BTD IO Error: File Info || Create || File already exists at \"{}\". If you wish to create one regardless, pass true into \"nukeIfAlreadyExists\".\n",
					absolutePath);
				return FileError::FileAlreadyExists;
			}

			//creates a file

			return FileError::None;
		}

		//deletes the file
	};
}