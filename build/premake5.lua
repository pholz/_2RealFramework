solution "_2Real"
        configurations {"Debug", "Release"}
        language "C++"
        REALROOT = ".."

        if os.is("linux") 
        then
           EIGEN_INCLUDE_DIRS = "/usr/include/eigen3"
           QT4_INCLUDE_DIRS = "/usr/include/qt4"
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

            libdirs {
               REALROOT .. "/kernel/lib"
            }
            
            if os.is("linux") 
            then
               buildoptions { "`pkg-config --cflags sdl2`" }
            end

            links {  "SDL2", "GL", "GLEW", "PocoNet", "PocoFoundation", "PocoUtil", "_2RealFramework" }
--            linkoptions { "-Wl,-rpath,'" .. REALROOT .. "/kernel/lib" .. "'" }

        project "TestBundle"
            kind "SharedLib"
            PROJROOT = REALROOT .. "/bundles/examples/testBundle"
            targetdir ( PROJROOT .. "/../lib" )

            files {
               PROJROOT .. "/src/**.h",
               PROJROOT .. "/src/**.cpp"
            }
            
            includedirs {
               REALROOT .. "/kernel/src",
               EIGEN_INCLUDE_DIRS
            }
            
            links { "_2RealFramework" }

        project "TestApp"
            kind "WindowedApp"
            PROJROOT = REALROOT .. "/bundles/examples/testApp"
            targetdir ( PROJROOT .. "/../bin" )

            files {
               PROJROOT .. "/src/main.cpp"
            }
            
            includedirs {
               REALROOT .. "/kernel/src",
               EIGEN_INCLUDE_DIRS,
               QT4_INCLUDE_DIRS,
               QT4_INCLUDE_DIRS .. "/QtGui",
               QT4_INCLUDE_DIRS .. "/QtCore",
               REALROOT .. "/bundles/unittest/include"
            }

            libdirs {
               REALROOT .. "/kernel/lib",
               REALROOT .. "/bundles/unittest/lib"
            }

            links { "QtGui", "QtCore", "_2RealFramework", "UnitTestBundle" }

        project "TestApp2"
            kind "WindowedApp"
            PROJROOT = REALROOT .. "/bundles/examples/testApp2"
            targetdir ( PROJROOT .. "/../bin" )

            files {
               PROJROOT .. "/src/main.cpp"
            }
            
            includedirs {
               REALROOT .. "/kernel/src",
               EIGEN_INCLUDE_DIRS
            }

            libdirs {
               REALROOT .. "/kernel/lib"
            }

            links { "_2RealFramework" }
            
            
