/*=======================================================================================
**
** File:  _tbdApp__tbldefs.h
**
** Purpose:
**    This file defines data structures used in _TBDAPP_'s table.
**
** Modification History:
**    Date       | Author          | Description
**    ---------- | --------------- | ----------------------------------------------------
**    _tbdDate_  | _tbdOwner_      | Initial revision
**
**=======================================================================================*/

#ifndef __tbdApp__tbldefs_h_
#define __tbdApp__tbldefs_h_

/*=======================================================================================
** Includes
**=======================================================================================*/

#include "common_types.h"
#include "_tbdApp__mission_cfg.h"
#include "_tbdApp__platform_cfg.h"

/*=======================================================================================
** Type Definitions
**=======================================================================================*/

/* Definition for _tbdTbl_ table */
typedef struct
{
    int8   cParam;
    int16  sParam;
    int32  iParam;
    float  fParam;
    double dParam;

    /* TODO:  Add type declaration for ILoad parameters here.
    **
    ** Examples:
    **    int8/char            cParam;
    **    int8/char            cParams[16];
    **    uint8/unsigned char  ucParam;
    **    uint8/unsigned char  ucParams[16];
    **
    **    int16   sParam;
    **    int16   sParams[8];
    **    uint16  usParam;
    **    uint16  usParams[8];
    **
    **    int32   iParam;
    **    int32   iParams[5];
    **    uint32  uiParam;
    **    uint32  uiParams[5];
    **
    **    float  fParam;
    **    float  fParams[3];
    **
    **    double  dParam;
    **    double  dParams[3];
    */
} _TBDAPP___TBDTBL_TBL_T;
    
#endif /* __tbdApp__tbldefs_h_ */

/*=======================================================================================
** End of file _tbdApp__tbdefs.h
**=======================================================================================*/

