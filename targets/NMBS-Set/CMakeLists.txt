add_executable(NMBS-Set)

target_sources(NMBS-Set
        PRIVATE
        src/nmbs-set.cpp
)

set_target_properties(NMBS-Set PROPERTIES
        OUTPUT_NAME nmbs-set
)

target_link_libraries(NMBS-Set
        PRIVATE
        NMBS-Library
)

generate_manpage(NMBS-Set "Binds ADatP-4774 Confidentiality Labels to data objects such as files")

install(TARGETS NMBS-Set
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
