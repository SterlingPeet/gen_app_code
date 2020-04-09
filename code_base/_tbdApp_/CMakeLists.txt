cmake_minimum_required(VERSION 2.6.4)
project(CFS__TBDAPP_ C)

include_directories(fsw/mission_inc)
include_directories(fsw/platform_inc)
include_directories(fsw/src)

aux_source_directory(fsw/src APP_SRC_FILES)

# Create the app module
add_cfe_app(_tbdApp_ ${APP_SRC_FILES})

# Add unit test, if enabled
if (ENABLE_UNIT_TESTS)
  add_subdirectory(fsw/unit_test)
endif (ENABLE_UNIT_TESTS)

