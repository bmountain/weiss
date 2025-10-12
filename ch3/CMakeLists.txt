add_library(Ch3 
  TwoLists.cpp
)

# Main
add_executable(TwoListsMain TwoListsMain.cpp TwoLists.cpp)
target_include_directories(TwoListsMain PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(TwoListsMain PRIVATE ../utility)

add_executable(JosephasMain JosephasMain.cpp Josephas.cpp)
target_include_directories(JosephasMain PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(JosephasMain PRIVATE ../utility)

# Test
add_test_executable(TestCh3 TestCh3.cpp TwoLists.cpp Josephas.cpp)