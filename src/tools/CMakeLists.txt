set(tools_dll tools)
file(GLOB_RECURSE tools_src src/*.*)
file(GLOB_RECURSE tools_hdr include/*.*)
set(tools_all ${tools_src} ${tools_hdr})


message(STATUS "${tools_src}")
message(STATUS "${tools_hdr}")

add_library(${tools_dll} SHARED ${tools_all})
target_compile_definitions(${tools_dll} PRIVATE __TOOLS__)
target_include_directories(${tools_dll} PUBLIC include)
target_link_libraries(${tools_dll} PRIVATE Iconv::Iconv )
#set_target_properties(${tools_dll} PROPERTIES DEBUG_POSTFIX "_d")
ds_source_group_by_dir(tools_all)