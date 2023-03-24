# Minimum CMake version
cmake_minimum_required(VERSION 3.10)

# Define the project 
project("C-CNC tests" VERSION 1.0 LANGUAGES C)

# Settings 
set(CMAKE_BUILD_TYPE Debug) # 2 types of build: debug and revise (to revise and share final version)
set(CMAKE_C_STANDARD 11) #2011, old glory of C standard
set(SOURCES ${CMAKE_CURRENT_LIST_DIR}/src) # Collect the path of our source files
include_directories(${CMAKE_CURRENT_LIST_DIR}/include) # path of header files

if(APPLE)
  if(EXISTS /usr/local)
    include(/usr/local/include)
    link_libraries(/usr/local/lib)
  endif()
  # M1/M2
  if(EXISTS /opt/homebrew)
    include(/opt/homebrew/include)
    link_libraries(/opt/homebrew/lib)
  endif()
endif()

#   _____                    _       
#  |_   _|_ _ _ __ __ _  ___| |_ ___ 
#    | |/ _` | '__/ _` |/ _ \ __/ __|
#    | | (_| | | | (_| |  __/ |_\__ \
#    |_|\__,_|_|  \__, |\___|\__|___/
#                 |___/              
add_executable(0_hello ${SOURCES}/0_hello.c)
add_executable(2_basics ${SOURCES}/2_basics.c)
add_executable(4_include_guards ${SOURCES}/4_include_guards.c)
add_executable(1_basics ${SOURCES}/1_basics.c)
add_executable(6_inout_p ${SOURCES}/6_inout_p.c)
add_executable(3_file ${SOURCES}/3_file.c)