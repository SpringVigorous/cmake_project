
set(KERNEL_DLL kernel)

FILE(GLOB_RECURSE kernel_hds include/${CURDLL}/*.*)
FILE(GLOB_RECURSE kernel_srcs src/*.*)

set(kernel_all ${kernel_hds} ${kernel_srcs})

add_library(${KERNEL_DLL}  SHARED ${kernel_all})
target_compile_definitions(${KERNEL_DLL} PRIVATE __KERNEL__)
target_include_directories(${KERNEL_DLL} PUBLIC include )

include_globally(target ${KERNEL_DLL} global_path ${CMAKE_CURRENT_LIST_DIR}/include)


ds_source_group_by_dir(kernel_all)
install(
  TARGETS ${KERNEL_DLL}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
)