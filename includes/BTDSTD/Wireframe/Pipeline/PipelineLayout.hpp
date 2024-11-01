#pragma once

//defines a pipeline layout

#include <BTDSTD/Wireframe/Core/GPU.hpp>
#include <BTDSTD/Wireframe/Util/ShaderStages.hpp>

#include <unordered_map>

namespace Wireframe::Pipeline
{
	//defines a push constant
	struct PushConstant
	{
		Shader::Util::ShaderStage stage = Shader::Util::ShaderStage::Vertex;
		uint32_t offset;
		uint32_t size;
		std::string name = "";
	};

	//defines a pipeline layout create info
	struct PipelineLayout_CreateInfo
	{
		std::vector<PushConstant> pushConstants;
	};

	//defines a pipeline layout
	struct PipelineLayout
	{
		std::unordered_map<std::string, size_t> pushConstants; //the push constants associated with this layout

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

					pushConstants[_info.pushConstants[i].name] = _info.pushConstants[i].size;

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
			vkCmdPushConstants(cmd, handle, VK_SHADER_STAGE_VERTEX_BIT, 0, pushConstants[pushConstantName], data);
		}
	};
}