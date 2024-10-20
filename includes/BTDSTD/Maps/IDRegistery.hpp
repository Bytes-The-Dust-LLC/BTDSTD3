#pragma once

//defines a ID registery, allowing us to create new IDs and free them

#include <vector>

namespace BTD::Map
{
	//defines a ID Registery
	struct IDRegistery
	{
		uint64_t lastUsedID = 0;
		std::vector<uint64_t> inUseIDs;
		std::vector<uint64_t> freeIDs;

		//generates a new ID || returns false if all are in use
		inline bool GenerateID(uint64_t& ID)
		{
			//checks free IDs
			if (freeIDs.size() > 0)
			{
				ID = freeIDs[0];
				freeIDs.erase(freeIDs.begin());
				inUseIDs.emplace_back(ID);
				return true;
			}

			//if we're out of IDs, leave
			if (lastUsedID == UINT64_MAX)
				return false;

			//generates a new ID
			ID = lastUsedID;
			inUseIDs.emplace_back(ID);
			lastUsedID++;

			return true;
		}
		
		//deletes a ID

		//clears the whole register of IDs

		//checks if a ID is in use
	};
}