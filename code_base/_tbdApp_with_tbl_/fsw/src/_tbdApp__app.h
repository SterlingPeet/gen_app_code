/*=======================================================================================
**
** File:  _tbdApp__app.h
**
** Purpose:
**    This file defines data types, internal macros, local constants, global variables, 
**    and function declarations used by _TBDAPP_ application.
**
** Modification History:
**    Date       | Author          | Description
**    ---------- | --------------- | ----------------------------------------------------
**    _tbdDate_  | _tbdOwner_      | Initial revision
**
**=======================================================================================*/

#ifndef __tbdApp__app_h_
#define __tbdApp__app_h_

/*=======================================================================================
** Includes
**=======================================================================================*/

#include <errno.h>
#include <string.h>
#include <unistd.h>

#include "cfe.h"

#include "_tbdApp__version.h"
#include "_tbdApp__platform_cfg.h"
#include "_tbdApp__mission_cfg.h"
#include "_tbdApp__events.h"
#include "_tbdApp__perfids.h"
#include "_tbdApp__msgids.h"
#include "_tbdApp__msg.h"
#include "_tbdApp__tbldefs.h"

/*=======================================================================================
** Macro Definitions
**=======================================================================================*/

/** \name _TBDAPP_ Return Codes */
/** \{ */
#define _TBDAPP__SUCCESS  0  /**< \brief Successful return from a function call */
#define _TBDAPP__ERROR    1  /**< \brief Error return from a function call */

/*
** TODO: Add more return codes here, if needed.
*/

/** \} */

/*
** TODO: Add more macros here, if needed.
*/

/*=======================================================================================
** Type Definitions
**=======================================================================================*/

/*
** \brief _TBDAPP_ global data structure
*/
typedef struct
{
    /* CFE event table */
    CFE_EVS_BinFilter_t  EventTbl[_TBDAPP__EVENT_CNT];    /**< \brief Table of _TBDAPP_ event IDs */

    /* CFE message pipes */
    CFE_SB_PipeId_t  SchPipeId;                      /**< \brief ID of scheduling pipe          */
    uint16           usSchPipeDepth;                 /**< \brief Depth of scheduling pipe       */
    char             cSchPipeName[OS_MAX_API_NAME];  /**< \brief Unique name of scheduling pipe */

    CFE_SB_PipeId_t  CmdPipeId;                      /**< \brief ID of command pipe             */
    uint16           usCmdPipeDepth;                 /**< \brief Depth of command pipe          */
    char             cCmdPipeName[OS_MAX_API_NAME];  /**< \brief Unique name of command pipe    */

    CFE_SB_PipeId_t  TlmPipeId;                      /**< \brief ID of telemetry pipe           */
    uint16           usTlmPipeDepth;                 /**< \brief Depth of telemetry pipe        */
    char             cTlmPipeName[OS_MAX_API_NAME];  /**< \brief Unique name of telemetry pipe  */

    /* Task-related data */
    uint32           uiRunStatus;  /**< \brief Application run status */
    
    /* Table-related data */
    CFE_TBL_Handle_t  _tbdTbl_TblHdl;   /**< \brief CFE TBL handle to this table */
    _TBDAPP___TBDTBL_TBL_T  *p_TbdTbl_Tbl;   /**< \brief Pointer to this table */

    /* _TBDAPP_ Telemetry */
    _TBDAPP__OutData_t    OutData;  /**< \brief Output data published at the end of a processing cycle */
    _TBDAPP__HkTlm_t      HkTlm;    /**< \brief Housekeeping data published upon request */

    /*
    ** TODO: Add data items to store subscribed data here.
    **       Add other data items local to _TBDAPP_ here, if needed.
    */

} _TBDAPP__AppData_t;

/*=======================================================================================
** Function Declarations
**=======================================================================================*/

void   _TBDAPP__AppMain(void);

int32  _TBDAPP__InitEvent(void);
int32  _TBDAPP__InitPipe(void);
int32  _TBDAPP__InitTable(void);
void   _TBDAPP__InitData(void);
int32  _TBDAPP__InitApp(void);

void   _TBDAPP__CleanupCallback(void);

int32  _TBDAPP__RcvMsg(int32);

int32   _TBDAPP__ProcessNewData(void);
int32   _TBDAPP__ProcessNewCmds(void);
int32   _TBDAPP__ProcessNewAppCmds(CFE_SB_MsgPtr_t);

void   _TBDAPP__SendHousekeeping(void);
void   _TBDAPP__SendOutData(void);

boolean  _TBDAPP__VerifyCmdLength(CFE_SB_MsgPtr_t, uint16);

#endif /* __tbdApp__app_h_ */

/*=======================================================================================
** End of file _tbdApp__app.h
**=======================================================================================*/

