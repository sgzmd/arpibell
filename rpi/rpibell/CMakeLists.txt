cmake_minimum_required(VERSION 3.2)
project(rpibell)

SET(requiredlibs)

FIND_PACKAGE(CURL)
IF(CURL_FOUND)
    INCLUDE_DIRECTORIES(${CURL_INCLUDE_DIR})
    SET(requiredlibs ${requiredlibs} ${CURL_LIBRARIES} )
ELSE(CURL_FOUND)
    MESSAGE(FATAL_ERROR "Could not find the CURL library and development files.")
ENDIF(CURL_FOUND)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.c mkaddr.c mkaddr.h pushover.c pushover.h pushover_api_constants.c pushover_api_constants.h)
add_executable(rpibell ${SOURCE_FILES})
target_link_libraries(rpibell curl)