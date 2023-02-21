add_executable(test_IPv4_app
        test_IPv4.c
        )

target_link_libraries(test_IPv4_app
        IPv4_module
        Unity
        )

add_test(test_IPv4 test_IPv4_app)