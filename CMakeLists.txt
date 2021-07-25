cmake_minimum_required( VERSION 3.17.0 )

project( one2III CXX )

set( CMAKE_CXX_STANDARD 17 )
set( CMAKE_CXX_STANDARD_REQUIRED ON )
set( CMAKE_INTERPROCEDURAL_OPTIMIZATION TRUE )

find_package( Catch2 CONFIG )
if( NOT Catch2_FOUND )
	Include( FetchContent )
	FetchContent_Declare(
	Catch2
	GIT_REPOSITORY https://github.com/catchorg/Catch2.git
	GIT_TAG        v2.13.1
	)
	FetchContent_MakeAvailable( Catch2 )
endif( )

include( ${CMAKE_CURRENT_SOURCE_DIR}/cpp_starter_project/cmake/CompilerWarnings.cmake )
add_library( project_warnings INTERFACE )
set_project_warnings( project_warnings )
link_libraries( project_warnings )

include( ${CMAKE_CURRENT_SOURCE_DIR}/cpp_starter_project/cmake/StaticAnalyzers.cmake )

set( one2III_INC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/inc )
set( one2III_SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src )
set( one2III_TEST_DIR ${CMAKE_CURRENT_SOURCE_DIR}/test )

set( TARGET_LIB one2III-lib )
set( TARGET_MAIN one2III )
set( TARGET_TEST one2III-test )

set( SOURCES_LIB
	${one2III_SRC_DIR}/conversionfunctions.cpp
	${one2III_SRC_DIR}/conversionrule.cpp
	${one2III_SRC_DIR}/converter.cpp
	${one2III_SRC_DIR}/helperfunctions.cpp
	${one2III_SRC_DIR}/rulebook.cpp
)
set( SOURCES_MAIN
	${one2III_SRC_DIR}/simplemenu.cpp
	${one2III_SRC_DIR}/one2IIImain.cpp
)
set( SOURCES_TEST
	${one2III_TEST_DIR}/converter_test.cpp
	${one2III_TEST_DIR}/conversionfunctions_test.cpp
	${one2III_TEST_DIR}/converter_test.cpp
	${one2III_TEST_DIR}/helperfunctions_test.cpp
	${one2III_TEST_DIR}/rulebook_test.cpp
	${one2III_TEST_DIR}/testmain.cpp
)

add_library( ${TARGET_LIB} STATIC ${SOURCES_LIB} )
target_include_directories( ${TARGET_LIB} PUBLIC ${one2III_INC_DIR} )

add_executable( ${TARGET_MAIN} ${SOURCES_MAIN} )
target_link_libraries( ${TARGET_MAIN} PRIVATE ${TARGET_LIB} )

add_executable( ${TARGET_TEST} ${SOURCES_TEST} )
target_include_directories( ${TARGET_TEST} SYSTEM PRIVATE ${Catch2_INCLUDE_DIRS} )
target_link_libraries( ${TARGET_TEST} PRIVATE ${TARGET_LIB} Catch2::Catch2 )
