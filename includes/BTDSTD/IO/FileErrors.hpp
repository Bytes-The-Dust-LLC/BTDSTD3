#pragma once

//defines various file errors and warnings

namespace BTD::IO
{
	//defines file warnings and errors
	enum class FileError
	{
		FileAlreadyExists = 0, //the file already exists

		FileDoesNotExist, //the file does not exist

		FileIsNotOpen, //the file is not open

		//the file is in use by another process


		None //no issues or wanrings
	};

	//returns a string variant of the enum

	//defines a data pair for a operation returning a file error
	template<typename T = size_t>
	struct FileError_DataPair
	{
		FileError error = FileError::None;
		T data;

		FileError_DataPair() {}
		FileError_DataPair(const FileError& e, const T& d)
		{
			error = e;
			data = d;
		}
	};
}