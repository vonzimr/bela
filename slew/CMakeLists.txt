add_library(slew slew.cpp)
target_include_directories (slew PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries (slew LINK_PUBLIC clock interpolation)
