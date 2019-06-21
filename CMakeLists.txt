cmake_minimum_required(VERSION 3.7)
project(echo_bot)

set(CMAKE_CXX_STANDARD 14)

add_subdirectory(lib/discordpp)          # discordpp
add_subdirectory(lib/rest-beast)         # discordpp-rest-beast
add_subdirectory(lib/websocket-beast)    # discordpp-websocket-beast

set(SOURCE_FILES main.cc)
add_executable(${PROJECT_NAME} ${SOURCE_FILES})

set(THREADS_PREFER_PTHREAD_FLAG ON)

find_package(Boost REQUIRED system filesystem)
find_package(Threads REQUIRED)
find_package(OpenSSL REQUIRED)

INCLUDE_DIRECTORIES(
        ${Boost_INCLUDE_DIRS}
        ${discordpp_SOURCE_DIR}
        ${discordpp-rest-beast_SOURCE_DIR}
        ${discordpp-websocket-beast_SOURCE_DIR}
        ${json_SOURCE_DIR}
        ${OPENSSL_INCLUDE_DIR}
)

add_definitions(-DBOOST_ALL_NO_LIB)

if (WIN32)
	add_definitions(-D_WIN32_WINNT=0x0601) # Target: Windows 7
endif()

target_link_libraries(
	${PROJECT_NAME} 
	${Boost_LIBRARIES}
	discordpp
        discordpp-rest-beast
        discordpp-websocket-beast
        Threads::Threads
)

target_link_libraries(
	${PROJECT_NAME}
	debug ${Boost_FILESYSTEM_LIBRARY_DEBUG}
	optimized ${Boost_FILESYSTEM_LIBRARY_RELEASE} 
)

target_link_libraries(
	${PROJECT_NAME}
	debug ${Boost_SYSTEM_LIBRARY_DEBUG}
	optimized ${Boost_SYSTEM_LIBRARY_RELEASE}
)

if (WIN32 AND MSVC)
	target_link_libraries(
		${PROJECT_NAME}
		debug ${LIB_EAY_DEBUG} 
		optimized ${LIB_EAY_RELEASE}
	)
	 
	target_link_libraries(
		${PROJECT_NAME}
		debug ${SSL_EAY_DEBUG}
		optimized ${SSL_EAY_RELEASE}
	)
else()
	target_link_libraries(
		${PROJECT_NAME}
		${CRYPTO_LIBRARIES}
		${OPENSSL_LIBRARIES}
	)
endif()
