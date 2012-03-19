local eigen3dir = "/usr/include/eigen3/"
local boostdir = "/usr/include/boost/"
local libtdir = "src/libtwilight/"
local tbindir = "src/twilightbin/"

solution "Twilight"
   configurations { "Release", "Debug" }
   location "build"
   targetname "twilight"
   buildoptions { "-std=c++0x" }
   flags { "ExtraWarnings" }
 
   project "TwilightBin"
      kind "ConsoleApp"
      language "C++"
      files { tbindir .. "**.hh", tbindir .. "**.cc" }
      includedirs { eigen3dir, boostdir, "src/" }
      links { "LibTwilight", "boost_program_options" }
 
      configuration "Debug"
         flags { "Symbols" }
 
      configuration "Release"
         flags { "OptimizeSpeed" }

   project "LibTwilight"
      kind "StaticLib"
      language "C++"
      files { libtdir .. "**.hh", libtdir .. "**.cc" }
      includedirs { eigen3dir }
 
      configuration "Debug"
         flags { "Symbols" }
 
      configuration "Release"
         flags { "OptimizeSpeed" }
