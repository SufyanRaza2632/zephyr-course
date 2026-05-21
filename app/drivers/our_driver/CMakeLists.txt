
message(STATUS "ENTERED our_driver CMakeLists.txt")
message(STATUS "CONFIG_OUR_DRIVER=${CONFIG_OUR_DRIVER}")
if(CONFIG_OUR_DRIVER)
    target_sources(app PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/our_driver.c)
    if(CONFIG_SHELL)
        target_sources(app PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/our_console_driver.c)  
    endif()
endif()