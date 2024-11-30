#pragma once

//defines a pipeline layout

#include <BTDSTD/Wireframe/Core/GPU.hpp>
#include <BTDSTD/Wireframe/Util/ShaderStages.hpp>

#include <BTDSTD/Formats/json.hpp>

#include <BTDSTD/IO/File.hpp>

#include <unordered_map>

namespace Wireframe::Pipeline
{
	//defines a push constant
	struct PushConstant
	{
		Shader::Util::ShaderStage stage = Shader::Util::ShaderStage::Vertex;
		uint32_t offset;
		uint32_t size;
		std::string name = "", //the name we use for finding it
			structName = ""; //the struct we use for storing the push constant data

		//converts this struct into a JSON object
		inline nlohmann::json ToJSON() const
		{
			nlohmann::json j;

			j["stage"] = (uint8_t)stage;
			j["offset"] = offset;
			j["size"] = size;
			j["name"] = name;
			j["structName"] = structName;

			return j;
		}

		//parses a JSON object into this struct
		inline void FromJSON(const nlohmann::json& j)
		{
			stage = (Shader::Util::ShaderStage)j["stage"];
			offset = j["offset"];
			size = j["size"];
			name = j["name"];
			structName = j["structName"];
		}

		//gets the defined extension for this custom filetype
		static inline std::string GetExtentionStr() { return "btdpushconstsettings"; }
	};

	//defines a pipeline layout create info
	struct PipelineLayout_CreateInfo
	{
		std::vector<PushConstant> pushConstants;
	};

	//defines a pipeline layout
	struct PipelineLayout
	{
		std::unordered_map<std::string, PushConstant> pushConstants; //the push constants associated with this layout

		VkPipelineLayout handle;

		//creates a pipeline layout
		inline bool Create(const PipelineLayout_CreateInfo& _info, Device::GPU* GPU)
		{
			VkPipelineLayoutCreateInfo info{};
			info.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
			info.pNext = nullptr;

			info.flags = 0;

			info.setLayoutCount = 0;
			info.pSetLayouts = nullptr;
			
			const size_t pushConstCount = _info.pushConstants.size();
			std::vector<VkPushConstantRange> consts; consts.resize(pushConstCount);
			if (pushConstCount > 0)
			{
				for (size_t i = 0; i < pushConstCount; ++i)
				{
					consts[i].stageFlags = (VkShaderStageFlags)_info.pushConstants[i].stage;
					consts[i].size = _info.pushConstants[i].size;
					consts[i].offset = _info.pushConstants[i].offset;

					pushConstants[_info.pushConstants[i].name] = _info.pushConstants[i];

				}

				info.pushConstantRangeCount = pushConstCount;
				info.pPushConstantRanges = consts.data();					
			}
			else
			{
				info.pushConstantRangeCount = 0;
				info.pPushConstantRanges = 0;
			}

			VK_CHECK(vkCreatePipelineLayout(GPU->device, &info, nullptr, &handle));

			return true;
		}

		//destroys a pipeline layout
		inline void Destroy(Device::GPU* GPU)
		{
			vkDestroyPipelineLayout(GPU->device, handle, nullptr);
		}

		//update push constant on the vertex stage
		inline void UpdatePushConstant_Vertex(VkCommandBuffer& cmd, const std::string pushConstantName, void* data)
		{
			PushConstant* c = &pushConstants[pushConstantName];
			vkCmdPushConstants(cmd, handle, static_cast<VkShaderStageFlags>(c->stage), c->offset, c->size, data);
		}
	};
}

namespace Wireframe::Pipeline::Serilize
{
	//writes pipeline push constant to a file
	inline bool WritePipelineLayoutPushConstantDataToFile(const BTD::IO::FileInfo& settingsFile, const PushConstant& data)
	{
		//checks if the file has the right extension, if not throw a warning and add it ourself
		BTD::IO::FileInfo f = settingsFile;
		if(!f.IsFileExtension(PushConstant::GetExtentionStr()))
		{
			fmt::print("Wireframe Pipeline Warning: Serilize || WritePipelineLayoutPushConstantDataToFile || \"{}\" does not end in .{}, this is the file extension for Wireframe Pipeline Layout Push Constant Setting files. This warning can be ignored as we will add the extension. But to make it go away, add it to your file. The PushConstant struct contains a static funtion for getting the correct file extension.\n",
				f.GetPathStr(), PushConstant::GetExtentionStr());

			f.AppendFileExtension(PushConstant::GetExtentionStr());
		}

		//build json and write to file
		BTD::IO::File::WriteWholeTextFile(f, data.ToJSON().dump());

		return true;
	}

	//loads pipeline push constant from a file
	inline bool LoadPipelineLayoutPushConstantDataFromFile(const BTD::IO::FileInfo& settingsFile, PushConstant& data)
	{
		//checks if the file has the right extension, if not error out
		if (!settingsFile.IsFileExtension(PushConstant::GetExtentionStr()))
		{
			fmt::print("Wireframe Shader Error: Serilize || LoadPipelineLayoutPushConstantDataToFile || \"{}\" does not end in .{}, this is the file extension for Wireframe Pipeline Layout Push Constant Setting files. We can not proove this is a valid Pipeline Layout Push Constant Settings file. Call \"WritePipelineLayoutPushConstantDataToFile\" to generate a proper file. If the file you are loading was made in a earlier version of the STD, please try updating the file with the newest functions.\n",
				settingsFile.GetPathStr(), PushConstant::GetExtentionStr());
			return false;
		}

		//parse JSON object and load data
		data.FromJSON(nlohmann::json::parse(BTD::IO::File::ReadWholeTextFile(settingsFile).data));

		return true;
	}
}