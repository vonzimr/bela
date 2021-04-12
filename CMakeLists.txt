cmake_minimum_required(VERSION 3.0.0)
project(Salt VERSION 0.1.0)

include(CTest)
enable_testing()

add_executable(Salt main.cpp)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O3 -g -fPIC -ftree-vectorize -ffast-math")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -g -fPIC -ftree-vectorize -ffast-math")

SET(CMAKE_FIND_LIBRARY_PREFIXES "lib" "xenomai")
set(BELA_SYSROOT "/usr/local/linaro/BelaSysroot")
set(XENOMAI "/usr/local/linaro/BelaSysroot/usr/xenomai")

message(STATUS "Sysroot is: ${CMAKE_SYSROOT}")
message(STATUS "Bela Sysroot is: ${BELA_SYSROOT}")
message(STATUS "suffixes: ${CMAKE_FIND_LIBRARY_SUFFIXES}")

find_library(
    LIB_MATH_NEON
    NAMES mathneon
    PATHS ${BELA_SYSROOT}/usr/lib
    )

find_library(
    LIB_NE10
    NAMES NE10
    PATHS ${BELA_SYSROOT}/usr/lib
    )

find_library(
    LIB_PRUSSDRV
    NAMES prussdrv
    PATHS ${BELA_SYSROOT}/usr/local/lib
    )


find_library(
    LIB_BELA
    NAMES bela
    PATHS ${BELA_SYSROOT}/root/Bela/lib
    )

find_library(
    LIB_BELA_EXTRA
    NAMES belaextra
    PATHS ${BELA_SYSROOT}/root/Bela/lib
    )

if (${LIB_MATH_NEON})
    message(FATAL_ERROR "mathneon not found")
else ()
    message(STATUS "mathneon: ${LIB_MATH_NEON}")
endif()
if (${LIB_NE10})
    message(FATAL_ERROR "NE10 not found")
else ()
    message(STATUS "NE10: ${LIB_NE10}")
endif()

if (${LIB_PRUSSDRV})
    message(FATAL_ERROR "prussdrv not found")
else ()
    message(STATUS "prussdrv: ${LIB_PRUSSDRV}")
endif()

if (${LIB_BELA})
    message(FATAL_ERROR "libbela not found")
else ()
    message(STATUS "libbela: ${LIB_BELA}")
endif()

if (${LIB_BELA_EXTRA})
    message(FATAL_ERROR "libbelaextra not found")
else ()
    message(STATUS "libbelaextra: ${LIB_BELA_EXTRA}")
endif()

link_libraries(${LIB_MATH_NEON} ${LIB_NE10} ${LIB_BELA} ${LIB_BELA_EXTRA})


include_directories(
    ${CMAKE_SYSROOT}/usr/include
    ${CMAKE_SYSROOT}/usr/include/c++/6.3.0
    ${CMAKE_SYSROOT}/usr/include/c++/6.3.0/cmath
    ${CMAKE_SYSROOT}/usr/include/arm-linux-gnueabihf/c++/6.3.0
    ./Bela/libraries
    ./Bela/include
    ./Bela/include/legacy
    ${XENOMAI}/include
    ${XENOMAI}/usr/include
    ${BELA_SYSROOT}/usr/include
    ${BELA_SYSROOT}/usr/local/include
    ${BELA_SYSROOT}/usr/local/include
)


link_directories(
    ${CMAKE_SYSROOT}/usr/lib/gcc/arm-linux-gnueabihf/6.3.0
    ${CMAKE_SYSROOT}/usr/local/lib
    ${XENOMAI}/lib
    ${BELA_SYSROOT}/usr/lib
    ${BELA_SYSROOT}/usr/local/lib
)

link_libraries(
    cobalt modechk pthread rt
    prussdrv asound seasocks NE10 mathneon dl
    pd atomic
)


add_subdirectory(wavetable)

install(TARGETS wavetable)
