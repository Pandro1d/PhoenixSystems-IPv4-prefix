add_library(IPv4_module STATIC
        IPv4_prefix_manager.c
        )

target_include_directories(IPv4_module PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}
        )