# Variable
set(LIB_NAME ch4)

# Macro
function(configure_executable TARGET_NAME)
  target_link_libraries( ${TARGET_NAME} PRIVATE ${LIB_NAME})
  target_include_directories(${TARGET_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}, ../utility)
endfunction()


# Library
# add_library(${LIB_NAME} 
#   TwoLists.cpp
#   Josephas.cpp
#   IsBalanced.cpp
#   CalcPostFix.cpp
#   Convert.cpp
# )
# target_include_directories(ch4 PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# Test
add_test_executable(TestCh4 TestCh4.cpp)
target_include_directories(TestCh4 PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})