cmake_minimum_required(VERSION 3.10)
project(MultithreadedChatServer)

set(CMAKE_CXX_STANDARD 17)

# Locate necessary libraries if needed
# find_package(SomeLibrary REQUIRED)

# Include directories if needed
# include_directories(${SomeLibrary_INCLUDE_DIRS})

# Add executable target
add_executable(chat_server
    src/main.cpp
    src/server.cpp
    src/client_handler.cpp
)

# Link libraries if needed
# target_link_libraries(chat_server ${SomeLibrary_LIBRARIES})
