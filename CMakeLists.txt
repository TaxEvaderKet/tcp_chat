cmake_minimum_required(VERSION 3.12)

project(userauth)

set(SODIUM_INCLUDE_DIR "/usr/include")

set(USER_AUTH_SOURCES
    src/user_auth.c
)

add_library(userauth SHARED ${USER_AUTH_SOURCES})

target_link_libraries(userauth sodium)

set_target_properties(userauth PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(APP_SOURCES
    src/app.c
)

add_executable(tcp_chat ${APP_SOURCES})

target_link_libraries(tcp_chat userauth)

set_target_properties(tcp_chat PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
