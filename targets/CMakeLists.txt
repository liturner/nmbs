add_subdirectory(NMBS-Library)
add_subdirectory(NMBS-Set-XMP)
add_subdirectory(NMBS-Tests)

# Add this to force the cli executables to be available for GTest
add_dependencies(NMBS-Tests NMBS-Set-XMP)

#
# Doxygen, man pages etc.
#

if (DOXYGEN_FOUND)
    set(DOXYGEN_GENERATE_HTML YES)
    set(DOXYGEN_GENERATE_MAN YES)
    set(DOXYGEN_MACRO_EXPANSION YES)
    set(DOXYGEN_EXCLUDE_SYMBOLS std::*)
    doxygen_add_docs(doxygen ALL
            NMBS-Library/include
    )

    install(DIRECTORY
            ${CMAKE_CURRENT_BINARY_DIR}/man/
            TYPE MAN
    )
endif ()

# Generate the man1 page from the executables --help command.
find_program(HELP2MAN_EXECUTABLE help2man)
if(HELP2MAN_EXECUTABLE)
    message(STATUS "Found help2man: ${HELP2MAN_EXECUTABLE}")

    set(MAN_PAGE "${CMAKE_CURRENT_BINARY_DIR}/nmbs-set-xmp.1")

    # 3. Create the rule to generate the man page
    add_custom_command(
            OUTPUT ${MAN_PAGE}
            # help2man executes the target binary directly from the build directory
            COMMAND ${HELP2MAN_EXECUTABLE}
            --no-discard-stderr
            --name="A brief one-line description of what mytool does"
            --output=${MAN_PAGE}
            $<TARGET_FILE:NMBS-Set-XMP>
            DEPENDS NMBS-Set-XMP
            COMMENT "Generating man page using help2man"
            VERBATIM
    )

    # Tie the custom command to a target so it actually runs during 'make'.
    add_custom_target(manpages ALL DEPENDS ${MAN_PAGE})

    # 5. Install the generated man page to the standard location
    install(FILES ${MAN_PAGE} DESTINATION ${CMAKE_INSTALL_MANDIR}/man1)
else()
    message(WARNING "help2man not found. Man pages will not be generated.")
endif()

#
# Resources, Files etc.
#

install(FILES
        NMBS-Library/resources/nl-cl.xsd
        NMBS-Library/resources/nl-mb.xsd
        DESTINATION share/xml/schema
)

#
# Targets and *Targets.cmake
#

install(TARGETS NMBS-Library NMBS-Set-XMP
        EXPORT ${PROJECT_NAME}Targets
        FILE_SET nmbs_headers
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

install(EXPORT ${PROJECT_NAME}Targets
        FILE ${PROJECT_NAME}Targets.cmake
        NAMESPACE ${PROJECT_NAME}::
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}
)

#
# *Config*.cmake
#

configure_package_config_file(${CMAKE_CURRENT_SOURCE_DIR}/Config.cmake.in
        "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake"
        INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}
)

write_basic_package_version_file(
        "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake"
        COMPATIBILITY SameMinorVersion
)

install(FILES
        "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake"
        "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake"
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}
)
