startProj(Visionary)

addIncludesAuto(${CMAKE_CURRENT_LIST_DIR}/src CMFT_SRC_c++ Source)
addIncludesAuto(${CMAKE_CURRENT_LIST_DIR}/include CMFT_HEADER_c++ Headers)

add_executable(Visionary "${INCLUDES}")
bindIncludes(Visionary)

target_link_libraries(Visionary DotVis ImGui)

endProj(Visionary)