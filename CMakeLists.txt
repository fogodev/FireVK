cmake_minimum_required(VERSION 3.5)
project(FireVK)

set(CMAKE_C_STANDARD 11)
set(CMAKE_BUILD_TYPE Release)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(HEADER_FILES
    include/helpers/helpers.h
    include/radixmp/radixmp.h
    include/validkmers/validkmers.h
    )

set(SOURCE_FILES
    src/radixmp/radixmp.c
    src/validkmers/validkmers.c
    src/main.c
    )

find_package(OpenMP REQUIRED)
if (OPENMP_FOUND)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")
    add_executable(FireVK ${HEADER_FILES} ${SOURCE_FILES})
else()
    error("OpenMP is required to build this project")
endif()
