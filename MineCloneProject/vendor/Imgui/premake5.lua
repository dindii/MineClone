project "ImGui"
    kind "StaticLib"
    language "C++"
	staticruntime "on"
    
    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    files
    {
        "imconfig.h",
        "imgui.h",
        "imgui.cpp",
        "imgui_draw.cpp",
        "imgui_internal.h",
        "imgui_widgets.cpp",
        "imstb_rectpack.h",
        "imstb_textedit.h",
        "imstb_truetype.h",
        "imgui_demo.cpp",
        "imgui_tables.cpp"
    }

    includedirs
    {
     "imgui"
    }
    
    filter "system:windows"
        systemversion "latest"
 
     defines
	 {
	 	 "MC_PLATFORM_WINDOWS"
	 }
 
     filter "configurations:Debug"
	 	defines "MC_DEBUG"
        runtime "Debug"
        symbols "on"               -- Deixamos on os debug symbols
        
     filter "configurations:Release"
	 	defines "MC_RELEASE"
        runtime "Release"
        optimize "on"            -- Ripamos todas as configurações de debug e otimizamos o projeto

     filter "configurations:Dist"
	 defines "MC_DIST"
	 runtime "Release"
	 symbols "Off"
	 optimize "Full"
