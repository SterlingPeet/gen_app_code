/*=======================================================================================
**
** File  _tbdApp__platform_cfg.h
**
** Purpose:
**    This file defines platform-specific configurations for _TBDAPP_ application.
**
** Modification History:
**    Date       | Author          | Description
**    ---------- | --------------- | ----------------------------------------------------
**    _tbdDate_  | _tbdOwner_      | Initial revision
**
**=======================================================================================*/

#ifndef __tbdApp__platform_cfg_h_
#define __tbdApp__platform_cfg_h_

/*=======================================================================================
** Macro Definitions
**=======================================================================================*/

/**
** \_tbdApp_platformcfg Unique name for _TBDAPP_ Scheduling pipe
**
** \par Description:
**      This pipe receives messages sent by the SCH application, typically the
**      WakeUp and SendHk messages.
*/
#define _TBDAPP__SCH_PIPE_NAME  "_TBDAPP__SCH_PIPE"

/**
** \_tbdApp_platformcfg Maximum number of messages in the Scheduling pipe
**
** \par Description:
**      When this number is reached, incoming messages will get dropped
**      until there is room in the pipe again.
*/
#define _TBDAPP__SCH_PIPE_DEPTH  3

/**
** \_tbdApp_platformcfg Unique name for _TBDAPP_ Command pipe
**
** \par Description:
**      This pipe receives command messages sent by any source.
*/
#define _TBDAPP__CMD_PIPE_NAME  "_TBDAPP__CMD_PIPE"

/**
** \_tbdApp_platformcfg Maximum number of messages in the Command pipe
**
** \par Description:
**      When this number is reached, incoming messages will get dropped
**      until there is room in the pipe again.
*/
#define _TBDAPP__CMD_PIPE_DEPTH  5

/**
** \_tbdApp_platformcfg Unique name for _TBDAPP_ Telemetry pipe
**
** \par Description:
**      This pipe receives telemetry messages that it subscribes to.
*/
#define _TBDAPP__TLM_PIPE_NAME  "_TBDAPP__TLM_PIPE"

/**
** \_tbdApp_platformcfg Maximum number of messages in the Telemetry pipe
**
** \par Description:
**      When this number is reached, incoming messages will get dropped
**      until there is room in the pipe again.
*/
#define _TBDAPP__TLM_PIPE_DEPTH  5

/**
** \_tbdApp_platformcfg Full filename of the table object file
**
** \par Description:
**      The path points to the location of the table object file on the
**      target.
*/
#define _TBDAPP___TBDTBL__FILENAME  "/cf/apps/_tbdApp___tbdTbl_.tbl"

/**
** \_tbdApp_platformcfg Table name
**
** \par Description:
**      Name of the table as registered with CFE Executive Service
*/
#define _TBDAPP___TBDTBL__TABLENAME  "_TBDTBL__TBL"


/*
** TODO: Add more definitions for platform-specific parameters here, if needed.
*/

#endif /* __tbdApp__platform_cfg_h_ */

/*=======================================================================================
** End of file _tbdApp__platform_cfg.h
**=======================================================================================*/

