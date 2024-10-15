
set(DYNAMIC_RUNTIME_DLL dynamic_runtime)

FILE(GLOB_RECURSE dynamic_runtime_hds include/${CURDLL}/*.*)
FILE(GLOB_RECURSE dynamic_runtime_srcs src/*.*)

set(dynamic_runtime_all ${dynamic_runtime_hds} ${dynamic_runtime_srcs})

add_library(${DYNAMIC_RUNTIME_DLL}  SHARED ${dynamic_runtime_all})
target_compile_definitions(${DYNAMIC_RUNTIME_DLL} PRIVATE __DYNAMIC_RUNTIME__)
target_include_directories(${DYNAMIC_RUNTIME_DLL} PUBLIC include )

include_globally(target ${DYNAMIC_RUNTIME_DLL} global_path ${CMAKE_CURRENT_LIST_DIR}/include)


ds_source_group_by_dir(dynamic_runtime_all)
install(
  TARGETS ${DYNAMIC_RUNTIME_DLL}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
)