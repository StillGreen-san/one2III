cmake_minimum_required(VERSION 3.12.0)

find_package(Catch2 CONFIG REQUIRED)

set(TARGET_MAIN testmain)
set(SOURCES_TEST
	${one2III_TEST_DIR}/converter_test.cpp
	${one2III_TEST_DIR}/conversionfunctions_test.cpp
	${one2III_TEST_DIR}/conversionrule_test.cpp
	${one2III_TEST_DIR}/converter_test.cpp
	${one2III_TEST_DIR}/helperfunctions_test.cpp
	${one2III_TEST_DIR}/rulebook_test.cpp
	${one2III_TEST_DIR}/ruletype_test.cpp
)
set(SOURCES_ADDITIONAL
	${one2III_SRC_DIR}/conversionfunctions.cpp
	${one2III_SRC_DIR}/conversionrule.cpp
	${one2III_SRC_DIR}/converter.cpp
	${one2III_SRC_DIR}/helperfunctions.cpp
	${one2III_SRC_DIR}/rulebook.cpp
	${one2III_SRC_DIR}/ruletype.cpp
)

add_executable(${TARGET_MAIN} ${TARGET_MAIN}.cpp)
target_include_directories(${TARGET_MAIN} PRIVATE ${one2III_INC_DIR})
target_include_directories(${TARGET_MAIN} SYSTEM PRIVATE ${Catch2_INCLUDE_DIRS})
target_sources(${TARGET_MAIN} PRIVATE ${SOURCES_TEST} ${SOURCES_ADDITIONAL})
target_link_libraries(${TARGET_MAIN} PRIVATE Catch2::Catch2)
