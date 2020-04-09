/*=======================================================================================
**
** File:  _tbdApp__testcases.h
**
** Purpose:
**    This file contains function declarations of test cases for the _tbdApp_ application.
**
** Modification History:
**    Date       | Author          | Description
**    ---------- | --------------- | ----------------------------------------------------
**    _tbdDate_  | _tbdOwner_      | Initial revision
**
**=======================================================================================*/

#ifndef ut__tbdApp__testcases_h
#define ut__tbdApp__testcases_h

/*=======================================================================================
** Includes
**=======================================================================================*/

#include <errno.h>

#include "cfe.h"

#include "utassert.h"
#include "uttest.h"
#include "utlist.h"
#include "ut_cfe_tbl_stubs.h"
#include "ut_cfe_tbl_hooks.h"
#include "ut_cfe_evs_stubs.h"
#include "ut_cfe_evs_hooks.h"
#include "ut_cfe_sb_stubs.h"
#include "ut_cfe_sb_hooks.h"
#include "ut_cfe_es_stubs.h"
#include "ut_osapi_stubs.h"
#include "ut_osfileapi_stubs.h"
#include "ut_cfe_fs_stubs.h"

#include "_tbdApp__app.h"

/*=======================================================================================
** External Global Variable Declarations
**=======================================================================================*/

extern _TBDAPP__AppData_t  g__TBDAPP__AppData;

/*=======================================================================================
** Function Declarations
**=======================================================================================*/

void Ut__TBDAPP__Setup(void);
void Ut__TBDAPP__Teardown(void);

void Ut__TBDAPP__InitEvent(void);
void Ut__TBDAPP__InitPipe(void);
void Ut__TBDAPP__InitData(void);
void Ut__TBDAPP__InitApp(void);

void Ut__TBDAPP__CleanupCallback(void);

void Ut__TBDAPP__RcvMsg(void);

void Ut__TBDAPP__ProcessNewData(void);
void Ut__TBDAPP__ProcessNewCmds(void);
void Ut__TBDAPP__ProcessNewAppCmds(void);

void Ut__TBDAPP__SendHousekeeping(void);
void Ut__TBDAPP__SendOutData(void);

void Ut__TBDAPP__VerifyCmdLength(void);

void Ut__TBDAPP__AppMain(void);

#endif  /* ut__tbdApp__testcases_h */

/*=======================================================================================
** End of file _tbdApp__testcases.h
**=======================================================================================*/


