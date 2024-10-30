#pragma once

//defines a file and operations

#include <BTDSTD/IO/FileInfo.hpp>

#include <stdio.h>

namespace BTD::IO
{
	//file operation flags
	enum class FileOp
	{
		Text_Write_Create = 0, //creates a text file and opens it for writing
		Text_Read, //reads a text file
	};

	//converts a OP into a string flag
	inline const char* FileOpToStrFlag(const FileOp& op)
	{
		switch (op)
		{
		case FileOp::Text_Write_Create:
			return "w";
		case FileOp::Text_Read:
			return "r";

		default:
			fmt::print("BTD IO Error: FileOp || FileOpToStrFlag || a valid FileOp flag was not passed in. Pass a correct one.\n");
			return "";
		}
	}

	//defines a file
	struct File
	{
		FileInfo fileInfo;

		FILE* file = nullptr;

		//opens the file
		inline FileError Open(const FileInfo& f, const FileOp& op, bool overwriteIfAlreadyExists)
		{
			//checks if it already exits
			if (f.Exists() && !overwriteIfAlreadyExists && op == FileOp::Text_Write_Create)
			{
				fmt::print("BTD IO Error: File || Open || File already exists at \"{}\". If you wish to create/overwrite one regardless, pass true into \"overwriteIfAlreadyExists\".\n",
					f.absolutePath);
				return FileError::FileAlreadyExists;
			}

			file = fopen(f.absolutePath.c_str(), FileOpToStrFlag(op)); // Open file in write mode
			if (!file)
			{
				fmt::print("BTD IO Error: File || Open || Failed to open file at \"{}\".\n",
					f.absolutePath);
				return FileError::FileDoesNotExist;
			}

			fileInfo = f;
			return FileError::None;
		}

		//closes the file
		inline FileError Close()
		{
			if (!file)
			{
				fmt::print("BTD IO Warning: File || Close || No file is open at \"{}\". No need to close, this is a warning. Remove the function call to stop it.\n",
					fileInfo.absolutePath);
				return FileError::FileIsNotOpen;
			}

			fclose(file); // Close the file
			file = nullptr;
			fileInfo = FileInfo();
			return FileError::None;
		}

		//gets the length of a file
		inline FileError_DataPair<size_t> GetFileLength()
		{
			if (!file)
			{
				fmt::print("BTD IO Error: File || GetFileLength || No file is open at \"{}\". Can not get length\n",
					fileInfo.absolutePath);
				return { FileError::FileIsNotOpen, 0 };
			}

			fseek(file, 0, SEEK_END);
			const size_t fileLength = ftell(file);
			fseek(file, 0, SEEK_SET);
			return { FileError::None, fileLength };
		}

		//writes text into the file
		inline FileError Write(const std::string& str)
		{
			if (!file)
			{
				fmt::print("BTD IO Error: File || Write || No file is open at \"{}\". Can not write data.\n",
					fileInfo.absolutePath);
				return FileError::FileIsNotOpen;
			}

			fwrite(str.data(), sizeof(char), str.size(), file);

			return FileError::None;
		}

		//reads the whole file as a single string
		inline FileError_DataPair<std::string> ReadWholeFile()
		{
			if (!file)
			{
				fmt::print("BTD IO Error: File || ReadWholeFile || No file is open at \"{}\". Can not read data.\n",
					fileInfo.absolutePath);
				return { FileError::FileIsNotOpen, "" };
			}

			std::string str = "";
			str.resize(GetFileLength().data);
			fread(str.data(), sizeof(char), str.size(), file);

			return { FileError::None, str };
		}

		//reads the whole file into a string array, split by new line chars

		//reads the whole file as a byte array

		//reads a whole text file
		static inline FileError_DataPair<std::string> ReadWholeTextFile(const FileInfo& info)
		{
			BTD::IO::File file;
			file.Open(info, BTD::IO::FileOp::Text_Read, false);
			FileError_DataPair<std::string> d = file.ReadWholeFile();
			file.Close();
			return d;
		}

		//writes a whole text file
		static inline FileError WriteWholeTextFile(const FileInfo& info, const std::string& str)
		{
			BTD::IO::File file;
			file.Open(info, BTD::IO::FileOp::Text_Write_Create, true);
			file.Write(str);
			file.Close();
		}
	};
}