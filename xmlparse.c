/******************************************************************************

                  ��Ȩ���� (C), 2016-2200, ����bsea

 ******************************************************************************
  �� �� ��   : xmlparse.c
  �� �� ��   : ����
  ��    ��   : bseazeng
  ��������   : Saturday, July 23, 2016
  ����޸�   :
  ��������   :   ����xml�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : Saturday, July 23, 2016
    ��    ��   : bseazeng
    �޸�����   : �����ļ�

******************************************************************************/
/*****************************************************************************
 �� �� ��  : loadFile
 ��������  : ���ļ�����������
 �������  : struct list_head *h
 �������  : ��
 �� �� ֵ  : void
 ���ú���  : 
 ��������  : 
 
 �޸���ʷ      :
  1.��    ��   : Saturday, July 23, 2016
    ��    ��   : bseazeng
    �޸�����   : �����ɺ���

*****************************************************************************/
#include "xmlparse.h"
#include <stdio.h>
#include <stdlib.h>

/*****************************************************************************
 �� �� ��  : trimLine
 ��������  : ������С�ע��,����<>���ߵĿո������Ŀո��
 �������  : const char *src  
             char *dst        
 �������  : ��
 �� �� ֵ  : 
 ���ú���  : 
 ��������  : 
 
 �޸���ʷ      :
  1.��    ��   : Saturday, July 23, 2016
    ��    ��   : bseazeng
    �޸�����   : �����ɺ���

*****************************************************************************/
int trimAndCheckLine(const char *src,char *dst)
{
    if ( NULL == src || NULL == dst )
    {
        printf("[%s][%d]\n",__FUNCTION__,__LINE__);
        return RETURN_NULL;
    }
    return RETURN_OK;
}

/*****************************************************************************
 �� �� ��  : getNodeStart
 ��������  : ��ȡ�ڵ㿪ʼ���
 �������  : const char *src
 �������  : ��
 �� �� ֵ  : char *
 ���ú���  : 
 ��������  : 
 
 �޸���ʷ      :
  1.��    ��   : Sunday, July 24, 2016
    ��    ��   : bseazeng
    �޸�����   : �����ɺ���

*****************************************************************************/
int getNodeStart( const char *src )
{
    if ( NULL == src )
    {
        printf("[%s][%d]\n",__FUNCTION__,__LINE__);
        return RETURN_NULL;
    }
    
    int len = strlen(src);
    
    //��ʼ���<name>,���ȴ���2
    if ( 2 > len )
    {
        printf("[%s][%d]\n",__FUNCTION__,__LINE__);
        return RETURN_XML_FORMAT_ERR;
    }

    //trimAndcheckLine�󣬽ڵ㿪ʼ��һ���ַ��͵ڶ����ַ��̶�,len-1
    if ( '<' == src[0] && '/' != src[1] && '>' == src[len-1] )
    {
        return RETURN_XML_NODE_START;
    }

    return RETURN_OK;
}

/*****************************************************************************
 �� �� ��  : getNodeEnd
 ��������  : ��ȡ�ڵ�������
 �������  : const char* src
 �������  : ��
 �� �� ֵ  : int
 ���ú���  : 
 ��������  : 
 
 �޸���ʷ      :
  1.��    ��   : Sunday, July 24, 2016
    ��    ��   : bseazeng
    �޸�����   : �����ɺ���

*****************************************************************************/
int getNodeEnd( const char* src )
{
    if ( NULL == src )
    {
        printf("[%s][%d]\n",__FUNCTION__,__LINE__);
        return RETURN_NULL;
    }
    
    int len = strlen(src);
    
    //��ʼ���</name>��<name/>,���ȴ���3
    if ( 3 > len )
    {
        printf("[%s][%d]\n",__FUNCTION__,__LINE__);
        return RETURN_XML_FORMAT_ERR;
    }

    //trimAndcheckLine�󣬽ڵ㿪ʼ��һ���ַ��͵ڶ����ַ��̶���len-1
    if ( '<' == src[0] && '/' == src[1] && '>' == src[len-1] )
    {
        return RETURN_XML_NODE_END;
    }
    //trimAndcheckLine�󣬽ڵ㿪ʼ��һ���ַ��͵�len-2,len-1�ַ��̶�
    if ( '<' == src[0] && '/' == src[len-2] && '>' == src[len-1] )
    {
        return RETURN_XML_NODE_END2;
    }

    return RETURN_ERR;
}

/*****************************************************************************
 �� �� ��  : getNodeName
 ��������  : ��ȡ�ڵ���,��������
 �������  : const char* src
             char **node_name
 �������  : ��
 �� �� ֵ  : int
 ���ú���  : 
 ��������  : 
 
 �޸���ʷ      :
  1.��    ��   : Sunday, July 24, 2016
    ��    ��   : bseazeng
    �޸�����   : �����ɺ���

*****************************************************************************/
int getNodeStartName( const char* src, char **node_name )
{
    if ( NULL == src || NULL == node_name )
    {
        printf("[%s][%d]\n",__FUNCTION__,__LINE__);
        return RETURN_NULL;
    }

    if ( RETURN_XML_NODE_START != getNodeStart(src) )
    {
        return RETURN_ERR;
    }

    int len = strlen(src);
    int i   = 0;
    int name_buf[XML_NODE_NAME_SIZE] = {0};
    
    for(i=1;i < len; i++)
    {
        if ( ' ' == src[i] || '>' == src[i] || '/' == src[i-1])
        {
            *node_name = (char*)malloc(i+1);
            name_buf[i-1] = '\0';
            memcpy(*node_name,name_buf,i+1);
            break;
        }
        else
        {
            name_buf[i-1] = src[i];
        }
    }

    return RETURN_OK;
}

/*****************************************************************************
 �� �� ��  : getNodeEndNameI
 ��������  : �ڵ�������Ϊ</name>ʱ����ȡname
 �������  : const char *src
             char ** node_name
 �������  : ��
 �� �� ֵ  : int
 ���ú���  : 
 ��������  : 
 
 �޸���ʷ      :
  1.��    ��   : Sunday, July 24, 2016
    ��    ��   : bseazeng
    �޸�����   : �����ɺ���

*****************************************************************************/
int getNodeEndNameI( const char *src, char ** node_name )
{
    int len = strlen(src);
    int i   = 0;
    int name_buf[XML_NODE_NAME_SIZE] = {0};
    
    for(i=2;i < len; i++)
    {
        if ( '>' == src[i] )
        {
            *node_name = (char*)malloc(i-1);
            name_buf[i-2] = '\0';
            memcpy(*node_name,name_buf,i-1);
            break;
        }
        else
        {
            name_buf[i-2] = src[i];
        }
    }
}


/*****************************************************************************
 �� �� ��  : getNodeEndNameII
 ��������  : �ڵ�������Ϊ<name/>ʱ����ȡname
 �������  : const char *src
             char ** node_name
 �������  : ��
 �� �� ֵ  : int
 ���ú���  : 
 ��������  : 
 
 �޸���ʷ      :
  1.��    ��   : Sunday, July 24, 2016
    ��    ��   : bseazeng
    �޸�����   : �����ɺ���

*****************************************************************************/
int getNodeEndNameII( const char *src, char ** node_name )
{
    return getNodeStartName(src,node_name);
}

/*****************************************************************************
 �� �� ��  : getNodeEndName
 ��������  : ��ȡ�ڵ���,��������
 �������  : const char* src
             char **node_name
 �������  : ��
 �� �� ֵ  : int
 ���ú���  : 
 ��������  : 
 
 �޸���ʷ      :
  1.��    ��   : Sunday, July 24, 2016
    ��    ��   : bseazeng
    �޸�����   : �����ɺ���

*****************************************************************************/
int getNodeEndName( const char* src, char **node_name )
{
    if ( NULL == src || NULL == node_name )
    {
        printf("[%s][%d]\n",__FUNCTION__,__LINE__);
        return RETURN_NULL;
    }

    if ( RETURN_XML_NODE_END == getNodeEnd(src) )
    {
        return getNodeEndNameI(src,node_name);
    }

     if ( RETURN_XML_NODE_END2 == getNodeEnd(src) )
    {
        return getNodeEndNameII(src,node_name);
    }   

    return RETURN_ERR;
}

/*****************************************************************************
 �� �� ��  : getNodeAttrNumber
 ��������  : ��ýڵ����Ը���
 �������  : const char *src
 �������  : ��
 �� �� ֵ  : int
 ���ú���  : 
 ��������  : 
 
 �޸���ʷ      :
  1.��    ��   : Monday, July 25, 2016
    ��    ��   : bseazeng
    �޸�����   : �����ɺ���

*****************************************************************************/
int getNodeAttrNumber( const char *src )
{
    if ( RETURN_XML_NODE_START != getNodeStart(src) )
    {
        printf("[%s][%d]\n",__FUNCTION__,__LINE__);
        return RETURN_ERR;
    }
    
    char *tmp = src;
    int  count = 0;
    while(NULL != tmp)
    {
        if ( ' ' == *tmp )
        {
            count++;
        }
        tmp++;
    }
    
    return count;
}

/*****************************************************************************
 �� �� ��  : getNodeAttrName
 ��������  : ��ȡ�ڵ�ĵ�attr_no��������
 �������  : const  char *src
             char **attr_name
             int attr_no
 �������  : ��
 �� �� ֵ  : int
 ���ú���  : 
 ��������  : 
 
 �޸���ʷ      :
  1.��    ��   : Sunday, July 24, 2016
    ��    ��   : bseazeng
    �޸�����   : �����ɺ���

*****************************************************************************/
int getNodeAttrName( const  char *src, char **attr_name, int attr_no )
{
    if ( RETURN_XML_NODE_START != getNodeStart(src) )
    {
        printf("[%s][%d]\n",__FUNCTION__,__LINE__);
        return RETURN_ERR;
    }

    int count = getNodeAttrNumber(src);
    if ( 0 > count || attr_no > count)
    {
        printf("[%s][%d]\n",__FUNCTION__,__LINE__);
        return RETURN_OK;
    }
    
    int i   = 0;
    int j   = 0;
    int len = strlen(src);
    char name_buff[XML_NODE_NAME_SIZE] = {0};
    count   = 0;
    for(i=0;i < len; i++)
    {
        if( count == attr_no )
        {
            if ( j > XML_NODE_NAME_SIZE )
            {
                printf("[%s][%d]\n",__FUNCTION__,__LINE__);
                return RETURN_XML_FORMAT_ERR;
            }
            
        }
        if ( ' ' == src[i] )
        {
            count++;
        }
        else
        {
        }
    }
}

/*****************************************************************************
 �� �� ��  : processNode
 ��������  : ���������ļ��е�һ���ڵ�
 �������  : const char *src
             struct list_head *h
 �������  : ��
 �� �� ֵ  : int
 ���ú���  : 
 ��������  : 
 
 �޸���ʷ      :
  1.��    ��   : Saturday, July 23, 2016
    ��    ��   : bseazeng
    �޸�����   : �����ɺ���

*****************************************************************************/
int processNode( const char *src, struct list_head *h )
{
    if ( NULL == src || NULL == h )
    {
        printf("[%s][%d]\n",__FUNCTION__,__LINE__);
        return RETURN_NULL;
    }

    int src_len = strlen(src);
    int space_count = 0;
    int i = 1;
    int j = 0;
    char tmp_buf[XML_NODE_NAME_SIZE] = {0};
    xml_node_struct  *tmp_node = NULL;
    if ( i = 1; i< src_len; i++ )
    {
        if ( ' ' == src[i] )
        {
            if ( 0 == space_count )
            {
               if ( j > XML_NODE_NAME_SIZE ) 
               {
                   printf("\n");
                   return RETURN_XML_FORMAT_ERR;
               }
               tmp_node = (xml_node_struct  *)malloc(sizeof(xml_node_struct));
               
               
            }
            else
            {
                
            }
            
            space_count++;
            memset(tmp_buf,0,XML_NODE_NAME_SIZE);
            j = 0;
                
        }
        else
        {
            tmp_buf[j] = src[j];
            j++;
        }
    }
    
}
/*****************************************************************************
 �� �� ��  : loadFile
 ��������  : ����xml�����ļ�
 �������  : const char *file_name  
             struct list_head *h    
 �������  : ��
 �� �� ֵ  : 
 ���ú���  : 
 ��������  : 
 
 �޸���ʷ      :
  1.��    ��   : Saturday, July 23, 2016
    ��    ��   : bseazeng
    �޸�����   : �����ɺ���

*****************************************************************************/
int loadFile( const char *file_name, struct list_head *h )
{
    if ( NULL == file_name )
    {
        printf("[%s][%d]\n",__FUNCTION__,__LINE__);
        return RETURN_NULL;
    }
    
    FILE *fp = open(file_name,"r");
    if ( NULL == fp )
    {
        printf("open file failed\n");
        return RETURN_ERR;
    }

    char line_buffer[XML_LINE_MAX_SIZE] = {0};
    char line_trim[XML_LINE_MAX_SIZE] = {0};
    
    INIT_LIST_HEAD(h);
    while( NULL != fgets(line_buffer,line_buffer, fp))
    {
        if ( RETURN_OK != trimAndCheckLine(line_buffer,line_trim) )
        {
            printf("xml file format is not right\n");
            break;
        }
        if ( RETURN_OK != processNode(line_trim,h))
        {
            printf("processNode failed\n");
            break;
        }
        memset(line_buffer,0, XML_LINE_MAX_SIZE);
        memset(line_trim,0, XML_LINE_MAX_SIZE);
    }
}
