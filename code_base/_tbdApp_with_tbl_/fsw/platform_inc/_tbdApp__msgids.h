/*=======================================================================================
**
** File:  _tbdApp__msgids.h
**
** Purpose:
**    This file defines Message IDs for _TBDAPP_ application.
**
** Modification History:
**    Date       | Author          | Description
**    ---------- | --------------- | ----------------------------------------------------
**    _tbdDate_  | _tbdOwner_      | Initial revision
**
**=======================================================================================*/

#ifndef __tbdApp__msgids_h_
#define __tbdApp__msgids_h_

/*=======================================================================================
** Macro Definitions
**=======================================================================================*/

/** \name _TBDAPP_ Command Message IDs */
/** \{ */
#define _TBDAPP__CMD_MID      0x18C0  /**< \brief Message ID for _TBDAPP_ commands;
                                           Typically send from Ground. <BR> 
                                           Packet definition: see Command Code definitions */
#define _TBDAPP__SEND_HK_MID  0x18C1  /**< \brief Message ID for _TBDAPP_ to send its housekeeping telemetry;
                                           Typically send by the SCH application, but can also be from Ground. <BR>
                                           Packet definition: #_TBDAPP__NoArgCmd_t */
#define _TBDAPP__WAKEUP_MID   0x18C2  /**< \brief Message ID to wake up _TBDAPP_;
                                           Typically send by the SCH application. <BR>
                                           Packet definition: #_TBDAPP__NoArgCmd_t */


/*
** TODO:  Add more command IDs here, if necessary.
**        These Message IDs below might need to be updated so that they can be all
**        unique among all the apps build for a mission.
*/

/** \} */


/** \name _TBDAPP_ Telemetry Message IDs */
/** \{ */
#define _TBDAPP__HK_TLM_MID    0x08C1  /**< \brief Message ID for _TBDAPP_ Housekeeping telemetry;
                                            Send by the _TBDAPP_ applicaiton upon receiving a request for
                                            its Housekeeping telemetry. <BR>
                                            Packet definition: #_TBDAPP__HkTlm_t */
#define _TBDAPP__OUT_DATA_MID  0x08C2  /**< \brief Message ID for _TBDAPP_ OutData telemetry;
                                            Typically send by the _TBDAPP_ application at the end of
                                            a WakeUp cycle. <BR>
                                            Packet definition: #_TBDAPP__OutData_t */


/*
** TODO:  Add more telemetry IDs here, if necessary.
**        These Message IDs below might need to be updated so that they can be all
**        unique among all the apps build for a mission.
*/

/** \} */

#endif /* __tbdApp__msgids_h_ */

/*=======================================================================================
** End of file _tbdApp__msgids.h
**=======================================================================================*/

