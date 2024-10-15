
set(PROJECT_TEMPLATE_DLL project_template)

FILE(GLOB_RECURSE project_template_hds include/${CURDLL}/*.*)
FILE(GLOB_RECURSE project_template_srcs src/*.*)

set(project_template_all ${project_template_hds} ${project_template_srcs})

add_library(${PROJECT_TEMPLATE_DLL}  SHARED ${project_template_all})
target_compile_definitions(${PROJECT_TEMPLATE_DLL} PRIVATE __PROJECT_TEMPLATE__)
target_include_directories(${PROJECT_TEMPLATE_DLL} PUBLIC include )

include_globally(target ${PROJECT_TEMPLATE_DLL} global_path ${CMAKE_CURRENT_LIST_DIR}/include)


ds_source_group_by_dir(project_template_all)
install(
  TARGETS ${PROJECT_TEMPLATE_DLL}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
)