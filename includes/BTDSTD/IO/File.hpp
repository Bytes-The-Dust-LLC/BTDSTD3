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

		Binary_Write_Create, //creates a binary file and opens it for writing
		Binary_Read, //reads as binary data
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

		case FileOp::Binary_Write_Create:
			return "wb";

		case FileOp::Binary_Read:
			return "rb";

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
					f.GetPathStr());
				return FileError::FileAlreadyExists;
			}

			file = fopen(f.GetPathStr().c_str(), FileOpToStrFlag(op)); // Open file in write mode
			if (!file)
			{
				fmt::print("BTD IO Error: File || Open || Failed to open file at \"{}\".\n",
					f.GetPathStr());
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
					fileInfo.GetPathStr());
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
					fileInfo.GetPathStr());
				return { FileError::FileIsNotOpen, 0 };
			}

			fseek(file, 0, SEEK_END);
			const size_t fileLength = ftell(file);
			fseek(file, 0, SEEK_SET);
			return { FileError::None, fileLength };
		}

		//writes data into the file
		inline FileError WriteData(const void* data, const size_t& memSizeOfElement, const size_t& elementCount)
		{
			if (!file)
			{
				fmt::print("BTD IO Error: File || WriteData || No file is open at \"{}\". Can not write data.\n",
					fileInfo.GetPathStr());
				return FileError::FileIsNotOpen;
			}

			fwrite(data, memSizeOfElement, elementCount, file);

			return FileError::None;
		}

		//writes text into the file
		inline FileError WriteText(const std::string& str)
		{
			FileError error = WriteData(str.data(), sizeof(char), str.size());
			if(error == FileError::FileIsNotOpen)
				fmt::print("BTD IO Error: File || Write || No file is open at \"{}\". Can not write data.\n",
					fileInfo.GetPathStr());

			return error;
		}

		//reads the whole file as a single array
		inline FileError ReadWholeFile_Data(void* data, const size_t& memSizeOfElement, const size_t& elementCount)
		{
			if (!file)
			{
				fmt::print("BTD IO Error: File || ReadWholeFile_Data || No file is open at \"{}\". Can not read data.\n",
					fileInfo.GetPathStr());
				return FileError::FileIsNotOpen;
			}

			fread(data, memSizeOfElement, elementCount, file);

			return FileError::None;
		}

		//reads the whole file as a single string
		inline FileError_DataPair<std::string> ReadWholeFile_Text()
		{
			if (!file)
			{
				fmt::print("BTD IO Error: File || ReadWholeFile || No file is open at \"{}\". Can not read data.\n",
					fileInfo.GetPathStr());
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
			FileError_DataPair<std::string> d = file.ReadWholeFile_Text();
			file.Close();
			return d;
		}

		//reads a whole data file
		static inline FileError ReadWholeBinaryFile(const FileInfo& info, void* data, const size_t& memSizeOfElements, const size_t& elementCount)
		{
			BTD::IO::File file;
			file.Open(info, BTD::IO::FileOp::Binary_Read, false);
			file.ReadWholeFile_Data(data, memSizeOfElements, elementCount);
			file.Close();
			return FileError::None;
		}

		//writes a whole text file
		static inline FileError WriteWholeTextFile(const FileInfo& info, const std::string& str)
		{
			BTD::IO::File file;
			file.Open(info, BTD::IO::FileOp::Text_Write_Create, true);
			file.WriteText(str);
			file.Close();
		}

		//writes a whole binary file
		static inline FileError WriteWholeBinaryFile(const FileInfo& info, const void* data, const size_t& memSizeOfElement, const size_t& elementCount)
		{
			BTD::IO::File file;
			file.Open(info, BTD::IO::FileOp::Binary_Write_Create, true);
			file.WriteData(data, memSizeOfElement, elementCount);
			file.Close();
		}
	};

	//creates a file and writes data into it

	//writes a whole array to a file

	//writes a whole string of text to a file

	//defines a text file
}