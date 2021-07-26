cmake_minimum_required(VERSION 3.6)

# Global properties
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# Project name
project(linkking)

# Doxygen
find_package(Doxygen)
if(DOXYGEN_FOUND)
  set(DOXYGEN "doxygen")
  if(NOT TARGET ${DOXYGEN})
    add_custom_command(OUTPUT "Doxyfile" COMMAND ${DOXYGEN_EXECUTABLE} "Doxyfile" WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/documents")
    add_custom_target(${DOXYGEN} DEPENDS "Doxyfile")
    set_target_properties(${DOXYGEN} PROPERTIES FOLDER "doxygen")
  endif()
endif()

# CMake module path
set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

# Compiler features
include(SetCompilerFeatures)
include(SetCompilerWarnings)
include(SetPlatformFeatures)
include(SystemInformation)

# External packages
if(CYGWIN)
  set(OPENSSL_ROOT_DIR "/usr/lib")
  set(OPENSSL_INCLUDE_DIR "/usr/include")
  set(OPENSSL_CRYPTO_LIBRARY "/usr/lib/libcrypto.dll.a")
  set(OPENSSL_SSL_LIBRARY "/usr/lib/libssl.dll.a")
elseif(MINGW)
  set(OPENSSL_ROOT_DIR "${CMAKE_CURRENT_SOURCE_DIR}/modules/OpenSSL/MinGW")
  set(OPENSSL_USE_STATIC_LIBS TRUE)
elseif(MSVC)
  set(OPENSSL_ROOT_DIR "${CMAKE_CURRENT_SOURCE_DIR}/modules/OpenSSL/VS")
  set(OPENSSL_USE_STATIC_LIBS TRUE)
  set(OPENSSL_MSVC_STATIC_RT TRUE)
endif()
find_package(OpenSSL REQUIRED)
if(WIN32)
  find_package(Crypt)
  find_package(WinSock)
endif()

# Modules
add_subdirectory("modules")
add_subdirectory(src/common)
add_subdirectory(src/lib)
add_subdirectory(src/rnp)
add_subdirectory(src/rnpkeys)

# Link libraries
list(APPEND LINKLIBS ${OPENSSL_LIBRARIES})
if(WIN32)
  list(APPEND LINKLIBS ${CRYPT_LIBRARIES})
  list(APPEND LINKLIBS ${WINSOCK_LIBRARIES})
endif()
list(APPEND LINKLIBS cppcommon)

# OpenSSL libraries
message(STATUS "OpenSSL version: ${OPENSSL_VERSION} ${OPENSSL_INCLUDE_DIR} ${OPENSSL_LIBRARIES}")

# System directories
include_directories(SYSTEM "${CMAKE_CURRENT_SOURCE_DIR}/modules")

# Library
file(GLOB_RECURSE LIB_HEADER_FILES "include/*.h" "source/*.h")
file(GLOB_RECURSE LIB_INLINE_FILES "include/*.inl" "source/*.inl")
file(GLOB_RECURSE LIB_SOURCE_FILES "include/*.cpp" "source/*.cpp")
add_library(linkking ${LIB_HEADER_FILES} ${LIB_INLINE_FILES} ${LIB_SOURCE_FILES})
set_target_properties(linkking PROPERTIES COMPILE_FLAGS "${PEDANTIC_COMPILE_FLAGS}" FOLDER "libraries")
target_include_directories(linkking PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")
target_link_libraries(linkking ${LINKLIBS} asio)
list(APPEND INSTALL_TARGETS linkking)
list(APPEND LINKLIBS linkking)

# Additional module components: benchmarks, server, plugins, tests, tools and install
if(NOT LINKKINGSERVER_MODULE)

  # Server
  file(GLOB SERVE_HEADER_FILES "serve/*.h")
  file(GLOB SERVE_INLINE_FILES "serve/*.inl")
  file(GLOB SERVE_SOURCE_FILES RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}/serve" "serve/*.cpp")
  foreach(SERVE_SOURCE_FILE ${SERVE_SOURCE_FILES})
    string(REGEX REPLACE "(.*)\\.cpp" "\\1" SERVE_NAME ${SERVE_SOURCE_FILE})
    set(SERVE_TARGET "linkking-serve-${SERVE_NAME}")
    add_executable(${SERVE_TARGET} ${SERVE_HEADER_FILES} ${SERVE_INLINE_FILES} "serve/${SERVE_SOURCE_FILE}")
    set_target_properties(${SERVE_TARGET} PROPERTIES COMPILE_FLAGS "${PEDANTIC_COMPILE_FLAGS}" FOLDER "severs")
    target_link_libraries(${SERVE_TARGET} ${LINKLIBS})
    list(APPEND INSTALL_TARGETS ${SERVE_TARGET})
    list(APPEND INSTALL_TARGETS_PDB ${SERVE_TARGET})
  endforeach()

  # Benchmarks
  file(GLOB BENCHMARK_HEADER_FILES "performance/*.h")
  file(GLOB BENCHMARK_INLINE_FILES "performance/*.inl")
  file(GLOB BENCHMARK_SOURCE_FILES RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}/performance" "performance/*.cpp")
  foreach(BENCHMARK_SOURCE_FILE ${BENCHMARK_SOURCE_FILES})
    string(REGEX REPLACE "(.*)\\.cpp" "\\1" BENCHMARK_NAME ${BENCHMARK_SOURCE_FILE})
    set(BENCHMARK_TARGET "linkking-performance-${BENCHMARK_NAME}")
    add_executable(${BENCHMARK_TARGET} ${BENCHMARK_HEADER_FILES} ${BENCHMARK_INLINE_FILES} "performance/${BENCHMARK_SOURCE_FILE}")
    set_target_properties(${BENCHMARK_TARGET} PROPERTIES COMPILE_FLAGS "${PEDANTIC_COMPILE_FLAGS}" FOLDER "performance")
    target_link_libraries(${BENCHMARK_TARGET} ${LINKLIBS} cppbenchmark)
    list(APPEND INSTALL_TARGETS ${BENCHMARK_TARGET})
    list(APPEND INSTALL_TARGETS_PDB ${BENCHMARK_TARGET})
  endforeach()

  # Tests
  file(GLOB TESTS_HEADER_FILES "tests/*.h")
  file(GLOB TESTS_INLINE_FILES "tests/*.inl")
  file(GLOB TESTS_SOURCE_FILES "tests/*.cpp")
  add_executable(linkking-tests ${TESTS_HEADER_FILES} ${TESTS_INLINE_FILES} ${TESTS_SOURCE_FILES} ${Catch2})
  set_target_properties(linkking-tests PROPERTIES COMPILE_FLAGS "${PEDANTIC_COMPILE_FLAGS}" FOLDER "tests")
  target_include_directories(linkking-tests PRIVATE ${Catch2})
  target_link_libraries(linkking-tests ${LINKLIBS})
  list(APPEND INSTALL_TARGETS linkking-tests)
  list(APPEND INSTALL_TARGETS_PDB linkking-tests)

  # CTest
  enable_testing()
  add_test(linkking-tests linkking-tests --durations yes --order lex)

  # Install
  install(TARGETS ${INSTALL_TARGETS}
    RUNTIME DESTINATION "${PROJECT_SOURCE_DIR}/bin"
    LIBRARY DESTINATION "${PROJECT_SOURCE_DIR}/bin"
    ARCHIVE DESTINATION "${PROJECT_SOURCE_DIR}/bin")

  # Install *.pdb files
  if(MSVC)
    foreach(INSTALL_TARGET_PDB ${INSTALL_TARGETS_PDB})
      install(FILES $<TARGET_PDB_FILE:${INSTALL_TARGET_PDB}> DESTINATION "${PROJECT_SOURCE_DIR}/bin")
    endforeach()
  endif()

endif()
