cmake_minimum_required (VERSION 3.10)

project("CredMannLib")

set(CMAKE_CXX_STANDARD 11)
set(BOOST_ROOT "/Users/stephen/Workspace/libs/boost_1_79_0")
set(CRYPTOPP_ROOT "/Users/stephen/vcpkg/packages/cryptopp_arm64-osx")
set(CryptoPP_INCLUDE_DIRS "/Users/stephen/vcpkg/packages/cryptopp_arm64-osx/include")
set(CryptoPP_LIB_DIRS "/Users/stephen/vcpkg/packages/cryptopp_arm64-osx/lib")

if ("${CMAKE_BUILD_TYPE}" STREQUAL "DEBUG")
    set(BOOST_STATIC_SYSTEM_LIBRARY ${Boost_SYSTEM_LIBRARY_DEBUG})
    set(BOOST_STATIC_FILESYSTEM_LIBRARY ${Boost_FILESYSTEM_LIBRARY_DEBUG})
else()
    set(BOOST_STATIC_SYSTEM_LIBRARY ${Boost_SYSTEM_LIBRARY_RELEASE})
    set(BOOST_STATIC_FILESYSTEM_LIBRARY ${Boost_FILESYSTEM_LIBRARY_RELEASE})
endif()

set(Boost_NO_SYSTEM_PATHS true)
set(Boost_USE_STATIC_LIBS ON)
set(Boost_USE_MULTITHREADED ON)

find_package(Boost 1.79 REQUIRED 
  COMPONENTS
  system program_options thread filesystem)

include_directories(${Boost_INCLUDE_DIRS})
include_directories(${CryptoPP_INCLUDE_DIRS})

link_directories(${CryptoPP_LIB_DIRS})

# Add source to this project's executable.
file(GLOB CredMannLib_SRC
    "*.h"
    "*.cpp"
)

## include_directories (${CMAKE_CURRENT_SOURCE_DIR}/include/common ${CMAKE_CURRENT_SOURCE_DIR}/include/engine)
## include_directories (${CMAKE_CURRENT_SOURCE_DIR}/src)

add_executable(${PROJECT_NAME} ${CredMannLib_SRC})

target_link_libraries(${PROJECT_NAME} cryptopp)

get_directory_property(_my_link_dirs LINK_DIRECTORIES)
message(STATUS "_my_link_dirs = ${Boost_INCLUDE_DIRS}")