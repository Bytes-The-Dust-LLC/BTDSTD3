#pragma once

//defines a serilize for the pipeline settings

#include <BTDSTD/Wireframe/Pipeline/PipelineSettings.hpp>
#include <BTDSTD/Formats/json.hpp>
#include <BTDSTD/IO/File.hpp>

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

		VkPipelineDepthStencilStateCreateInfo _depthStencil = {};
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

	/*loads pipeline settings from a JSON object || does not do viewport, scissor, shaders, or vertex input as thoses are not needed to be stored commonly
	scissor and viewport are set dynamically
	vertex input is set by Smok but also specific to any engine or renderer needing to set up pipelines
	shaders have their own JSON setting files, theses are seprate and also depend on the vertex input or extra stuff we don't want to cover in this file
	*/
	inline bool ConvertJSONToPipelineSettings(const nlohmann::json& json, PipelineSettings& settings)
	{
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
		settings._depthStencil.depthWriteEnable =json["depthStencil_depthWriteEnable"];
		settings._depthStencil.depthCompareOp = json["depthStencil_depthCompareOp"];
		settings._depthStencil.depthBoundsTestEnable = json["depthStencil_depthBoundsTestEnable"];
		settings._depthStencil.stencilTestEnable = json["depthStencil_stencilTestEnable"];

		settings._depthStencil.front.failOp = json["depthStencil_front"]["depthStencil_front_failOp"];
		settings._depthStencil.front.passOp = json["depthStencil_front"]["depthStencil_front_passOp"];
		settings._depthStencil.front.depthFailOp = json["depthStencil_front"]["depthStencil_front_depthFailOp"];
		settings._depthStencil.front.compareOp = json["depthStencil_front"]["depthStencil_front_compareOP"];
		settings._depthStencil.front.compareMask = json["depthStencil_front"]["depthStencil_front_compareMask"];
		settings._depthStencil.front.writeMask = json["depthStencil_front"]["depthStencil_front_writeMask"];
		settings._depthStencil.front.reference = json["depthStencil_front"]["depthStencil_front_reference"];

		settings._depthStencil.back.failOp = json["depthStencil_back"]["depthStencil_back_failOp"];
		settings._depthStencil.back.passOp = json["depthStencil_back"]["depthStencil_back_passOp"];
		settings._depthStencil.back.depthFailOp = json["depthStencil_back"]["depthStencil_back_depthFailOp"];
		settings._depthStencil.back.compareOp = json["depthStencil_back"]["depthStencil_back_compareOP"];
		settings._depthStencil.back.compareMask = json["depthStencil_back"]["depthStencil_back_compareMask"];
		settings._depthStencil.back.writeMask = json["depthStencil_back"]["depthStencil_back_writeMask"];
		settings._depthStencil.back.reference = json["depthStencil_back"]["depthStencil_back_reference"];

		settings._depthStencil.minDepthBounds = json["depthStencil_minDepthBounds"];
		settings._depthStencil.maxDepthBounds = json["depthStencil_maxDepthBounds"];

		return true;
	}

	//returns the file extension for a pipeline settings file
	static inline std::string GetPipelineSettingExtentionStr(){return "btdpipelinesettings";}

	/*writes pipeline settings to a data file || does not do viewport, scissor, shaders, or vertex input as thoses are not needed to be stored commonly
	scissor and viewport are set dynamically
	vertex input is set by Smok but also specific to any engine or renderer needing to set up pipelines
	shaders have their own JSON setting files, theses are seprate and also depend on the vertex input or extra stuff we don't want to cover in this file
	*/
	inline bool WritePipelineSettingsDataToFile(const BTD::IO::FileInfo& settingsFile, const PipelineSettings& data)
	{
		//checks if the file has the right extension, if not throw a warning and add it ourself
		BTD::IO::FileInfo f = settingsFile;
		if (settingsFile.extension != GetPipelineSettingExtentionStr())
		{
			fmt::print("Wireframe Pipeline Settings Warning: Serilize || WritePipelineSettingsDataToFile || \"{}\" does not end in .{}, this is the file extension for Wireframe Pipeline Setting files. This warning can be ignored as we will add the extension. But to make it go away, add it to your file. The PipelineSettingsSerilize header file contains a static funtion for getting the correct file extension.\n",
				settingsFile.absolutePath, GetPipelineSettingExtentionStr());

			//if we need a period
			if (settingsFile.absolutePath[settingsFile.absolutePath.size() - 1] != '.')
				f = BTD::IO::FileInfo(settingsFile.absolutePath + "." + GetPipelineSettingExtentionStr());
			else
				f = BTD::IO::FileInfo(settingsFile.absolutePath + GetPipelineSettingExtentionStr());
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
				settingsFile.absolutePath, GetPipelineSettingExtentionStr());
			return false;
		}

		//parse JSON object and load data
		ConvertJSONToPipelineSettings(nlohmann::json::parse(BTD::IO::File::ReadWholeTextFile(settingsFile).data), data);

		return true;
	}
}