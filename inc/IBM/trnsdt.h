/**************************** Module Header ***********************************/
/*                                                                            */
/* Module Name : TRNSDT.H                                                     */
/*                                                                            */
/* Description : Header file for TrnsDt                                       */
/*                                                                            */
/* Copyright Notice: IBM Personal Communication/3270 Version 4.1              */
/*                   (C) COPYRIGHT IBM CORP. 1989,1996 - PROGRAM PROPERTY     */
/*                   OF IBM ALL RIGHTS RESERVED                               */
/******************************************************************************/
#ifdef __cplusplus
  extern "C" {
#endif

typedef struct  DtParm
       {
         WORD           parm_length;
         WORD           exit_code;
         WORD           in_length;
         LPBYTE         in_addr;
         WORD           out_length;
         LPBYTE         out_addr;
         WORD           trns_id;
         WORD           in_page;
         WORD           out_page;
         WORD           option;
       } PASSSTRUCT;

WORD FAR PASCAL TrnsDt(PASSSTRUCT *PassParm);

#ifdef __cplusplus
  }
#endif
