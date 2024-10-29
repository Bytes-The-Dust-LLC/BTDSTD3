#pragma once

//defines various file errors and warnings

namespace BTD::IO
{
	//defines file warnings and errors
	enum class FileError
	{
		FileAlreadyExists = 0, //the file already exists

		//the file does not exist

		//the file is in use by another process


		None //no issues or wanrings
	};

	//returns a string variant of the enum
}