/*=======================================================================================
**
** File:  _tbdApp__msgdefs.h
**
** Purpose:
**    This file defines constants used in _TBDAPP_ application's command & telemetry 
**    messages.
**
** Modification History:
**    Date       | Author          | Description
**    ---------- | --------------- | ----------------------------------------------------
**    _tbdDate_  | _tbdOwner_      | Initial revision
**
**=======================================================================================*/

#ifndef __tbdApp__msgdefs_h_
#define __tbdApp__msgdefs_h_

/**************************************
** Command Codes for Command Messages
***************************************/

/** \name _TBDAPP_ Command Codes */
/** \{ */

/** \_tbdApp_cmd _TBDAPP_ No-Op Command
**
**  \par Description:
**       This command increments the _TBDAPP_ application's #_TBDAPP__HkTlm_t.usCmdCntr telemetry.
**
**  \par Command Structure:
**       #_TBDAPP__NoArgCmd_t
**
**  \par Command Arguments:
**       None
**
**  \par Command Verifications:
**       Successful execution of this command may be verified with the following telemetry:
**       - #_TBDAPP__HkTlm_t.usCmdCntr telemetry will increment.
**       - The #_TBDAPP__CMD_INF_EID informational event message will be issued acknowledging 
**         No-Op command has been received.
**
**  \par Error Conditions:
**       This command may fail for the following reason(s):
**       - Unexpected command length.
**
**       Evidence of an unexpected command length error may be found in the following telemetry:
**       - #_TBDAPP__HkTlm_t.usCmdErrCntr telemetry will increment.
**       - The #_TBDAPP__CMDMSG_LEN_ERR_EID error event message will be issued.
**
**  \par Criticality
**       None
*/
#define _TBDAPP__NOOP_CC         0    

/** \_tbdApp_cmd _TBDAPP_ Reset-Counters Command
**
**  \par Description:
**       This command resets the following telemetry:
**       - #_TBDAPP__HkTlm_t.usCmdCntr
**       - #_TBDAPP__HkTlm_t.usCmdErrCntr
**       - #_TBDAPP__HkTlm_t.uiExecCntr
**
**  \par Command Structure:
**       #_TBDAPP__NoArgCmd_t
**
**  \par Command Arguments:
**       None
**
**  \par Command Verifications:
**       Successful execution of this command may be verified with the following telemetry:
**       - #_TBDAPP__HkTlm_t.usCmdCntr telemetry will be set to zero.
**       - #_TBDAPP__HkTlm_t.usCmdErrCntr telemetry will be set to zero.
**       - #_TBDAPP__HkTlm_t.uiExecCntr telemetry will be set to zero.
**       - The #_TBDAPP__CMD_INF_EID informational event message will be issued acknowledging 
**         Reset-Counters command has been received.
**
**  \par Error Conditions:
**       This command may fail for the following reason(s):
**       - Unexpected command length.
**
**       Evidence of an unexpected command length error may be found in the following telemetry:
**       - #_TBDAPP__HkTlm_t.usCmdErrCntr telemetry will increment.
**       - The #_TBDAPP__CMDMSG_LEN_ERR_EID error event message will be issued.
**
**  \par Criticality:
**       This command is not inherently dangerous.
**       However, it is possible for ground systems and on-board safing procedures to be designed 
**       such that they react to changes in the counter values that are reset by this command.
*/
#define _TBDAPP__RESET_CNTRS_CC  1

#endif /* __tbdApp__msgdefs_h_ */

/*=======================================================================================
** End of file _tbdApp__msgdefs.h
**=====================================================================================*/
    
