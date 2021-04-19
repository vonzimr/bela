add_executable(wavetable
    ${CMAKE_SOURCE_DIR}/Bela/core/default_main.cpp
    render.cpp
    wavetable.cpp
    wavetablegroup.cpp
    interpolation.cpp
    functiongenerators.cpp
)

target_link_libraries (wavetable LINK_PUBLIC clock)

install(TARGETS wavetable DESTINATION)
