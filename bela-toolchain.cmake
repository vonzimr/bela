set(CMAKE_SYSTEM_NAME Linux)
set(CMAKE_SYSTEM_PROCESSOR arm)

set(triple arm-linux-gnueabihf)

set(CMAKE_C_COMPILER clang)
set(CMAKE_C_COMPILER_TARGET ${triple})
set(CMAKE_CXX_COMPILER clang++)
set(CMAKE_CXX_COMPILER_TARGET ${triple})
set(CMAKE_SYSROOT /usr/local/linaro/sysroot)

set(CMAKE_C_FLAGS "-v")

set(CMAKE_C_COMPILER_EXTERNAL_TOOLCHAIN /usr/local/linaro/${triple})
set(CMAKE_CXX_COMPILER_EXTERNAL_TOOLCHAIN /usr/local/linaro/${triple})