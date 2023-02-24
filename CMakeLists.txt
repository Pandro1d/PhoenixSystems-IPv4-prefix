cmake_minimum_required(VERSION 3.20)
project(PhoenixSystems_IPv4_prefix C)

set(CMAKE_C_STANDARD 17)

set(TARGET_GROUP test CACHE STRING "Group to build")

add_subdirectory(IPv4_prefix_manager)

if(TARGET_GROUP STREQUAL production)
    add_subdirectory(main)

elseif(TARGET_GROUP STREQUAL test)
    include(CTest)

    add_subdirectory(external)
    add_subdirectory(test)
else()
    message(FATAL_ERROR "Given TARGET_GROUP unknown")
endif()
