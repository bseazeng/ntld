/******************************************************************************

                  ��Ȩ���� (C), 2016-2200, ����bsea

 ******************************************************************************
  �� �� ��   : ntld.c
  �� �� ��   : ����
  ��    ��   : bseazeng
  ��������   : Wednesday, July 13, 2016
  ����޸�   :
  ��������   : ͨ��Э��ntld��ʵ��
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : Wednesday, July 13, 2016
    ��    ��   : bseazeng
    �޸�����   : �����ļ�

******************************************************************************/
#include "ntld.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*****************************************************************************
 �� �� ��  : setHead
 ��������  : ���ntldЭ��ͷ
 �������  : unsigned long long opcode
 �������  : ntld_message_head_struct *head
 �� �� ֵ  : int
 ���ú���  : 
 ��������  : 
 
 �޸���ʷ      :
  1.��    ��   : Wednesday, July 13, 2016
    ��    ��   : bseazeng
    �޸�����   : �����ɺ���

*****************************************************************************/
int setHead( unsigned long long opcode ,int len, ntld_message_head_struct *head)
{
    if ( NULL == head )
    {
        printf("[%s][%d]\n",__FUNCTION__,__LINE__);
        return RETURN_NULL;
    }

    head->safe_code[0] = 0xa5;
    head->safe_code[1] = 0x5a;
    head->msg_len      = len;
    head->opcode       = opcode;

    return RETURN_OK;
}

/*****************************************************************************
 �� �� ��  : isFilled
 ��������  : �жϱ���Ѿ����(����)
 �������  : const char number, struct list_head *h
 �������  : ��
 �� �� ֵ  : int
 ���ú���  : 
 ��������  : 
 
 �޸���ʷ      :
  1.��    ��   : Sunday, July 17, 2016
    ��    ��   : bseazeng
    �޸�����   : �����ɺ���

*****************************************************************************/
int isFilled( const unsigned char number , struct list_head *h)
{
    struct list_head *tmp                = NULL;
    struct list_head *n                  = NULL;
    ntld_message_data_struct *data_entry = NULL;

    //�жϸñ���ǲ��Ѿ�
    list_for_each_safe(tmp ,n,h)
    {
        data_entry = list_entry(tmp,ntld_message_data_struct,item_list);
        if ( NULL != data_entry )
        {
            if ( number == data_entry->number )
            {
                return RETURN_FILLED;
            }
            data_entry = NULL;
        }
    }

    return RETURN_OK;
}

/*****************************************************************************
 �� �� ��  : setData
 ��������  : �������
 �������  : ntld_message_data_struct *data, struct list_head *h
 �������  : ��
 �� �� ֵ  : int
 ���ú���  : 
 ��������  : 
 
 �޸���ʷ      :
  1.��    ��   : Sunday, July 17, 2016
    ��    ��   : bseazeng
    �޸�����   : �����ɺ���

*****************************************************************************/
int setData( ntld_message_data_struct *data_node ,char* value, struct list_head *h )
{
    data_node->data = (char*)malloc(sizeof(unsigned char));
    if ( NULL == data_node->data )
    {
        printf("[%s][%d]\n",__FUNCTION__,__LINE__);
        return RETURN_NULL;
    }

    memcpy(data_node->data,value,data_node->len);
    list_add(&data_node->item_list,h);
    return 	data_node->len+3;
}
/*****************************************************************************
 �� �� ��  : setUCharData
 ��������  : ���unsigned char ����
 �������  : unsigned char number, unsigned char value
 �������  : struct list_head *h
 �� �� ֵ  : int
*****************************************************************************/
int setUCharData( unsigned char number, unsigned char value , struct list_head *h )
{
    if ( NULL == h )
    {
        printf("[%s][%d]\n",__FUNCTION__,__LINE__);
        return RETURN_NULL;
    }

    if ( RETURN_FILLED == isFilled(number, h))
    {
        return RETURN_FILLED;
    }

    ntld_message_data_struct *data_node = NULL;
    data_node  = (ntld_message_data_struct*)malloc(sizeof(ntld_message_data_struct));
    if ( NULL == data_node )
    {
        printf("[%s][%d]\n",__FUNCTION__,__LINE__);
        return RETURN_NULL;
    }

    data_node->len    = sizeof(unsigned char);
    data_node->number = number;
    data_node->type   = YPPE_UCHAR;	

    return setData(data_node, (char*)&value, h);
}
/*****************************************************************************
 �� �� ��  : setCharData
 ��������  : ��� char ����
 �������  : unsigned char number, char value 
 �������  : struct list_head *h
 �� �� ֵ  : int
*****************************************************************************/
int setCharData( unsigned char number, char value , struct list_head *h )
{
    if ( NULL == h )
    {
        printf("[%s][%d]\n",__FUNCTION__,__LINE__);
        return RETURN_NULL;
    }

    if ( RETURN_FILLED == isFilled(number, h))
    {
        return RETURN_FILLED;
    }

    ntld_message_data_struct *data_node = NULL;
    data_node  = (ntld_message_data_struct*)malloc(sizeof(ntld_message_data_struct));
    if ( NULL == data_node )
    {
        printf("[%s][%d]\n",__FUNCTION__,__LINE__);
        return RETURN_NULL;
    }

    data_node->len    = sizeof(char);
    data_node->number = number;
    data_node->type   = TYPE_CHAR;

    return setData(data_node, (char*)&value, h);
}


/*****************************************************************************
 �� �� ��  : setIntData
 ��������  : ���int����
 �������  : unsigned char number, int value 
 �������  : struct list_head *h
 �� �� ֵ  : int
*****************************************************************************/
int setIntData( unsigned char number, int value , struct list_head *h )
{
    if ( NULL == h )
    {
        printf("[%s][%d]\n",__FUNCTION__,__LINE__);
        return RETURN_NULL;
    }

    if ( RETURN_FILLED == isFilled(number, h))
    {
        return RETURN_FILLED;
    }

    ntld_message_data_struct *data_node = NULL;
    data_node  = (ntld_message_data_struct*)malloc(sizeof(ntld_message_data_struct));
    if ( NULL == data_node )
    {
        printf("[%s][%d]\n",__FUNCTION__,__LINE__);
        return RETURN_NULL;
    }

    data_node->len    = sizeof(int);
    data_node->number = number;
    data_node->type   = TYPE_INT;

    return setData(data_node, (char*)&value, h);
}

/*****************************************************************************
 �� �� ��  : setUIntData
 ��������  : ���unsigned int����
 �������  : unsigned char number, int value 
 �������  : struct list_head *h
 �� �� ֵ  : int
*****************************************************************************/
int setUIntData( unsigned char number, unsigned int value , struct list_head *h )
{
    if ( NULL == h )
    {
        printf("[%s][%d]\n",__FUNCTION__,__LINE__);
        return RETURN_NULL;
    }

    if ( RETURN_FILLED == isFilled(number, h))
    {
        return RETURN_FILLED;
    }

    ntld_message_data_struct *data_node = NULL;
    data_node  = (ntld_message_data_struct*)malloc(sizeof(ntld_message_data_struct));
    if ( NULL == data_node )
    {
        printf("[%s][%d]\n",__FUNCTION__,__LINE__);
        return RETURN_NULL;
    }

    data_node->len    = sizeof(unsigned int);
    data_node->number = number;
    data_node->type   = TYPE_UINT;

    return setData(data_node, (char*)&value, h);
}

/*****************************************************************************
 �� �� ��  : setLongData
 ��������  : ���long����
 �������  : unsigned char number, long value 
 �������  : struct list_head *h
 �� �� ֵ  : int
*****************************************************************************/
int setLongData( unsigned char number, long value , struct list_head *h )
{
    if ( NULL == h )
    {
        printf("[%s][%d]\n",__FUNCTION__,__LINE__);
        return RETURN_NULL;
    }

    if ( RETURN_FILLED == isFilled(number, h))
    {
        return RETURN_FILLED;
    }

    ntld_message_data_struct *data_node = NULL;
    data_node  = (ntld_message_data_struct*)malloc(sizeof(ntld_message_data_struct));
    if ( NULL == data_node )
    {
        printf("[%s][%d]\n",__FUNCTION__,__LINE__);
        return RETURN_NULL;
    }

    data_node->len    = sizeof(long);
    data_node->number = number;
    data_node->type   = TYPE_LONG;

    return setData(data_node, (char*)&value, h);
}

/*****************************************************************************
 �� �� ��  : setULongData
 ��������  : ���unsigned long����
 �������  : unsigned char number, int value 
 �������  : struct list_head *h
 �� �� ֵ  : int
*****************************************************************************/
int setULongData( unsigned char number, unsigned long value , struct list_head *h )
{
    if ( NULL == h )
    {
        printf("[%s][%d]\n",__FUNCTION__,__LINE__);
        return RETURN_NULL;
    }

    if ( RETURN_FILLED == isFilled(number, h))
    {
        return RETURN_FILLED;
    }

    ntld_message_data_struct *data_node = NULL;
    data_node  = (ntld_message_data_struct*)malloc(sizeof(ntld_message_data_struct));
    if ( NULL == data_node )
    {
        printf("[%s][%d]\n",__FUNCTION__,__LINE__);
        return RETURN_NULL;
    }

    data_node->len    = sizeof(unsigned long);
    data_node->number = number;
    data_node->type   = TYPE_ULONG;

    return setData(data_node, (char*)&value, h);
}

/*****************************************************************************
 �� �� ��  : setLongLongData
 ��������  : ���long long����
 �������  : unsigned char number, long long value 
 �������  : struct list_head *h
 �� �� ֵ  : int
*****************************************************************************/
int setLongLongData( unsigned char number, long long value , struct list_head *h )
{
    if ( NULL == h )
    {
        printf("[%s][%d]\n",__FUNCTION__,__LINE__);
        return RETURN_NULL;
    }

    if ( RETURN_FILLED == isFilled(number, h))
    {
        return RETURN_FILLED;
    }

    ntld_message_data_struct *data_node = NULL;
    data_node  = (ntld_message_data_struct*)malloc(sizeof(ntld_message_data_struct));
    if ( NULL == data_node )
    {
        printf("[%s][%d]\n",__FUNCTION__,__LINE__);
        return RETURN_NULL;
    }

    data_node->len    = sizeof(long long);
    data_node->number = number;
    data_node->type   = TYPE_LONGLONG;

    return setData(data_node, (char*)&value, h);
}

/*****************************************************************************
 �� �� ��  : setULongLongData
 ��������  : ���unsigned long long����
 �������  : unsigned char number, unsigned long long value 
 �������  : struct list_head *h
 �� �� ֵ  : int
*****************************************************************************/
int setULongLongData( unsigned char number, unsigned long long value , struct list_head *h )
{
    if ( NULL == h )
    {
        printf("[%s][%d]\n",__FUNCTION__,__LINE__);
        return RETURN_NULL;
    }

    if ( RETURN_FILLED == isFilled(number, h))
    {
        return RETURN_FILLED;
    }

    ntld_message_data_struct *data_node = NULL;
    data_node  = (ntld_message_data_struct*)malloc(sizeof(ntld_message_data_struct));
    if ( NULL == data_node )
    {
        printf("[%s][%d]\n",__FUNCTION__,__LINE__);
        return RETURN_NULL;
    }

    data_node->len    = sizeof(unsigned long long);
    data_node->number = number;
    data_node->type   = TYPE_ULONGLONG;

    return setData(data_node, (char*)&value, h);
}

/*****************************************************************************
 �� �� ��  : setStringData
 ��������  : ���unsigned long long����
 �������  : unsigned char number, unsigned long long value 
 �������  : struct list_head *h
 �� �� ֵ  : int
*****************************************************************************/
int setStringData( unsigned char number, char* value , struct list_head *h )
{
    if ( NULL == h || NULL == value)
    {
        printf("[%s][%d]\n",__FUNCTION__,__LINE__);
        return RETURN_NULL;
    }

    if ( RETURN_FILLED == isFilled(number, h))
    {
        return RETURN_FILLED;
    }

    ntld_message_data_struct *data_node = NULL;
    data_node  = (ntld_message_data_struct*)malloc(sizeof(ntld_message_data_struct));
    if ( NULL == data_node )
    {
        printf("[%s][%d]\n",__FUNCTION__,__LINE__);
        return RETURN_NULL;
    }

    data_node->len    = strlen(value)+1;
    data_node->number = number;
    data_node->type   = TYPE_STRING;

    return setData(data_node, (char*)value, h);
}


/*****************************************************************************
 �� �� ��  : copyMsgToBuffer
 ��������  : ��һntld��Ϣcopy����Ҫ���͵Ļ�����
 �������  : ntld_message_struct *msg, int buf_len
 
 �������  : char *buffer
 �� �� ֵ  : int ,����copy���ֽ���,����������
 ���ú���  : 
 ��������  : 
 
 �޸���ʷ      :
  1.��    ��   : Saturday, July 16, 2016
    ��    ��   : bseazeng
    �޸�����   : �����ɺ���

*****************************************************************************/
int copyMsgToBuffer( ntld_message_struct *msg, char *buffer , int buf_len)
{
    int msg_head_len = sizeof(ntld_message_head_struct);
    int msg_data_base_len = 3; //��Ϣ�������ͳ��Ȱ���number,type,len
    if ( NULL == msg )
    {
        printf("[%s][%d]\n",__FUNCTION__,__LINE__);
        return RETURN_NULL;
    }

    if ( buf_len < msg_head_len )
    {
        printf("[%s][%d]\n",__FUNCTION__,__LINE__);
        return RETURN_BUFFER_NOT_ENOUGH;
    }	
    memcpy(buffer,&msg->msg_head, msg_head_len);

    struct list_head *tmp = NULL;
    ntld_message_data_struct *entry = NULL;
    int offset = msg_head_len;
    list_for_each(tmp,&msg->record_list)
    {
        entry = list_entry(tmp,ntld_message_data_struct,item_list);
        if ( NULL != entry )
        {	
            if ( buf_len < offset )
            {
                printf("[%s][%d]\n",__FUNCTION__,__LINE__);
                return RETURN_BUFFER_NOT_ENOUGH;
            }
            memcpy(buffer+offset,entry,msg_data_base_len);	
            offset+= msg_data_base_len;
            memcpy(buffer+offset,entry->data,entry->len);
            offset += entry->len;
        }
    }	
    return offset;
}

/*****************************************************************************
 �� �� ��  : copyBufferToMsg
 ��������  : �������յ���Ϣ����Ϣ�ṹ����
 �������  : const char *buffer,const int len,
             
 �������  : ntld_message_struct **msg
 �� �� ֵ  : int
 ���ú���  : 
 ��������  : 
 
 �޸���ʷ      :
  1.��    ��   : Saturday, July 16, 2016
    ��    ��   : bseazeng
    �޸�����   : �����ɺ���

*****************************************************************************/
int copyBufferToMsg( const char *buffer,const int len, ntld_message_struct *msg )
{
    int msg_head_len                 = sizeof(ntld_message_head_struct);
    int msg_data_base_len = 3; //��Ϣ�������ͳ��Ȱ���number,type,len
    ntld_message_struct *tmp_msg      = NULL;
    ntld_message_data_struct *tmp_data = NULL;
    ntld_message_data_struct *nod_data = NULL;
    int offset = 0;
    if ( NULL == buffer || NULL == msg )
    {
        printf("[%s][%d]\n",__FUNCTION__,__LINE__);
        return RETURN_NULL;
    }

    tmp_msg = (ntld_message_struct*)buffer;
    if ( len != tmp_msg->msg_head.msg_len )
    {
        printf("[%s][%d]\n",__FUNCTION__,__LINE__);
        return RETURN_BUFFER_NOT_ENOUGH;
    }

    memcpy(&msg->msg_head, buffer,msg_head_len);
    INIT_LIST_HEAD(&msg->record_list);
    offset = msg_head_len;
    while(len != offset)
    {
        tmp_data = (ntld_message_data_struct*)(buffer+offset);
        nod_data = (ntld_message_data_struct*)malloc(sizeof(ntld_message_data_struct));
        if(NULL == nod_data)
        {
            printf("[%s][%d]\n",__FUNCTION__,__LINE__);
            return RETURN_NULL;
        }
        nod_data->len = tmp_data->len;		
        nod_data->number = tmp_data->number;
        nod_data->type = tmp_data->type;
        offset += msg_data_base_len;
        nod_data->data = (char*)malloc(nod_data->len);
        if(NULL == nod_data->data)
        {
            printf("[%s][%d]\n",__FUNCTION__,__LINE__);
            return RETURN_NULL;
        }

        memcpy(nod_data->data,buffer+offset,nod_data->len);
        list_add(&nod_data->item_list,&msg->record_list);
        offset += nod_data->len;
        tmp_data = NULL;
        nod_data = NULL;

    }

    return RETURN_OK;
}

/*****************************************************************************
 �� �� ��  : printData
 ��������  : ��ӡһ������
 �������  : ntld_message_data_struct *data
 �������  : ��
 �� �� ֵ  : void
 ���ú���  : 
 ��������  : 
 
 �޸���ʷ      :
  1.��    ��   : Saturday, July 16, 2016
    ��    ��   : bseazeng
    �޸�����   : �����ɺ���

*****************************************************************************/
void printData( ntld_message_data_struct *data)
{
    switch(data->type)
    {
        case TYPE_CHAR:
        {
            printf("[%d][%s][%d]=[%c]\n",(int)data->number,"TYPE_CHAR",(int)data->len,*(char*)data->data);
            break;
        }
        case YPPE_UCHAR:
        {
            printf("[%d][%s][%d]=[%c]\n",(int)data->number,"YPPE_UCHAR",(int)data->len,*(unsigned char*)data->data);
            break;
        }
        case TYPE_INT:
        {
            printf("[%d][%s][%d]=[%d]\n",(int)data->number,"TYPE_INT",(int)data->len,*(int*)data->data);
            break;
        }
        case TYPE_UINT:
        {
            printf("[%d][%s][%d]=[%u]\n",(int)data->number,"TYPE_UINT",(int)data->len,*(unsigned int*)data->data);
            break;
        }
        case TYPE_LONG:
        {
            printf("[%d][%s][%d]=[%ld]\n",(int)data->number,"TYPE_LONG",(int)data->len,*(long*)data->data);
            break;
        }
        case TYPE_ULONG:
        {
            printf("[%d][%s][%d]=[%lud]\n",(int)data->number,"TYPE_ULONG",(int)data->len,*(unsigned long*)data->data);
            break;
        }
        case TYPE_LONGLONG:
        {
            printf("[%d][%s][%d]=[%lld]\n",(int)data->number,"TYPE_LONGLONG",(int)data->len,*(long long*)data->data);
            break;
        }
        case TYPE_ULONGLONG:
        {
            printf("[%d][%s][%d]=[%lld]\n",(int)data->number,"TYPE_ULONGLONG",(int)data->len,*(unsigned long long*)data->data);
            break;
        }
        case TYPE_STRING:
        {
            printf("[%d][%s][%d]=[%s]\n",(int)data->number,"TYPE_STRING",(int)data->len,data->data);
            break;
        }
        default:
        {
            printf("Unknown\n");
        }
    }
}

/*****************************************************************************
 �� �� ��  : printMsg
 ��������  : ��ӡ��Ϣ
 �������  : ntld_message_struct *msg
 �������  : ��
 �� �� ֵ  : void
 ���ú���  : 
 ��������  : 
 
 �޸���ʷ      :
  1.��    ��   : Saturday, July 16, 2016
    ��    ��   : bseazeng
    �޸�����   : �����ɺ���

*****************************************************************************/
void printMsg( ntld_message_struct *msg )
{
    struct list_head *tmp = NULL;
    ntld_message_data_struct *entry = NULL;
    int i = 0;

    printf("[%s][%d]\n",__FUNCTION__,__LINE__);
    if(NULL == msg) 
    {
        printf("[%s][%d]\n",__FUNCTION__,__LINE__);
        return;
    }

    printf("--------------message start-------------------\n");
    for(i=0;i<2;i++)
    {
        printf("safe_code[%d]:%2x\n",i,(char)msg->msg_head.safe_code[i]);
    }
    for(i=0;i<6;i++)
    {
        printf("reserved[%d]:%2x\n",i,msg->msg_head.reserved[i]);
    }
    printf("opcode:%lld\n",msg->msg_head.opcode);
    printf("msg_len:%d\n",msg->msg_head.msg_len);
    printf("-------------data------------\n");

    list_for_each(tmp,&msg->record_list)
    {
        entry = list_entry(tmp,ntld_message_data_struct,item_list);
        if ( NULL != entry )
        {
            printData(entry);
        }
    }

    printf("--------------message end-------------------\n");
}

/*****************************************************************************
 �� �� ��  : freeMsgData
 ��������  : �ͷ���Ϣ�еļ�¼
 �������  : struct  list_head *h
 �������  : ��
 �� �� ֵ  : void
 ���ú���  : 
 ��������  : 
 
 �޸���ʷ      :
  1.��    ��   : Sunday, July 17, 2016
    ��    ��   : bseazeng
    �޸�����   : �����ɺ���

*****************************************************************************/
void freeMsgData( struct  list_head *h )
{
    struct list_head *tmp                = NULL;
    struct list_head *n                  = NULL;
    ntld_message_data_struct *data_entry = NULL;

    //�жϸñ���ǲ��Ѿ�
    list_for_each_safe(tmp ,n,h)
    {
        data_entry = list_entry(tmp,ntld_message_data_struct,item_list);
        if ( NULL != data_entry && NULL != data_entry->data)
        {
            free(data_entry->data);
            data_entry->data = NULL;

            list_del(&data_entry->item_list);
            free(data_entry);
            data_entry = NULL;
        }
    }
}

