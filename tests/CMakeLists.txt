include(FetchContent)

FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.17.0.zip
    DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)

FetchContent_MakeAvailable(googletest)

add_executable(M6502Tests
    cpu_test.cpp
)

target_link_libraries(M6502Tests
    PRIVATE
        M6502Lib
        GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(M6502Tests)