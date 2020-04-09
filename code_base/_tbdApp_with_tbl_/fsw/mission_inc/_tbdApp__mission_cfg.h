/*=======================================================================================
**
** File:  _tbdApp__mission_cfg.h
**
** Purpose:
**    This file defines mission-specific configurations for _TBDAPP_ application.
**
** Modification History:
**    Date       | Author          | Description
**    ---------- | --------------- | ----------------------------------------------------
**    _tbdDate_  | _tbdOwner_      | Initial revision
**
**=======================================================================================*/
 
#ifndef __tbdApp__mission_cfg_h_
#define __tbdApp__mission_cfg_h_

/*=======================================================================================
** Includes
**=======================================================================================*/

#include "cfe.h"

/*=======================================================================================
** Macro Definitions
**=======================================================================================*/

/** \_tbdApp_missioncfg Mission-specific version number for _TBDAPP_ application
**  
**  \par Description:
**       An application version number consists of four parts:
**       major version number, minor version number, revision
**       number and mission-specific revision number. The mission
**       specific revision number is defined here and the other
**       parts are defined in "_tbdApp__version.h".
**
**  \par Limits:
**       Must be defined as a numeric value that is greater than
**       or equal to zero.
*/
#define _TBDAPP__MISSION_REVISION  0

/**
** \_tbdApp_missioncfg Execution rate in Hertz (Hz)
**
** \par Description:
**      The rate at which _TBDAPP_ can run per second, which should equals the publishing
**      rate of its WakeUp message.
**
** \par Limits:
**      Must be defined as a numeric value between 1 and the maximum allowable rate 
**      spcified for the mission.
*/
#define _TBDAPP__EXECUTION_RATE_IN_HZ  1

/** \_tbdApp_missioncfg Time to wait for all applications to be started
**  
**  \par Description:
**       Wait time, in milliseconds, for system startup synchronization.
**
**  \par Limits:
**       Must be defined as a numeric value that is equal to or greater than 0.
*/
#define _TBDAPP__STARTUP_WAIT_IN_MILLISECS  100


/*
** TODO: Add definitions for mission-specific parameters here, if needed.
*/

#endif /* __tbdApp__mission_cfg_h_ */

/*=======================================================================================
** End of file _tbdApp__mission_cfg.h
**=======================================================================================*/

