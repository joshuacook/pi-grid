cmake_minimum_required(VERSION 3.10)

# Basic project setup
project(pi_grid C)

# Set C standard
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Add the executable
add_executable(hello src/main.c)
