
set(TEST_EIGEN3_DLL test_eigen3)

FILE(GLOB_RECURSE test_eigen3_hds include/${CURDLL}/*.*)
FILE(GLOB_RECURSE test_eigen3_srcs src/*.*)

set(test_eigen3_all ${test_eigen3_hds} ${test_eigen3_srcs})




add_executable(${TEST_EIGEN3_DLL}  ${test_eigen3_all})

target_link_libraries(${TEST_EIGEN3_DLL} PRIVATE Eigen3::Eigen)

target_compile_definitions(${TEST_EIGEN3_DLL} PRIVATE __TEST_EIGEN3__)
target_include_directories(${TEST_EIGEN3_DLL} PUBLIC include )

include_globally(target ${TEST_EIGEN3_DLL} global_path ${CMAKE_CURRENT_LIST_DIR}/include)


ds_source_group_by_dir(test_eigen3_all)
install(
  TARGETS ${TEST_EIGEN3_DLL}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
)