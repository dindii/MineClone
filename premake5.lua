workspace "MineCloneProject"
		architecture "x64"
		startproject "SandBox"


configurations
{
	"Debug",
	"Release",
	"Dist"
}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "MineCloneProject"
	location "MineCloneProject"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir("bin/" .. outputdir .. "/%{prj.name}")
	objdir("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "mcpch.h"
	pchsource "MineCloneProject/src/mcpch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"%{prj.name}/src"
	}
	
	filter "system:windows"
	systemversion "latest"

	defines
	{
		"MC_PLATFORM_WINDOWS"
		--Maybe i turn it on multiplatform someday, who knows?
	}

	filter "configurations:Debug"
	defines "MC_DEBUG"
	runtime "Debug"
	symbols "on"

	filter "configurations:Release"
	defines "MC_RELEASE"
	runtime "Release"
	optimize "Debug"

	filter "configurations:Dist"
	defines "MC_DIST"
	runtime "Release"
	symbols "Off"
	optimize "Full"



	project "SandBox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir("bin/" .. outputdir .. "/%{prj.name}")
	objdir("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"%{prj.name}/src",
		"MineCloneProject/src"
	}

	links                      -- Linkamos a Engine no Sandbox também
      {
      	 --"MineCloneProject"
      }
	
	filter "system:windows"
	systemversion "latest"

	defines
	{
		"MC_PLATFORM_WINDOWS"
		--Maybe i turn it on multiplatform someday, who knows?
	}

	filter "configurations:Debug"
	defines "MC_DEBUG"
	runtime "Debug"
	symbols "on"

	filter "configurations:Release"
	defines "MC_RELEASE"
	runtime "Release"
	optimize "Debug"

	filter "configurations:Dist"
	defines "MC_DIST"
	runtime "Release"
	symbols "Off"
	optimize "Full"
	
	
