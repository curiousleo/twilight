local eigen3dir = "/usr/include/eigen3/"
local boostdir = "/usr/include/boost/"
local libtdir = "src/libtwilight/"
local tbindir = "src/twilightbin/"

solution "Twilight"
   configurations { "Debug", "Release" }
   location "build"
   targetname "twilight"
   targetdir "bin"
   buildoptions { "-std=c++0x" }
 
   project "TwilightBin"
      kind "ConsoleApp"
      language "C++"
      files { tbindir .. "**.hh", tbindir .. "**.cc" }
      includedirs { eigen3dir, boostdir, "src/" }
      links { "LibTwilight", "boost_program_options" }
 
      configuration "Debug"
         defines { "DEBUG" }
         flags { "Symbols" }
 
      configuration "Release"
         defines { "NDEBUG" }
         flags { "Optimize" }

   project "LibTwilight"
      kind "StaticLib"
      language "C++"
      files { libtdir .. "**.hh", libtdir .. "**.cc" }
      includedirs { eigen3dir }
