

if(CMAKE_CXX_COMPILER MATCHES "clang")

    set(CXX_WFLAGS "${CXX_WFLAGS} -Wall")
    set(CXX_WFLAGS "${CXX_WFLAGS} -Wno-unknown-argument")
    set(CXX_WFLAGS "${CXX_WFLAGS} -Wno-missing-braces")
    set(CXX_WFLAGS "${CXX_WFLAGS} -Wno-delete-incomplete")
    set(CXX_WFLAGS "${CXX_WFLAGS} -Wno-microsoft-enum-value")
    set(CXX_WFLAGS "${CXX_WFLAGS} -Wno-unused-variable")
    set(CXX_WFLAGS "${CXX_WFLAGS} -Wno-format")
    set(CXX_WFLAGS "${CXX_WFLAGS} -Wno-reorder")
    set(CXX_WFLAGS "${CXX_WFLAGS} -Wno-unused-const-variable")
    set(CXX_WFLAGS "${CXX_WFLAGS} -Wno-ignored-qualifiers")
    set(CXX_WFLAGS "${CXX_WFLAGS} -Wno-sign-compare")
    set(CXX_WFLAGS "${CXX_WFLAGS} -Wno-unused-parameter")
else()
    if(WIN32)
        set(CXX_WFLAGS "${CXX_WFLAGS} /W4")
        set(CXX_WFLAGS "${CXX_WFLAGS} /wd4752") #found Intel(R) Advanced Vector Extensions; consider using /arch:AVX
        set(CXX_WFLAGS "${CXX_WFLAGS} /wd4100") #unreferenced formal parameter
        set(CXX_WFLAGS "${CXX_WFLAGS} /wd4505") #unreferenced local function has been removed
        #set(CXX_WFLAGS "${CXX_WFLAGS} /W4748") #On gyp, not on MS docs
    endif()
endif()

if(CMAKE_CXX_COMPILER MATCHES "clang")

    set(CXX_WERRORFLAG "-Werror")

else()
    if(WIN32)
        set(CXX_WERRORFLAG "/WX")
    endif()
endif()



macro(ApplyWarningPolicy)

    set(options DEBUG PUBLIC)
    set(oneValueArgs "")
    set(multiValueArgs TARGETS)

    cmake_parse_arguments(ARG "${options}" "${oneValueArgs}"
                          "${multiValueArgs}" ${ARGN} )

    if(ARG_DEBUG)

        if(ARG_TARGETS)
            message("Setting warnings for targets ${ARG_TARGETS}")
        else()
            message("Setting warnings for all targets")
        endif()
        message("Warning flags: ${CXX_WFLAGS}")
    endif()

    if(ARG_PUBLIC)
        set(FLAG_TRANSITIVITY "PUBLIC")
    else()
        set(FLAG_TRANSITIVITY "PRIVATE")
    endif()

    if(CXX_WFLAGS)
        if(ARG_TARGETS)
            string(REPLACE " " ";" FLAGLIST ${CXX_WFLAGS})
            foreach(targ IN LISTS ARG_TARGETS)
                target_compile_options(${targ} ${FLAG_TRANSITIVITY} ${FLAGLIST})
            endforeach(targ)
        else()
            set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${CXX_WFLAGS}")
        endif()
    else()
        message("Warning policy not defined for your configuration!")
    endif()
endmacro()

macro(WarningAsErrors)

    set(options DEBUG PUBLIC)
    set(oneValueArgs "")
    set(multiValueArgs TARGETS)

    cmake_parse_arguments(ARG "${options}" "${oneValueArgs}"
                          "${multiValueArgs}" ${ARGN} )

    if(ARG_DEBUG)
        if(ARG_TARGETS)
            message("Setting warnings as error for targets ${ARG_TARGETS}")
        else()
            message("Setting warnings as error for all targets")
        endif()
        message("Flag: ${CXX_WERRORFLAG}")
    endif()

    if(ARG_PUBLIC)
        set(FLAG_TRANSITIVITY "PUBLIC")
    else()
        set(FLAG_TRANSITIVITY "PRIVATE")
    endif()

    if(CXX_WERRORFLAG)
        if(ARG_TARGETS)
            foreach(targ IN LISTS ARG_TARGETS)
                target_compile_options(${targ} ${FLAG_TRANSITIVITY} ${CXX_WERRORFLAG})
            endforeach(targ)
        else()
            set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${CXX_WERRORFLAG}")
        endif()
    else()
        message("Flag for Warning as errors not defined for your configuration!")
    endif()
endmacro()
