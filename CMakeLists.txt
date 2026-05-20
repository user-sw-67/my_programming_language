cmake_minimum_required(VERSION 3.15)
project(ATOM VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Debug" CACHE STRING "Build type" FORCE)
endif()

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/include/addition
    ${CMAKE_CURRENT_SOURCE_DIR}/include/base
    ${CMAKE_CURRENT_SOURCE_DIR}/include/lexer
    ${CMAKE_CURRENT_SOURCE_DIR}/include/parser
    ${CMAKE_CURRENT_SOURCE_DIR}/include/parser/ast
    ${CMAKE_CURRENT_SOURCE_DIR}/include/semantics
    ${CMAKE_CURRENT_SOURCE_DIR}/include/semantics/visitors
    ${CMAKE_CURRENT_SOURCE_DIR}/include/builds
)

set(SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp
    
    ${CMAKE_CURRENT_SOURCE_DIR}/src/addition/error_manager.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/addition/source_manager.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/addition/program_manager.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/addition/mermaid_visitor.cpp
    
    ${CMAKE_CURRENT_SOURCE_DIR}/src/lexer/lexer.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/lexer/token.cpp
    
    ${CMAKE_CURRENT_SOURCE_DIR}/src/parser/parser.cpp

    ${CMAKE_CURRENT_SOURCE_DIR}/src/semantics/semantics_manager.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/semantics/symbol_table.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/semantics/value.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/semantics/visitors/base.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/semantics/visitors/analysis_visitor.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/semantics/visitors/definition_visitor.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/semantics/visitors/optimization_visitor.cpp

    ${CMAKE_CURRENT_SOURCE_DIR}/src/builds/functions.cpp
)

add_executable(atm ${SOURCES})

message(STATUS "Тип сборки: ${CMAKE_BUILD_TYPE}")
message(STATUS "Стандарт C++: ${CMAKE_CXX_STANDARD}")
