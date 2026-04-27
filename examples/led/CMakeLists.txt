cmake_minimum_required(VERSION 3.16)

set(EXTRA_COMPONENT_DIRS "${CMAKE_CURRENT_LIST_DIR}/../../components")

include($ENV{IDF_PATH}/tools/cmake/project.cmake)
project(led_matter_accessory)

idf_build_get_property(idf_version IDF_VER)
message(STATUS "Detected ESP-IDF version: ${idf_version}")

if(idf_version VERSION_LESS "5.4.0")
    message(FATAL_ERROR
            "Unsupported ESP-IDF version: ${idf_version}. "
            "This example requires ESP-IDF >= 5.4.0 and currently targets the 5.4.x dependency set.")
endif()
