include_directories(../)
add_executable(TEST_EXE test.c)
target_link_libraries(TEST_EXE sharna)
add_test(TEST_SH TEST_EXE)