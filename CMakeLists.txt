cmake_minimum_required(VERSION 3.7)
project(league_projects)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

add_subdirectory(lib/discordpp)          # discordpp
add_subdirectory(lib/rest-beast)         # discordpp-rest-beast
add_subdirectory(lib/websocket-beast)    # discordpp-websocket-beast
add_subdirectory(lib/plugin-overload)    # discordpp-plugin-overload
add_subdirectory(lib/plugin-responder)   # discordpp-plugin-responder
add_subdirectory(lib/SQLiteCpp)



file(GLOB_RECURSE TARGET_HEADERS ${CMAKE_CURRENT_LIST_DIR}/include/*.h)
file(GLOB_RECURSE TARGET_CPP ${CMAKE_CURRENT_LIST_DIR}/src/*.cpp)
include_directories( "include" )

set(SOURCE_FILES main.cc ${TARGET_CPP} ${TARGET_HEADERS})
add_executable(${PROJECT_NAME} ${SOURCE_FILES})

set(THREADS_PREFER_PTHREAD_FLAG ON)

find_package(Boost 1.71.0 REQUIRED system date_time)
find_package(Threads REQUIRED)
find_package(OpenSSL REQUIRED)
find_package (SQLite3)
if (SQLITE3_FOUND)
	include_directories(${SQLITE3_INCLUDE_DIRS})
	target_link_libraries (${PROJECT_NAME} ${SQLITE3_LIBRARIES})
endif (SQLITE3_FOUND)
target_link_libraries(${PROJECT_NAME} SQLiteCpp)


if (WIN32)
	add_definitions(-D_WIN32_WINNT=0x0601) # Windows 7
endif()

if (MSVC)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /bigobj")
	set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} /bigobj")
endif()

INCLUDE_DIRECTORIES(
        ${Boost_INCLUDE_DIRS}
        ${discordpp_SOURCE_DIR}
        ${discordpp-rest-beast_SOURCE_DIR}
        ${discordpp-websocket-beast_SOURCE_DIR}
        ${discordpp-plugin-overload_SOURCE_DIR}
        ${discordpp-plugin-responder_SOURCE_DIR}
        ${json_SOURCE_DIR}
        ${OPENSSL_INCLUDE_DIR}
)

TARGET_LINK_LIBRARIES(
        ${PROJECT_NAME}
        ${Boost_LIBRARIES}
        discordpp
        discordpp-rest-beast
        discordpp-websocket-beast
        Threads::Threads
        ${OPENSSL_LIBRARIES}
)

if(EXISTS ${CMAKE_SOURCE_DIR}/token.dat)
	configure_file(build/token.dat ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)
elseif(EXISTS ${CMAKE_CURRENT_BINARY_DIR}/token.dat)
	file(REMOVE ${CMAKE_CURRENT_BINARY_DIR}/token.dat)
endif()
