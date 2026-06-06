cmake_minimum_required(VERSION 3.23)
project(
        TT-NMBS
        LANGUAGES CXX
        VERSION 1.0.0
)

set(CPACK_GENERATOR "TGZ")
set(CPACK_PACKAGE_VENDOR "TurnerTech")
set(CPACK_PACKAGE_CONTACT "luke.ian.turner@outlook.de")

set(CMAKE_DEBUG_POSTFIX "d")

include(CPack)
include(GoogleTest)
include(GNUInstallDirs)
include(CMakePackageConfigHelpers)

set(Boost_USE_STATIC_LIBS ON)

find_package(exiv2 "0.28.5" REQUIRED)
find_package(Boost "1.83.0" REQUIRED CONFIG)                      # libboost-all-dev
find_package(GTest "1.15.0" REQUIRED)                             # libgtest-dev
find_package(Doxygen "1.9.8" OPTIONAL_COMPONENTS dot mscgen dia)  # doxygen

enable_testing()

add_subdirectory(targets)