//
// Created by Andromeda on 03/02/2022.
//

#ifndef SINGULARITY_SINGULARITY_H
#define SINGULARITY_SINGULARITY_H

#include "Rendering/Device.h"
#include "Rendering/Pipeline.h"
#include "Rendering/SwapChain.h"
#include "Window.h"

#include <memory>

namespace sy
{
    class Singularity {

    public:

        static constexpr int WIDTH = 800;
        static constexpr int HEIGHT = 600;

        Singularity();
        ~Singularity();

        Singularity(const Singularity &) = delete;
        Singularity &operator=(const Singularity &) = delete;

        void Update();

    private:

        void CreatePipelineLayout();
        void CreatePipeline();
        void CreateCommandBuffer();
        void DrawFrame();

        Window mWindow{WIDTH, HEIGHT, "Hello Vulkan!"};

        Device mDevice {mWindow};

        SwapChain mSwapChain { mDevice, mWindow.GetExtent()};

        std::unique_ptr<Pipeline> mPipeline;

        VkPipelineLayout mPipelineLayout;

        std::vector<VkCommandBuffer> mCommandBuffers;
    };
}



#endif //SINGULARITY_SINGULARITY_H
