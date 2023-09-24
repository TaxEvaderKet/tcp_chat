cmake_minimum_required(VERSION 3.20)

project(userauth)

set(SODIUM_INCLUDE_DIR "/usr/include")

set(USER_AUTH_SOURCES
    src/user_auth.c
)

set(CHAT_FILTER_SOURCES
    src/filter.c
)

set(APP_SOURCES
    src/app.c
)

add_library(userauth SHARED ${USER_AUTH_SOURCES})
add_library(chatfilter SHARED ${CHAT_FILTER_SOURCES})

target_link_libraries(userauth sodium)

set_target_properties(userauth PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set_target_properties(chatfilter PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_executable(app ${APP_SOURCES})

target_link_libraries(app userauth chatfilter)
set_target_properties(app PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
