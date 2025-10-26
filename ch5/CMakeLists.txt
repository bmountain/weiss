# Variable
set(LIB_NAME ch5)

# Macro
function(configure_executable TARGET_NAME)
  target_link_libraries( ${TARGET_NAME} PRIVATE ${LIB_NAME})
  target_include_directories(${TARGET_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}, ../utility)
endfunction()

# Library
add_library(${LIB_NAME}
PrimeNumber.cpp
)
target_include_directories(${LIB_NAME}
PUBLIC
${CMAKE_CURRENT_SOURCE_DIR})

# Main
add_executable(
  CollisionCounter
  CollisionCounter.cpp
  PrimeNumber.cpp
)
target_link_libraries(
  CollisionCounter
  PRIVATE
  utility
)
target_include_directories(CollisionCounter
  PRIVATE
  ${CMKAE_SOURCE_DIR}/utility)


# Test
add_test_executable(TestCh5 TestCh5.cpp)
target_include_directories(TestCh5 PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(TestCh5 PRIVATE ${LIB_NAME})