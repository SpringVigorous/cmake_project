set(TEST_EXE test)
file(GLOB_RECURSE test_srcs src/*.*)
file(GLOB_RECURSE test_hds include/*.*)

add_executable(${TEST_EXE}  ${test_srcs} ${test_hds})
target_link_libraries(${TEST_EXE} PUBLIC  tools kernel_serialize kernel) 
set_target_properties(${TEST_EXE} PROPERTIES DEBUG_POSTFIX "_d")
target_include_directories(${TEST_EXE} PUBLIC include)

message(STATUS "hds: ${test_hds}")


message(STATUS "CMAKE_INSTALL_PREFIX=${CMAKE_INSTALL_BINDIR}")

set(test_all ${test_hds} ${test_srcs})
ds_source_group_by_dir(test_all)



install(
  TARGETS ${TEST_EXE}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
)
