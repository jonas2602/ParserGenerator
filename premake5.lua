workspace "ParserGenerator"
	architecture "x64"

	configurations
	{
		"Debug",
		"Release"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "ParserCore"
	location "ParserCore"
	kind "SharedLib"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files 
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs 
	{
	
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"PARSER_BUILD_DLL",
			"_WINDLL"
		}

		postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Calculator"),
			("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/ParserGenerator")
		}

	filter "configurations:Debug"
		defines ""
		symbols "On"

	filter "configurations:Release"
		defines ""
		optimize "On"

	filter { "system:windows", "configurations:Release" }
		buildoptions "/MT"



project "ParserGenerator"
	location "ParserGenerator"
	kind "ConsoleApp"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files 
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/src/**.g"
	}

	includedirs 
	{
		"ParserCore/src"
	}

	links
	{
		"ParserCore"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"_WINDLL"
		}

	filter "configurations:Debug"
		defines ""
		symbols "On"

	filter "configurations:Release"
		defines ""
		optimize "On"

	filter { "system:windows", "configurations:Release" }
		buildoptions "/MT"



project "Calculator"
	location "Calculator"
	kind "ConsoleApp"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files 
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/src/**.g"
	}

	includedirs
	{
		"ParserCore/src"
	}

	links
	{
		"ParserCore"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"_WINDLL"
		}

	filter "configurations:Debug"
		defines ""
		symbols "On"

	filter "configurations:Release"
		defines ""
		optimize "On"

	filter { "system:windows", "configurations:Release" }
		buildoptions "/MT"