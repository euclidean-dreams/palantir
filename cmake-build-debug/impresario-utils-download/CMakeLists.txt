cmake_minimum_required(VERSION 3.13)
project(impresario-utils-download)
include(ExternalProject)
ExternalProject_Add(
        impresario-utils
        GIT_REPOSITORY git@github.com:impresario-systems/impresario-utils.git
        GIT_TAG origin/dev
        SOURCE_DIR "/home/josiah/projects/code/impresario-systems/palantir/cmake-build-debug/impresario-utils-src"
        BINARY_DIR "/home/josiah/projects/code/impresario-systems/palantir/cmake-build-debug/impresario-utils-build"
        CONFIGURE_COMMAND ""
        BUILD_COMMAND ""
        INSTALL_COMMAND ""
        TEST_COMMAND ""
)
