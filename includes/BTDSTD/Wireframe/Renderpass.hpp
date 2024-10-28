#pragma once

//defines render pass operations

#include <BTDSTD/Wireframe/Util/Subpass.hpp>
#include <BTDSTD/Wireframe/Core/GPU.hpp>

namespace Wireframe::Renderpass
{
	//defines a render pass create info
	struct Renderpass_CreateInfo
	{
		Wireframe::Util::Subpass::Subpass subpass;
		std::vector<Wireframe::Util::Subpass::SubpassDependency> dependencies;
		std::vector<Wireframe::Util::Attachment::Attachment> attachments;
	};

	//defines a render passs
	struct Renderpass
	{
		VkRenderPass _renderPass;

		VkSubpassDescription subpass_vulkan;
		std::vector<VkSubpassDependency> deps;
		std::vector<VkAttachmentDescription> attachmentDescs;

		//creates a render pass
		inline bool Create(Renderpass_CreateInfo& info, Device::GPU* GPU)
		{
			//automatically generate dependency array
			const size_t depCount = info.dependencies.size();
			deps.clear(); deps.resize(depCount);
			for (size_t i = 0; i < depCount; ++i)
				deps[i] = info.dependencies[i].GenerateVulkanSubpassDependency();

			//automatically generated by index in the attachment
			const size_t attachmentCount = info.attachments.size();
			attachmentDescs.clear(); attachmentDescs.resize(attachmentCount);
			for (size_t i = 0; i < attachmentCount; ++i)
				attachmentDescs[info.attachments[i].attachmentIndex] = info.attachments[i].GenerateVulkanAttachmentDescription();

			subpass_vulkan = info.subpass.GenerateVulkanSubpassDescription();

			VkRenderPassCreateInfo render_pass_info = {};
			render_pass_info.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;

			render_pass_info.subpassCount = 1;
			render_pass_info.pSubpasses = &subpass_vulkan;

			render_pass_info.attachmentCount = attachmentCount;
			render_pass_info.pAttachments = attachmentDescs.data();

			render_pass_info.dependencyCount = depCount;
			render_pass_info.pDependencies = deps.data();

			VK_CHECK(vkCreateRenderPass(GPU->device, &render_pass_info, nullptr, &_renderPass));
		
			return true;
		}

		//destroys a render pass
		inline void Destroy(Device::GPU* GPU)
		{
			vkDestroyRenderPass(GPU->device, _renderPass, nullptr);
		}
	};

	//defines render operations
	namespace RenderOperation
	{
		//defines the data of a render pass
		struct RenderPassData
		{
			VkOffset2D renderOffset = { 0, 0 };
			VkExtent2D renderSize = { 1, 1 };

			float depth = 1.0f;
			uint32_t stencil = 0;

			VkClearColorValue clearColor = { { 0.0f, 0.0f, 0.0f, 1.0f } };
		};

		//starts a content inlined render pass
		static inline void StartRenderPass_InlinedContent(VkCommandBuffer& cmd, VkRenderPass renderpass, VkFramebuffer framebuffer,
			const RenderPassData& renderpassData)
		{
			VkRenderPassBeginInfo info = {};
			info.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
			info.pNext = nullptr;

			info.renderArea.extent = renderpassData.renderSize;
			info.renderArea.offset = renderpassData.renderOffset;

			info.clearValueCount = 2;
			VkClearValue clearValue; clearValue.color = renderpassData.clearColor;
			VkClearValue depthClear; depthClear.depthStencil.depth = renderpassData.depth; depthClear.depthStencil.stencil = renderpassData.stencil;
			VkClearValue clearValues[] = { clearValue, depthClear };
			info.pClearValues = clearValues;

			info.renderPass = renderpass;
			info.framebuffer = framebuffer;

			vkCmdBeginRenderPass(cmd, &info, VK_SUBPASS_CONTENTS_INLINE);
		}

		//ends a render pass
		static inline void EndRenderPass(VkCommandBuffer& cmd) { vkCmdEndRenderPass(cmd); }
	}
}