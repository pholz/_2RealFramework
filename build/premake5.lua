solution "_2Real"
        configurations {"Debug", "Release"}
        language "C++"
        REALROOT = ".."

        if os.is("linux") 
        then
           EIGEN_INCLUDE_DIRS = "/usr/include/eigen3"
           defines { "_UNIX", "_2REAL_UNIX" }
           buildoptions { "-std=c++11" }
        end

        configuration "Debug"
            defines { "_DEBUG" }
            flags {"Symbols"}
            targetsuffix "D"

        configuration "Release"
            optimize "On"

        project "_2RealFramework"
            kind "SharedLib"
            targetdir ( REALROOT .. "/kernel/lib" )
            
            files {
               REALROOT .. "/kernel/src/**.cpp"
            }

            includedirs {
               REALROOT .. "/kernel/src",
               EIGEN_INCLUDE_DIRS
            }
            
            libdirs {
               REALROOT .. "/kernel/lib"
            }

            links { "PocoNet", "PocoXML" }

            linkoptions { "-Wl,-soname,lib_2RealFramework.so"}

        project "ImageTestingBundle"
            kind "SharedLib"
            PROJROOT = REALROOT .. "/testing/"
            targetdir ( PROJROOT .. "/lib" )
            files {
               PROJROOT .. "/src/" .. project().name .. "/*.cpp",
               PROJROOT .. "/src/" .. project().name .. "/*.h"
            }

            includedirs {
               REALROOT .. "/kernel/src",
               EIGEN_INCLUDE_DIRS
            }
            
            libdirs {
               REALROOT .. "/kernel/lib"
            }

            links { "_2RealFramework" }

        project "ImageTestingApp"
            kind "WindowedApp"
            PROJROOT = REALROOT .. "/testing"
            targetdir ( PROJROOT .. "/bin" )
            files {
               PROJROOT .. "/src/" .. project().name .. "/*.cpp",
               PROJROOT .. "/src/" .. project().name .. "/*.h"
            }

            includedirs {
               REALROOT .. "/kernel/src",
               EIGEN_INCLUDE_DIRS
            }
            
            if os.is("linux") 
            then
               buildoptions { "`pkg-config --cflags sdl2`" }
            end

            links {  "SDL2", "GL", "GLEW", "PocoNet", "PocoFoundation", "PocoUtil", "_2RealFramework" }
            linkoptions { "-Wl,-rpath,'" .. REALROOT .. "/kernel/lib" .. "'" }

        project "TestBundle"
            kind "SharedLib"
            PROJROOT = REALROOT .. "/bundles/examples/test"
            targetdir ( PROJROOT .. "/lib" )

            files {
               PROJROOT .. "/src/**.h",
               PROJROOT .. "/src/**.cpp"
            }
            
            includedirs {
               REALROOT .. "/kernel/src",
               EIGEN_INCLUDE_DIRS
            }
            
            libdirs {
               REALROOT .. "/kernel/lib"
            }
            
            links { "_2RealFramework" }
            
            
