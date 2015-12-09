project(slowcat)
cmake_minimum_required(VERSION 2.8)

set(SOURCES
    main.cpp
)

find_package( Boost REQUIRED COMPONENTS
    program_options chrono system thread
)
include_directories(${Boost_INCLUDE_DIRS})


add_executable(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES})

install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION bin)
