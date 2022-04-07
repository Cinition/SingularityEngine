//
// Created by Andromeda on 03/02/2022.
//

#include <stdexcept>
#include "Window.h"

namespace sy
{
    Window::Window(int pWidth, int pHeight, std::string pWindowName)
    : mWidth(pWidth)
    , mHeight(pHeight)
    , mWindowName(pWindowName)
    {
        InitWindow();
    }

    Window::~Window()
    {
        glfwDestroyWindow(mWindow);
        glfwTerminate();
    }

    void Window::InitWindow()
    {
        glfwInit();
        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
        glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

        mWindow = glfwCreateWindow(mWidth, mHeight, mWindowName.c_str(), nullptr, nullptr);
    }

    void Window::CreateWindowSurface(VkInstance pInstance, VkSurfaceKHR *pSurface)
    {
        if (glfwCreateWindowSurface(pInstance, mWindow, nullptr, pSurface) != VK_SUCCESS)
        {
            throw std::runtime_error("Failed to create window surface");
        }
    }
}