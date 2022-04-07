workspace "SingularityEngine"

    configurations { "Debug" }
    platforms { "x64" }
    libdirs { "./lib/*" }
	startproject "SingularityEngine"

    -- Main Project
    project "SingularityEngine"
        kind "ConsoleApp"
        language "C++"
        location "./build"
        targetdir "./build"
    
        files { "./src/**.h", "./src/**.cpp" }

        links { "$(VULKAN_SDK)/lib/vulkan-1.lib", "glfw3" }

        includedirs { "$(VULKAN_SDK)/include" }

        sysincludedirs { "./include/*" }

        filter "configurations:Debug"
            defines { "DEBUG" }
            symbols "On"
            optimize "Debug"
