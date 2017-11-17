################################################################################
cmake_minimum_required (VERSION 3.9.0 FATAL_ERROR)
################################################################################

if("${CMAKE_SOURCE_DIR}" STREQUAL "${CMAKE_BINARY_DIR}")
  message (FATAL_ERROR
    "In-source builds are not supported. Please remove CMakeCache.txt from"
    " the source directories and configure an out-of-source build in another"
    " directory."
  )
endif()

project (ClangOnWindows)

add_executable (
  ClangOnWindows
  "Sources/main.cpp"
)

target_compile_definitions (ClangOnWindows
  PRIVATE
    "_UNICODE"
    "UNICODE"
)

install (
  TARGETS
    ClangOnWindows  
  RUNTIME DESTINATION
    "${CMAKE_SOURCE_DIR}/../__install-output/${PROJECT_NAME}"
)