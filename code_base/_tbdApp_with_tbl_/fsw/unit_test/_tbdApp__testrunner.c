/*=======================================================================================
**
** File:  _tbdApp__testrunner.c
**
** Purpose:
**    This file contains a unit-test runner for the _tbdApp_ application.
**
** Modification History:
**    Date       | Author          | Description
**    ---------- | --------------- | ----------------------------------------------------
**    _tbdDate_  | _tbdOwner_      | Initial revision
**
**=======================================================================================*/

#include "_tbdApp__testcases.h"

/*=======================================================================================
** Adding test cases
**=======================================================================================*/

static void Ut__TBDAPP__AddTestCases(void)
{
    UtTest_Add(Ut__TBDAPP__InitEvent,
               Ut__TBDAPP__Setup, Ut__TBDAPP__Teardown,
               "_TBDAPP__InitEvent");

    UtTest_Add(Ut__TBDAPP__InitPipe,
               Ut__TBDAPP__Setup, Ut__TBDAPP__Teardown,
               "Ut__TBDAPP__InitPipe");

    UtTest_Add(Ut__TBDAPP__InitTable,
               Ut__TBDAPP__Setup, Ut__TBDAPP__Teardown,
               "Ut__TBDAPP__InitTable");

    UtTest_Add(Ut__TBDAPP__InitData,
               Ut__TBDAPP__Setup, Ut__TBDAPP__Teardown,
               "Ut__TBDAPP__InitData");

    UtTest_Add(Ut__TBDAPP__InitApp,
               Ut__TBDAPP__Setup, Ut__TBDAPP__Teardown,
               "Ut__TBDAPP__InitApp");

    UtTest_Add(Ut__TBDAPP__CleanupCallback,
               Ut__TBDAPP__Setup, Ut__TBDAPP__Teardown,
               "Ut__TBDAPP__CleanupCallback");

    UtTest_Add(Ut__TBDAPP__RcvMsg,
               Ut__TBDAPP__Setup, Ut__TBDAPP__Teardown,
               "Ut__TBDAPP__RcvMsg");

    UtTest_Add(Ut__TBDAPP__ProcessNewData,
               Ut__TBDAPP__Setup, Ut__TBDAPP__Teardown,
               "Ut__TBDAPP__ProcessNewData");

    UtTest_Add(Ut__TBDAPP__ProcessNewCmds,
               Ut__TBDAPP__Setup, Ut__TBDAPP__Teardown,
               "Ut__TBDAPP__ProcessNewCmds");

    UtTest_Add(Ut__TBDAPP__ProcessNewAppCmds,
               Ut__TBDAPP__Setup, Ut__TBDAPP__Teardown,
               "Ut__TBDAPP__ProcessNewAppCmds");

    UtTest_Add(Ut__TBDAPP__SendHousekeeping,
               Ut__TBDAPP__Setup, Ut__TBDAPP__Teardown,
               "Ut__TBDAPP__SendHousekeeping");

    UtTest_Add(Ut__TBDAPP__SendOutData,
               Ut__TBDAPP__Setup, Ut__TBDAPP__Teardown,
               "Ut__TBDAPP__SendOutData");

    UtTest_Add(Ut__TBDAPP__VerifyCmdLength,
               Ut__TBDAPP__Setup, Ut__TBDAPP__Teardown,
               "Ut__TBDAPP__VerifyCmdLength");

    UtTest_Add(Ut__TBDAPP__AppMain,
               Ut__TBDAPP__Setup, Ut__TBDAPP__Teardown,
               "Ut__TBDAPP__AppMain");

    UtTest_Add(Ut__TBDAPP__Init_TbdTbl_Table,
               Ut__TBDAPP__Setup, Ut__TBDAPP__Teardown,
               "Ut__TBDAPP__Init_TbdTbl_Table");

    UtTest_Add(Ut__TBDAPP__Validate_TbdTbl_Table,
               Ut__TBDAPP__Setup, Ut__TBDAPP__Teardown,
               "Ut__TBDAPP__Validate_TbdTbl_Table");

    UtTest_Add(Ut__TBDAPP__ProcessNew_TbdTbl_Table,
               Ut__TBDAPP__Setup, Ut__TBDAPP__Teardown,
               "Ut__TBDAPP__ProcessNew_TbdTbl_Table");
} 

/*=======================================================================================
** Test main
**=======================================================================================*/

int main(void)
{
    Ut__TBDAPP__AddTestCases();

    return (UtTest_Run());
}

/*=======================================================================================
** End of file _tbdApp__testrunner.c
**=======================================================================================*/

