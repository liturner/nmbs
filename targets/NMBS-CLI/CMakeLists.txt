add_executable(NMBS-CLI)

target_sources(NMBS-CLI
        PRIVATE
        src/nmbs-confidentiality-label.cpp
)

include_directories(${Boost_INCLUDE_DIRS})

set_target_properties(NMBS-CLI PROPERTIES
        LINKER_LANGUAGE CXX
        CXX_STANDARD 20
        CXX_STANDARD_REQUIRED ON
        CXX_EXTENSIONS OFF
        POSITION_INDEPENDENT_CODE 1
        VERSION ${PROJECT_VERSION}
        SOVERSION ${PROJECT_VERSION_MAJOR}
        OUTPUT_NAME nmbs-confidentiality-label
)

target_include_directories(NMBS-CLI
        PUBLIC
        "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
        "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>"
        PRIVATE
        src
)

target_link_libraries(NMBS-CLI
        PRIVATE
        Exiv2::exiv2lib
)