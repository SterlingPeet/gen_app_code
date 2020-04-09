set(THISAPP "_tbdApp_")

enable_testing()

include_directories(${MISSION_SOURCE_DIR}/tools/ut_assert/inc)
include_directories(${MISSION_SOURCE_DIR}/osal/src/os/inc)
include_directories(${MISSION_SOURCE_DIR}/cfe/fsw/cfe-core/src/inc)
include_directories(${MISSION_SOURCE_DIR}/cfe/fsw/cfe-core/src/es)
include_directories(${MISSION_SOURCE_DIR}/cfe/fsw/cfe-core/src/sb)
include_directories(${MISSION_SOURCE_DIR}/cfe/fsw/cfe-core/src/time)

set(CMAKE_C_FLAGS  " ${CMAKE_C_FLAGS} -Wall -Wstrict-prototypes -g -fprofile-arcs -ftest-coverage -pg -p -DSOFTWARE_LITTLE_BIT_ORDER -D_EL -D__ix86_ -DUT_VERBOSE -m32 -D_LINUX_OS_ ")

set(CMAKE_LINKER_FLAGS " ${CMAKE_LINKER_FLAGS} -m32 -pg -p -fprofile-arcs -ftest-coverage -lgcov -pthread ")

# Source for this app's UT executable
aux_source_directory(${MISSION_SOURCE_DIR}/apps/${THISAPP}/fsw/unit_test UT_SRCS)
aux_source_directory(${MISSION_SOURCE_DIR}/apps/${THISAPP}/fsw/src UT_SRCS)
aux_source_directory(${MISSION_SOURCE_DIR}/tools/ut_assert/src UT_SRCS)

add_executable(${THISAPP}_ut ${UT_SRCS})

add_test(${THISAPP}_ut ${THISAPP}_ut)

install(TARGETS ${THISAPP}_ut DESTINATION ${APP}_ut/${UT_INSTALL_SUBDIR})

set(LCOV_OUTPUT ${MISSION_BINARY_DIR}/${SIMULATION}/coverage.info)
set(LCOV_DIR ${MISSION_BINARY_DIR}/${SIMULATION}/lcov)

add_custom_command(
    OUTPUT ${LCOV_OUTPUT}
    # Remove all .gcda files
    COMMAND find ${MISSION_BINARY_DIR}/${SIMULATION}/apps/${THISAPP}/fsw/unit_test -name "*.gcda" -type f -delete 
    COMMAND make
    COMMAND ./${THISAPP}_ut
    # Remove other .gcda files and leave only those of this app
    COMMAND find ${MISSION_BINARY_DIR}/${SIMULATION}/apps/${THISAPP}/fsw/unit_test -name "ut*" -type f -delete 
    COMMAND lcov --capture --directory ${MISSION_BINARY_DIR}/${SIMULATION}/apps/${THISAPP}/fsw/unit_test --output-file ${LCOV_OUTPUT}
    COMMAND genhtml ${LCOV_OUTPUT} --output-directory ${LCOV_DIR}
    COMMAND echo -e "Coverage Report Link: file: ${LCOV_DIR}/index.html\n"
    DEPENDS ${THISAPP}_ut
)

add_custom_target(${THISAPP}_lcov DEPENDS ${LCOV_OUTPUT})

