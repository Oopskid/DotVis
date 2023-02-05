startLib(DotVis)

include(${CMGym_DIR}/platform/win/D3D/d3dCore.cmake)

addIncludesAuto(${CMAKE_CURRENT_LIST_DIR}/src CMFT_SRC_c++ Source)
addIncludesAuto(${CMAKE_CURRENT_LIST_DIR}/include CMFT_HEADER_c++ Headers)
#addIncludesAuto(${CMAKE_CURRENT_LIST_DIR}/shaders CMFT_SHADER_hlsl Resources/Shaders)

add_library(DotVis STATIC "${INCLUDES}")
bindIncludes(DotVis)

target_compile_features(DotVis PUBLIC cxx_std_17)
target_link_libraries(DotVis Deed WSTRCore)

set(HLSL_SHADER_GLOBAL_WORK_DIRECTORY "${CMAKE_CURRENT_LIST_DIR}/shaders" CACHE STRING "" FORCE)

defineShaders(DotVis ${HLSL_TYPE_COMPUTE} "${CMAKE_CURRENT_LIST_DIR}/shaders/Raytracing/TraceScene.hlsl")
set(hlsli "hlsli") 
getDirFiles(hlsl_headers "${CMAKE_CURRENT_LIST_DIR}/shaders" hlsli 1)
defineShaders(DotVis ${HLSL_TYPE_HEADER} "${hlsl_headers}" 1)

endLib(DotVis)