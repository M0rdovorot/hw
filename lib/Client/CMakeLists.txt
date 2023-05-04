add_library(client src/client.cpp)
target_include_directories(client PUBLIC include)

add_subdirectory(tests)