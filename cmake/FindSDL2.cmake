message ("-- SDL2")
SET(SDL2_INCLUDE_DIR
    ${PLATFORM_PATHS}/SDL2/include
    CACHE STRING "Where to find SDL.h"
    )

if(NOT APPLE)
    find_package(Threads)
endif()

if(WIN32)
    set(SDL2_LIBRARY
        ${PLATFORM_PATHS}/SDL2/lib/${PLATFORM_ARCH}/SDL2main.lib
        ${PLATFORM_PATHS}/SDL2/lib/${PLATFORM_ARCH}/SDL2.lib
        ${PLATFORM_PATHS}/SDL2/lib/${PLATFORM_ARCH}/SDL2_image.${LIBRARY_EXTENSION}
        ${PLATFORM_PATHS}/SDL2/lib/${PLATFORM_ARCH}/SDL2_mixer.${LIBRARY_EXTENSION}
        ${PLATFORM_PATHS}/SDL2/lib/${PLATFORM_ARCH}/SDL2_ttf.${LIBRARY_EXTENSION}
        ${CMAKE_THREAD_LIBS_INIT}
        CACHE STRING "All the SDL2 Libraries"
        )
elseif(UNIX)
    set(SDL2_LIBRARY
        ${PLATFORM_PATHS}/SDL2/lib/libSDL2main.a
        ${PLATFORM_PATHS}/SDL2/lib/libSDL2.so
        ${PLATFORM_PATHS}/SDL2/lib/libSDL2_image.${LIBRARY_EXTENSION}
        ${PLATFORM_PATHS}/SDL2/lib/libSDL2_mixer.${LIBRARY_EXTENSION}
        ${PLATFORM_PATHS}/SDL2/lib/libSDL2_ttf.${LIBRARY_EXTENSION}
        ${CMAKE_THREAD_LIBS_INIT}
        CACHE STRING "All the SDL2 Libraries"
        )
endif()

