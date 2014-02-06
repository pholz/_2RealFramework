solution "TestBundle"
        configurations {"Debug", "Release"}

        REALROOT = "../../../.."

        if os.is("linux") 
        then
           EIGEN_INCLUDE_DIRS = "/usr/include/eigen3"
           defines { "_UNIX" }
           buildoptions { "-std=c++11" }
        end

        project "TestBundle"
            kind "SharedLib"
            language "C++"
            targetdir "../lib"

            files {
               "../src/**.h",
               "../src/**.cpp"
            }
            
            includedirs {
               REALROOT .. "/kernel/src",
               EIGEN_INCLUDE_DIRS
            }
            
            libdirs {
               REALROOT .. "/kernel/lib"
            }
            
            configuration "Debug"
            defines { "DEBUG" }
            flags {"Symbols"}
            
            configuration "Release"
            defines {"NDEBUG"}
            flags {"Optimize"}
            
