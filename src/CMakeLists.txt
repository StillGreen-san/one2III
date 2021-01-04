cmake_minimum_required(VERSION 3.12.0)

set(TARGET_MAIN one2IIImain)
set(SOURCES_ADDITIONAL
	conversionfunctions.cpp
	conversionrule.cpp
	converter.cpp
	helperfunctions.cpp
	rulebook.cpp
	ruletype.cpp
	simplemenu.cpp
	conversionstates.cpp
)

add_executable(${TARGET_MAIN} ${TARGET_MAIN}.cpp)
target_include_directories(${TARGET_MAIN} PRIVATE ${one2III_INC_DIR})
target_sources(${TARGET_MAIN} PRIVATE ${SOURCES_ADDITIONAL})
