#   _____                           _           
#  | ____|_  ____ _ _ __ ___  _ __ | | ___  ___ 
#  |  _| \ \/ / _` | '_ ` _ \| '_ \| |/ _ \/ __|
#  | |___ >  < (_| | | | | | | |_) | |  __/\__ \
#  |_____/_/\_\__,_|_| |_| |_| .__/|_|\___||___/
#                            |_|                
cmake_minimum_required(VERSION 3.10)
project("C-CNC tests" VERSION 1.0 LANGUAGES C)

#   ____       _   _   _                 
#  / ___|  ___| |_| |_(_)_ __   __ _ ___ 
#  \___ \ / _ \ __| __| | '_ \ / _` / __|
#   ___) |  __/ |_| |_| | | | | (_| \__ \
#  |____/ \___|\__|\__|_|_| |_|\__, |___/
#                              |___/     
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_C_STANDARD 11)
set(SOURCES ${CMAKE_CURRENT_LIST_DIR}/src)
include_directories(${CMAKE_CURRENT_LIST_DIR}/include)

if(APPLE)
  # On Intel Macs, brew uses /usr/local
  if(EXISTS /usr/local)
    include_directories(/usr/local/include)
    link_directories(/usr/local/lib)
  endif()
  # on M1 Macs, brew uses /opt/homebrew:
  if(EXISTS /opt/homebrew)
    include_directories(/opt/homebrew/include)
    link_directories(/opt/homebrew/lib)
  endif()
endif()

#   _____                    _       
#  |_   _|_ _ _ __ __ _  ___| |_ ___ 
#    | |/ _` | '__/ _` |/ _ \ __/ __|
#    | | (_| | | | (_| |  __/ |_\__ \
#    |_|\__,_|_|  \__, |\___|\__|___/
#                 |___/              
add_executable(ex1 ${SOURCES}/exercise1.c)
add_executable(ex2 ${SOURCES}/exercise2.c)