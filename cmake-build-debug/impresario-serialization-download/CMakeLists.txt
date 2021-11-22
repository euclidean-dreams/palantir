cmake_minimum_required(VERSION 3.13)
project(impresario-serialization-download)
include(ExternalProject)
ExternalProject_Add(
        impresario-serialization
        GIT_REPOSITORY git@github.com:impresario-systems/impresario-serialization.git
        GIT_TAG origin/dev
        SOURCE_DIR "/home/josiah/projects/code/impresario-systems/palantir/cmake-build-debug/impresario-serialization-src"
        BINARY_DIR "/home/josiah/projects/code/impresario-systems/palantir/cmake-build-debug/impresario-serialization-build"
        CONFIGURE_COMMAND ""
        BUILD_COMMAND ""
        INSTALL_COMMAND ""
        TEST_COMMAND ""
)
