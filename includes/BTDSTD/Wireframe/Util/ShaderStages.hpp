#pragma once

//defines shader stages

#include <volk.h>

namespace Wireframe::Shader::Util
{
	//defines the shader stages
	enum class ShaderStage
	{
		Vertex = VK_SHADER_STAGE_VERTEX_BIT,
		Fragment = VK_SHADER_STAGE_FRAGMENT_BIT,
		Vertex_Fragment = VK_SHADER_STAGE_VERTEX_BIT | VK_SHADER_STAGE_FRAGMENT_BIT
	};
}