add_executable(sample-player-filter
    ${CMAKE_SOURCE_DIR}/Bela/core/default_main.cpp
    MonoFilePlayer.cpp
    render.cpp
)

target_link_libraries (sample-player-filter LINK_PUBLIC filters)

install(DIRECTORY ${CMAKE_CURRENT_LIST_DIR} DESTINATION /tmp/${INSTALL_PATH}
          FILES_MATCHING PATTERN "*.wav")

install(TARGETS sample-player-filter)
