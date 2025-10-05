# testing CMake and GTest
add_executable(hello hello.cpp)
add_test_executable(hello_test hello_test.cpp)

# 1.1
add_executable(selection selection.cpp)
add_test_executable(selection_test selection_test.cpp)

add_executable(selection_time selection_time.cpp)

# 1.4
add_executable(include include.cpp)

# 1.5
add_library(count_binary_one count_binary_one.cpp)
target_include_directories(count_binary_one PUBLIC "{CMAKE_CURRENT_SOURCE_DIR}")

add_executable(count_binary_one_main count_binary_one_main.cpp)
target_link_libraries(count_binary_one_main PRIVATE count_binary_one)

add_test_executable(count_binary_one_test count_binary_one_test.cpp)
target_link_libraries(count_binary_one_test PRIVATE count_binary_one)

# 1. 13
add_library(collection collection.h)
set_target_properties(collection PROPERTIES LINKER_LANGUAGE CXX)
target_include_directories(collection PUBLIC "{CMAKE_CURRENT_SOURCE_DIR}")

add_test_executable(collection_test collection_test.cpp)
target_link_libraries(collection_test PRIVATE collection)

# 1.14
add_library(OrderedCollection OrderedCollection.h)
set_target_properties(OrderedCollection PROPERTIES LINKER_LANGUAGE CXX)
add_test_executable(OrderedCollectionTest OrderedCollectionTest.cpp)
target_link_libraries(OrderedCollectionTest PRIVATE OrderedCollection)