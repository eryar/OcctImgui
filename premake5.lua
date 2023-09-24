workspace "OcctImgui"
    configurations {"Debug", "Release"}
    system "Windows"
    platforms {"Win64"}
    architecture "X64"
    language "C++"
    
project "OcctImgui"
    kind "ConsoleApp"
    language "C++"
    targetdir "build/bin/%{cfg.buildcfg}"
    objdir "build/obj/%{cfg.buildcfg}"
    
    files { "**.h",  "**.cpp"}
    
    -- Header files.
    includedirs
    {
        "D:/OpenCASCADE-7.7.0/opencascade-7.7.0/inc", 
        "D:/glfw-3.3.8/include"
    }
    
    -- Library files.
    links
    {
        "TKernel", "TKMath", "TKG2d", "TKG3d", "TKGeomBase", "TKGeomAlgo", "TKBRep", "TKTopAlgo", "TKPrim", "TKMesh", "TKService", "TKOpenGl", "TKV3d", 
        "glfw3"
    }

    filter "configurations:Debug"
      defines { "DEBUG" }
      symbols "On"
      
      libdirs
      {
          "D:/OpenCASCADE-7.7.0/opencascade-7.7.0/win64/vc14/libd", 
          "D:/glfw-3.3.8/libd"
      }
      
      debugenvs
      {
          "path=%path%;D:/OpenCASCADE-7.7.0/opencascade-7.7.0/win64/vc14/bind"
      }

   filter "configurations:Release"
      defines { "NDEBUG" }
      symbols "Off"
      optimize "On"
      libdirs
      {
          "D:/OpenCASCADE-7.7.0/opencascade-7.7.0/win64/vc14/lib", 
          "D:/glfw-3.3.8/lib"
      }
      
      debugenvs
      {
          "path=%path%;D:/OpenCASCADE-7.7.0/opencascade-7.7.0/win64/vc14/bin"
      }