//
// Created by Andromeda on 03/02/2022.
//

#include "Pipeline.h"

#include <fstream>
#include <iostream>
#include <cassert>

namespace sy
{
    Pipeline::Pipeline(Device& pDevice,const std::string& pVertFilePath, const std::string& pFragFilePath,
                       const PipelineConfigInfo& pConfig)
    : mDevice(pDevice)
    {
        CreateGraphicsPipeline(pVertFilePath, pFragFilePath, pConfig);
    }

    Pipeline::~Pipeline() {
        vkDestroyShaderModule(mDevice.device(), mVertShaderModule, nullptr);
        vkDestroyShaderModule(mDevice.device(), mFragShaderModule, nullptr);

        vkDestroyPipeline(mDevice.device(), mGraphicsPipeline, nullptr);
    }

    void Pipeline::CreateGraphicsPipeline(const std::string &pVertFilePath, const std::string &pFragFilePath,
                                          const PipelineConfigInfo& pConfig )
    {
        assert(pConfig.PipelineLayout != VK_NULL_HANDLE && "Cannot create graphics pipeline :: No PipelineLayout provided in ConfigInfo");
        assert(pConfig.RenderPass != VK_NULL_HANDLE && "Cannot create graphics pipeline :: No RenderPass provided in ConfigInfo");

        auto vert_code = ReadFile(pVertFilePath);
        auto frag_code = ReadFile(pFragFilePath);

        CreateShaderModule(vert_code, &mVertShaderModule);
        CreateShaderModule(frag_code, &mFragShaderModule);

        VkPipelineShaderStageCreateInfo shader_stages[2];

        shader_stages[0].sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
        shader_stages[0].stage = VK_SHADER_STAGE_VERTEX_BIT;
        shader_stages[0].module = mVertShaderModule;
        shader_stages[0].pName = "main";
        shader_stages[0].flags = 0;
        shader_stages[0].pNext = nullptr;
        shader_stages[0].pSpecializationInfo = nullptr;

        shader_stages[1].sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
        shader_stages[1].stage = VK_SHADER_STAGE_FRAGMENT_BIT;
        shader_stages[1].module = mFragShaderModule;
        shader_stages[1].pName = "main";
        shader_stages[1].flags = 0;
        shader_stages[1].pNext = nullptr;
        shader_stages[1].pSpecializationInfo = nullptr;

        VkPipelineVertexInputStateCreateInfo vertex_input_info{};
        vertex_input_info.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
        vertex_input_info.vertexAttributeDescriptionCount = 0;
        vertex_input_info.vertexBindingDescriptionCount = 0;
        vertex_input_info.pVertexAttributeDescriptions = nullptr;
        vertex_input_info.pVertexBindingDescriptions = nullptr;

        VkPipelineViewportStateCreateInfo viewport_info {};
        viewport_info.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
        viewport_info.viewportCount = 1;
        viewport_info.pViewports = &pConfig.Viewport;
        viewport_info.scissorCount = 1;
        viewport_info.pScissors = &pConfig.Scissor;

        VkGraphicsPipelineCreateInfo pipeline_info{};
        pipeline_info.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
        pipeline_info.stageCount = 2;
        pipeline_info.pStages = shader_stages;
        pipeline_info.pVertexInputState = &vertex_input_info;
        pipeline_info.pInputAssemblyState = &pConfig.InputAssemblyInfo;
        pipeline_info.pViewportState = &viewport_info;
        pipeline_info.pRasterizationState = &pConfig.RasterizationInfo;
        pipeline_info.pMultisampleState = &pConfig.MultisampleInfo;
        pipeline_info.pColorBlendState = &pConfig.ColorBlendInfo;
        pipeline_info.pDepthStencilState = &pConfig.DepthStencilInfo;
        pipeline_info.pDynamicState = nullptr;

        pipeline_info.layout = pConfig.PipelineLayout;
        pipeline_info.renderPass = pConfig.RenderPass;
        pipeline_info.subpass = pConfig.Subpass;

        pipeline_info.basePipelineIndex = -1;
        pipeline_info.basePipelineHandle = VK_NULL_HANDLE;

        if (vkCreateGraphicsPipelines(mDevice.device(), VK_NULL_HANDLE, 1, &pipeline_info, nullptr, &mGraphicsPipeline) != VK_SUCCESS)
        {
            throw std::runtime_error("Failed to create Graphics pipeline");
        }
    }

    void Pipeline::CreateShaderModule(const std::vector<char> &pShaderCode, VkShaderModule *pShaderModule)
    {
        VkShaderModuleCreateInfo CreateInfo{};
        CreateInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
        CreateInfo.codeSize = pShaderCode.size();
        CreateInfo.pCode = reinterpret_cast<const uint32_t*>(pShaderCode.data());

        if (vkCreateShaderModule(mDevice.device(), &CreateInfo, nullptr, pShaderModule) != VK_SUCCESS)
        {
            throw std::runtime_error("Failed to create Shader Module");
        }
    }

    PipelineConfigInfo Pipeline::DefaultPipelineInfo(uint32_t pWidth, uint32_t pHeight)
    {
        PipelineConfigInfo ConfigInfo{};

        ConfigInfo.InputAssemblyInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
        ConfigInfo.InputAssemblyInfo.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
        ConfigInfo.InputAssemblyInfo.primitiveRestartEnable = VK_FALSE;

        ConfigInfo.Viewport.x = 0.0f;
        ConfigInfo.Viewport.y = 0.0f;
        ConfigInfo.Viewport.width = static_cast<float>(pWidth);
        ConfigInfo.Viewport.height = static_cast<float>(pHeight);
        ConfigInfo.Viewport.minDepth = 0.0f;
        ConfigInfo.Viewport.maxDepth = 1.0f;

        ConfigInfo.Scissor.offset = {0,0};
        ConfigInfo.Scissor.extent = {pWidth, pHeight};

        ConfigInfo.RasterizationInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
        ConfigInfo.RasterizationInfo.depthClampEnable = VK_FALSE;
        ConfigInfo.RasterizationInfo.rasterizerDiscardEnable = VK_FALSE;
        ConfigInfo.RasterizationInfo.polygonMode = VK_POLYGON_MODE_FILL;
        ConfigInfo.RasterizationInfo.lineWidth = 1.0f;
        ConfigInfo.RasterizationInfo.cullMode = VK_CULL_MODE_NONE;
        ConfigInfo.RasterizationInfo.frontFace = VK_FRONT_FACE_CLOCKWISE;
        ConfigInfo.RasterizationInfo.depthBiasEnable = VK_FALSE;
        ConfigInfo.RasterizationInfo.depthBiasConstantFactor = 0.0f;  // Optional
        ConfigInfo.RasterizationInfo.depthBiasClamp = 0.0f;           // Optional
        ConfigInfo.RasterizationInfo.depthBiasSlopeFactor = 0.0f;     // Optional

        ConfigInfo.MultisampleInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
        ConfigInfo.MultisampleInfo.sampleShadingEnable = VK_FALSE;
        ConfigInfo.MultisampleInfo.rasterizationSamples = VK_SAMPLE_COUNT_1_BIT;
        ConfigInfo.MultisampleInfo.minSampleShading = 1.0f;           // Optional
        ConfigInfo.MultisampleInfo.pSampleMask = nullptr;             // Optional
        ConfigInfo.MultisampleInfo.alphaToCoverageEnable = VK_FALSE;  // Optional
        ConfigInfo.MultisampleInfo.alphaToOneEnable = VK_FALSE;       // Optional

        ConfigInfo.ColorBlendAttachment.colorWriteMask =
                VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT |
                VK_COLOR_COMPONENT_A_BIT;
        ConfigInfo.ColorBlendAttachment.blendEnable = VK_FALSE;
        ConfigInfo.ColorBlendAttachment.srcColorBlendFactor = VK_BLEND_FACTOR_ONE;   // Optional
        ConfigInfo.ColorBlendAttachment.dstColorBlendFactor = VK_BLEND_FACTOR_ZERO;  // Optional
        ConfigInfo.ColorBlendAttachment.colorBlendOp = VK_BLEND_OP_ADD;              // Optional
        ConfigInfo.ColorBlendAttachment.srcAlphaBlendFactor = VK_BLEND_FACTOR_ONE;   // Optional
        ConfigInfo.ColorBlendAttachment.dstAlphaBlendFactor = VK_BLEND_FACTOR_ZERO;  // Optional
        ConfigInfo.ColorBlendAttachment.alphaBlendOp = VK_BLEND_OP_ADD;              // Optional

        ConfigInfo.ColorBlendInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
        ConfigInfo.ColorBlendInfo.logicOpEnable = VK_FALSE;
        ConfigInfo.ColorBlendInfo.logicOp = VK_LOGIC_OP_COPY;  // Optional
        ConfigInfo.ColorBlendInfo.attachmentCount = 1;
        ConfigInfo.ColorBlendInfo.pAttachments = &ConfigInfo.ColorBlendAttachment;
        ConfigInfo.ColorBlendInfo.blendConstants[0] = 0.0f;  // Optional
        ConfigInfo.ColorBlendInfo.blendConstants[1] = 0.0f;  // Optional
        ConfigInfo.ColorBlendInfo.blendConstants[2] = 0.0f;  // Optional
        ConfigInfo.ColorBlendInfo.blendConstants[3] = 0.0f;  // Optional

        ConfigInfo.DepthStencilInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO;
        ConfigInfo.DepthStencilInfo.depthTestEnable = VK_TRUE;
        ConfigInfo.DepthStencilInfo.depthWriteEnable = VK_TRUE;
        ConfigInfo.DepthStencilInfo.depthCompareOp = VK_COMPARE_OP_LESS;
        ConfigInfo.DepthStencilInfo.depthBoundsTestEnable = VK_FALSE;
        ConfigInfo.DepthStencilInfo.minDepthBounds = 0.0f;  // Optional
        ConfigInfo.DepthStencilInfo.maxDepthBounds = 1.0f;  // Optional
        ConfigInfo.DepthStencilInfo.stencilTestEnable = VK_FALSE;
        ConfigInfo.DepthStencilInfo.front = {};  // Optional
        ConfigInfo.DepthStencilInfo.back = {};   // Optional

        return ConfigInfo;
    }

    std::vector<char> Pipeline::ReadFile(const std::string &pFilePath)
    {
        std::ifstream file(pFilePath, std::ios::ate | std::ios::binary);

        if (!file.is_open())
        {
            throw std::runtime_error("Failed to open file: " + pFilePath);
        }

        size_t file_size = static_cast<size_t>(file.tellg());
        std::vector<char> buffer(file_size);

        file.seekg(0);
        file.read(buffer.data(), file_size);

        file.close();
        return buffer;
    }

    void Pipeline::Bind(VkCommandBuffer pCommandBuffer) {
        vkCmdBindPipeline(pCommandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, mGraphicsPipeline);
    }
}