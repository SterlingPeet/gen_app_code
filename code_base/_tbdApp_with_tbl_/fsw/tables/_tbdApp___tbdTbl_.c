/*=======================================================================================
**
** File:  _tbdApp___tbdTbl_.c
**
** Purpose:
**    This file defines the table content of _TBDTBL_ table.
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
**    1. This code is adhere to SSET Coding Standards - January 2014 baseline.
**
** Modification History:
**    Date       | Author          | Description
**    ---------- | --------------- | ----------------------------------------------------
**    _tbdDate_  | _tbdOwner_      | Initial revision
**
**=======================================================================================*/

#include "cfe_tbl_filedef.h"
#include "_tbdApp__tbldefs.h"

/*=======================================================================================
** Table Definition
**=======================================================================================*/

_TBDAPP___TBDTBL_TBL_T  g__TBDAPP___tbdTbl_Tbl =
{
    .cParam = 'a',
    .sParam = 123,
    .iParam = 4567,
    .fParam = 123.456,
    .dParam = 12.345678
};

/*=======================================================================================
** Table Declaration
**=======================================================================================*/

/* Arguments: Variable name, Table name, Text description, File name */
CFE_TBL_FILEDEF(g__TBDAPP___tbdTbl_Tbl, _TBDAPP_._TBDTBL__TBL, _TBDAPP_ _tbdTbl_ table, _tbdApp___tbdTbl_.tbl)

/*=======================================================================================
** End of file _tbdApp___tbdTbl_.c
**=======================================================================================*/

