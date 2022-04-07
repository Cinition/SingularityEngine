//
// Created by Andromeda on 03/02/2022.
//

#ifndef SINGULARITY_PIPELINE_H
#define SINGULARITY_PIPELINE_H

#include "Device.h"
#include <string>
#include <vector>

namespace sy
{
    struct PipelineConfigInfo {
        VkViewport Viewport;
        VkRect2D Scissor;
        VkPipelineInputAssemblyStateCreateInfo InputAssemblyInfo;
        VkPipelineRasterizationStateCreateInfo RasterizationInfo;
        VkPipelineMultisampleStateCreateInfo MultisampleInfo;
        VkPipelineColorBlendAttachmentState ColorBlendAttachment;
        VkPipelineColorBlendStateCreateInfo ColorBlendInfo;
        VkPipelineDepthStencilStateCreateInfo DepthStencilInfo;
        VkPipelineLayout PipelineLayout = NULL;
        VkRenderPass RenderPass = NULL;
        uint32_t Subpass = NULL;
    };

    class Pipeline {

    public:

        Pipeline(Device& pDevice,const std::string& pVertFilePath, const std::string& pFragFilePath, const PipelineConfigInfo& pConfig);

        ~Pipeline();

        Pipeline(const Pipeline&) = delete;
        void operator=(const Pipeline&) = delete;

        void Bind(VkCommandBuffer pCommandBuffer);

        static PipelineConfigInfo DefaultPipelineInfo(uint32_t pWidth, uint32_t pHeight);

    private:

        static std::vector<char> ReadFile(const std::string& pFilePath);

        void CreateGraphicsPipeline(const std::string& pVertFilePath, const std::string& pFragFilePath, const PipelineConfigInfo& pConfig );

        void CreateShaderModule(const std::vector<char>& pShaderCode, VkShaderModule* pShaderModule);

        Device& mDevice;
        VkPipeline mGraphicsPipeline;
        VkShaderModule mVertShaderModule;
        VkShaderModule mFragShaderModule;
    };
}


#endif //SINGULARITY_PIPELINE_H
