/*=======================================================================================
**
** File:  _tbdApp__app.c
**
** Purpose:
**    This file defines function definitions for _TBDAPP_ application.
**
** Limitations, Assumptions, External Events, and Notes:
**    1. List assumptions that are made that apply to all functions in the file.
**    2. List the external source(s) and event(s) that can cause the funcs in this
**       file to execute.
**    3. List known limitations that apply to the funcs in this file.
**    4. If there are no assumptions, external events, or notes then enter NONE.
**       Do not omit the section.
**
** Notes:
**    1. This code is adhere to JSC ER SSET Coding Standards - January 2014 baseline.
**
** Modification History:
**    Date       | Author          | Description
**    ---------- | --------------- | ----------------------------------------------------
**    _tbdDate_  | _tbdOwner_      | Initial revision
**
**=======================================================================================*/

/*=======================================================================================
** Includes
**=======================================================================================*/

#include <string.h>

#include "cfe.h"

#include "_tbdApp__app.h"

/*=======================================================================================
** Local Macro Definitions
**=======================================================================================*/

/*=======================================================================================
** Local Type Definitions
**=======================================================================================*/

/*=======================================================================================
** External Global Variable Declarations
**=======================================================================================*/

/*=======================================================================================
** Global Variable Declarations
**=======================================================================================*/

_TBDAPP__AppData_t  g__TBDAPP__AppData = {};

/*=======================================================================================
** Function Definitions
**=======================================================================================*/

/**
** \brief _TBDAPP_ Event Table Initialization
**
** \par Description:
**      Initialize _TBDAPP_ Event Table
** 
** \par Assumptions, External Events, and Notes:
**      Event IDs are defined in _tbdApp__events.h.
**
** \return CFE_SUCCESS
** \return Any of the return values from CFE_EVS_Register()
*/
int32 _TBDAPP__InitEvent()
{
    int32 iStatus = 0;

    /* Create the event table */
    CFE_PSP_MemSet((void*)g__TBDAPP__AppData.EventTbl, (uint8)0x00, 
                   (uint32)sizeof(g__TBDAPP__AppData.EventTbl));

    g__TBDAPP__AppData.EventTbl[0].EventID = _TBDAPP__RESERVED_EID;
    g__TBDAPP__AppData.EventTbl[1].EventID = _TBDAPP__INF_EID;
    g__TBDAPP__AppData.EventTbl[2].EventID = _TBDAPP__INIT_INF_EID;
    g__TBDAPP__AppData.EventTbl[3].EventID = _TBDAPP__TBL_INF_EID;
    g__TBDAPP__AppData.EventTbl[4].EventID = _TBDAPP__PIPE_INF_EID;
    g__TBDAPP__AppData.EventTbl[5].EventID = _TBDAPP__CMD_INF_EID;
    g__TBDAPP__AppData.EventTbl[6].EventID = _TBDAPP__TLM_INF_EID;
   
    g__TBDAPP__AppData.EventTbl[ 7].EventID = _TBDAPP__ERR_EID;
    g__TBDAPP__AppData.EventTbl[ 8].EventID = _TBDAPP__INIT_ERR_EID;
    g__TBDAPP__AppData.EventTbl[ 9].EventID = _TBDAPP__TBL_ERR_EID;
    g__TBDAPP__AppData.EventTbl[10].EventID = _TBDAPP__PIPE_ERR_EID;
    g__TBDAPP__AppData.EventTbl[11].EventID = _TBDAPP__CMD_ERR_EID;
    g__TBDAPP__AppData.EventTbl[12].EventID = _TBDAPP__TLM_ERR_EID;

    /* Register the table with CFE */
    iStatus = CFE_EVS_Register(g__TBDAPP__AppData.EventTbl,
                               _TBDAPP__EVENT_CNT, CFE_EVS_BINARY_FILTER);
    if (iStatus != CFE_SUCCESS)
    {
        CFE_ES_WriteToSysLog("_TBDAPP__InitEvent(): CFE_EVS_Register() failed (0x%04X)\n", 
                             (unsigned int)iStatus);
    }

    return (iStatus);
}

/*=======================================================================================*/

/**
** \brief _TBDAPP_ Message Pipe Initialization
**
** \par Description:
**      Initialize all _TBDAPP_ message pipes
** 
** \par Assumptions, External Events, and Notes:
**      Pipe names & depths are defined in _tbdApp__platform_cfg.h.
**
** \return CFE_SUCCESS
** \return Any of the return values from CFE_CreatePipe()
** \return Any of the return values from CFE_SB_Subscribe()
*/
int32 _TBDAPP__InitPipe()
{
    int32 iStatus = 0;

    /* Init scheduling pipe */
    g__TBDAPP__AppData.usSchPipeDepth = _TBDAPP__SCH_PIPE_DEPTH;
    CFE_PSP_MemSet((void*)g__TBDAPP__AppData.cSchPipeName, (uint8)'\0', 
                   (uint32)sizeof(g__TBDAPP__AppData.cSchPipeName));
    strncpy(g__TBDAPP__AppData.cSchPipeName, _TBDAPP__SCH_PIPE_NAME, OS_MAX_API_NAME-1);

    /* Create scheduling pipe */
    iStatus = CFE_SB_CreatePipe(&g__TBDAPP__AppData.SchPipeId,
                                 g__TBDAPP__AppData.usSchPipeDepth,
                                 g__TBDAPP__AppData.cSchPipeName);
    if (iStatus != CFE_SUCCESS)
    {
        /* Flag error */
        CFE_EVS_SendEvent(_TBDAPP__PIPE_ERR_EID, CFE_EVS_ERROR,
                          "_TBDAPP__InitPipe(): CFE_SB_CreatePipe(SCH) failed (0x%04X)",
                          (unsigned int)iStatus);
        goto _TBDAPP__InitPipe_Exit_Tag;
    }

    /* Subscribe to _TBDAPP_ WakeUp message */
    iStatus = CFE_SB_Subscribe(_TBDAPP__WAKEUP_MID, g__TBDAPP__AppData.SchPipeId);
    if (iStatus != CFE_SUCCESS)
    {
        /* Flag error */
        CFE_EVS_SendEvent(_TBDAPP__CMD_ERR_EID, CFE_EVS_ERROR,
                          "_TBDAPP__InitPipe(): CFE_SB_Subscribe(_TBDAPP__WAKEUP_MID) failed (0x%04X)",
                          (unsigned int)iStatus);
        goto _TBDAPP__InitPipe_Exit_Tag;
    }

    /* Flag successful SCH pipe creation & initialization */
    CFE_EVS_SendEvent(_TBDAPP__PIPE_INF_EID, CFE_EVS_INFORMATION,
                      "_TBDAPP_: Pipe initialized (SCH)");

    /* Init command pipe */
    g__TBDAPP__AppData.usCmdPipeDepth = _TBDAPP__CMD_PIPE_DEPTH ;
    CFE_PSP_MemSet((void*)g__TBDAPP__AppData.cCmdPipeName, (uint8)'\0', 
                   (uint32)sizeof(g__TBDAPP__AppData.cCmdPipeName));
    strncpy(g__TBDAPP__AppData.cCmdPipeName, _TBDAPP__CMD_PIPE_NAME, OS_MAX_API_NAME-1);

    /* Create command pipe */
    iStatus = CFE_SB_CreatePipe(&g__TBDAPP__AppData.CmdPipeId,
                                 g__TBDAPP__AppData.usCmdPipeDepth,
                                 g__TBDAPP__AppData.cCmdPipeName);
    if (iStatus != CFE_SUCCESS)
    {
        /* Flag error */
        CFE_EVS_SendEvent(_TBDAPP__PIPE_ERR_EID, CFE_EVS_ERROR,
                          "_TBDAPP__InitPipe(): CFE_SB_CreatePipe(CMD) failed (0x%04X)",
                          (unsigned int)iStatus);
        goto _TBDAPP__InitPipe_Exit_Tag;
    }

    /* Subscribe to _TBDAPP_ command messages */
    iStatus = CFE_SB_Subscribe(_TBDAPP__CMD_MID, g__TBDAPP__AppData.CmdPipeId);
    if (iStatus != CFE_SUCCESS)
    {
        /* Flag error */
        CFE_EVS_SendEvent(_TBDAPP__CMD_ERR_EID, CFE_EVS_ERROR,
                          "_TBDAPP__InitPipe(): CFE_SB_Subscribe(_TBDAPP__CMD_MID) failed (0x%04X)",
                          (unsigned int)iStatus);
        goto _TBDAPP__InitPipe_Exit_Tag;
    }

    /* Subscribe to _TBDAPP_ housekeeping request messages */
    iStatus = CFE_SB_Subscribe(_TBDAPP__SEND_HK_MID, g__TBDAPP__AppData.CmdPipeId);
    if (iStatus != CFE_SUCCESS)
    {
        /* Flag error */
        CFE_EVS_SendEvent(_TBDAPP__CMD_ERR_EID, CFE_EVS_ERROR,
                          "_TBDAPP__InitPipe(): CFE_SB_Subscribe(_TBDAPP__SEND_HK_MID) failed (0x%04X)",
                          (unsigned int)iStatus);
        goto _TBDAPP__InitPipe_Exit_Tag;
    }

    /* Flag successful CMD pipe creation & initialization */
    CFE_EVS_SendEvent(_TBDAPP__PIPE_INF_EID, CFE_EVS_INFORMATION,
                      "_TBDAPP_: Pipe initialized (CMD)");

    /* Init telemetry pipe */
    g__TBDAPP__AppData.usTlmPipeDepth = _TBDAPP__TLM_PIPE_DEPTH;
    CFE_PSP_MemSet((void*)g__TBDAPP__AppData.cTlmPipeName, (uint8)'\0', 
                   (uint32)sizeof(g__TBDAPP__AppData.cTlmPipeName));
    strncpy(g__TBDAPP__AppData.cTlmPipeName, _TBDAPP__TLM_PIPE_NAME, OS_MAX_API_NAME-1);

    /* Create telemetry pipe */
    iStatus = CFE_SB_CreatePipe(&g__TBDAPP__AppData.TlmPipeId,
                                 g__TBDAPP__AppData.usTlmPipeDepth,
                                 g__TBDAPP__AppData.cTlmPipeName);
    if (iStatus != CFE_SUCCESS)
    {
        /* Flag error */
        CFE_EVS_SendEvent(_TBDAPP__PIPE_ERR_EID, CFE_EVS_ERROR,
                          "_TBDAPP__InitPipe(): CFE_SB_CreatePipe(TLM) failed (0x%04X)\n",
                          (unsigned int)iStatus);
        goto _TBDAPP__InitPipe_Exit_Tag;
    }

    /* Subscribe to other apps' OutData messages */
    /*
    ** TODO: Add CFE_SB_Subscribe() calls for other apps' OutData here.
    **       Examples: CFE_SB_Subscribe(GNCEXEC_OUT_DATA_MID, g__TBDAPP__AppData.TlmPipeId);
    */

    /* Flag successful TLM pipe creation & initialization */
    CFE_EVS_SendEvent(_TBDAPP__PIPE_INF_EID, CFE_EVS_INFORMATION,
                      "_TBDAPP_: Pipe initialized (TLM)");

_TBDAPP__InitPipe_Exit_Tag:
    return (iStatus);
}

/*=======================================================================================*/

/**
** \brief _TBDAPP_ Data Initialization
**
** \par Description:
**      Initialize local data & messages
** 
** \par Assumptions, External Events, and Notes:
**      None
**
** \return CFE_SUCCESS
*/
void _TBDAPP__InitData()
{
    /* Init input data */

    /*
    ** TODO: Initialize data items used to store local copy of subscribed OutData here.
    */

    /* Init output data */
    CFE_SB_InitMsg((void*)&g__TBDAPP__AppData.OutData, (CFE_SB_MsgId_t)_TBDAPP__OUT_DATA_MID, 
                   (uint16)sizeof(g__TBDAPP__AppData.OutData), TRUE);

    /* Init housekeeping packet */
    CFE_SB_InitMsg((void*)&g__TBDAPP__AppData.HkTlm, (CFE_SB_MsgId_t)_TBDAPP__HK_TLM_MID, 
                   (uint16)sizeof(g__TBDAPP__AppData.HkTlm), TRUE);
}

/*=======================================================================================*/

/**
** \brief Application Initialization
**
** \par Description:
**      Initialize all _TBDAPP_ data elements.
** 
** \par Assumptions, External Events, and Notes:
**      None
**
** \return CFE_SUCCESS
** \return Any of the return values from #_TBDAPP__InitEvent()
** \return Any of the return values from #_TBDAPP__InitPipe()
*/
int32 _TBDAPP__InitApp()
{
    int32 iStatus = 0;

    iStatus = _TBDAPP__InitEvent();
    if (iStatus != CFE_SUCCESS)
    {
        CFE_ES_WriteToSysLog("_TBDAPP__InitApp(): _TBDAPP__InitEvent() failed (0x%04X)\n",
                             (unsigned int)iStatus);
        CFE_ES_WriteToSysLog("_TBDAPP_: Failed to initialize application. Version %d.%d.%d.%d\n",
                             (int)_TBDAPP__MAJOR_VERSION, (int)_TBDAPP__MINOR_VERSION, (int)_TBDAPP__REVISION,
                             (int)_TBDAPP__MISSION_REVISION);
        goto _TBDAPP__InitApp_Exit_Tag;
    }

    iStatus = _TBDAPP__InitPipe();
    if (iStatus != CFE_SUCCESS)
    {
        CFE_EVS_SendEvent(_TBDAPP__INIT_ERR_EID, CFE_EVS_ERROR,
                          "_TBDAPP__InitApp(): _TBDAPP__InitPipe() failed (0x%04X)\n",
                          (unsigned int)iStatus);
        CFE_EVS_SendEvent(_TBDAPP__INIT_ERR_EID, CFE_EVS_ERROR,
                          "_TBDAPP_: Failed to initialize application. Version %d.%d.%d.%d\n",
                          (int)_TBDAPP__MAJOR_VERSION, (int)_TBDAPP__MINOR_VERSION, (int)_TBDAPP__REVISION,
                          (int)_TBDAPP__MISSION_REVISION);
        goto _TBDAPP__InitApp_Exit_Tag;
    }

    _TBDAPP__InitData();

    /* Install the cleanup callback */
    OS_TaskInstallDeleteHandler((void*)&_TBDAPP__CleanupCallback);

    CFE_EVS_SendEvent(_TBDAPP__INIT_INF_EID, CFE_EVS_INFORMATION,
                      "_TBDAPP_: Application initialized. Version %d.%d.%d.%d",
                      (int)_TBDAPP__MAJOR_VERSION, (int)_TBDAPP__MINOR_VERSION, (int)_TBDAPP__REVISION,
                      (int)_TBDAPP__MISSION_REVISION);

_TBDAPP__InitApp_Exit_Tag:
    return (iStatus);
}

/*=======================================================================================*/

/**
** \brief Cleanup handler
**
** \par Description:
**      Perform all necessary cleanup before the application exits
** 
** \par Assumptions, External Events, and Notes:
**      None
*/
void _TBDAPP__CleanupCallback()
{
    /*
    ** TODO:  Add code to close out channels, cleanup memory and other cleanup here
    */

    /* For unit testing only, not harmfull at this point. */
    CFE_PSP_MemSet((void*)&g__TBDAPP__AppData.HkTlm, 0x00, 
                   sizeof(g__TBDAPP__AppData.HkTlm));
}

/*=======================================================================================*/

/**
** \brief Process incoming messages from scheduling pipe
**
** \par Description:
**      Read from scheduling pipe & process 1 incoming message per function call.
** 
** \par Assumptions, External Events, and Notes:
**      None
**
** \param[in] iBlocking  Blocking timeout (set to CFE_SB_PEND_FOREVER)
**
** \return CFE_SUCCESS
** \return Any of the return values from CFE_SB_RcvMsg()
*/
int32 _TBDAPP__RcvMsg(int32 iBlocking)
{
    int32 iStatus = 0;
    CFE_SB_MsgPtr_t pMsg = NULL;
    CFE_SB_MsgId_t msgId;

    /* Getting Scheduling messages */
    iStatus = CFE_SB_RcvMsg(&pMsg, g__TBDAPP__AppData.SchPipeId, iBlocking);
    if (iStatus == CFE_SUCCESS)
    {
        msgId = CFE_SB_GetMsgId(pMsg);
        switch (msgId)
        {
            case _TBDAPP__WAKEUP_MID:
                /* Start Performance Log entry - handling commands */
                CFE_ES_PerfLogEntry(_TBDAPP__CMD_HANDLING_PERF_ID);

                _TBDAPP__ProcessNewCmds();

                /* Stop Performance Log entry - handling commands */
                CFE_ES_PerfLogExit(_TBDAPP__CMD_HANDLING_PERF_ID);

                /* Start Performance Log entry - handling telemetry */
                CFE_ES_PerfLogEntry(_TBDAPP__TLM_HANDLING_PERF_ID);

                _TBDAPP__ProcessNewData();

                /* Stop Performance Log entry - handling telemetry */
                CFE_ES_PerfLogExit(_TBDAPP__TLM_HANDLING_PERF_ID);

                /* TODO: Add more code here to handle other things when _TBDAPP_ wakes up */

                /* The last thing to do at the end of a WakeUp cycle should be to publish OutData. */
                _TBDAPP__SendOutData();
                break;

            default:
                CFE_EVS_SendEvent(_TBDAPP__CMD_ERR_EID, CFE_EVS_ERROR,
                                  "_TBDAPP__RcvMsg(): Recvd invalid CMD MID (0x%04X)",
                                  (unsigned int)msgId);
                break;
        }
    }

    else if (iStatus == CFE_SB_NO_MESSAGE)
    {
        /*
        ** If there's no incoming message, you can do something here, 
        ** or do nothing as the default.
        */
    }

    else
    {
        /*
        ** This is an example of the app exiting on an error.
        **
        ** Note that a SB read error is not always going to result in an app quitting.
        ** To exit cleanly, just set the uiRunStatus to CFE_ES_APP_EXIT or CFE_ES_APP_ERROR,
        ** and let the application clean up after itself.
        */
        CFE_EVS_SendEvent(_TBDAPP__PIPE_ERR_EID, CFE_EVS_ERROR,
                          "_TBDAPP__RcvMsg(): CFE_SB_RcvMsg(SCH) failed (0x%04X). App will exit",
                          (unsigned int)iStatus);

        g__TBDAPP__AppData.uiRunStatus= CFE_ES_APP_ERROR;
    }

    return (iStatus);
}

/*=======================================================================================*/

/**
** \brief Process incoming messages from telemetry pipe
**
** \par Description:
**      Read from telemetry pipe & process all incoming messages
** 
** \par Assumptions, External Events, and Notes:
**      None
**
** \return CFE_SUCCESS
** \return Any of the return values from CFE_SB_RcvMsg()
*/
int32 _TBDAPP__ProcessNewData()
{
    int32 iStatus = CFE_SUCCESS;
    CFE_SB_MsgPtr_t pMsg = NULL;
    CFE_SB_MsgId_t msgId;

    /* Process Telemetry messages till the pipe is empty */
    while (iStatus == CFE_SUCCESS)
    {
        iStatus = CFE_SB_RcvMsg(&pMsg, g__TBDAPP__AppData.TlmPipeId, CFE_SB_POLL);
        if (iStatus == CFE_SUCCESS)
        {
            msgId = CFE_SB_GetMsgId(pMsg);
            switch (msgId)
            {
                /*
                ** TODO: Add code to process all subscribed data here 
                **
                ** Example: case GNC_OUT_DATA_MID:
                **              _TBDAPP__ProcessGncData(pMsg);
                **              break;
                */

                default:
                    CFE_EVS_SendEvent(_TBDAPP__TLM_ERR_EID, CFE_EVS_ERROR,
                                      "_TBDAPP__ProcessNewData(): Recvd invalid TLM MID (0x%04X)",
                                      (unsigned int)msgId);
                    break;
            }
        }

        else if (iStatus == CFE_SB_NO_MESSAGE)
        {
            /*
            ** If there's no incoming message, you can do something here, 
            ** or do nothing as the default.
            */
        }

        else
        {
            /*
            ** To exit cleanly, just set the uiRunStatus to CFE_ES_APP_EXIT or CFE_ES_APP_ERROR,
            ** and let the application clean up after itself.
            */
            CFE_EVS_SendEvent(_TBDAPP__PIPE_ERR_EID, CFE_EVS_ERROR,
                              "_TBDAPP__ProcessNewData(): CFE_SB_RcvMsg(TLM) failed (0x%04X). "
                              "App will exit.", (unsigned int)iStatus);

            g__TBDAPP__AppData.uiRunStatus = CFE_ES_APP_ERROR;
        }
    }

    return (iStatus);
}

/*=======================================================================================*/

/**
** \brief Process incoming messages from command pipe
**
** \par Description:
**      Read from command pipe & process all incoming messages
** 
** \par Assumptions, External Events, and Notes:
**      - g__TBDAPP__AppData.HkTlm.usCmdCntr and
**        g__TBDAPP__AppData.HkTlm.usCmdErrCntr are updated here based on
**        the return value of _TBDAPP__ProcessNewAppCmds, and nowhere else.
**
** \return CFE_SUCCESS
** \return -1 if #_TBDAPP__VerifyCmdLength() returns FALSE
** \return -1 if MID is invalid
** \return Any of the return values from CFE_SB_RcvMsg()
*/
int32 _TBDAPP__ProcessNewCmds()
{
    int32 iStatus = CFE_SUCCESS;
    CFE_SB_MsgPtr_t pMsg = NULL;
    CFE_SB_MsgId_t msgId;

    /* Process Command messages till the pipe is empty */
    while (iStatus == CFE_SUCCESS)
    {
        iStatus = CFE_SB_RcvMsg(&pMsg, g__TBDAPP__AppData.CmdPipeId, CFE_SB_POLL);
        if(iStatus == CFE_SUCCESS)
        {
            msgId = CFE_SB_GetMsgId(pMsg);
            switch (msgId)
            {
                case _TBDAPP__CMD_MID:
                    /* NOTE: Command message length is specific to a command code, hence,
                       verify command length is done in _TBDAPP__ProcessNewAppCmds() */
                    iStatus = _TBDAPP__ProcessNewAppCmds(pMsg);
                    if (iStatus == CFE_SUCCESS)
                    {
                        g__TBDAPP__AppData.HkTlm.usCmdCntr++;
                    }
                    else
                    {
                        g__TBDAPP__AppData.HkTlm.usCmdErrCntr++;
                    }
                    break;

                case _TBDAPP__SEND_HK_MID:
                    if (_TBDAPP__VerifyCmdLength(pMsg, (uint16)sizeof(_TBDAPP__NoArgCmd_t)) == TRUE)
                    {
                        _TBDAPP__SendHousekeeping();
                    }
                    break;

                /* TODO:  Add code to process other subscribed commands here
                **
                ** Example: case CFE_TIME_DATA_CMD_MID:
                **              _TBDAPP__ProcessTimeDataCmd(pMsg);
                **              break;
                */

                default:
                    CFE_EVS_SendEvent(_TBDAPP__CMD_ERR_EID, CFE_EVS_ERROR,
                                      "_TBDAPP__ProcessNewCmds(): Recvd invalid CMD MID (0x%04X)",
                                      (unsigned int)msgId);
                    break;
            }
        }

        else if (iStatus == CFE_SB_NO_MESSAGE)
        {
            /*
            ** If there's no incoming message, you can do something here, 
            ** or do nothing as the default.
            */
        }

        else
        {
            /*
            ** To exit cleanly, just set the uiRunStatus to CFE_ES_APP_EXIT or CFE_ES_APP_ERROR,
            ** and let the application clean up after itself.
            */
            CFE_EVS_SendEvent(_TBDAPP__PIPE_ERR_EID, CFE_EVS_ERROR,
                              "_TBDAPP__ProcessNewCmds(): CFE_SB_RcvMsg(CMD) failed (0x%04X). "
                              "App will exit.", (unsigned int)iStatus);

            g__TBDAPP__AppData.uiRunStatus = CFE_ES_APP_ERROR;
        }
    }

    return (iStatus);
}

/*=======================================================================================*/

/**
** \brief Process a command code
**
** \par Description:
**      Process a command message based on its command code.
**      If received valid command, increment usCmdCntr of housekeeping telemetry.
**      If received an invalid command, increment usCmdErrCntr of housekeeping telemetry.
**      If received a valid reset command, reset usCmdCntr, usCmdErrCntr & uiExecCntr
**      of housekeeping telemetry.
** 
** \par Assumptions, External Events, and Notes:
**      - g__TBDAPP__AppData.HkTlm.usCmdCntr and
**        g__TBDAPP__AppData.HkTlm.usCmdErrCntr are updated by the calling function
**        based on this function return value.
**
** \param[in] pMsg  Pointer to a CCSDS message
**
** \return CFE_SUCCESS
** \return -1 if #_TBDAPP__VerifyCmdLength() returns FALSE
** \return -1 if command code is invalid
*/
int32 _TBDAPP__ProcessNewAppCmds(CFE_SB_MsgPtr_t pMsg)
{
    int32 iStatus = -1;
    uint16 usCmdCode = 0;

    if (pMsg != NULL)
    {
        usCmdCode = CFE_SB_GetCmdCode(pMsg);
        switch (usCmdCode)
        {
            case _TBDAPP__NOOP_CC:
                if (_TBDAPP__VerifyCmdLength(pMsg, (uint16)sizeof(_TBDAPP__NoArgCmd_t)) == TRUE)
                {
                    CFE_EVS_SendEvent(_TBDAPP__CMD_INF_EID, CFE_EVS_INFORMATION,
                                      "_TBDAPP_: Recvd NOOP cmd (%d). Version %d.%d.%d.%d", 
                                      (int)usCmdCode,
                                      (int)_TBDAPP__MAJOR_VERSION, (int)_TBDAPP__MINOR_VERSION,
                                      (int)_TBDAPP__REVISION, (int)_TBDAPP__MISSION_REVISION);
                    iStatus = CFE_SUCCESS;
                }
                break;

            case _TBDAPP__RESET_CNTRS_CC:
                if (_TBDAPP__VerifyCmdLength(pMsg, (uint16)sizeof(_TBDAPP__NoArgCmd_t)) == TRUE)
                {
                    g__TBDAPP__AppData.HkTlm.usCmdCntr    = 0;
                    g__TBDAPP__AppData.HkTlm.usCmdErrCntr = 0;
                    g__TBDAPP__AppData.HkTlm.uiExecCntr   = 0;
                    CFE_EVS_SendEvent(_TBDAPP__CMD_INF_EID, CFE_EVS_INFORMATION,
                                      "_TBDAPP_: Recvd RESET cmd (%d)", (int)usCmdCode);
                    iStatus = CFE_SUCCESS;
                }
                break;

            /* TODO:  Add code to process the rest of the _TBDAPP_ commands here */

            default:
                CFE_EVS_SendEvent(_TBDAPP__CMD_ERR_EID, CFE_EVS_ERROR,
                                  "_TBDAPP__ProcessNewAppCmds(): Recvd invalid CMD CC "
                                  "(0x%04X) - cc=%d",
                                  (unsigned int)CFE_SB_GetMsgId(pMsg), (int)usCmdCode);
                break;
        }
    }

    return (iStatus);
}

/*=======================================================================================*/

/**
** \brief Publish the housekeeping telemetry
**
** \par Description:
**      Timestamp & publish housekeeping telemetry on SB.
** 
** \par Assumptions, External Events, and Notes:
**      None
*/
void _TBDAPP__SendHousekeeping(void)
{
    /* TODO:  Add code to update housekeeping data items here, if needed. */

    CFE_SB_TimeStampMsg((CFE_SB_MsgPtr_t)&g__TBDAPP__AppData.HkTlm);
    CFE_SB_SendMsg((CFE_SB_MsgPtr_t)&g__TBDAPP__AppData.HkTlm);
}

/*=======================================================================================*/

/**
** \brief Publish the OutData telemetry
**
** \par Description:
**      Timestamp & publish OutData telemetry on SB.
** 
** \par Assumptions, External Events, and Notes:
**      None
*/
void _TBDAPP__SendOutData(void)
{
    /* TODO:  Add code to update OutData data item here, if needed. */

    CFE_SB_TimeStampMsg((CFE_SB_MsgPtr_t)&g__TBDAPP__AppData.OutData);
    CFE_SB_SendMsg((CFE_SB_MsgPtr_t)&g__TBDAPP__AppData.OutData);
}

/*=======================================================================================*/

/**
** \brief Verify command message length
**
** \par Description:
**      Verify command message length based on its command code.
** 
** \par Assumptions, External Events, and Notes:
**      None
**
** \param[in] pMsg  Pointer to a CCSDS command message
** \param[in] usExpectedLen  Expected message length
**
** \return TRUE
** \return FALSE
*/
boolean _TBDAPP__VerifyCmdLength(CFE_SB_MsgPtr_t pMsg,
                                 uint16 usExpectedLen)
{
    boolean bResult = FALSE;
    uint16 usMsgLen = 0;
    uint16 usCmdCode = 0;
    CFE_SB_MsgId_t msgId;

    if (pMsg != NULL)
    {
        usMsgLen = CFE_SB_GetTotalMsgLength(pMsg);

        if (usExpectedLen == usMsgLen)
        {
            bResult = TRUE;
        }
        else
        {
            msgId = CFE_SB_GetMsgId(pMsg);
            usCmdCode = CFE_SB_GetCmdCode(pMsg);

            CFE_EVS_SendEvent(_TBDAPP__CMD_ERR_EID, CFE_EVS_ERROR,
                              "_TBDAPP__VerifyCmdLength(): Recvd invalid CMD MSGLEN "
                              "(0x%04X) - cc=%d, expected=%d, actual=%d",
                              (unsigned int)msgId, (int)usCmdCode,
                              (int)usExpectedLen, (int)usMsgLen);
        }
    }
    else
    {
        CFE_EVS_SendEvent(_TBDAPP__CMD_ERR_EID, CFE_EVS_ERROR,
                          "_TBDAPP__VerifyCmdLength(): Recvd NULL pMsg");
    }

    return (bResult);
}

/*=======================================================================================*/

/**
** \brief Top level function
**
** \par Description:
**      _TBDAPP_ main entry point
** 
** \par Assumptions, External Events, and Notes:
**      None
*/
void _TBDAPP__AppMain(void)
{
    int32 iStatus = 0;

    /* Initially set running status to error until it's initialized */
    g__TBDAPP__AppData.uiRunStatus = CFE_ES_APP_ERROR;

    /* Register the application with Executive Services */
    iStatus = CFE_ES_RegisterApp();
    if (iStatus == CFE_SUCCESS)
    {
        /* Start Perf logging: app inits */
        CFE_ES_PerfLogEntry(_TBDAPP__APP_INIT_PERF_ID);

        iStatus = _TBDAPP__InitApp();

        /* Stop Perf logging: app inits  */
        CFE_ES_PerfLogExit(_TBDAPP__APP_INIT_PERF_ID);

        if (iStatus == CFE_SUCCESS)
        {
            g__TBDAPP__AppData.uiRunStatus = CFE_ES_APP_RUN;

            CFE_ES_WaitForStartupSync(_TBDAPP__STARTUP_WAIT_IN_MILLISECS);
        }

        /* Start Perf logging: app main */
        CFE_ES_PerfLogEntry(_TBDAPP__APP_MAIN_PERF_ID);

        /* Application main loop */
        while (CFE_ES_RunLoop(&g__TBDAPP__AppData.uiRunStatus) == TRUE)
        {
            /* Stop Perf logging: app main */
            CFE_ES_PerfLogExit(_TBDAPP__APP_MAIN_PERF_ID);

            /* Start Perf logging: handling scheduling msgs */
            CFE_ES_PerfLogEntry(_TBDAPP__SCH_HANDLING_PERF_ID);

            _TBDAPP__RcvMsg(CFE_SB_PEND_FOREVER);

            /* Stop Perf logging: handling scheduling msgs */
            CFE_ES_PerfLogExit(_TBDAPP__SCH_HANDLING_PERF_ID);

            /* Start Perf logging: app main */
            CFE_ES_PerfLogEntry(_TBDAPP__APP_MAIN_PERF_ID);
        }

        /* Stop Perf logging: app main */
        CFE_ES_PerfLogExit(_TBDAPP__APP_MAIN_PERF_ID);

        /* Exit the application */
        CFE_ES_ExitApp(g__TBDAPP__AppData.uiRunStatus);
    }
    else
    {
        CFE_ES_WriteToSysLog("_TBDAPP__AppMain(): CFE_ES_RegisterApp() failed (0x%04X)\n",
                             (unsigned int)iStatus);
        CFE_ES_WriteToSysLog("_TBDAPP_: Failed to initialize application. Version %d.%d.%d.%d\n",
                             (int)_TBDAPP__MAJOR_VERSION, (int)_TBDAPP__MINOR_VERSION, 
                             (int)_TBDAPP__REVISION, (int)_TBDAPP__MISSION_REVISION);
    }
}

/*=======================================================================================
** End of file _tbdApp__app.c
**=======================================================================================*/

