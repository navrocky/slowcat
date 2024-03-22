cmake_minimum_required(VERSION 3.5)

project(slowcat)

set(SOURCES
    main.cpp
)

add_link_options(-static -static-libgcc -static-libstdc++ -s)

find_package(Boost REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})

add_executable(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME} boost::boost)

install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION bin)
