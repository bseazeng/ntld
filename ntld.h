/******************************************************************************

                  版权所有 (C), 2016-2200, 个人bsea

 ******************************************************************************
  文 件 名   : ntld.h
  版 本 号   : 初稿
  作    者   : bseazeng
  生成日期   : Wednesday, July 13, 2016
  最近修改   :
  功能描述   : ntld.c 的头文件
  函数列表   :
  修改历史   :
  1.日    期   : Wednesday, July 13, 2016
    作    者   : bseazeng
    修改内容   : 创建文件

******************************************************************************/

#ifndef __NTLD_H__
#define __NTLD_H__


#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */

#include "list.h"
#include "common.h"


#define TYPE_DEFINE     (0x00)
#define TYPE_CHAR       (TYPE_DEFINE+1)
#define YPPE_UCHAR      (TYPE_DEFINE+2)
#define TYPE_INT        (TYPE_DEFINE+3)
#define TYPE_UINT       (TYPE_DEFINE+4)
#define TYPE_LONG       (TYPE_DEFINE+5)
#define TYPE_ULONG      (TYPE_DEFINE+6)
#define TYPE_LONGLONG   (TYPE_DEFINE+7)
#define TYPE_ULONGLONG  (TYPE_DEFINE+8)
#define TYPE_STRING      (TYPE_DEFINE+9)

typedef struct ntld_message_head_struct_
{
	char safe_code[2];//两字节安全过滤码
	char reserved[6];//保留
	unsigned long long opcode; //操作码
	unsigned int msg_len;//数据长度
}ntld_message_head_struct;

typedef struct ntld_message_data_struct_
{
	unsigned char number;//数据编号
	unsigned char type;//数据类型
	unsigned char len;//数据长度
	char *data;       //数据
	struct list_head item_list;
}ntld_message_data_struct;
typedef struct ntld_message_struct_
{
	ntld_message_head_struct msg_head;	
	struct list_head record_list; //ntld_message_data_struct *msg_data;
}ntld_message_struct;

extern int setHead( unsigned long long opcode ,int len, ntld_message_head_struct *head);

extern int setUCharData( unsigned char number, unsigned char value , struct list_head *h );

extern int setCharData( unsigned char number, char value , struct list_head *h );

extern int setIntData( unsigned char number, int value , struct list_head *h );

extern int setUIntData( unsigned char number, unsigned int value , struct list_head *h );

extern int setLongData( unsigned char number, long value , struct list_head *h );

extern int setULongData( unsigned char number, unsigned long value , struct list_head *h );

extern int setLongLongData( unsigned char number, long long value , struct list_head *h );

extern int setULongLongData( unsigned char number, unsigned long long value , struct list_head *h );

extern int setStringData( unsigned char number, char* value , struct list_head *h );

extern int copyMsgToBuffer( ntld_message_struct *msg, char *buffer , int buf_len);
extern int copyBufferToMsg( const char *buffer,const int len, ntld_message_struct *msg );

extern void printMsg( ntld_message_struct *msg );

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */


#endif /* __NTLD_H__ */
