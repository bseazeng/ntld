/******************************************************************************

                  ��Ȩ���� (C), 2016-2200, ����bsea

 ******************************************************************************
  �� �� ��   : ntld.h
  �� �� ��   : ����
  ��    ��   : bseazeng
  ��������   : Wednesday, July 13, 2016
  ����޸�   :
  ��������   : ntld.c ��ͷ�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : Wednesday, July 13, 2016
    ��    ��   : bseazeng
    �޸�����   : �����ļ�

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
	char safe_code[2];//���ֽڰ�ȫ������
	char reserved[6];//����
	unsigned long long opcode; //������
	unsigned int msg_len;//���ݳ���
}ntld_message_head_struct;

typedef struct ntld_message_data_struct_
{
	unsigned char number;//���ݱ��
	unsigned char type;//��������
	unsigned char len;//���ݳ���
	char *data;       //����
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
