/*=======================================================================================
**
** File:  _tbdApp__testcases.c
**
** Purpose:
**    This file contains test cases for the _tbdApp_ application.
**
** Modification History:
**    Date       | Author          | Description
**    ---------- | --------------- | ----------------------------------------------------
**    _tbdDate_  | _tbdOwner_      | Initial revision
**
**=======================================================================================*/

#include <unistd.h>

#include "_tbdApp__testcases.h"

/*=======================================================================================
** Test Setup & Teardown functions
**=======================================================================================*/

void Ut__TBDAPP__Setup(void)
{
    Ut_OSAPI_Reset();
    Ut_CFE_SB_Reset();
    Ut_CFE_ES_Reset();
    Ut_CFE_EVS_Reset();
    Ut_CFE_TBL_Reset();
}

/*=======================================================================================*/

void Ut__TBDAPP__Teardown(void)
{
    CFE_PSP_MemSet((void*)&g__TBDAPP__AppData.HkTlm, 0x00, 
                   sizeof(g__TBDAPP__AppData.HkTlm));
    CFE_PSP_MemSet((void*)&g__TBDAPP__AppData.OutData, 0x00, 
                   sizeof(g__TBDAPP__AppData.OutData));
}

/*=======================================================================================
** _TBDAPP__InitEvent() test cases
**=======================================================================================*/

void Ut__TBDAPP__InitEvent(void)
{
    int32 retCode = 0;

    /* ----- Test case #1 - Nominal ----- */
    /* Setup additional inputs - none */
    /* Execute test */
    retCode = _TBDAPP__InitEvent();
    /* Verify outputs */
    UtAssert_True(retCode == CFE_SUCCESS, "_InitEvent() - 1/2:Nominal");

    /* ----- Test case #2 - EventRegisterFail ----- */
    /* Setup additonal inputs
       - Force CFE_EVS_Register() to return an error */
    Ut_CFE_EVS_SetReturnCode(UT_CFE_EVS_REGISTER_INDEX, CFE_EVS_UNKNOWN_FILTER, 1);
    /* Execute test */
    retCode = _TBDAPP__InitEvent();
    /* Verify outputs */
    UtAssert_True(retCode != CFE_SUCCESS, "_InitEvent() - 2/2:EventRegisterFail");
}

/*=======================================================================================
** _TBDAPP__InitPipe() test cases
**=======================================================================================*/

void Ut__TBDAPP__InitPipe(void)
{
    int32 retCode = 0;

    /* ----- Test case #1 - Nominal ----- */
    /* Setup additional inputs - none */
    /* Execute test */
    retCode = _TBDAPP__InitPipe();
    /* Verify outputs */
    UtAssert_True(retCode == CFE_SUCCESS, "_InitPipe() - 1/7:Nominal");

    /* ----- Test case #2 - CreatePipeFail for SCH ----- */
    /* Setup additional inputs
       - Force CFE_SB_CreatePipe() for Scheduling pipe to return an error */
    Ut_CFE_SB_SetReturnCode(UT_CFE_SB_CREATEPIPE_INDEX, CFE_SB_BAD_ARGUMENT, 1);
    /* Execute test */
    retCode = _TBDAPP__InitPipe();
    /* Verify outputs */
    UtAssert_True(retCode == CFE_SB_BAD_ARGUMENT,
                  "_InitPipe() - 2/7:CreatePipeFail (SCH)");

    /* ----- Test case #3 - CreatePipeFail for CMD ----- */
    /* Setup additional inputs
       - Force CFE_SB_CreatePipe() for Command pipe to return an error */
    Ut_CFE_SB_SetReturnCode(UT_CFE_SB_CREATEPIPE_INDEX, CFE_SB_BAD_ARGUMENT, 2);
    /* Execute test */
    retCode = _TBDAPP__InitPipe();
    /* Verify outputs */
    UtAssert_True(retCode == CFE_SB_BAD_ARGUMENT,
                  "_InitPipe() - 3/7:CreatePipeFail (CMD)");

    /* ----- Test case #4 - CreatePipeFail for TLM ----- */
    /* Setup additional inputs
       - Force CFE_SB_CreatePipe() for Telemetry pipe to return an error */
    Ut_CFE_SB_SetReturnCode(UT_CFE_SB_CREATEPIPE_INDEX, CFE_SB_BAD_ARGUMENT, 3);
    /* Execute test */
    retCode = _TBDAPP__InitPipe();
    /* Verify outputs */
    UtAssert_True(retCode == CFE_SB_BAD_ARGUMENT,
                  "_InitPipe() - 4/7:CreatePipeFail (TLM)");

    /* ----- Test case #5 - SubscribeFail for SCH ----- */
    /* Setup additional inputs
       - Force CFE_SB_Subscribe() for Scheduling pipe to return an error */
    Ut_CFE_SB_SetReturnCode(UT_CFE_SB_SUBSCRIBE_INDEX, CFE_SB_BAD_ARGUMENT, 1);
    /* Execute test */
    retCode = _TBDAPP__InitPipe();
    /* Verify outputs */
    UtAssert_True(retCode == CFE_SB_BAD_ARGUMENT,
                  "_InitPipe() - 5/7:SubscribeFail (SCH)");

    /* ----- Test case #6 - SubscribeFail for CMD ----- */
    /* Setup additional inputs
       - Force CFE_SB_Subscribe() for Command pipe to return an error */
    Ut_CFE_SB_SetReturnCode(UT_CFE_SB_SUBSCRIBE_INDEX, CFE_SB_BAD_ARGUMENT, 2);
    /* Execute test */
    retCode = _TBDAPP__InitPipe();
    /* Verify outputs */
    UtAssert_True(retCode == CFE_SB_BAD_ARGUMENT,
                  "_InitPipe() - 6/7:SubscribeFail (CMD)");

    /* ----- Test case #7 - SubscribeFail for SendHk CMD ----- */
    /* Setup additional inputs
       - Force CFE_SB_Subscribe() for Command pipe to return an error */
    Ut_CFE_SB_SetReturnCode(UT_CFE_SB_SUBSCRIBE_INDEX, CFE_SB_BAD_ARGUMENT, 3);
    /* Execute test */
    retCode = _TBDAPP__InitPipe();
    /* Verify outputs */
    UtAssert_True(retCode == CFE_SB_BAD_ARGUMENT,
                  "_InitPipe() - 7/7:SubscribeFail (SendHk CMD)");
}

/*=======================================================================================
** _TBDAPP__InitData() test cases
**=======================================================================================*/

void Ut__TBDAPP__InitData(void)
{
    boolean retCode = FALSE;

    /* ----- Test case #1 - Nominal ----- */
    /* Setup additional inputs - none */
    /* Execute test */
    _TBDAPP__InitData();
    /* Verify outputs */
    retCode = ((CFE_SB_GetMsgId((CFE_SB_MsgPtr_t)&g__TBDAPP__AppData.OutData) == 
                _TBDAPP__OUT_DATA_MID) &&
               (CFE_SB_GetMsgId((CFE_SB_MsgPtr_t)&g__TBDAPP__AppData.HkTlm) == 
                _TBDAPP__HK_TLM_MID));
    UtAssert_True(retCode == TRUE, "_InitData() - 1/1:Nominal");
}

/*=======================================================================================
** _TBDAPP__InitApp() test cases
**=======================================================================================*/

void Ut__TBDAPP__InitApp(void)
{
    int32 retCode = 0;

    /* ----- Test case #1 - Nominal ----- */
    /* Setup additional inputs - none */
    /* Execute test */
    retCode = _TBDAPP__InitApp();
    /* Verify outputs */
    UtAssert_True(retCode == CFE_SUCCESS, "_InitApp() - 1/3:Nominal");

    /* ----- Test case #2 - InitEventFail ----- */
    /* Setup additional inputs
       - Force CFE_EVS_Register() to return error */
    Ut_CFE_EVS_SetReturnCode(UT_CFE_EVS_REGISTER_INDEX, CFE_EVS_UNKNOWN_FILTER, 1);
    /* Execute test */
    retCode = _TBDAPP__InitApp();
    /* Verify outputs */
    UtAssert_True(retCode != CFE_SUCCESS, "_InitApp() - 2/2:InitEventFail");

    /* ----- Test case #3 - InitPipeFail ----- */
    /* Setup additional inputs
       - Force CFE_SB_CreatePipe() to return error */
    Ut_CFE_SB_SetReturnCode(UT_CFE_SB_CREATEPIPE_INDEX, CFE_SB_BAD_ARGUMENT, 1);
    /* Execute test */
    retCode = _TBDAPP__InitApp();
    /* Verify outputs */
    UtAssert_True(retCode != CFE_SUCCESS, "_InitApp() - 3/3:InitPipeFail");
}

/*=======================================================================================
** _TBDAPP__CleanupCallback() test cases
**=======================================================================================*/

void Ut__TBDAPP__CleanupCallback(void)
{
    boolean retCode = FALSE;

    /* ----- Test case #1 - Nominal ----- */
    /* Setup additional inputs
       - Set HkTlm MID */
    CFE_SB_SetMsgId((CFE_SB_MsgPtr_t)&g__TBDAPP__AppData.HkTlm, _TBDAPP__HK_TLM_MID);
    /* Execute test */
    _TBDAPP__CleanupCallback();
    /* Verify outputs */
    retCode = (CFE_SB_GetMsgId((CFE_SB_MsgPtr_t)&g__TBDAPP__AppData.HkTlm) != 
               _TBDAPP__HK_TLM_MID);
    UtAssert_True(retCode == TRUE, "_CleanupCallback() - 1/1:Nominal");    
}

/*=======================================================================================
** _TBDAPP__RcvMsg() test cases
**=======================================================================================*/

void Ut__TBDAPP__RcvMsg(void)
{
    int32 retCode = 0;
    _TBDAPP__NoArgCmd_t cmdMsg = {};
    CFE_SB_MsgPtr_t pMsg = (CFE_SB_MsgPtr_t)&cmdMsg;

    /* ----- Test case #1 - Nominal ----- */
    /* Setup additional inputs
       - Initialize the pipes
       - Set the application run status to RUN
       - Construct & send a WakeUp message to Scheduling pipe */
    _TBDAPP__InitPipe();
    g__TBDAPP__AppData.uiRunStatus = CFE_ES_APP_RUN;
    CFE_SB_SetMsgId(pMsg, _TBDAPP__WAKEUP_MID);
    CFE_SB_SetTotalMsgLength(pMsg, sizeof(cmdMsg));
    Ut_CFE_SB_AddMsgToPipe(pMsg, g__TBDAPP__AppData.SchPipeId);
    /* Execute test */
    retCode = _TBDAPP__RcvMsg(CFE_SB_PEND_FOREVER);
    /* Verify outputs */
    UtAssert_True(retCode == CFE_SUCCESS, "_RcvMsg() - 1/5:Nominal WakeUp");
    
    /* ----- Test case #2 - NoMsg ----- */
    /* Setup additional inputs - none */
    /* Execute test */
    retCode = _TBDAPP__RcvMsg(CFE_SB_POLL);
    /* Verify output */
    UtAssert_True(retCode == CFE_SB_NO_MESSAGE, "_RcvMsg() - 2/5:NoMsg");
    
    /* ----- Test case #3 - BadMID ----- */
    /* Setup additional inputs
       - Send a WakeUp message with an invalid MID */
    CFE_SB_SetMsgId(pMsg, 0x00);
    Ut_CFE_SB_AddMsgToPipe(pMsg, g__TBDAPP__AppData.SchPipeId);
    /* Execute test */
    retCode = _TBDAPP__RcvMsg(CFE_SB_PEND_FOREVER);
    /* Verify output */
    UtAssert_EventSent(_TBDAPP__CMD_ERR_EID, CFE_EVS_ERROR,
                       "_TBDAPP__RcvMsg(): Recvd invalid CMD MID (0x0000)",
                       "_RcvMsg() - 3/5:BadMID");
    
    /* ----- Test case #4 - TimedOut ----- */
    /* Setup additional inputs - none */
    /* Execute test */
    retCode = _TBDAPP__RcvMsg(10);
    /* Verify output */
    UtAssert_True(retCode == CFE_SB_TIME_OUT, "_RcvMsg() - 4/5:TimedOut");
    
    /* ----- Test case #5 - RecvMsgFail ----- */
    /* Setup additional inputs
       - Force CFE_SB_RcvMsg() to return error */
    Ut_CFE_SB_SetReturnCode(UT_CFE_SB_RCVMSG_INDEX, -1, 1);
    /* Execute test */
    retCode = _TBDAPP__RcvMsg(CFE_SB_POLL);
    /* Verify output */
    UtAssert_True(retCode != CFE_SUCCESS, "_RcvMsg() - 5/5:RecvMsgFail");
}

/*=======================================================================================
** _TBDAPP__ProcessNewData() test cases
**=======================================================================================*/

void Ut__TBDAPP__ProcessNewData(void)
{
    int32 retCode = 0;
    _TBDAPP__HkTlm_t tlmMsg = {};
    CFE_SB_MsgPtr_t pMsg = (CFE_SB_MsgPtr_t)&tlmMsg;

    /* ----- Test case #1 - Nominal ---- */
    /* Setup additional inputs
       - Initialize Telemetry pipe */
    _TBDAPP__InitPipe();
    /* Execute test - TBD */
    /* Verify output - TBD */
    UtAssert_True(TRUE, "_ProcessNewData() - 1/4:Nominal - TBD for subscribed data");

    /* ----- Test case #2 - NoMsg ----- */
    /* Setup additional inputs - none */
    /* Execute test */
    retCode = _TBDAPP__ProcessNewData();
    /* Verify output */
    UtAssert_True(retCode == CFE_SB_NO_MESSAGE, "_ProcessNewData() -2/4:NoMsg");
    
    /* ----- Test case #3 - BadMID ----- */
    /* Setup additional inputs
       - Send a Telemetry message with an invalid MID */
    CFE_SB_SetMsgId(pMsg, 0x00);
    CFE_SB_SetTotalMsgLength(pMsg, sizeof(tlmMsg));
    Ut_CFE_SB_AddMsgToPipe(pMsg, g__TBDAPP__AppData.TlmPipeId);
    /* Execute test */
    retCode = _TBDAPP__ProcessNewData();
    /* Verify output */
    UtAssert_EventSent(_TBDAPP__TLM_ERR_EID, CFE_EVS_ERROR,
                       "_TBDAPP__ProcessNewData(): Recvd invalid TLM MID (0x0000)",
                       "_ProcessNewData() - 3/4:BadMID");
        
    /* ----- Test case #4 - RecvMsgFail ----- */
    /* Setup additional inputs
       - Force CFE_SB_RcvMsg() to return error */
    Ut_CFE_SB_SetReturnCode(UT_CFE_SB_RCVMSG_INDEX, -1, 1);
    /* Execute test */
    retCode = _TBDAPP__ProcessNewData();
    /* Verify output */
    UtAssert_True(retCode != CFE_SUCCESS, "_ProcessNewData() - 4/4:RecvMsgFail");
}

/*=======================================================================================
** _TBDAPP__ProcessNewCmds() test cases
**=======================================================================================*/

void Ut__TBDAPP__ProcessNewCmds(void)
{
    int32 retCode = 0;
    char errStr[125] = {};
    _TBDAPP__NoArgCmd_t cmdMsg = {};
    CFE_SB_MsgPtr_t pMsg = (CFE_SB_MsgPtr_t)&cmdMsg;

    /* ----- Test case #1 - Nominal CmdMsg ---- */
    /* Setup additional inputs
       - Initialize Command pipe
       - Send a NoOp Command message */
    _TBDAPP__InitPipe();
    CFE_SB_SetMsgId(pMsg, _TBDAPP__CMD_MID);
    CFE_SB_SetCmdCode(pMsg, _TBDAPP__NOOP_CC);
    CFE_SB_SetTotalMsgLength(pMsg, sizeof(cmdMsg));
    Ut_CFE_SB_AddMsgToPipe(pMsg, g__TBDAPP__AppData.CmdPipeId);
    /* Execute test */
    retCode = _TBDAPP__ProcessNewCmds();
    /* Verify output */
    UtAssert_True(retCode == CFE_SB_NO_MESSAGE, "_ProcessNewCmds() - 1/7:Nominal CmdMsg");

    /* ----- Test case #2 - Nominal SendHkMsg ---- */
    /* Setup additional inputs
       - Send a SendHk Command message */
    CFE_SB_SetMsgId(pMsg, _TBDAPP__SEND_HK_MID);
    Ut_CFE_SB_AddMsgToPipe(pMsg, g__TBDAPP__AppData.CmdPipeId);
    /* Execute test */
    retCode = _TBDAPP__ProcessNewCmds();
    /* Verify output */
    UtAssert_True(retCode == CFE_SB_NO_MESSAGE, "_ProcessNewCmds() - 2/7:Nominal SendHkMsg");


    /* ----- Test case #3 - SendHk BadMsgLen ---- */
    /* Setup additional inputs
       - Send a SendHk Command message with invalid message length */
    CFE_SB_SetTotalMsgLength(pMsg, sizeof(cmdMsg)+1);
    Ut_CFE_SB_AddMsgToPipe(pMsg, g__TBDAPP__AppData.CmdPipeId);
    /* Execute test */
    retCode = _TBDAPP__ProcessNewCmds();
    /* Verify output */
    snprintf(errStr, sizeof(errStr), "_TBDAPP__VerifyCmdLength(): Recvd invalid CMD MSGLEN "
                                     "(0x%04X) - cc=0, expected=%d, actual=%d",
                                     (int)_TBDAPP__SEND_HK_MID, (int)sizeof(cmdMsg), 
                                     (int)sizeof(cmdMsg)+1);
    UtAssert_EventSent(_TBDAPP__CMD_ERR_EID, CFE_EVS_ERROR, errStr,
                       "_ProcessNewCmds() - 3/7:SendHk BadMsgLen");

    /* ----- Test case #4 - NoMsg ----- */
    /* Setup additional inputs - none */
    /* Execute test */
    retCode = _TBDAPP__ProcessNewCmds();
    /* Verify output */
    UtAssert_True(retCode == CFE_SB_NO_MESSAGE, "_ProcessNewCmds() - 4/7:NoMsg");
    
    /* ----- Test case #5 - BadMID ----- */
    /* Setup additional inputs
       - Send a Command message with an invalid MID */
    CFE_SB_SetMsgId(pMsg, 0x00);
    Ut_CFE_SB_AddMsgToPipe(pMsg, g__TBDAPP__AppData.CmdPipeId);
    /* Execute test */
    retCode = _TBDAPP__ProcessNewCmds();
    /* Verify output */
    UtAssert_EventSent(_TBDAPP__CMD_ERR_EID, CFE_EVS_ERROR,
                       "_TBDAPP__ProcessNewCmds(): Recvd invalid CMD MID (0x0000)",
                       "_ProcessNewCmds() - 5/7:BadMID");

    /* ----- Test case #6 - BadCmd ----- */
    /* Setup additional inputs
       - Send a Command message with an invalid Command Code */
    CFE_SB_SetMsgId(pMsg, _TBDAPP__CMD_MID);
    CFE_SB_SetCmdCode(pMsg, 111);
    CFE_SB_SetTotalMsgLength(pMsg, sizeof(cmdMsg));
    Ut_CFE_SB_AddMsgToPipe(pMsg, g__TBDAPP__AppData.CmdPipeId);
    /* Execute test */
    retCode = _TBDAPP__ProcessNewCmds();
    /* Verify output */
    snprintf(errStr, sizeof(errStr), "_TBDAPP__ProcessNewAppCmds(): Recvd invalid CMD CC "
                                     "(0x%04X) - cc=111",
                                     (unsigned int)_TBDAPP__CMD_MID);
    UtAssert_EventSent(_TBDAPP__CMD_ERR_EID, CFE_EVS_ERROR, errStr,
                       "_ProcessNewCmds() - 6/7:BadCmd");
  
    /* ----- Test case #7 - RecvMsgFail ----- */
    /* Setup additional inputs
       - Force CFE_SB_RcvMsg() to return error */
    Ut_CFE_SB_SetReturnCode(UT_CFE_SB_RCVMSG_INDEX, -1, 1);
    /* Execute test */
    retCode = _TBDAPP__ProcessNewCmds();
    /* Verify output */
    UtAssert_True(retCode != CFE_SUCCESS, "_ProcessNewCmds() - 7/7:RecvMsgFail");
}

/*=======================================================================================
** _TBDAPP__ProcessNewAppCmds() test cases
**=======================================================================================*/

void Ut__TBDAPP__ProcessNewAppCmds(void)
{
    int32 retCode = 0;
    _TBDAPP__NoArgCmd_t cmdMsg = {};
    CFE_SB_MsgPtr_t pMsg = (CFE_SB_MsgPtr_t)&cmdMsg;

    /* ----- Test case #1 - Nominal NoOp CmdCode ---- */
    /* Setup additional inputs
       - Pass in a NoOp Command message */
    CFE_SB_SetMsgId(pMsg, _TBDAPP__CMD_MID);
    CFE_SB_SetCmdCode(pMsg, _TBDAPP__NOOP_CC);
    CFE_SB_SetTotalMsgLength(pMsg, sizeof(cmdMsg));
    /* Execute test */
    retCode = _TBDAPP__ProcessNewAppCmds(pMsg);
    /* Verify output */
    UtAssert_True(retCode == CFE_SUCCESS, 
                  "_ProcessNewAppCmds() - 1/6:Nominal NoOp");

    /* ----- Test case #2 - Nominal ResetCntrs CmdCode ---- */
    /* Setup additional inputs
       - Pass in a ResetCntrs Command message */
    CFE_SB_SetCmdCode(pMsg, _TBDAPP__RESET_CNTRS_CC);
    /* Execute test */
    retCode = _TBDAPP__ProcessNewAppCmds(pMsg);
    /* Verify output */
    UtAssert_True(retCode == CFE_SUCCESS, 
                  "_ProcessNewAppCmds() - 2/6:Nominal ResetCntrs");

    /* ----- Test case #3 - NoOp BadMsgLen ---- */
    /* Setup additional inputs
       - Pass in a NoOp Command message with an invalid message length */
    CFE_SB_SetCmdCode(pMsg, _TBDAPP__NOOP_CC);
    CFE_SB_SetTotalMsgLength(pMsg, sizeof(cmdMsg)+1);
    /* Execute test */
    retCode = _TBDAPP__ProcessNewAppCmds(pMsg);
    /* Verify output */
    UtAssert_True(retCode != CFE_SUCCESS, 
                  "_ProcessNewAppCmds() - 3/6:NoOp BadMsgLen");

    /* ----- Test case #4 - ResetCntrs BadMsgLen ---- */
    /* Setup additional inputs
       - Pass in a ResetCntrs Command message with an invalid message length */
    CFE_SB_SetCmdCode(pMsg, _TBDAPP__RESET_CNTRS_CC);
    /* Execute test */
    retCode = _TBDAPP__ProcessNewAppCmds(pMsg);
    /* Verify output */
    UtAssert_True(retCode != CFE_SUCCESS, 
                  "_ProcessNewAppCmds() - 4/6:ResetCntrs BadMsgLen");

    /* ----- Test case #5 - BadCmdCode ---- */
    /* Setup additional inputs
       - Pass in a Command message with an invalid command code */
    CFE_SB_SetCmdCode(pMsg, 111);
    /* Execute test */
    retCode = _TBDAPP__ProcessNewAppCmds(pMsg);
    /* Verify output */
    UtAssert_True(retCode != CFE_SUCCESS, "_ProcessNewAppCmds() - 5/6:BadCmdCode");

    /* ----- Test case #6 - NullMsgPtr ---- */
    /* Setup additional inputs - none */
    /* Execute test */
    retCode = _TBDAPP__ProcessNewAppCmds(NULL);
    /* Verify output */
    UtAssert_True(retCode != CFE_SUCCESS, "_ProcessNewAppCmds() - 6/6:NullMsgPtr");
}

/*=======================================================================================
** _TBDAPP__SendHousekeeping() test cases
**=======================================================================================*/

void Ut__TBDAPP__SendHousekeeping(void)
{
    boolean retCode = FALSE;
    CFE_TIME_SysTime_t msgTimeBefore;
    CFE_TIME_SysTime_t msgTimeAfter;

    /* ----- Test case #1 - Nominal ---- */
    /* Setup additional inputs
       - Get message timestamp before calling the function 
       - Let time elapses some */
    msgTimeBefore = CFE_SB_GetMsgTime((CFE_SB_MsgPtr_t)&g__TBDAPP__AppData.HkTlm);
    usleep(500);
    /* Execute test */
    _TBDAPP__SendHousekeeping();
    /* Verify output */
    msgTimeAfter = CFE_SB_GetMsgTime((CFE_SB_MsgPtr_t)&g__TBDAPP__AppData.HkTlm);
    retCode = (memcmp((void*)&msgTimeBefore, (void*)&msgTimeAfter, 
                      sizeof(msgTimeBefore)) != sizeof(msgTimeBefore));
    UtAssert_True(retCode == TRUE, "_SendHousekeeping() - 1/1:Nominal");
}

/*=======================================================================================
** _TBDAPP__SendOutData() test cases
**=======================================================================================*/

void Ut__TBDAPP__SendOutData(void)
{
    boolean retCode = FALSE;
    CFE_TIME_SysTime_t msgTimeBefore;
    CFE_TIME_SysTime_t msgTimeAfter;

    /* ----- Test case #1 - Nominal ---- */
    /* Setup additional inputs
       - Get message timestamp before calling the function 
       - Let time elapses some */
    msgTimeBefore = CFE_SB_GetMsgTime((CFE_SB_MsgPtr_t)&g__TBDAPP__AppData.OutData);
    usleep(500);
    /* Execute test */
    _TBDAPP__SendOutData();
    /* Verify output */
    msgTimeAfter = CFE_SB_GetMsgTime((CFE_SB_MsgPtr_t)&g__TBDAPP__AppData.OutData);
    retCode = (memcmp((void*)&msgTimeBefore, (void*)&msgTimeAfter, 
                      sizeof(msgTimeBefore)) != sizeof(msgTimeBefore));
    UtAssert_True(retCode == TRUE, "_SendOutData() - 1/1:Nominal");
}

/*=======================================================================================
** _TBDAPP__VerifyCmdLength() test cases
**=======================================================================================*/

void Ut__TBDAPP__VerifyCmdLength(void)
{
    boolean retCode = FALSE;
    _TBDAPP__NoArgCmd_t cmdMsg = {};
    CFE_SB_MsgPtr_t pMsg = (CFE_SB_MsgPtr_t)&cmdMsg;

    /* ----- Test case #1 - Nominal ---- */
    /* Setup additional inputs
       - Pass in a NoOp Command message */
    CFE_SB_SetMsgId(pMsg, _TBDAPP__CMD_MID);
    CFE_SB_SetCmdCode(pMsg, _TBDAPP__NOOP_CC);
    CFE_SB_SetTotalMsgLength(pMsg, sizeof(cmdMsg));
    /* Execute test */
    retCode = _TBDAPP__VerifyCmdLength(pMsg, (uint16)sizeof(_TBDAPP__NoArgCmd_t));
    /* Verify output */
    UtAssert_True(retCode == TRUE, "_VerifyCmdLength() - 1/3:Nominal");

    /* ----- Test case #2 - BadMsgLen ---- */
    /* Setup additional inputs
       - Pass in a Command message with an invalid length */
    CFE_SB_SetTotalMsgLength(pMsg, sizeof(cmdMsg)+1);
    /* Execute test */
    retCode = _TBDAPP__VerifyCmdLength(pMsg, (uint16)sizeof(_TBDAPP__NoArgCmd_t));
    /* Verify output */
    UtAssert_True(retCode == FALSE, "_VerifyCmdLength() - 2/3:BadMsgLen");

    /* ----- Test case #3 - NullMsgPtr ---- */
    /* Setup additional inputs - none */
    /* Execute test */
    retCode = _TBDAPP__VerifyCmdLength(NULL, 0);
    /* Verify output */
    UtAssert_True(retCode == FALSE, "_VerifyCmdLength() - 3/3:NullMsgPtr");
}

/*=======================================================================================
** _TBDAPP__AppMain() test cases
**=======================================================================================*/

void Ut__TBDAPP__AppMain(void)
{
    /* Setup Inputs */
    boolean retCode = FALSE;

    /* ----- Test case #1 - Nominal ---- */
    /* Setup additional inputs - none */
    /* Execute test - none */
    /* Verify output */
    UtAssert_True(TRUE, "_AppMain() - 1/4:Can't test nominal due to infinite loop");

    /* ----- Test case #2 - RegisterAppFail ---- */
    /* Setup additional inputs -
       - Set g__TBDAPP__AppData.uiRunStatus to RUN
       - Force CFE_ES_RegisterApp() to return error */
    g__TBDAPP__AppData.uiRunStatus = CFE_ES_APP_RUN;
    Ut_CFE_ES_SetReturnCode(UT_CFE_ES_REGISTERAPP_INDEX, -1, 1);
    /* Execute test */
    _TBDAPP__AppMain();
    /* Verify output */
    retCode = (g__TBDAPP__AppData.uiRunStatus == CFE_ES_APP_ERROR);
    UtAssert_True(retCode == TRUE, "_AppMain() - 2/4:RegisterAppFail");


    /* ----- Test case #3 - InitAppFail ---- */
    /* Setup additional inputs -
       - Set g__TBDAPP__AppData.uiRunStatus to RUN
       - Force CFE_ES_RegisterApp() to return error */
    g__TBDAPP__AppData.uiRunStatus = CFE_ES_APP_RUN;
    Ut_CFE_EVS_SetReturnCode(UT_CFE_EVS_REGISTER_INDEX, CFE_EVS_UNKNOWN_FILTER, 1);
    /* Execute test */
    _TBDAPP__AppMain();
    /* Verify output */
    retCode = (g__TBDAPP__AppData.uiRunStatus == CFE_ES_APP_ERROR);
    UtAssert_True(retCode == TRUE, "_AppMain() - 3/4:InitAppFail");

    /* ----- Test case #4 - RcvMsgFail ---- */
    /* Setup additional inputs -
       - Set g__TBDAPP__AppData.uiRunStatus to RUN
       - Force CFE_ES_RegisterApp() to return error */
    g__TBDAPP__AppData.uiRunStatus = CFE_ES_APP_RUN;
    Ut_CFE_SB_SetReturnCode(UT_CFE_SB_RCVMSG_INDEX, CFE_SB_BAD_ARGUMENT, 1);
    /* Execute test */
    _TBDAPP__AppMain();
    /* Verify output */
    retCode = (g__TBDAPP__AppData.uiRunStatus == CFE_ES_APP_ERROR);
    UtAssert_True(retCode == TRUE, "_AppMain() - 4/4:RcvMsgFail");
}

/*=======================================================================================
** End of file _tbdApp__testcases.c
**=======================================================================================*/

