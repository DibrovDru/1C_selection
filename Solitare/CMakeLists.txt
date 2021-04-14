cmake_minimum_required(VERSION 3.14)
project(Solitaire)

set(CMAKE_CXX_STANDARD 17)
set(BINARY ${CMAKE_PROJECT_NAME})

add_executable(Solitaire
    main.cpp
    game_graph.hpp
    game_graph.cpp
    parser.hpp
    util.hpp)

add_library(${BINARY}_lib STATIC     	
    main.cpp
    game_graph.hpp
    game_graph.cpp
    parser.hpp
    util.hpp)

install(TARGETS Solitaire
        RUNTIME DESTINATION  ${Prac1_SOURCE_DIR}/bin
        )
