file
(
    GLOB_RECURSE GAME_FILES
    "*.cpp"
    "*.hpp"
)

add_library(Motherload STATIC ${SOURCE_FILES})
target_link_libraries(Motherload ${EXTRA_LIBS})

add_executable(motherload ${GAME_FILES})
target_link_libraries(motherload ${EXTRA_LIBS} Motherload)