#pragma once

//defines a overload for testing viewports and scissors

#include <vulkan/vulkan.h>

namespace Wireframe::Util
{
	//is the viewports the same
	inline bool IsViewportSame(const VkViewport& v1, const VkViewport& v2)
	{
		return (v1.height == v2.height && v1.width == v2.width && v1.x == v2.x && v1.y == v2.y &&
			v1.maxDepth == v2.maxDepth && v1.minDepth == v2.minDepth);
	}

	//is the scissors the same
	inline bool IsScissorSame(const VkRect2D& r1, const VkRect2D& r2)
	{
		return (r1.extent.width == r2.extent.width && r1.extent.width == r2.extent.width &&
			r1.offset.x == r2.offset.x && r1.offset.y == r2.offset.y);
	}
}