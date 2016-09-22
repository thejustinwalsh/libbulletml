newoption {
  trigger     = "with-tests",
  description = "Include test suite in project files",
}

-- Workspace
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


-- Static Library
project "libbulletml"
  kind "StaticLib"
  language "C++"
  targetdir "bin/%{cfg.buildcfg}"

  includedirs { "include", "src" }

  files { "include/**.h", "src/**.h", "src/**.cpp" }


-- Dynamic Library
project "libbulletml-shared"
  kind "SharedLib"
  language "C++"
  targetdir "bin/%{cfg.buildcfg}"

  defines { "BULLETML_SHARED_LIB" }

  includedirs { "include", "src" }

  files { "include/**.h", "src/**.h", "src/**.cpp" }


-- Test Suite (googletest)
if (_OPTIONS["with-tests"]) then
project "tests"
  kind "ConsoleApp"
  language "C++"
  targetdir "bin/%{cfg.buildcfg}"

  includedirs { "include", "vendor/googletest/googletest/include", "vendor/googletest/googletest" }

  files { "tests/**.cpp", "vendor/googletest/googletest/src/gtest_main.cc", "vendor/googletest/googletest/src/gtest-all.cc" }

  links { "libbulletml" }
end
