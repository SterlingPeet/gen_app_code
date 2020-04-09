/*=======================================================================================
**
** File:  _tbdApp__perfids.h
**
** Purpose:
**    This file defines Performance IDs for _TBDAPP_ application.
**
** Modification History:
**    Date       | Author          | Description
**    ---------- | --------------- | ----------------------------------------------------
**    _tbdDate_  | _tbdOwner_      | Initial revision
**
**=======================================================================================*/

#ifndef __tbdApp__perfids_h_
#define __tbdApp__perfids_h_

/*=======================================================================================
** Macro Definitions
**=======================================================================================*/

#define _TBDAPP__APP_MAIN_PERF_ID      125  /**< \brief Performance ID for application's main task */
#define _TBDAPP__APP_INIT_PERF_ID      126  /**< \brief Performance ID for application initializations */
#define _TBDAPP__SCH_HANDLING_PERF_ID  127  /**< \brief Performance ID for handling scheduling msgs */
#define _TBDAPP__CMD_HANDLING_PERF_ID  128  /**< \brief Performance ID for handling commands */
#define _TBDAPP__TLM_HANDLING_PERF_ID  129  /**< \brief Performance ID for handling telemetry */


/*
** TODO:  Add more Performance IDs here, if needed.
**        These Performance IDs below might need to be updated so that they can all be
**        unique among all the CFS applications build for a mission.
*/

#endif /* __tbdApp__perfids_h_ */

/*=======================================================================================
** End of file _tbdApp__perfids.h
**=======================================================================================*/

