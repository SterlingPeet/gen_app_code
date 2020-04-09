/*=======================================================================================
**
** File:  _tbdApp__tblutils.c
**
** Purpose:
**    This file defines function definitions for _TBDAPP_'s tables.
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

#include "cfe.h"

#include "_tbdApp__app.h"
#include "_tbdApp__tblutils.h"

/*=======================================================================================
** Local Macro Definitions
**=======================================================================================*/

/*=======================================================================================
** Local Type Definitions
**=======================================================================================*/

/*=======================================================================================
** External Global Variable Declarations
**=======================================================================================*/

extern _TBDAPP__AppData_t  g__TBDAPP__AppData;

/*=======================================================================================
** Global Variable Declarations
**=======================================================================================*/

/*=======================================================================================
** Function Definitions
**=======================================================================================*/

/**
** \brief _TBDTBL_ Table Initialization
**
** \par Description:
**      Initialize _TBDTBL_ table
** 
** \par Assumptions, External Events, and Notes:
**      None
**
** \return CFE_SUCCESS
** \return Any of the return values from CFE_TBL_Register()
** \return Any of the return values from CFE_TBL_Load()
** \return Any of the return values from CFE_TBL_Manage()
** \return Any of the return values from CFE_TBL_GetAddress()
*/
int32 _TBDAPP__Init_TbdTbl_Table()
{
    int32  iStatus = -1;

    /* Register the table */
    iStatus = CFE_TBL_Register(&g__TBDAPP__AppData._tbdTbl_TblHdl,
                               _TBDAPP___TBDTBL__TABLENAME,
                               sizeof(_TBDAPP___TBDTBL_TBL_T),
                               CFE_TBL_OPT_DEFAULT,
                               (CFE_TBL_CallbackFuncPtr_t)_TBDAPP__Validate_TbdTbl_Table);
    if (iStatus != CFE_SUCCESS)
    {
        CFE_EVS_SendEvent(_TBDAPP__TBL_ERR_EID, CFE_EVS_ERROR,
                          "_TBDAPP__Init_TbdTbl_Table(): CFE_TBL_Register() failed (0x%04X)\n",
                          (unsigned int)iStatus);
        goto _TBDAPP__Init_TbdTbl_Table_Exit_Tag;
    }

    /* Load the table .tbl file */
    iStatus = CFE_TBL_Load(g__TBDAPP__AppData._tbdTbl_TblHdl,
                           CFE_TBL_SRC_FILE,
                           _TBDAPP___TBDTBL__FILENAME);
    if (iStatus != CFE_SUCCESS)
    {
        CFE_EVS_SendEvent(_TBDAPP__TBL_ERR_EID, CFE_EVS_ERROR,
                          "_TBDAPP__Init_TbdTbl_Table(): CFE_TBL_Load() failed (0x%04X)\n",
                          (unsigned int)iStatus);
        goto _TBDAPP__Init_TbdTbl_Table_Exit_Tag;
    }

    /* Manage the table */
    iStatus = CFE_TBL_Manage(g__TBDAPP__AppData._tbdTbl_TblHdl);
    if (iStatus != CFE_SUCCESS)
    {
        CFE_EVS_SendEvent(_TBDAPP__TBL_ERR_EID, CFE_EVS_ERROR,
                          "_TBDAPP__Init_TbdTbl_Table(): CFE_TBL_Manage() failed (0x%04X)\n",
                             (unsigned int)iStatus);
        goto _TBDAPP__Init_TbdTbl_Table_Exit_Tag;
    }

    /* Make sure the table is accessible */
    iStatus = CFE_TBL_GetAddress((void*)&g__TBDAPP__AppData.p_TbdTbl_Tbl,
                                 g__TBDAPP__AppData._tbdTbl_TblHdl);
    if (iStatus != CFE_TBL_INFO_UPDATED)
    {
        CFE_EVS_SendEvent(_TBDAPP__TBL_ERR_EID, CFE_EVS_ERROR,
                          "_TBDAPP__Init_TbdTbl_Table(): CFE_TBL_GetAddress() failed (0x%04X)\n",
                          (unsigned int)iStatus);
        goto _TBDAPP__Init_TbdTbl_Table_Exit_Tag;
    }

    iStatus = CFE_SUCCESS;

_TBDAPP__Init_TbdTbl_Table_Exit_Tag:
    return (iStatus);
}

/*=======================================================================================*/

/**
** \brief _TBDTBL_ Table Validation
**
** \par Description:
**      Validate _TBDTBL_ table content, making sure values are within specified limits.
** 
** \par Assumptions, External Events, and Notes:
**      None
**
** \param pTbl  Pointer to the table
**
** \return CFE_SUCCESS
** \return -1
*/
int32 _TBDAPP__Validate_TbdTbl_Table(void *pTbl)
{
    int32 iStatus = CFE_SUCCESS;
    _TBDAPP___TBDTBL_TBL_T *p_TbdTbl_Table = (_TBDAPP___TBDTBL_TBL_T*)pTbl;

    if (p_TbdTbl_Table != NULL)
    {
        /* 
        ** TODO:  Add code to validate new data values here.
        **
        ** Examples:
        **    if (pTbl->sParam <= 16)
        **    {
        **        CFE_EVS_SendEvent(_TBDAPP__TBL_ERR_EID, CFE_EVS_ERROR,
        **                          "_TBDAPP__Validate_TbdTbl_Table(): sParam out-of-range");
        **        iStatus = -1;
        **    }
        */
    }

    else
    {
        iStatus = -1;
    }

    return (iStatus);
}

/*=======================================================================================*/

/**
** \brief _TBDTBL_ Table Processing
**
** \par Description:
**      Validate and process _TBDTBL_ table content
** 
** \par Assumptions, External Events, and Notes:
**      This function is called upon receiving a new _TBDTBL_ table update.
**
** \return CFE_SUCCESS
** \return -1
*/
int32 _TBDAPP__ProcessNew_TbdTbl_Table(void)
{
    int32 iStatus = -1;

    /* Must validate the table content before making any table updates */
    iStatus = _TBDAPP__Validate_TbdTbl_Table(g__TBDAPP__AppData.p_TbdTbl_Tbl);
    if (iStatus == CFE_SUCCESS)
    {
        /*
        ** TODO: Add code to process new table values, if necessary.
        */
    }

    else
    {
        CFE_EVS_SendEvent(_TBDAPP__TBL_ERR_EID, CFE_EVS_ERROR,
                          "_TBDAPP__ProcessNew_TbdTbl_Table(): _TBDAPP__Validate_TbdTbl_Tbl() failed (0x%04X)\n",
                          (unsigned int)iStatus);
    }

    return (iStatus);
}

/*=======================================================================================
** End of file _tbdApp__tblutils.c
**=======================================================================================*/

