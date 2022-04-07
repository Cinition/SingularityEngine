//
// Created by Andromeda on 03/02/2022.
//

#include "Singularity.h"
#include "Misc/Console.h"
#include "Misc/String.h"
#include <stdexcept>

namespace sy
{
    Singularity::Singularity()
    {
        CreatePipelineLayout();
        CreatePipeline();
        CreateCommandBuffer();

        String test = String("Testing int: %f", 256.3253f);

        Log(test.ToChar());
    }

    Singularity::~Singularity()
    {
        vkDestroyPipelineLayout(mDevice.device(), mPipelineLayout, nullptr);
    }

    void Singularity::Update() {

        while (!mWindow.ShouldClose())
        {
            glfwPollEvents();
            DrawFrame();
        }

        vkDeviceWaitIdle(mDevice.device());
    }

    void Singularity::CreatePipelineLayout()
    {
        VkPipelineLayoutCreateInfo pipeline_layout_info{};
        pipeline_layout_info.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
        pipeline_layout_info.setLayoutCount = 0;
        pipeline_layout_info.pSetLayouts = nullptr;
        pipeline_layout_info.pushConstantRangeCount = 0;
        pipeline_layout_info.pPushConstantRanges = nullptr;

        if (vkCreatePipelineLayout(mDevice.device(), &pipeline_layout_info, nullptr, &mPipelineLayout) != VK_SUCCESS)
        {
            throw std::runtime_error("Failed to create pipeline layout");
        }
    }

    void Singularity::CreatePipeline()
    {
        auto pipeline_config = Pipeline::DefaultPipelineInfo(mSwapChain.width(), mSwapChain.height());
        pipeline_config.RenderPass = mSwapChain.getRenderPass();
        pipeline_config.PipelineLayout = mPipelineLayout;
        mPipeline = std::make_unique<Pipeline>(mDevice, "../src/Rendering/Shaders/SimpleShader.vert.spv", "../src/Rendering/Shaders/SimpleShader.frag.spv", pipeline_config);
    }

    void Singularity::CreateCommandBuffer()
    {
        mCommandBuffers.resize(mSwapChain.imageCount());

        VkCommandBufferAllocateInfo allocate_info{};
        allocate_info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
        allocate_info.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
        allocate_info.commandPool = mDevice.getCommandPool();
        allocate_info.commandBufferCount = static_cast<uint32_t>(mCommandBuffers.size());

        if (vkAllocateCommandBuffers(mDevice.device(), &allocate_info, mCommandBuffers.data()) != VK_SUCCESS)
        {
            throw std::runtime_error("Failed to allocate command buffers");
        }

        for (size_t i = 0; i < mCommandBuffers.size(); ++i) {
            VkCommandBufferBeginInfo begin_info{};
            begin_info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;

            if (vkBeginCommandBuffer(mCommandBuffers[i], &begin_info) != VK_SUCCESS)
            {
                throw std::runtime_error("Failed to begin recording command buffer");
            }

            VkRenderPassBeginInfo renderpass_info{};
            renderpass_info.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
            renderpass_info.renderPass = mSwapChain.getRenderPass();
            renderpass_info.framebuffer = mSwapChain.getFrameBuffer(i);

            renderpass_info.renderArea.offset = {0,0};
            renderpass_info.renderArea.extent = mSwapChain.getSwapChainExtent();

            VkClearValue testing[2];
            testing[0].color = { 0.1f,0.1f,0.1f,1.0f };
            testing[1].depthStencil = { 1.0f, 0 };
            renderpass_info.clearValueCount = 2;
            renderpass_info.pClearValues = testing;

            vkCmdBeginRenderPass(mCommandBuffers[i], &renderpass_info, VK_SUBPASS_CONTENTS_INLINE);

            mPipeline->Bind(mCommandBuffers[i]);
            vkCmdDraw(mCommandBuffers[i], 3, 1, 0, 0);

            vkCmdEndRenderPass(mCommandBuffers[i]);
            if (vkEndCommandBuffer(mCommandBuffers[i]) != VK_SUCCESS)
            {
                throw std::runtime_error("Failed to record command buffer");
            }
        }
    }

    void Singularity::DrawFrame()
    {
        uint32_t  image_index;
        auto result = mSwapChain.acquireNextImage(&image_index);

        if (result != VK_SUCCESS && result != VK_SUBOPTIMAL_KHR)
        {
            throw std::runtime_error("Failed to acquire swap chain image!");
        }

        result = mSwapChain.submitCommandBuffers(&mCommandBuffers[image_index], &image_index);
        if (result != VK_SUCCESS)
        {
            throw std::runtime_error("Failed to present swap chain image");
        }
    }
}


