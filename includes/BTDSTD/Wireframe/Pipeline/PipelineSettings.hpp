#pragma once

//defines pipeline settings

#include <BTDSTD/Wireframe/Shader.hpp>

#include <BTDSTD/Formats/json.hpp>
#include <BTDSTD/IO/File.hpp>

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

namespace Wireframe::Pipeline::Serilize
{
	/*converts pipeline settings to a JSON object || does not do viewport, scissor, shaders, or vertex input as thoses are not needed to be stored commonly
	scissor and viewport are set dynamically
	vertex input is set by Smok but also specific to any engine or renderer needing to set up pipelines
	shaders have their own JSON setting files, theses are seprate and also depend on the vertex input or extra stuff we don't want to cover in this file
	*/
	inline bool ConvertPipelineSettingsToJSON(nlohmann::json& json, const PipelineSettings& settings)
	{
		json["inputASM_topology"] = (uint32_t)settings._inputAssembly.topology;
		json["inputASM_primitiveRestartEnable"] = settings._inputAssembly.primitiveRestartEnable;

		json["rasterizer_depthClampEnable"] = settings._rasterizer.depthClampEnable;
		json["rasterizer_rasterizerDiscardEnable"] = settings._rasterizer.rasterizerDiscardEnable;
		json["rasterizer_polygonMode"] = (uint32_t)settings._rasterizer.polygonMode;
		json["rasterizer_cullMode"] = (uint32_t)settings._rasterizer.cullMode;
		json["rasterizer_frontFace"] = (uint32_t)settings._rasterizer.frontFace;
		json["rasterizer_depthBiasEnable"] = settings._rasterizer.depthBiasEnable;
		json["rasterizer_depthBiasConstantFactor"] = settings._rasterizer.depthBiasConstantFactor;
		json["rasterizer_depthBiasClamp"] = settings._rasterizer.depthBiasClamp;
		json["rasterizer_depthBiasSlopeFactor"] = settings._rasterizer.depthBiasSlopeFactor;
		json["rasterizer_lineWidth"] = settings._rasterizer.lineWidth;

		json["colorBlendAtt_blendEnable"] = settings._colorBlendAttachment.blendEnable;
		json["colorBlendAtt_srcColorBlendFactor"] = (uint32_t)settings._colorBlendAttachment.srcColorBlendFactor;
		json["colorBlendAtt_dstColorBlendFactor"] = (uint32_t)settings._colorBlendAttachment.dstColorBlendFactor;
		json["colorBlendAtt_colorBlendOp"] = (uint32_t)settings._colorBlendAttachment.colorBlendOp;
		json["colorBlendAtt_srcAlphaBlendFactor"] = (uint32_t)settings._colorBlendAttachment.srcAlphaBlendFactor;
		json["colorBlendAtt_dstAlphaBlendFactor"] = (uint32_t)settings._colorBlendAttachment.dstAlphaBlendFactor;
		json["colorBlendAtt_alphaBlendOp"] = (uint32_t)settings._colorBlendAttachment.alphaBlendOp;
		json["colorBlendAtt_colorWriteMask"] = (uint32_t)settings._colorBlendAttachment.colorWriteMask;

		json["multisample_rasterizationSampleCount"] = (uint32_t)settings._multisampling.rasterizationSamples;
		json["multisample_sampleShadingEnable"] = settings._multisampling.sampleShadingEnable;
		json["multisample_minSampleShading"] = settings._multisampling.minSampleShading;
		json["multisample_alphaToCoverageEnable"] = settings._multisampling.alphaToCoverageEnable;
		json["multisample_alphaToOneEnable"] = settings._multisampling.alphaToOneEnable;

		json["depthStencil_depthTestEnable"] = settings._depthStencil.depthTestEnable;
		json["depthStencil_depthWriteEnable"] = settings._depthStencil.depthWriteEnable;
		json["depthStencil_depthCompareOp"] = (uint32_t)settings._depthStencil.depthCompareOp;
		json["depthStencil_depthBoundsTestEnable"] = settings._depthStencil.depthBoundsTestEnable;
		json["depthStencil_stencilTestEnable"] = settings._depthStencil.stencilTestEnable;

		json["depthStencil_front"] = {
			json["depthStencil_front_failOp"] = (uint32_t)settings._depthStencil.front.failOp,
			json["depthStencil_front_passOp"] = (uint32_t)settings._depthStencil.front.passOp,
			json["depthStencil_front_depthFailOp"] = (uint32_t)settings._depthStencil.front.depthFailOp,
			json["depthStencil_front_compareOp"] = (uint32_t)settings._depthStencil.front.compareOp,
			json["depthStencil_front_compareMask"] = settings._depthStencil.front.compareMask,
			json["depthStencil_front_writeMask"] = settings._depthStencil.front.writeMask,
			json["depthStencil_front_reference"] = settings._depthStencil.front.reference
		};

		json["depthStencil_back"] = {
			json["depthStencil_back_failOp"] = (uint32_t)settings._depthStencil.back.failOp,
			json["depthStencil_back_passOp"] = (uint32_t)settings._depthStencil.back.passOp,
			json["depthStencil_back_depthFailOp"] = (uint32_t)settings._depthStencil.back.depthFailOp,
			json["depthStencil_back_compareOp"] = (uint32_t)settings._depthStencil.back.compareOp,
			json["depthStencil_back_compareMask"] = settings._depthStencil.back.compareMask,
			json["depthStencil_back_writeMask"] = settings._depthStencil.back.writeMask,
			json["depthStencil_back_reference"] = settings._depthStencil.back.reference
		};

		json["depthStencil_minDepthBounds"] = settings._depthStencil.minDepthBounds;
		json["depthStencil_maxDepthBounds"] = settings._depthStencil.maxDepthBounds;

		return true;
	}

	/*loads pipeline settings from a JSON object, THIS DOES ZERO OUT THE PIPELINE SETTINGS FIRST || does not do viewport, scissor, shaders, or vertex input as thoses are not needed to be stored commonly
	scissor and viewport are set dynamically
	vertex input is set by Smok but also specific to any engine or renderer needing to set up pipelines
	shaders have their own JSON setting files, theses are seprate and also depend on the vertex input or extra stuff we don't want to cover in this file
	*/
	inline bool ConvertJSONToPipelineSettings(const nlohmann::json& json, PipelineSettings& settings)
	{
		settings.SetPipelineSettingToDefault_All(); //zeros out the pipeline

		settings._inputAssembly.topology = json["inputASM_topology"];
		settings._inputAssembly.primitiveRestartEnable = json["inputASM_primitiveRestartEnable"];

		settings._rasterizer.depthClampEnable = json["rasterizer_depthClampEnable"];
		settings._rasterizer.rasterizerDiscardEnable = json["rasterizer_rasterizerDiscardEnable"];
		settings._rasterizer.polygonMode = json["rasterizer_polygonMode"];
		settings._rasterizer.cullMode = json["rasterizer_cullMode"];
		settings._rasterizer.frontFace = json["rasterizer_frontFace"];
		settings._rasterizer.depthBiasEnable = json["rasterizer_depthBiasEnable"];
		settings._rasterizer.depthBiasConstantFactor = json["rasterizer_depthBiasConstantFactor"];
		settings._rasterizer.depthBiasClamp = json["rasterizer_depthBiasClamp"];
		settings._rasterizer.depthBiasSlopeFactor = json["rasterizer_depthBiasSlopeFactor"];
		settings._rasterizer.lineWidth = json["rasterizer_lineWidth"];

		settings._colorBlendAttachment.blendEnable = json["colorBlendAtt_blendEnable"];
		settings._colorBlendAttachment.srcColorBlendFactor = json["colorBlendAtt_srcColorBlendFactor"];
		settings._colorBlendAttachment.dstColorBlendFactor = json["colorBlendAtt_dstColorBlendFactor"];
		settings._colorBlendAttachment.colorBlendOp = json["colorBlendAtt_colorBlendOp"];
		settings._colorBlendAttachment.srcAlphaBlendFactor = json["colorBlendAtt_srcAlphaBlendFactor"];
		settings._colorBlendAttachment.dstAlphaBlendFactor = json["colorBlendAtt_dstAlphaBlendFactor"];
		settings._colorBlendAttachment.alphaBlendOp = json["colorBlendAtt_alphaBlendOp"];
		settings._colorBlendAttachment.colorWriteMask = json["colorBlendAtt_colorWriteMask"];

		settings._multisampling.rasterizationSamples = json["multisample_rasterizationSampleCount"];
		settings._multisampling.sampleShadingEnable = json["multisample_sampleShadingEnable"];
		settings._multisampling.minSampleShading = json["multisample_minSampleShading"];
		settings._multisampling.alphaToCoverageEnable = json["multisample_alphaToCoverageEnable"];
		settings._multisampling.alphaToOneEnable = json["multisample_alphaToOneEnable"];

		settings._depthStencil.depthTestEnable = json["depthStencil_depthTestEnable"];
		settings._depthStencil.depthWriteEnable = json["depthStencil_depthWriteEnable"];
		settings._depthStencil.depthCompareOp = json["depthStencil_depthCompareOp"];
		settings._depthStencil.depthBoundsTestEnable = json["depthStencil_depthBoundsTestEnable"];
		settings._depthStencil.stencilTestEnable = json["depthStencil_stencilTestEnable"];

		settings._depthStencil.front.failOp = json["depthStencil_front"][0];
		settings._depthStencil.front.passOp = json["depthStencil_front"][1];
		settings._depthStencil.front.depthFailOp = json["depthStencil_front"][2];
		settings._depthStencil.front.compareOp = json["depthStencil_front"][3];
		settings._depthStencil.front.compareMask = json["depthStencil_front"][4];
		settings._depthStencil.front.writeMask = json["depthStencil_front"][5];
		settings._depthStencil.front.reference = json["depthStencil_front"][6];

		settings._depthStencil.back.failOp = json["depthStencil_back"][0];
		settings._depthStencil.back.passOp = json["depthStencil_back"][1];
		settings._depthStencil.back.depthFailOp = json["depthStencil_back"][2];
		settings._depthStencil.back.compareOp = json["depthStencil_back"][3];
		settings._depthStencil.back.compareMask = json["depthStencil_back"][4];
		settings._depthStencil.back.writeMask = json["depthStencil_back"][5];
		settings._depthStencil.back.reference = json["depthStencil_back"][6];

		settings._depthStencil.minDepthBounds = json["depthStencil_minDepthBounds"];
		settings._depthStencil.maxDepthBounds = json["depthStencil_maxDepthBounds"];

		return true;
	}

	//returns the file extension for a pipeline settings file
	static inline std::string GetPipelineSettingExtentionStr() { return "btdpipelinesettings"; }

	/*writes pipeline settings to a data file || does not do viewport, scissor, shaders, or vertex input as thoses are not needed to be stored commonly
	scissor and viewport are set dynamically
	vertex input is set by Smok but also specific to any engine or renderer needing to set up pipelines
	shaders have their own JSON setting files, theses are seprate and also depend on the vertex input or extra stuff we don't want to cover in this file
	*/
	inline bool WritePipelineSettingsDataToFile(const BTD::IO::FileInfo& settingsFile, const PipelineSettings& data)
	{
		//checks if the file has the right extension, if not throw a warning and add it ourself
		BTD::IO::FileInfo f = settingsFile;
		const std::string p = settingsFile.GetPathStr();
		if (settingsFile.extension != GetPipelineSettingExtentionStr())
		{
			fmt::print("Wireframe Pipeline Settings Warning: Serilize || WritePipelineSettingsDataToFile || \"{}\" does not end in .{}, this is the file extension for Wireframe Pipeline Setting files. This warning can be ignored as we will add the extension. But to make it go away, add it to your file. The PipelineSettings header file contains a static funtion for getting the correct file extension.\n",
				p, GetPipelineSettingExtentionStr());

			//if we need a period
			if (p[p.size() - 1] != '.')
				f = BTD::IO::FileInfo(p + "." + GetPipelineSettingExtentionStr());
			else
				f = BTD::IO::FileInfo(p + GetPipelineSettingExtentionStr());
		}

		//build json and write to file
		nlohmann::json j; ConvertPipelineSettingsToJSON(j, data);
		BTD::IO::File::WriteWholeTextFile(f, j.dump());

		return true;
	}

	/*loads pipeline settings from a data file || does not do viewport, scissor, shaders, or vertex input as thoses are not needed to be stored commonly
	scissor and viewport are set dynamically
	vertex input is set by Smok but also specific to any engine or renderer needing to set up pipelines
	shaders have their own JSON setting files, theses are seprate and also depend on the vertex input or extra stuff we don't want to cover in this file
	*/
	inline bool LoadPipelineSettingsDataFromFile(const BTD::IO::FileInfo& settingsFile, PipelineSettings& data)
	{
		//checks if the file has the right extension, if not error out
		if (settingsFile.extension != GetPipelineSettingExtentionStr())
		{
			fmt::print("Wireframe Pipeline Settings Error: Serilize || LoadPipelineSettingsDataFromFile || \"{}\" does not end in .{}, this is the file extension for Wireframe Pipeline Setting files. We can not proove this is a valid Pipeline Settings file. Call \"WritePipelineSettingsDataFromFile\" to generate a proper file. If the file you are loading was made in a earlier version of the STD, please try updating the file with the newest functions.\n",
				settingsFile.GetPathStr(), GetPipelineSettingExtentionStr());
			return false;
		}

		//parse JSON object and load data
		ConvertJSONToPipelineSettings(nlohmann::json::parse(BTD::IO::File::ReadWholeTextFile(settingsFile).data), data);

		return true;
	}
}