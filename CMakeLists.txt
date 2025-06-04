cmake_minimum_required(VERSION 3.10)

# Basic project setup
project(pi_grid C)

# Set C standard
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Optional dependencies
find_package(PkgConfig)
pkg_check_modules(LIBMONOME libmonome)
pkg_check_modules(ALSA alsa)

# Add the executable
add_executable(hello src/main.c)

# Link against libmonome and ALSA if available
if(LIBMONOME_FOUND AND ALSA_FOUND)
  target_compile_definitions(hello PRIVATE HAVE_LIBMONOME HAVE_ALSA)
  target_include_directories(hello PRIVATE ${LIBMONOME_INCLUDE_DIRS} ${ALSA_INCLUDE_DIRS})
  target_link_libraries(hello PRIVATE ${LIBMONOME_LIBRARIES} ${ALSA_LIBRARIES})
else()
  message(WARNING "Building without libmonome/ALSA; resulting binary prints hello only")
endif()
