//build implementation for VMA Allocator

#define VK_NO_PROTOTYPES
#define VOLK_IMPLEMENTATION
#include "../Volk/volk.h"
#include <VkBootstrapDispatch.h>

#define VMA_IMPLEMENTATION
#include <vk_mem_alloc.h>