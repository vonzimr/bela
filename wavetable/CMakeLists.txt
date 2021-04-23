add_executable(wavetable
    ${CMAKE_SOURCE_DIR}/Bela/core/default_main.cpp
    render.cpp
    wavetable.cpp
    wavetablegroup.cpp
        functiongenerators.cpp
)

target_link_libraries (wavetable LINK_PUBLIC clock slew interpolation)


install(TARGETS wavetable DESTINATION)
