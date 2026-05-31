cmake_minimum_required(VERSION 3.15)

project(ATOM VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Debug" CACHE STRING "Build type (Release, Debug)" FORCE)
endif()

option(ENABLE_SANITIZERS "Enable Address and Undefined Behavior Sanitizers" ON)

set(SOURCES
    src/main.cpp

    src/addition/error_manager.cpp
    src/addition/source_manager.cpp
    src/addition/program_manager.cpp
    src/addition/mermaid_visitor.cpp
    src/addition/builds_manager.cpp

    src/lexer/lexer.cpp
    src/lexer/token.cpp

    src/parser/parser.cpp

    src/base/visitor.cpp

    src/semantics/semantics_manager.cpp
    src/semantics/symbol_table.cpp
    src/semantics/value.cpp
    src/semantics/visitors/base.cpp
    src/semantics/visitors/analysis_visitor.cpp
    src/semantics/visitors/definition_visitor.cpp
    src/semantics/visitors/optimization_visitor.cpp
)

add_executable(atm ${SOURCES})

target_include_directories(atm PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/include/addition
    ${CMAKE_CURRENT_SOURCE_DIR}/include/base
    ${CMAKE_CURRENT_SOURCE_DIR}/include/lexer
    ${CMAKE_CURRENT_SOURCE_DIR}/include/parser
    ${CMAKE_CURRENT_SOURCE_DIR}/include/parser/ast
    ${CMAKE_CURRENT_SOURCE_DIR}/include/semantics
    ${CMAKE_CURRENT_SOURCE_DIR}/include/semantics/visitors
)

target_compile_options(atm PRIVATE
    -Wall 
    -Wextra 
    -Wpedantic
    -Wno-unused-parameter
    -Wnon-virtual-dtor
)

if(CMAKE_BUILD_TYPE STREQUAL "Debug" AND ENABLE_SANITIZERS)
    message(STATUS "Включение санитайзеров: AddressSanitizer + UndefinedBehaviorSanitizer")

    target_compile_options(atm PRIVATE 
        -fsanitize=address,undefined 
        -fno-omit-frame-pointer 
        -g
    )

    target_link_options(atm PRIVATE 
        -fsanitize=address,undefined
    )
endif()

message(STATUS "----------------------------------------")
message(STATUS "Проект: ${PROJECT_NAME} v${PROJECT_VERSION}")
message(STATUS "Тип сборки: ${CMAKE_BUILD_TYPE}")
message(STATUS "Стандарт C++: ${CMAKE_CXX_STANDARD}")
message(STATUS "----------------------------------------")