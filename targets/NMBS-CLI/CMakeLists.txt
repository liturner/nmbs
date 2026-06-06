add_executable(NMBS-CONFIDENTIALITY-LABEL)

target_sources(NMBS-CONFIDENTIALITY-LABEL
        PRIVATE
        src/nmbs-confidentiality-label.cpp
)

set_target_properties(NMBS-CONFIDENTIALITY-LABEL PROPERTIES
        VERSION ${PROJECT_VERSION}
        SOVERSION ${PROJECT_VERSION_MAJOR}
        OUTPUT_NAME nmbs-confidentiality-label
)

target_link_libraries(NMBS-CONFIDENTIALITY-LABEL
        PRIVATE
        NMBS-LIB
)

##
##
##

add_executable(NMBS-CANONICALIZE)

target_sources(NMBS-CANONICALIZE
        PRIVATE
        src/nmbs-canonicalize.cpp
)

set_target_properties(NMBS-CANONICALIZE PROPERTIES
        VERSION ${PROJECT_VERSION}
        SOVERSION ${PROJECT_VERSION_MAJOR}
        OUTPUT_NAME nmbs-canonicalize
)

target_link_libraries(NMBS-CANONICALIZE
        PRIVATE
        NMBS-LIB
)
