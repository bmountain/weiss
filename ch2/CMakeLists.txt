add_executable(loop loop.cpp)
target_include_directories(loop PRIVATE ../utility)

add_executable(RandomPermutation RandomPermutation.cpp)
target_include_directories(RandomPermutation PRIVATE ../utility)
# add_test_executable(TestRandomPermutation TestRandomPermutation.cpp RandomPermutation.cpp)