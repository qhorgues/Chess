# Seulement une version de cmake >= 3.22
cmake_minimum_required(VERSION 3.22.0)

project(Chess)

set (INCLUDE_DIRECTORIES ../include)
set (SOURCE_DIR ../src)

include_directories(${INCLUDE_DIRECTORIES})

# Les headers
set (HEADERS
    ${INCLUDE_DIRECTORIES}/Board.h
    ${INCLUDE_DIRECTORIES}/listMove.h
    ${INCLUDE_DIRECTORIES}/except.h
)

# Les fichiers sources
set (SOURCES
    ${SOURCE_DIR}/main.c
    ${SOURCE_DIR}/Board.c
    ${SOURCE_DIR}/listMove.c
)

# C 17
set (CMAKE_C_STANDARD 17)

# L'executable chess cree a partir des sources et des headers
add_executable (Chess ${SOURCES} ${HEADERS}) 

