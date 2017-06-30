cmake_minimum_required(VERSION 3.1)
project("netlib")

find_package(PkgConfig REQUIRED)
find_package(Poco COMPONENTS Foundation Util Net)
pkg_search_module(Pqxx REQUIRED libpqxx)

include_directories(${Pqxx_INCLUDE_DIRS})
include_directories(${Poco_INCLUDE_DIRS})
include_directories(. handlers)

link_directories(${Poco_LIBRARY_DIRS})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -ggdb -O0 -pg")

add_subdirectory(handlers)

set(SRC NetLibApp.cpp HandlerFactory.cpp RequestHandler.cpp Transaction.h Transaction.cpp
        SqlFormat.h SqlFormat.cpp )

add_executable(netlib ${SRC})
target_link_libraries(netlib netlibhandlers ${Poco_LIBRARIES} ${Pqxx_LIBRARIES})
