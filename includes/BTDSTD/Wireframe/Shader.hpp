#pragma once

//defines shaders

#include <BTDSTD/Logger.hpp>
#include <BTDSTD/IO/File.hpp>
#include <BTDSTD/Wireframe/Core/GPU.hpp>
#include <BTDSTD/Wireframe/Util/ShaderStages.hpp>

#include <fstream>
#include <vector>

namespace Wireframe::Shader
{
	//defines a shader module
	struct ShaderModule
	{
		VkShaderModule shaderModule;

		//creates a shader module
		inline bool Create(const char* filepath, Device::GPU* GPU)
		{
			//open the file. With cursor at the end
			std::ifstream file(filepath, std::ios::ate | std::ios::binary);

			if (!file.is_open())
			{
				fmt::print("Wireframe Error: Shader Module || Create || Failed to open a compiled shader at \"{}\". Please make sure the path actually exists\n", filepath);
				return false;
			}

			//find what the size of the file is by looking up the location of the cursor
			//because the cursor is at the end, it gives the size directly in bytes
			size_t fileSize = (size_t)file.tellg();

			//spirv expects the buffer to be on uint32, so make sure to reserve a int vector big enough for the entire file
			std::vector<uint32_t> buffer(fileSize / sizeof(uint32_t));

			//put file cursor at beggining
			file.seekg(0);

			//load the entire file into the buffer
			file.read((char*)buffer.data(), fileSize);

			//now that the file is loaded into the buffer, we can close it
			file.close();

			//create a new shader module, using the buffer we loaded
			VkShaderModuleCreateInfo createInfo = {};
			createInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
			createInfo.pNext = nullptr;

			//codeSize has to be in bytes, so multply the ints in the buffer by size of int to know the real size of the buffer
			createInfo.codeSize = buffer.size() * sizeof(uint32_t);
			createInfo.pCode = buffer.data();

			//check that the creation goes well.
			if (vkCreateShaderModule(GPU->device, &createInfo, nullptr, &shaderModule) != VK_SUCCESS)
			{
				fmt::print("Wireframe Error: Shader Module || Create || Failed to create a shader from Byte Code loaded at \"{}\". Please make sure the path actually exists and is a compiled SPRV shader. The BTDSTD comes with tools for compiling shaders. If you are missing parts of the SDK or have a question go to {}\n",
					filepath, "\"www.bytesthedust.co\"");
				return false;
			}

			return true;
		}

		//destroys the module
		inline void Destroy(Device::GPU* GPU)
		{
			vkDestroyShaderModule(GPU->device, shaderModule, nullptr);
		}
	};

	//generates a shader stage info for a pipeline
	inline VkPipelineShaderStageCreateInfo GenerateShaderStageInfoForPipeline(const ShaderModule& shader, const Util::ShaderStage& stage, const char* entryPointFuncName = "main")
	{
		VkPipelineShaderStageCreateInfo info{};
		info.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
		info.pNext = nullptr;

		//shader stage
		info.stage = (VkShaderStageFlagBits)stage;
		//module containing the code for this shader stage
		info.module = shader.shaderModule;
		//the entry point of the shader
		info.pName = entryPointFuncName;

		return info;
	}
}

#include <BTDSTD/Formats/json.hpp>

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
	inline bool WriteShaderDataToFile(const BTD::IO::FileInfo& settingsFile, const ShaderSerilizeData& data, const bool isProductionBuild)
	{
		//checks if the file has the right extension, if not throw a warning and add it ourself
		BTD::IO::FileInfo f = settingsFile;
		const std::string p = settingsFile.GetPathStr();
		if (settingsFile.extension != ShaderSerilizeData::GetExtentionStr())
		{
			fmt::print("Wireframe Shader Warning: Serilize || WriteShaderDataToFile || \"{}\" does not end in .{}, this is the file extension for Wireframe Shader Setting files. This warning can be ignored as we will add the extension. But to make it go away, add it to your file. The ShaderSerilizeData struct contains a static funtion for getting the correct file extension.\n",
				p, ShaderSerilizeData::GetExtentionStr());

			//if we need a period
			if (p[p.size() - 1] != '.')
				f = BTD::IO::FileInfo(p + "." + ShaderSerilizeData::GetExtentionStr());
			else
				f = BTD::IO::FileInfo(p + ShaderSerilizeData::GetExtentionStr());
		}

		//build json and write to file
		BTD::IO::File::WriteWholeTextFile(f, data.ToJSON(isProductionBuild).dump());

		return true;
	}

	//loads shader settings from a file || if isProductionBuild is true, will not load debug data
	inline bool LoadShaderDataFromFile(const BTD::IO::FileInfo& settingsFile, ShaderSerilizeData& data, const bool isProductionBuild)
	{
		//checks if the file has the right extension, if not error out
		if (settingsFile.extension != ShaderSerilizeData::GetExtentionStr())
		{
			fmt::print("Wireframe Shader Error: Serilize || LoadShaderDataToFile || \"{}\" does not end in .{}, this is the file extension for Wireframe Shader Setting files. We can not proove this is a valid Shader Settings file. Call \"WriteShaderDataToFile\" to generate a proper file. If the file you are loading was made in a earlier version of the STD, please try updating the file with the newest functions.\n",
				settingsFile.GetPathStr(), ShaderSerilizeData::GetExtentionStr());
			return false;
		}

		//parse JSON object and load data
		data.FromJSON(nlohmann::json::parse(BTD::IO::File::ReadWholeTextFile(settingsFile).data));

		return true;
	}
}

namespace Wireframe::IO::Shader
{
	//takes in a directory and returns all shader setting files
}