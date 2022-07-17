cmake_minimum_required (VERSION 3.14)

project("CredMann")

add_subdirectory("CredMannLib")

set(BOOST_ROOT "/Users/stephen/Workspace/libs/boost_1_79_0")
set(CRYPTOPP_ROOT "/Users/stephen/vcpkg/packages/cryptopp_arm64-osx/include")

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

