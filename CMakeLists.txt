add_subdirectory("${CMAKE_CURRENT_LIST_DIR}/externals")
add_subdirectory("${CMAKE_CURRENT_LIST_DIR}/DotVis")

include("${CMAKE_CURRENT_LIST_DIR}/Visionary/CMakeLists.txt")

setMain(Visionary)