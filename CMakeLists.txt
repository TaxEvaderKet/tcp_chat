cmake_minimum_required(VERSION 3.20)

project(tcp_chat
    DESCRIPTION "Unwise decisions."
)

set(USER_AUTH_SOURCES src/user_auth/user_auth.c)
set(FILTER_SOURCES src/chat/filter.c)
set(APP_SOURCES src/app.c)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_library(userauth SHARED ${USER_AUTH_SOURCES})
add_library(filter SHARED ${FILTER_SOURCES})
target_link_libraries(userauth sodium ssl crypto)

add_executable(app ${APP_SOURCES})
target_link_libraries(app userauth filter)
add_custom_command(
    TARGET app
    POST_BUILD
    COMMAND strip ${CMAKE_BINARY_DIR}/bin/* ${CMAKE_BINARY_DIR}/lib/*
)
