cmake_minimum_required(VERSION 3.20)

# import custom cmake modules
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")


set(CMAKE_CXX_STANDARD 20)
set (CMAKE_CXX_STANDARD_REQUIRD ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set (CMAKE_CXX_FLAG "-Wall") 
set(CMAKE_DEBUG_POSTFIX "_d")

if(NOT CMAKE_BUILD_TYPE)
  message(STATUS "Set default build type as Debug")
  set(CMAKE_BUILD_TYPE
        Debug
      CACHE STRING "Build Type" FORCE)
endif()

# import 3rd party deps configured by vcpkg
set(VCPKG_ROOT "${CMAKE_SOURCE_DIR}/3rd/vcpkg")

# set cmake tool chain
set(CMAKE_TOOLCHAIN_FILE
    ${VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake
    CACHE STRING "Vcpkg toolchain file")




set(VCPKG_VERBOSE
    ON
    CACHE BOOL "Vcpkg VCPKG_VERBOSE")

    # set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR})
    # set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR})
    # set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_BINDIR})

    
set(OUTPUT_MID_PATH $<$<CONFIG:Debug>:/debug>)
set(OUTPUT_PATH ${CMAKE_BINARY_DIR}/${OUTPUT_MID_PATH})

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${OUTPUT_PATH}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${OUTPUT_PATH}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_PATH}/bin)

set(CMAKE_INSTALL_PREFIX ${CMAKE_BINARY_DIR}/install)

message(STATUS "CMAKE_BINARY_DIR=${CMAKE_BINARY_DIR}")
message(STATUS "CMAKE_INSTALL_LIBDIR=${CMAKE_INSTALL_LIBDIR}")
message(STATUS "CMAKE_INSTALL_BINDIR=${CMAKE_INSTALL_BINDIR}")

link_directories(${OUTPUT_MID_PATH}/lib )

# use, i.e. don't skip the full RPATH for the build tree
set(CMAKE_SKIP_BUILD_RPATH FALSE)

# when building, don't use the install RPATH already (but later on when
# installing)
set(CMAKE_BUILD_WITH_INSTALL_RPATH OFF)

if(NOT APPLE)
  # add system bin auto dly-load such as
  list(APPEND CMAKE_INSTALL_RPATH $ORIGIN/../${CMAKE_INSTALL_LIBDIR};$ORIGIN/${CMAKE_INSTALL_LIBDIR};$ORIGIN)
endif()
# add the automatically determined parts of the RPATH which point to directories
# outside the build tree to the install RPATH
set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)

# dynamic_path specify the 3rd party short deps path depends on os-platform
set(dynamic_path $<IF:$<PLATFORM_ID:Windows>,bin,lib>)
message(STATUS "dynamic libraries path search: ${dynamic_path}")
set(my_dependency_paths
    ${VCPKG_INSTALLED_DIR}/${VCPKG_TARGET_TRIPLET}$<IF:$<CONFIG:Debug>,/deubg/${dynamic_path},/${dynamic_path}>
)

set(VCPKG_INCLUDE ${VCPKG_INSTALLED_DIR}/${VCPKG_TARGET_TRIPLET}/include)
include_directories(${VCPKG_INCLUDE})

project(test_cmake CXX)




include(InstallRequiredSystemLibraries)
include(ds-source-group)
include(ConfigIncludeGlobally)
option(INCLUDE_GLOBALLY "Include project directories globally" ON)
message(STATUS "Include project directories globally: ${INCLUDE_GLOBALLY}")

find_package(cereal CONFIG REQUIRED)
find_package(Boost REQUIRED COMPONENTS locale)
find_package(Iconv)
find_package(Eigen3 CONFIG REQUIRED)
if(Iconv_FOUND)
message(STATUS "Iconv is found")
endif()

add_subdirectory(src)

