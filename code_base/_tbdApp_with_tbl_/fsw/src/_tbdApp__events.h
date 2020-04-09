/*=======================================================================================
**
** File:  _tbdApp__events.h
**
** Purpose:
**    This file defines Event IDs for _TBDAPP_ application.
**
** Modification History:
**    Date       | Author          | Description
**    ---------- | --------------- | ----------------------------------------------------
**    _tbdDate_  | _tbdOwner_      | Initial revision
**
**=======================================================================================*/

#ifndef __tbdApp__events_h_
#define __tbdApp__events_h_

/*=======================================================================================
** Macro Definitions
**=======================================================================================*/

/*
** _TBDAPP_ Event Message IDs...
*/

/**
** \brief Reserved event ID
**/
#define _TBDAPP__RESERVED_EID  0

/**
** \brief Generic event message of informational type
**
** \par Message:
**      "_TBDAPP__%s(): %s"
**
** \par Type: INFORMATION
**
** \par Cause:
**      Issued as-needed to notify a specific nominal event just occurred.
**      Contains the function name that triggers the event and a brief event description.
**/
#define _TBDAPP__INF_EID    1

/**
** \brief Informational event message about application initialization
**
** \par Message:
**      "_TBDAPP__%s(): %s"
**
** \par Type: INFORMATION
**
** \par Cause:
**      Issued as-needed to notify a nominal event relating to initializations.
**      Contains the function name that triggers the event and a brief event description.
**/
#define _TBDAPP__INIT_INF_EID    2

/**
** \brief Informational event message about tables
**
** \par Message:
**      "_TBDAPP__%s(): %s"
**
** \par Type: INFORMATION
**
** \par Cause:
**      Issued as-needed to notify a nominal event relating to tables.
**      Contains the function name that triggers the event and a brief event description.
**/
#define _TBDAPP__TBL_INF_EID    3

/**
** \brief Informational event message about pipes
**
** \par Message:
**      "_TBDAPP__%s(): %s"
**
** \par Type: INFORMATION
**
** \par Cause:
**      Issued as-needed to notify a nominal event relating to pipes.
**      Contains the function name that triggers the event and a brief event description.
**/
#define _TBDAPP__PIPE_INF_EID    4

/**
** \brief Informational event message about commands
**
** \par Message:
**      "_TBDAPP__%s(): %s"
**
** \par Type: INFORMATION
**
** \par Cause:
**      Issued as-needed to notify a nominal event relating to command messages.
**      Contains the function name that triggers the event and a brief event description.
**/
#define _TBDAPP__CMD_INF_EID    5

/**
** \brief Informational event message about telemetry
**
** \par Message:
**      "_TBDAPP__%s(): %s"
**
** \par Type: INFORMATION
**
** \par Cause:
**      Issued as-needed to notify a nominal event relating to telemetry messages.
**      Contains the function name that triggers the event and a brief event description.
**/
#define _TBDAPP__TLM_INF_EID    6

/**
** \brief Generic event message of error type
**
** \par Message:
**      "_TBDAPP__%s(): %s"
**
** \par Type: ERROR
**
** \par Cause:
**      Issued as-needed to notify certain off-nominal event.
**      Contains the function name that triggers the event and a brief event description.
**/
#define _TBDAPP__ERR_EID    101

/**
** \brief Error event message about application initializations
**
** \par Message:
**      "_TBDAPP__%s(): %s"
**
** \par Type: ERROR
**
** \par Cause:
**      Issued as-needed to notify off-nominal event relating to initializations.
**      Contains the function name that triggers the event and a brief event description.
**/
#define _TBDAPP__INIT_ERR_EID    102

/**
** \brief Error event message about tables
**
** \par Message:
**      "_TBDAPP__%s(): %s"
**
** \par Type: ERROR
**
** \par Cause:
**      Issued as-needed to notify off-nominal event relating to tables.
**      Contains the function name that triggers the event and a brief event description.
**/
#define _TBDAPP__TBL_ERR_EID    103

/**
** \brief Error event message about pipes
**
** \par Message:
**      "_TBDAPP__%s(): %s"
**
** \par Type: ERROR
**
** \par Cause:
**      Issued as-needed to notify off-nominal event relating to pipes.
**      Contains the function name that triggers the event and a brief event description.
**/
#define _TBDAPP__PIPE_ERR_EID    104

/**
** \brief Error event message about commands
**
** \par Message:
**      "_TBDAPP__%s(): %s"
**
** \par Type: ERROR
**
** \par Cause:
**      Issued as-needed to notify off-nominal event relating to command messages.
**      Contains the function name that triggers the event and a brief event description.
**/
#define _TBDAPP__CMD_ERR_EID   105

/**
** \brief Error event message about telemetry
**
** \par Message:
**      "_TBDAPP__%s(): %s"
**
** \par Type: ERROR
**
** \par Cause:
**      Issued as-needed to notify off-nominal event relating to telemetry messages.
**      Contains the function name that triggers the event and a brief event description.
**/
#define _TBDAPP__TLM_ERR_EID   106


/*
** TODO:  Add more event IDs here, as necessary, and update _TBDAPP__EVT_CNT value.
*/

/**
** \brief Total number of events defined
**/
#define _TBDAPP__EVENT_CNT    13

#endif /* __tbdApp__events_h_ */

/*=======================================================================================
** End of file _tbdApp__events.h
**=====================================================================================*/
    
