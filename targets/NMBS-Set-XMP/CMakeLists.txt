add_executable(NMBS-Set-XMP)

target_sources(NMBS-Set-XMP
        PRIVATE
        src/nmbs-set-xmp.cpp
)

set_target_properties(NMBS-Set-XMP PROPERTIES
        VERSION ${PROJECT_VERSION}
        SOVERSION ${PROJECT_VERSION_MAJOR}
        OUTPUT_NAME nmbs-set-xmp
)

target_link_libraries(NMBS-Set-XMP
        PRIVATE
        NMBS-Library
)
