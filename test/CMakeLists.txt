cmake_minimum_required(VERSION 3.12.0)

find_package(Catch2 CONFIG REQUIRED)

set(TARGET_MAIN testmain)
set(SOURCES_ADDITIONAL
	${one2III_SRC_DIR}/converter.cpp
	${one2III_SRC_DIR}/helper.cpp
	${one2III_SRC_DIR}/conversionrules.cpp
)

add_executable(${TARGET_MAIN} ${TARGET_MAIN}.cpp)
target_include_directories(${TARGET_MAIN} PRIVATE ${one2III_SRC_DIR})
target_include_directories(${TARGET_MAIN} SYSTEM PRIVATE ${Catch2_INCLUDE_DIRS})
target_sources(${TARGET_MAIN} PRIVATE ${SOURCES_ADDITIONAL})
target_link_libraries(${TARGET_MAIN} PRIVATE Catch2::Catch2)
