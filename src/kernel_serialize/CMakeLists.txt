
set(KERNEL_SERIALIZE_DLL kernel_serialize)

FILE(GLOB_RECURSE kernel_serialize_hds include/${CURDLL}/*.*)
FILE(GLOB_RECURSE kernel_serialize_srcs src/*.*)

set(kernel_serialize_all ${kernel_serialize_hds} ${kernel_serialize_srcs} )

add_library(${KERNEL_SERIALIZE_DLL}  SHARED ${kernel_serialize_all})
target_compile_definitions(${KERNEL_SERIALIZE_DLL} PRIVATE __KERNEL_SERIALIZE__)

target_include_directories(${KERNEL_SERIALIZE_DLL} PUBLIC include)
target_link_libraries(${KERNEL_SERIALIZE_DLL}  PUBLIC kernel)
include_globally(target ${KERNEL_SERIALIZE_DLL} global_path ${CMAKE_CURRENT_LIST_DIR}/include)

ds_source_group_by_dir(kernel_serialize_all)
install(
  TARGETS ${KERNEL_SERIALIZE_DLL}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
)