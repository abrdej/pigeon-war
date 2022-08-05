function(create_config)
  configure_file(${PROJECT_SOURCE_DIR}/cmake/config.h.in ${CMAKE_CURRENT_SOURCE_DIR}/config.h @ONLY)
endfunction()
