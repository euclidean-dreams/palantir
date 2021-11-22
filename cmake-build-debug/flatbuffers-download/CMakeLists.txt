cmake_minimum_required(VERSION 3.13)
project(flatbuffers-download)
include(ExternalProject)
ExternalProject_Add(
        flatbuffers
        GIT_REPOSITORY git@github.com:google/flatbuffers.git
        GIT_TAG 6df40a2471737b27271bdd9b900ab5f3aec746c7
        SOURCE_DIR "/home/josiah/projects/code/impresario-systems/palantir/cmake-build-debug/flatbuffers-src"
        BINARY_DIR "/home/josiah/projects/code/impresario-systems/palantir/cmake-build-debug/flatbuffers-build"
        CONFIGURE_COMMAND ""
        BUILD_COMMAND ""
        INSTALL_COMMAND ""
        TEST_COMMAND ""
)
