#######################################################################################
#
# File:    CFS Application Makefile 
# Author:  GSFC/Flight Software Branch/Code 582
#
#######################################################################################

#
# Subsystem produced by this makefile
#
APPTARGET = _tbdApp_

#
# Entry Point for task
#
ENTRY_PT = _TBDAPP__AppMain

#
# Object files required to build subsystem.
#
OBJS = _tbdApp__app.o

#
# Source files required to build subsystem; used to generate dependencies.
# As long as there are no assembly files this can be automated.
#
SOURCES = $(OBJS:.o=.c)

#
# Specify extra C Flags needed to build this subsystem
#
LOCAL_COPTS = 

#
# EXEDIR is defined here, just in case it needs to be different for a custom build
#
EXEDIR=../exe

#
# Certain OSs and Application Loaders require the following option for shared libraries.
# Currently only needed for vxWorks 5.5 and RTEMS.
# For each shared library that this app depends on, you need to have an entry like the
# following:
#    -R../tst_lib/tst_lib.elf
#
SHARED_LIB_LINK = 

#======================================================================================
# Should not have to change below this line, except for customized mission and cFE
# directory structures
#======================================================================================
#
# Set build type to CFE_APP.
# This allows us to define different compiler flags for the cFE Core and Apps.
#
BUILD_TYPE = CFE_APP

#
# Include all necessary cFE make rules
# Any of these can be copied to a local file and changed if needed.
#
#       cfe-config.mak contains PSP and OS selection
#
include ../cfe/cfe-config.mak
#
#       debug-opts.mak contains debug switches
#
include ../cfe/debug-opts.mak
#
#       compiler-opts.mak contains compiler definitions and switches/defines
#
include $(CFE_PSP_SRC)/$(PSP)/make/compiler-opts.mak

#
# Setup the include path for this subsystem
# The OS specific includes are in the build-rules.make file
#
# If this subsystem needs include files from another app, add the path here.
#
INCLUDE_PATH = ../inc \
               -I$(CFS_MISSION_INC) \
               -I$(CFS_APP_SRC)/inc \
               -I$(CFS_APP_SRC)/$(APPTARGET)/fsw/src \
               -I$(CFE_CORE_SRC)/inc \
               -I$(OSAL_SRC)/inc \
               -I$(CFE_PSP_SRC)/inc \
               -I$(CFE_PSP_SRC)/$(PSP)/inc

#
# Define the VPATH make variable.
# This can be modified to include source from another directory.
# If there is no corresponding app in the cfs-apps directory, then this can be discarded,
# or if the mission chooses to put the src in another directory such as "src", then that
# can be added here as well.
#
VPATH = $(CFS_APP_SRC)/$(APPTARGET)/fsw/src

#
# Include the common make rules for building a cFE Application
#
include $(CFE_CORE_SRC)/make/app-rules.mak

#######################################################################################

