================================================================================

_TBDAPP_ UNIT TESTS

Author: _tbdOwner_

================================================================================

--------------------------------------------------------------------------------
ASSUMPTIONS
--------------------------------------------------------------------------------

1. These tests make use of a CFS tool called ut_assert with all the necessary
   stubs & hooks for cfe, osal & psp. It is also assumed that ut_assert is 
   available under the 'tools' directory. If not so, then make the necessary
   update to the build environment variables in CMakeLists.txt and/or gnuMakefile.

--------------------------------------------------------------------------------
FILE OVERVIEW
--------------------------------------------------------------------------------

1. _tbdApp__testcases.c
     Contains the unit test cases

2. _tbdApp__testrunner.c
     Contains the main function to kickoff the unit testing as well as
     setup, teardown & addtest functions

3. CMakeLists.txt
     cmake file to build and run the unit tests

4. gnuMakefile
     GNU make file to build and run the unit tests

--------------------------------------------------------------------------------
NOTES
--------------------------------------------------------------------------------

- MISSION directory refers to the project's top-level directory that contains 
  CFE, OSAL, PSP, APPS, TOOLS, PRJ_DEFS subdirectories.

- PRJ_DEFS directory contains cmake build files for the projects.

--------------------------------------------------------------------------------
TEST INSTRUCTIONS
--------------------------------------------------------------------------------

USING CMAKE,

1. Edit the file, MISSION/PRJ_DEFS/targets.cmake, to add this app to the build.

2. Edit the file, $MISSION/Makefile to add target build for this app's unit test 
   executable as followed:

   FROM
       test:
           (cd $(O)/$(ARCH) && ctest -O ctest.log)
   TO
       test:
           (cd $(O)/$(ARCH) && ctest -O ctest.log)

       _tbdApp__test:
           (cd $(O)/$(ARCH) && ctest -O ctest.log -R _tbdApp_ -E cfe_core_default)

3. From MISSION directory, build the unit test executable,

     $ make SIMULATION=cpu1 ENABLE_UNIT_TESTS=TRUE prep
     $ make

4. From MISSION directory, run the unit tests,

     $ make ARCH=cpu1 _tbdApp__test

5. From MISSION directory, run code coverage using lcov,
   a graphical GCOV front-end,

     $ make ARCH_cpu1 _tbdApp__lcov

   To view the report,

     $ firefox MISSION/build/cpu1/lcov/index.html

---------------------------------------------------------------------

USING GNU MAKE, 

1. Go to directory, MISSION/apps/_tbdApp_/fsw/unit_test.

2. Edit the file, gnuMakefile, to update any necessary build environment
   variables relating to paths.

3. Build the unit tests for Linux platform
     $ make

2. Run the unit tests
   (Pass/Fail stats will be shown at the bottom of the output.)
     $ make run

3. Run code coverage using gcov
   (The coverage should be 100.00%.)
     $ make gcov

4. Clean the build
     $ make clean

