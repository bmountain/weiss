# Variable
set(LIB_NAME ch3)

# Macro
function(configure_executable TARGET_NAME)
  target_link_libraries( ${TARGET_NAME} PRIVATE ${LIB_NAME})
  target_include_directories(${TARGET_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}, ../utility)
endfunction()


# Library
add_library(${LIB_NAME} 
  TwoLists.cpp
  Josephas.cpp
  IsBalanced.cpp
  CalcPostFix.cpp
)
target_include_directories(ch3 PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# Main
add_executable(TwoListsMain TwoListsMain.cpp)
configure_executable(TwoListsMain)

add_executable(JosephasMain JosephasMain.cpp)
configure_executable(JosephasMain)

add_executable(MainMinStack MainMinStack.cpp)
configure_executable(MainMinStack)

# Test
add_test_executable(TestCh3 TestCh3.cpp)
configure_executable(TestCh3)