#pragma once

//defines pipeline settings

#include <BTDSTD/Wireframe/Shader.hpp>
#include <vector>

namespace Wireframe::Pipeline
{
	struct PipelineSettings
	{
		std::vector<VkPipelineShaderStageCreateInfo> _shaderStages = {};
		VkPipelineVertexInputStateCreateInfo _vertexInputInfo = {};
		VkPipelineInputAssemblyStateCreateInfo _inputAssembly = {};
		VkViewport _viewport = {};
		VkRect2D _scissor = {};
		VkPipelineRasterizationStateCreateInfo _rasterizer = {};
		VkPipelineColorBlendAttachmentState _colorBlendAttachment = {};
		VkPipelineMultisampleStateCreateInfo _multisampling = {};
		VkPipelineDepthStencilStateCreateInfo _depthStencil = {};

		//sets a default for vertex input state
		inline void SetPipelineSettingToDefault_VertexInputState()
		{
			_vertexInputInfo = {};
			_vertexInputInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
			_vertexInputInfo.pNext = nullptr;

			//no vertex bindings or attributes
			_vertexInputInfo.vertexBindingDescriptionCount = 0;
			_vertexInputInfo.vertexAttributeDescriptionCount = 0;
		}

		//sets a default for input assembly state
		inline void SetPipelineSettingToDefault_InputAssemblyState()
		{
			_inputAssembly = {};
			_inputAssembly.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
			_inputAssembly.pNext = nullptr;

			_inputAssembly.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
			//we are not going to use primitive restart on the entire tutorial so leave it on false
			_inputAssembly.primitiveRestartEnable = VK_FALSE;
		}

		//sets defaults for rasterizer state
		inline void SetPipelineSettingToDefault_RasterizerState()
		{
			_rasterizer = {};
			_rasterizer.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
			_rasterizer.pNext = nullptr;

			_rasterizer.depthClampEnable = VK_FALSE;
			//rasterizer discard allows objects with holes, default to no
			_rasterizer.rasterizerDiscardEnable = VK_FALSE;

			_rasterizer.polygonMode = VK_POLYGON_MODE_FILL;
			_rasterizer.lineWidth = 1.0f;
			//no backface cull
			_rasterizer.cullMode = VK_CULL_MODE_NONE;
			_rasterizer.frontFace = VK_FRONT_FACE_CLOCKWISE;
			//no depth bias
			_rasterizer.depthBiasEnable = VK_FALSE;
			_rasterizer.depthBiasConstantFactor = 0.0f;
			_rasterizer.depthBiasClamp = 0.0f;
			_rasterizer.depthBiasSlopeFactor = 0.0f;
		}

		//sets the polygon mode
		inline void SetPipelineSetting_Resterizer_PolygonMode(const VkPolygonMode mode, const float lineWidth = 1.0f)
		{
			_rasterizer.polygonMode = mode;
			_rasterizer.lineWidth = lineWidth;
		}

		//sets the cull mode
		inline void SetPipelineSetting_Resterizer_CullMode(VkCullModeFlags cullMode, VkFrontFace frontFace)
		{
			_rasterizer.cullMode = cullMode;
			_rasterizer.frontFace = frontFace;
		}

		//sets defaults for color blend attachment state
		inline void SetPipelineSettingToDefault_ColorBlendAttachmentState()
		{
			_colorBlendAttachment = {};
			_colorBlendAttachment.colorWriteMask = VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT |
				VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT;
			_colorBlendAttachment.blendEnable = VK_FALSE;
		}

		//disables color blending
		inline void SetPipelineSetting_ColorBlendAttachmentState_DisableBlending()
		{
			// default write mask
			_colorBlendAttachment.colorWriteMask = VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT;
			// no blending
			_colorBlendAttachment.blendEnable = VK_FALSE;
		}

		//sets defaults for multisample state
		inline void SetPipelineSettingToDefault_MultisampleState()
		{
			_multisampling = {};

			_multisampling.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
			_multisampling.pNext = nullptr;

			_multisampling.sampleShadingEnable = VK_FALSE;
			//multisampling defaulted to no multisampling (1 sample per pixel)
			_multisampling.rasterizationSamples = VK_SAMPLE_COUNT_1_BIT;
			_multisampling.minSampleShading = 1.0f;
			_multisampling.pSampleMask = nullptr;
			_multisampling.alphaToCoverageEnable = VK_FALSE;
			_multisampling.alphaToOneEnable = VK_FALSE;
		}

		//sets defaults for depth stencil state
		inline void SetPipelineSettingToDefault_DepthStencilState()
		{
			_depthStencil = {};
			_depthStencil.sType = VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO;
			_depthStencil.pNext = nullptr;

			_depthStencil.depthTestEnable = VK_TRUE;
			_depthStencil.depthWriteEnable = VK_TRUE;
			_depthStencil.depthCompareOp = _depthStencil.depthTestEnable ? VK_COMPARE_OP_LESS_OR_EQUAL : VK_COMPARE_OP_ALWAYS;
			_depthStencil.depthBoundsTestEnable = VK_FALSE;
			_depthStencil.minDepthBounds = 0.0f; // Optional
			_depthStencil.maxDepthBounds = 1.0f; // Optional
			_depthStencil.stencilTestEnable = VK_FALSE;
		}

		//disables depth testing
		inline void SetPipelineSetting_DepthStencilState_DisableDepthTesting()
		{
			_depthStencil.depthTestEnable = VK_FALSE;
			_depthStencil.depthWriteEnable = VK_FALSE;
			_depthStencil.depthCompareOp = VK_COMPARE_OP_NEVER;
			_depthStencil.depthBoundsTestEnable = VK_FALSE;
			_depthStencil.stencilTestEnable = VK_FALSE;
			_depthStencil.front = {};
			_depthStencil.back = {};
			_depthStencil.minDepthBounds = 0.f;
			_depthStencil.maxDepthBounds = 1.f;
		}

		//sets defaults for shader stages
		inline void SetPipelineSettingToDefault_ShaderStages()
		{
			_shaderStages = {};
		}

		//resets the entire pipeline settings to defaults
		inline void SetPipelineSettingToDefault_All()
		{
			SetPipelineSettingToDefault_InputAssemblyState();
			SetPipelineSettingToDefault_RasterizerState();
			SetPipelineSettingToDefault_MultisampleState();
			SetPipelineSettingToDefault_ColorBlendAttachmentState();
			SetPipelineSettingToDefault_DepthStencilState();
			SetPipelineSettingToDefault_VertexInputState();
			SetPipelineSettingToDefault_ShaderStages();
		}
	};
}