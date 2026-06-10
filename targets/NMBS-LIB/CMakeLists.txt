add_library(NMBS-LIB SHARED)

configure_file(src/version.h.in src/nmbs/version.h @ONLY)

target_sources(NMBS-LIB
        PUBLIC
        FILE_SET nmbs_headers
        TYPE HEADERS
        BASE_DIRS include
        FILES
        include/nmbs/nmbs.h
        PRIVATE
        src/nmbs.cpp
)

set_target_properties(NMBS-LIB PROPERTIES
        VERSION ${PROJECT_VERSION}
        SOVERSION ${PROJECT_VERSION_MAJOR}
        OUTPUT_NAME nmbs
)

target_include_directories(NMBS-LIB
        PUBLIC
        "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
        "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>"
        PRIVATE
        src
        ${CMAKE_CURRENT_BINARY_DIR}/src
)

target_link_libraries(NMBS-LIB
        PRIVATE
        exiv2lib
)
