cmake_minimum_required(VERSION 3.13)
project(palantir VERSION 0.1)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include(lib/cmake-utils/dependency-integrator.cmake)
integrate_cmake_dependency(
        NAME impresario-utils
        GIT_URL git@github.com:impresario-systems/impresario-utils.git
        GIT_TAG origin/dev
)

# SDL
find_package(SDL2 REQUIRED)
include_directories(palantir ${SDL2_INCLUDE_DIRS})

set(
        SOURCE_FILES
        src/gizmo/RGBColor.h
        src/Palantir.cpp src/Palantir.h
        src/framework/Libs.h
        src/framework/Constants.h src/SDLFailure.h
        src/gizmo/Tchotchke.cpp src/gizmo/Tchotchke.h src/percipient/CosmographerPercipient.cpp src/percipient/CosmographerPercipient.h

        src/framework/Framework.h src/Default.h)
list(APPEND TARGETS euclid)
add_executable(euclid src/main.cpp ${SOURCE_FILES})

# finalize
foreach (target IN LISTS TARGETS)
    target_include_directories(${target} PRIVATE src)
    target_link_libraries(${target} PRIVATE impresario-utils)
    target_link_libraries(${target} PRIVATE ${SDL2_LIBRARIES})
endforeach ()
