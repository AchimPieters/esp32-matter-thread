cmake_minimum_required(VERSION 3.16)

set(EXTRA_COMPONENT_DIRS "${CMAKE_CURRENT_LIST_DIR}/../../components")

include($ENV{IDF_PATH}/tools/cmake/project.cmake)
project(led_matter_accessory)

if(IDF_VERSION VERSION_LESS "5.4")
    message(FATAL_ERROR
            "Unsupported ESP-IDF version: ${IDF_VERSION}. "
            "This example requires ESP-IDF >= 5.4 and currently targets the 5.4.x dependency set.")
endif()
