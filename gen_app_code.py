#!/usr/bin/env python

#========================================================================================
# File:  gen_app_code.py
#
# Modification History:
#    Date       | Author          | Description
#    ---------- | --------------- | ----------------------------------------
#    2012/02/22 | Tam Ngo         | Initial revision
#    2015-10-07 | Susanne Strege  | Added calls to generate perfids, message ids, and message
#         ^     |     ^           | definition header files
#    2016-03-31 | Mike Rosburg    | Commented out call to generate global types header file
#    2018/07/18 | Tam Ngo         | Re-vamped how code is generated
#========================================================================================

import os, sys, time, datetime, shutil, gen_app_code_version

#========================================================================================

# Global variables - only global to this file
g_Date = ""

g_Owner   = ""
g_Mission = ""

g_OutDir = "."

g_ucApp = ""
g_lcApp = ""

g_ucTbl = ""
g_lcTbl = ""
g_wdTbl = ""

g_Dirs = []

g_ucAppKey = "_TBDAPP_"
g_lcAppKey = "_tbdApp_"
g_DateKey  = "_tbdDate_ "
g_OwnerKey = "_tbdOwner_"
g_ucTblKey = "_TBDTBL_"
g_lcTblKey = "_tbdTbl_"
g_wdTblKey = "_TbdTbl_"

#========================================================================================

def parse_command_line_args():
    global g_OutDir, g_Mission, g_Date, g_Owner, g_lcApp, g_ucApp, g_lcTbl, g_ucTbl, g_wdTbl

    g_Date = datetime.date.today()

    print "\nVersion: %s.%s.%s\n" % (gen_app_code_version.g_MAJOR,
                                     gen_app_code_version.g_MINOR,
                                     gen_app_code_version.g_REVISION)

    if len(sys.argv) < 4:
        print "Usage:  python gen_app_code.py [MISSION <mission-name>]  // No spaces in name"
        print "                               [OWNER \"<owner-name>\"]    // Quoted string; can have spaces in string"
        print "                               [APP <app-name>]          // Application name; all lowercase"
        print "                               [TBL <tbl-name>]          // Table name; all lowercase; Optional"
        print "                               [OUTDIR <output-dir>]     // No spaces in path"
        print "\nEx:  python gen_app_code.py MISSION myProj OWNER \"Jane Smith\" APP foo OUTDIR /home/jsmith/projA/apps"
        print "     python gen_app_code.py MISSION myProj OWNER \"John Smith\" APP bar TBL iloads OUTDIR .\n"
        sys.exit()

    else:
        argList = []
        argList.extend(sys.argv)

        # Remove script name
        argList.pop(0)

        curArg  = ""
        argKeys = ['MISSION', 'OWNER', 'OUTDIR', 'APP', 'TBL']

        for itm in argList:
            if itm in argKeys:
                curArg = itm
            elif curArg == 'MISSION':
                g_Mission = itm
            elif curArg == 'OWNER':
                g_Owner = itm
            elif curArg == 'OUTDIR':
                g_OutDir = itm
            elif curArg == 'APP':
                g_lcApp = itm.lower()
                g_ucApp = itm.upper()
            elif curArg == 'TBL':
                g_lcTbl = itm.lower()
                g_ucTbl = itm.upper()
                g_wdTbl = itm.title()
            else:
                pass
        
        # DEBUG: print list of arguments
        if g_lcTbl == "":
            print "Date = %s, MISSION = %s, OWNER = %s, APP = %s, OUTDIR = %s\n" \
                  % (g_Date, g_Mission, g_Owner, g_lcApp, g_OutDir)
        else:
            print "Date = %s, MISSION = %s, OWNER = %s, APP = %s, TBL = %s, OUTDIR = %s\n" \
                  % (g_Date, g_Mission, g_Owner, g_lcApp, g_lcTbl, g_OutDir)

#========================================================================================

def copy_files_from_code_base():
    global g_OutDir, g_Mission, g_Date, g_Owner, g_lcApp, g_ucApp, g_lcTbl, g_ucTbl, g_wdTbl, \
           g_ucAppKey, g_lcAppKey, g_DateKey, g_OwnerKey

    if g_lcTbl == "":
        srcDir = "./code_base/" + g_lcAppKey
    else:
        srcDir = "./code_base/" + g_lcAppKey + "with_tbl_"

    dstDir = os.path.join(g_OutDir, g_lcApp)
    
    # Copy files from base code
    if os.path.exists(dstDir):
        # Only copy files if app directory does not exist
        print "Directory %s already exists. Exiting!\n" % dstDir
        return
    else:
        shutil.copytree(srcDir, dstDir, False, None)

    # Rename app name
    for root, dirs, files in os.walk(dstDir):
        for file in files:
            curName = os.path.join(root, file)
            newName = curName.replace(g_lcAppKey, g_lcApp)
            if newName != curName:
                os.rename(curName, newName)

    # Rename table name
    if g_lcTbl != "":
        for root, dirs, files in os.walk(dstDir):
            for file in files:
                curName = os.path.join(root, file)
                newName = curName.replace(g_lcTblKey, g_lcTbl)
                if newName != curName:
                    os.rename(curName, newName)

    # Global replace app names in file content
    for root, dirs, files in os.walk(dstDir):
        for file in files:
            # First, replace all instances of g_lcAppKey value with g_lcApp value
            cmdStr = 'sed -i -e \'s/%s/%s/g\' %s' \
                     % (g_lcAppKey, g_lcApp, os.path.join(root, file))
            os.system(cmdStr)
            # Second, replace all instances of g_ucAppKey value with g_ucApp value
            cmdStr = 'sed -i -e \'s/%s/%s/g\' %s' \
                     % (g_ucAppKey, g_ucApp, os.path.join(root, file))
            os.system(cmdStr)
            # Third, replace all g_DateKey value with current date
            cmdStr = 'sed -i -e \'s/%s/%s/g\' %s' \
                     % (g_DateKey, g_Date, os.path.join(root, file))
            os.system(cmdStr)
            # Fourth, replace all g_OwnerKey value with g_Owner value
            cmdStr = 'sed -i -e \'s/%s/%s/g\' %s' \
                     % (g_OwnerKey, g_Owner, os.path.join(root, file))
            os.system(cmdStr)
            if g_lcTbl != "":
                # Fifth, replace all g_lcTblKey value with g_lcTbl value
                cmdStr = 'sed -i -e \'s/%s/%s/g\' %s' \
                         % (g_lcTblKey, g_lcTbl, os.path.join(root, file))
                os.system(cmdStr)
                # Sixth, replace all g_ucTblKey value with g_ucTbl value
                cmdStr = 'sed -i -e \'s/%s/%s/g\' %s' \
                         % (g_ucTblKey, g_ucTbl, os.path.join(root, file))
                os.system(cmdStr)
                # Seventh, replace all g_wdTblKey value with g_wdTbl value
                cmdStr = 'sed -i -e \'s/%s/%s/g\' %s' \
                         % (g_wdTblKey, g_wdTbl, os.path.join(root, file))
                os.system(cmdStr)

    print "Created source directory for \"%s\" application at %s\n" % (g_lcApp, dstDir)

#========================================================================================

# Main
parse_command_line_args()
copy_files_from_code_base()

#========================================================================================
# End of gen_app_code.py
#========================================================================================

