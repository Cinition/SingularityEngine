//
// Created by Andromeda on 03/02/2022.
//

#ifndef SINGULARITY_WINDOW_H
#define SINGULARITY_WINDOW_H

#define GLFW_INCLUDE_VULKAN

#include <string>
#include <glfw3.h>

namespace sy
{
    class Window {

    public:

        Window(int pWidth, int pHeight, std::string pWindowName);
        ~Window();

        Window(const Window &) = delete;
        Window &operator=(const Window &) = delete;

        bool ShouldClose() { return glfwWindowShouldClose(mWindow); }
        VkExtent2D GetExtent() { return {static_cast<uint32_t>(mWidth), static_cast<uint32_t>(mHeight)}; }

        void CreateWindowSurface(VkInstance pInstance, VkSurfaceKHR* pSurface);

    private:

        void InitWindow();

        const int mWidth;
        const int mHeight;

        std::string mWindowName;

        GLFWwindow* mWindow;

    };
}

#endif //SINGULARITY_WINDOW_H
