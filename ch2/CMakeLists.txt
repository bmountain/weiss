add_executable(loop loop.cpp)
target_include_directories(loop PRIVATE ../utility)

add_executable(RandomPermutation RandomPermutation.cpp)
target_include_directories(RandomPermutation PRIVATE ../utility)
# add_test_executable(TestRandomPermutation TestRandomPermutation.cpp RandomPermutation.cpp)

add_library(FindMatch FindMatch.cpp)
add_test_executable(TestFindMatch TestFindMatch.cpp FindMatch.cpp)

add_library(Gcd Gcd.cpp)
add_test_executable(TestGcd TestGcd.cpp Gcd.cpp)

add_library(IntermediateValue IntermediateValue.cpp)
add_test_executable(TestIntermediateValue TestIntermediateValue.cpp IntermediateValue.cpp)