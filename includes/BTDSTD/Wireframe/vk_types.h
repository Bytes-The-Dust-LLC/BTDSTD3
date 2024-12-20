﻿// vulkan_guide.h : Include file for standard system include files,
// or project specific include files.

#pragma once

//#include <vulkan/vulkan.h>
#define VK_NO_PROTOTYPES
//#define VK_VERSION_1_3
#include "../Volk/volk.h"
#include <vk_mem_alloc.h>

#include <iostream>

//we want to immediately abort when there is an error. In normal engines this would give an error message to the user, or perform a dump of state.
using namespace std;
#define VK_CHECK(x)                                                 \
	do                                                              \
	{                                                               \
		VkResult err = x;                                           \
		if (err)                                                    \
		{                                                           \
			std::cout <<"Detected Vulkan error: " << err << std::endl; \
			abort();                                                \
		}                                                           \
	} while (0)


//vulkan memory buffer
struct AllocatedBuffer {
	VkBuffer _buffer;
	VmaAllocation _allocation;
};

//vulkan image
struct AllocatedImage {
	VkImage _image;
	VmaAllocation _allocation;
};