cmake_minimum_required(VERSION 3.7)
project(example_bot)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cc)
add_executable(example_bot ${SOURCE_FILES})

add_subdirectory(lib/discordpp)
add_subdirectory(lib/rest-curlpp)
add_subdirectory(lib/websocket-websocketpp)

find_package(Boost REQUIRED system filesystem)

INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIRS} ${discordpp_INCLUDE_DIRS})
TARGET_LINK_LIBRARIES(${PROJECT_NAME} ${Boost_LIBRARIES} discordpp)