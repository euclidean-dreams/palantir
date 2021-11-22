
if(NOT "/home/josiah/projects/code/impresario-systems/palantir/cmake-build-debug/impresario-serialization-download/impresario-serialization-prefix/src/impresario-serialization-stamp/impresario-serialization-gitinfo.txt" IS_NEWER_THAN "/home/josiah/projects/code/impresario-systems/palantir/cmake-build-debug/impresario-serialization-download/impresario-serialization-prefix/src/impresario-serialization-stamp/impresario-serialization-gitclone-lastrun.txt")
  message(STATUS "Avoiding repeated git clone, stamp file is up to date: '/home/josiah/projects/code/impresario-systems/palantir/cmake-build-debug/impresario-serialization-download/impresario-serialization-prefix/src/impresario-serialization-stamp/impresario-serialization-gitclone-lastrun.txt'")
  return()
endif()

execute_process(
  COMMAND ${CMAKE_COMMAND} -E rm -rf "/home/josiah/projects/code/impresario-systems/palantir/cmake-build-debug/impresario-serialization-src"
  RESULT_VARIABLE error_code
  )
if(error_code)
  message(FATAL_ERROR "Failed to remove directory: '/home/josiah/projects/code/impresario-systems/palantir/cmake-build-debug/impresario-serialization-src'")
endif()

# try the clone 3 times in case there is an odd git clone issue
set(error_code 1)
set(number_of_tries 0)
while(error_code AND number_of_tries LESS 3)
  execute_process(
    COMMAND "/usr/bin/git"  clone --no-checkout --config "advice.detachedHead=false" "git@github.com:impresario-systems/impresario-serialization.git" "impresario-serialization-src"
    WORKING_DIRECTORY "/home/josiah/projects/code/impresario-systems/palantir/cmake-build-debug"
    RESULT_VARIABLE error_code
    )
  math(EXPR number_of_tries "${number_of_tries} + 1")
endwhile()
if(number_of_tries GREATER 1)
  message(STATUS "Had to git clone more than once:
          ${number_of_tries} times.")
endif()
if(error_code)
  message(FATAL_ERROR "Failed to clone repository: 'git@github.com:impresario-systems/impresario-serialization.git'")
endif()

execute_process(
  COMMAND "/usr/bin/git"  checkout origin/dev --
  WORKING_DIRECTORY "/home/josiah/projects/code/impresario-systems/palantir/cmake-build-debug/impresario-serialization-src"
  RESULT_VARIABLE error_code
  )
if(error_code)
  message(FATAL_ERROR "Failed to checkout tag: 'origin/dev'")
endif()

set(init_submodules TRUE)
if(init_submodules)
  execute_process(
    COMMAND "/usr/bin/git"  submodule update --recursive --init 
    WORKING_DIRECTORY "/home/josiah/projects/code/impresario-systems/palantir/cmake-build-debug/impresario-serialization-src"
    RESULT_VARIABLE error_code
    )
endif()
if(error_code)
  message(FATAL_ERROR "Failed to update submodules in: '/home/josiah/projects/code/impresario-systems/palantir/cmake-build-debug/impresario-serialization-src'")
endif()

# Complete success, update the script-last-run stamp file:
#
execute_process(
  COMMAND ${CMAKE_COMMAND} -E copy
    "/home/josiah/projects/code/impresario-systems/palantir/cmake-build-debug/impresario-serialization-download/impresario-serialization-prefix/src/impresario-serialization-stamp/impresario-serialization-gitinfo.txt"
    "/home/josiah/projects/code/impresario-systems/palantir/cmake-build-debug/impresario-serialization-download/impresario-serialization-prefix/src/impresario-serialization-stamp/impresario-serialization-gitclone-lastrun.txt"
  RESULT_VARIABLE error_code
  )
if(error_code)
  message(FATAL_ERROR "Failed to copy script-last-run stamp file: '/home/josiah/projects/code/impresario-systems/palantir/cmake-build-debug/impresario-serialization-download/impresario-serialization-prefix/src/impresario-serialization-stamp/impresario-serialization-gitclone-lastrun.txt'")
endif()

