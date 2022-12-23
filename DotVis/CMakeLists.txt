startLib(DotVis)

addIncludesAuto(${CMAKE_CURRENT_LIST_DIR}/src CMFT_SRC_c++ Source)
addIncludesAuto(${CMAKE_CURRENT_LIST_DIR}/include CMFT_HEADER_c++ Headers)
addIncludesAuto(${CMAKE_CURRENT_LIST_DIR}/shaders CMFT_SHADER_hlsl Resources/Shaders)

add_library(DotVis STATIC "${INCLUDES}")
bindIncludes(DotVis)

target_compile_features(DotVis PUBLIC cxx_std_17)
target_link_libraries(DotVis Deed WSTRCore)

endLib(DotVis)