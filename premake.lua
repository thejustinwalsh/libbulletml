workspace "BulletML"
  configurations { "Debug", "Release" }

  filter { "action:xcode*" }
    xcodebuildsettings {
      ["CLANG_CXX_LANGUAGE_STANDARD"] = "c++11",
      ["CLANG_CXX_LIBRARY"] = "libc++"
    }

  filter { "action:gmake*" }
    flags { "C++11" }

  filter "configurations:Debug"
     defines { "DEBUG" }
     flags { "Symbols" }

  filter "configurations:Release"
     defines { "NDEBUG" }
     optimize "On"


project "libbulletml"
  kind "StaticLib"
  language "C++"
  targetdir "bin/%{cfg.buildcfg}"

  includedirs { "src" }

  files { "src/**.h", "src/**.cpp" }
