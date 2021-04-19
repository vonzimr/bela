add_executable(wavetable
    ${CMAKE_SOURCE_DIR}/Bela/core/default_main.cpp
    render.cpp
    wavetable.cpp
    wavetablegroup.cpp
    interpolation.cpp
    functiongenerators.cpp
)

install(TARGETS wavetable DESTINATION)
