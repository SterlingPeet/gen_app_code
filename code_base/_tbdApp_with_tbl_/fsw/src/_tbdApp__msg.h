/*=======================================================================================
**
** File:  _tbdApp__msg.h
**
** Purpose:
**    This file defines command & telemetry messages for _TBDAPP_ application.
**
** Modification History:
**    Date       | Author          | Description
**    ---------- | --------------- | ----------------------------------------------------
**    _tbdDate_  | _tbdOwner_      | Initial revision
**
**=======================================================================================*/

#ifndef __tbdApp__msg_h_
#define __tbdApp__msg_h_

/*=======================================================================================
** Includes
**=======================================================================================*/

#include "cfe.h"

#include "_tbdApp__mission_cfg.h"
#include "_tbdApp__platform_cfg.h"
#include "_tbdApp__msgdefs.h"

/*=======================================================================================
** Type Definitions
**=======================================================================================*/

/********************************
** Command Message Data Formats
*********************************/

/**
** \brief Generic "no argument" command
**
** \par This command structure is used for commands that do not have any parameter.
**      This includes:
**        -# The Wakeup Message
**        -# The Send-Housekeeping Message
**        -# The No-Op Command (For details, see #_TBDAPP__NOOP_CC)
**        -# The Reset-Counters Command (For details, see #_TBDAPP__RESET_CNTRS_CC)
*/
typedef struct
{
    uint8  ucCmdHeader[CFE_SB_CMD_HDR_SIZE];  /**< \brief CCSDS command message header */

} _TBDAPP__NoArgCmd_t;

/**********************************
** Telemetry Message Data Formats
***********************************/

/**
** \brief Housekeeping telemetry
*/
typedef struct
{
    uint8   ucTlmHeader[CFE_SB_TLM_HDR_SIZE];  /**< \brief CCSDS telemetry message header */
    uint16  usCmdCntr;                         /**< \brief \_tbdApp_tlm Command Counter of valid commands received */
    uint16  usCmdErrCntr;                      /**< \brief \_tbdApp_tlm Command Error Counter of invalid commands received */
    uint32  uiExecCntr;                        /**< \brief \_tbdApp_tlm Execution Counter of execution cycles performed so far */

/*
** TODO:  Add more data items here, if necessary.
*/

} _TBDAPP__HkTlm_t;

/**********************************
** Output Message Data Formats
***********************************/

/**
** \brief Output telemetry
*/
typedef struct
{
    uint8  ucTlmHeader[CFE_SB_TLM_HDR_SIZE];  /**< \brief CCSDS telemetry message header */

/*
** TODO:  Add more data items here, if necessary.
*/

} _TBDAPP__OutData_t;

#endif /* __tbdApp__msg_h_ */

/*=======================================================================================
** End of file _tbdApp__msg.h
**=====================================================================================*/
    
