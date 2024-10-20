#pragma once

//defines a ID String Registery, maps a string to a ID

#include <BTDSTD/Maps/IDRegistery.hpp>

#include <string>
#include <unordered_map>

namespace BTD::Map
{
	//defines a string ID Registery
	struct IDStringRegistery
	{
		IDRegistery registery; //stores the IDs

		std::unordered_map<uint64_t, std::string> IDToStrs; //the unordered map for IDs to strings
	
		//generates a new ID to String maping
		inline uint64_t GenerateID(const std::string& name)
		{
			uint64_t ID = 0;
			registery.GenerateID(ID);
			IDToStrs[ID] = name;
			return ID;
		}

		//clears all string ID pairs
	};
}