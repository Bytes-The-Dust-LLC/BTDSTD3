#pragma once

//handles writing and reading data files describing the shader settings

#include <BTDSTD/IO/File.hpp>
#include <BTDSTD/Wireframe/Util/ShaderStages.hpp>

#include <BTDSTD/Formats/json.hpp>
#include <string>

namespace Wireframe::Shader::Serilize
{
	//defines a shader serilize object
	struct ShaderSerilizeData
	{
		std::string name = "", //used for debug tracking || NOT FOR PRODUCTION BUILDS
			sourceFilepath = "", //where the source code file is located || NOT FOR PRODUCTION BUILDS
			binaryFilepath = "", //binary SPRV file for shader bytecode, normally relative to the settings file loaded in
			entryPointFuncName = "main"; //the name of the function to call as a entry point in the shader, normally main

		Util::ShaderStage stage = Util::ShaderStage::Vertex; //the shader stage this shader belongs to

		//converts this struct into a JSON object
		inline nlohmann::json ToJSON(const bool isProductionBuild) const
		{
			nlohmann::json j;

			j["isProductionBuild"] = isProductionBuild; //are we a production build file

			//if we're in not in production
			if (!isProductionBuild)
			{
				j["name"] = name;
				j["sourceFP"] = sourceFilepath;
			}

			j["binaryFP"] = binaryFilepath;
			j["entryFunc"] = entryPointFuncName;
			j["stage"] = (uint8_t)stage;

			return j;
		}

		//parses a JSON object into this struct
		inline void FromJSON(const nlohmann::json& j)
		{
			const bool isProductionBuild = j["isProductionBuild"];

			//if we're in not in production
			if (!isProductionBuild)
			{
				name = j["name"];
				sourceFilepath = j["sourceFP"];
			}

			binaryFilepath = j["binaryFP"];
			entryPointFuncName = j["entryFunc"];
			stage = j["stage"];
		}

		//gets the defined extension for this custom filetype
		static inline std::string GetExtentionStr() { return "btdshadersettings"; }
	};

	//writes shader settings to a file || if isProductionBuild is true, will not write debug data
	inline bool WriteShaderDataToFile(BTD::IO::FileInfo& settingsFile, const ShaderSerilizeData& data, const bool isProductionBuild)
	{
		//checks if the file has the right extension, if not throw a warning and add it ourself
		if (settingsFile.extension != ShaderSerilizeData::GetExtentionStr())
		{
			fmt::print("Wireframe Shader Warning: Serilize || WriteShaderDataToFile || \"{}\" does not end in .{}, this is the file extension for Wireframe Shader Setting files. This warning can be ignored as we will add the extension. But to make it go away, add it to your file. The ShaderSerilizeData struct contains a static funtion for getting the correct file extension.\n",
				settingsFile.absolutePath, ShaderSerilizeData::GetExtentionStr());
			
			//if we need a period
			if(settingsFile.absolutePath[settingsFile.absolutePath.size() - 1] != '.')
				settingsFile = BTD::IO::FileInfo(settingsFile.absolutePath + "." + ShaderSerilizeData::GetExtentionStr());
			else
				settingsFile = BTD::IO::FileInfo(settingsFile.absolutePath + ShaderSerilizeData::GetExtentionStr());
		}

		//build json and write to file
		BTD::IO::File::WriteWholeTextFile(settingsFile, data.ToJSON(isProductionBuild).dump());

		return true;
	}

	//loads shader settings from a file || if isProductionBuild is true, will not load debug data
	inline bool LoadShaderDataFromFile(const BTD::IO::FileInfo& settingsFile, ShaderSerilizeData& data, const bool isProductionBuild)
	{
		//checks if the file has the right extension, if not error out
		if (settingsFile.extension != ShaderSerilizeData::GetExtentionStr())
		{
			fmt::print("Wireframe Shader Error: Serilize || LoadShaderDataToFile || \"{}\" does not end in .{}, this is the file extension for Wireframe Shader Setting files. We can not proove this is a valid Shader Settings file. Call \"WriteShaderDataToFile\" to generate a proper file. If the file you are loading was made in a earlier version of the STD, please try updating the file with the newest functions.\n",
				settingsFile.absolutePath, ShaderSerilizeData::GetExtentionStr());
			return false;
		}

		//parse JSON object and load data
		data.FromJSON(nlohmann::json::parse(BTD::IO::File::ReadWholeTextFile(settingsFile).data));
		
		return true;
	}
}