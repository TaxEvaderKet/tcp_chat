cmake_minimum_required(VERSION 3.20)

file(GLOB LIBUSERAUTH_SOURCES ${CMAKE_BINARY_DIR}/src/user_auth/*.c)
file(GLOB LIBCHAT_SOURCES ${CMAKE_BINARY_DIR}/src/chat/*.c)

project(tcp_chat
    DESCRIPTION "Unwise decisions."
)

set(APP_SOURCES src/app.c)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_library(userauth SHARED ${LIBUSERAUTH_SOURCES})
add_library(chat SHARED ${LIBCHAT_SOURCES})
target_link_libraries(userauth sodium ssl crypto)

add_executable(app ${APP_SOURCES})
target_link_libraries(app userauth chat)
add_custom_command(
    TARGET app
    POST_BUILD
    COMMAND strip ${CMAKE_BINARY_DIR}/bin/* ${CMAKE_BINARY_DIR}/lib/*
)
