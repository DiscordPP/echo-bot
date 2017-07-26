cmake_minimum_required(VERSION 3.7)
project(example_bot)

set(CMAKE_CXX_STANDARD 14)

add_subdirectory(lib/discordpp)
add_subdirectory(lib/rest-curlpp)
add_subdirectory(lib/websocket-websocketpp)

set(SOURCE_FILES main.cc)
add_executable(${PROJECT_NAME} ${SOURCE_FILES})

find_package(Boost REQUIRED system filesystem)

INCLUDE_DIRECTORIES(
        ${Boost_INCLUDE_DIRS}
        ${discordpp_SOURCE_DIR}
        ${discordpp-rest-curlpp_SOURCE_DIR}
        ${discordpp-websocket-websocketpp_SOURCE_DIR}
        ${json_SOURCE_DIR}
)

TARGET_LINK_LIBRARIES(
        ${PROJECT_NAME}
        ${Boost_LIBRARIES}
        discordpp
        discordpp-rest-curlpp
        discordpp-websocket-websocketpp
)