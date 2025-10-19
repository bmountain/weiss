function(configure_executable TARGET_NAME)
  target_link_libraries( ${TARGET_NAME} PRIVATE ${LIB_NAME})
  target_include_directories(${TARGET_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}, ../utility)
endfunction()

function(configure_library TARGET_NAME)
  target_include_directories(${TARGET_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}, ../utility)
endfunction()


