cmake_minimum_required(VERSION 3.10)

# Basic project setup
project(pi_grid C)

# Set C standard
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Enable testing
enable_testing()

# Optional dependencies
find_package(PkgConfig)
pkg_check_modules(LIBMONOME libmonome)
pkg_check_modules(ALSA alsa)

# Shared utilities library
add_library(grid STATIC src/note_utils.c)
target_include_directories(grid PUBLIC include)

# Main executable
add_executable(pi-grid src/main.c)
target_link_libraries(pi-grid PRIVATE grid)

# Unit tests
add_executable(test_note_utils tests/test_note_utils.c)
target_link_libraries(test_note_utils PRIVATE grid)
add_test(NAME note_utils COMMAND test_note_utils)

# Link against libmonome and ALSA if available
if(LIBMONOME_FOUND AND ALSA_FOUND)
  target_compile_definitions(pi-grid PRIVATE HAVE_LIBMONOME HAVE_ALSA)
  target_include_directories(pi-grid PRIVATE ${LIBMONOME_INCLUDE_DIRS} ${ALSA_INCLUDE_DIRS})
  target_link_libraries(pi-grid PRIVATE ${LIBMONOME_LIBRARIES} ${ALSA_LIBRARIES})
else()
  message(WARNING "Building without libmonome/ALSA; resulting binary prints hello only")
endif()

# Install target
install(TARGETS pi-grid RUNTIME DESTINATION bin)
