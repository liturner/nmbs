add_executable(NMBS-Verify)

target_sources(NMBS-Verify
        PRIVATE
        src/nmbs-verify.cpp
)

set_target_properties(NMBS-Verify PROPERTIES
        OUTPUT_NAME nmbs-verify
)

target_link_libraries(NMBS-Verify
        PRIVATE
        NMBS-Library
)

generate_manpage(NMBS-Verify "Reads and validates bound Confidentiality Labels from objects such as files.")

install(TARGETS NMBS-Verify
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
