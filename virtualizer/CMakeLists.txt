set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wno-deprecated-register")

project(simple_wc_example CXX)

cmake_minimum_required(VERSION 3.1)

find_package(BISON REQUIRED)
find_package(FLEX REQUIRED)

BISON_TARGET(vc_parser
             vc_parser.yy
             ${CMAKE_CURRENT_BINARY_DIR}/vc_parser.tab.cc)
FLEX_TARGET(vc_lexer
            vc_lexer.l
            ${CMAKE_CURRENT_BINARY_DIR}/vc_lexer.yy.cc)
ADD_FLEX_BISON_DEPENDENCY(vc_lexer vc_parser)

add_executable(vcompiler
    main.cc
    vc_orchestrator.cc

    ${FLEX_vc_lexer_OUTPUTS}
    ${BISON_vc_parser_OUTPUTS}
)
target_include_directories(vcompiler
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${FLEX_INCLUDE_DIRS}
        ${CMAKE_CURRENT_BINARY_DIR})
set_property(TARGET vcompiler
             PROPERTY CXX_STANDARD 14)
