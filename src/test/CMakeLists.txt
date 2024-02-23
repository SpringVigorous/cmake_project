set(TEST_EXE test)
file(GLOB_RECURSE test_srcs src/*.*)
file(GLOB_RECURSE test_hds include/*.*)

add_executable(${TEST_EXE}  ${test_srcs} ${test_hds})
target_link_libraries(${TEST_EXE} PUBLIC  tools kernel_serialize kernel) 
set_target_properties(${TEST_EXE} PROPERTIES DEBUG_POSTFIX "_d")
target_include_directories(${TEST_EXE} PUBLIC include)

set(test_all ${test_hds} ${test_srcs})
ds_source_group_by_dir(test_all)


# 源文件夹路径
set(COPY_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/test_data")


  set(COPY_TARGET_DIR ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})


# 确保目标目录存在
#file(MAKE_DIRECTORY ${COPY_TARGET_DIR})

# 使用add_custom_command拷贝整个文件夹
add_custom_command(
    # 在生成目标前执行
    TARGET ${TEST_EXE}
    PRE_BUILD
    COMMAND echo  source:${COPY_SOURCE_DIR}  dest:${COPY_TARGET_DIR}
    # 拷贝命令
    COMMAND xcopy \"${COPY_SOURCE_DIR}\"  \"${COPY_TARGET_DIR}\"  /E /I /Y /S
    COMMENT "Copying data folder to configuration-specific directory..."
)

# 如果需要，确保清理时也删除该目录
#set_property(DIRECTORY APPEND PROPERTY ADDITIONAL_MAKE_CLEAN_FILES ${COPY_TARGET_DIR})


install(
  TARGETS ${TEST_EXE}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
)
