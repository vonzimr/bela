add_library(filters firstorderlpf.cpp secondorderlpf.cpp)
target_include_directories (filters PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
