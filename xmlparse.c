/******************************************************************************

                  版权所有 (C), 2016-2200, 个人bsea

 ******************************************************************************
  文 件 名   : xmlparse.c
  版 本 号   : 初稿
  作    者   : bseazeng
  生成日期   : Saturday, July 23, 2016
  最近修改   :
  功能描述   :   解析xml文件
  函数列表   :
  修改历史   :
  1.日    期   : Saturday, July 23, 2016
    作    者   : bseazeng
    修改内容   : 创建文件

******************************************************************************/
/*****************************************************************************
 函 数 名  : loadFile
 功能描述  : 将文件放入链表中
 输入参数  : struct list_head *h
 输出参数  : 无
 返 回 值  : void
 调用函数  : 
 被调函数  : 
 
 修改历史      :
  1.日    期   : Saturday, July 23, 2016
    作    者   : bseazeng
    修改内容   : 新生成函数

*****************************************************************************/
#include "xmlparse.h"
#include <stdio.h>
#include <stdlib.h>

/*****************************************************************************
 函 数 名  : trimLine
 功能描述  : 清除空行、注释,符号<>两边的空格，连续的空格等
 输入参数  : const char *src  
             char *dst        
 输出参数  : 无
 返 回 值  : 
 调用函数  : 
 被调函数  : 
 
 修改历史      :
  1.日    期   : Saturday, July 23, 2016
    作    者   : bseazeng
    修改内容   : 新生成函数

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
 函 数 名  : getNodeStart
 功能描述  : 获取节点开始标记
 输入参数  : const char *src
 输出参数  : 无
 返 回 值  : char *
 调用函数  : 
 被调函数  : 
 
 修改历史      :
  1.日    期   : Sunday, July 24, 2016
    作    者   : bseazeng
    修改内容   : 新生成函数

*****************************************************************************/
int getNodeStart( const char *src )
{
    if ( NULL == src )
    {
        printf("[%s][%d]\n",__FUNCTION__,__LINE__);
        return RETURN_NULL;
    }
    
    int len = strlen(src);
    
    //开始标记<name>,长度大于2
    if ( 2 > len )
    {
        printf("[%s][%d]\n",__FUNCTION__,__LINE__);
        return RETURN_XML_FORMAT_ERR;
    }

    //trimAndcheckLine后，节点开始第一个字符和第二个字符固定,len-1
    if ( '<' == src[0] && '/' != src[1] && '>' == src[len-1] )
    {
        return RETURN_XML_NODE_START;
    }

    return RETURN_OK;
}

/*****************************************************************************
 函 数 名  : getNodeEnd
 功能描述  : 获取节点结束标记
 输入参数  : const char* src
 输出参数  : 无
 返 回 值  : int
 调用函数  : 
 被调函数  : 
 
 修改历史      :
  1.日    期   : Sunday, July 24, 2016
    作    者   : bseazeng
    修改内容   : 新生成函数

*****************************************************************************/
int getNodeEnd( const char* src )
{
    if ( NULL == src )
    {
        printf("[%s][%d]\n",__FUNCTION__,__LINE__);
        return RETURN_NULL;
    }
    
    int len = strlen(src);
    
    //开始标记</name>、<name/>,长度大于3
    if ( 3 > len )
    {
        printf("[%s][%d]\n",__FUNCTION__,__LINE__);
        return RETURN_XML_FORMAT_ERR;
    }

    //trimAndcheckLine后，节点开始第一个字符和第二个字符固定，len-1
    if ( '<' == src[0] && '/' == src[1] && '>' == src[len-1] )
    {
        return RETURN_XML_NODE_END;
    }
    //trimAndcheckLine后，节点开始第一个字符和第len-2,len-1字符固定
    if ( '<' == src[0] && '/' == src[len-2] && '>' == src[len-1] )
    {
        return RETURN_XML_NODE_END2;
    }

    return RETURN_ERR;
}

/*****************************************************************************
 函 数 名  : getNodeName
 功能描述  : 获取节点名,该名规则
 输入参数  : const char* src
             char **node_name
 输出参数  : 无
 返 回 值  : int
 调用函数  : 
 被调函数  : 
 
 修改历史      :
  1.日    期   : Sunday, July 24, 2016
    作    者   : bseazeng
    修改内容   : 新生成函数

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
 函 数 名  : getNodeEndNameI
 功能描述  : 节点结束标记为</name>时，获取name
 输入参数  : const char *src
             char ** node_name
 输出参数  : 无
 返 回 值  : int
 调用函数  : 
 被调函数  : 
 
 修改历史      :
  1.日    期   : Sunday, July 24, 2016
    作    者   : bseazeng
    修改内容   : 新生成函数

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
 函 数 名  : getNodeEndNameII
 功能描述  : 节点结束标记为<name/>时，获取name
 输入参数  : const char *src
             char ** node_name
 输出参数  : 无
 返 回 值  : int
 调用函数  : 
 被调函数  : 
 
 修改历史      :
  1.日    期   : Sunday, July 24, 2016
    作    者   : bseazeng
    修改内容   : 新生成函数

*****************************************************************************/
int getNodeEndNameII( const char *src, char ** node_name )
{
    return getNodeStartName(src,node_name);
}

/*****************************************************************************
 函 数 名  : getNodeEndName
 功能描述  : 获取节点名,该名规则
 输入参数  : const char* src
             char **node_name
 输出参数  : 无
 返 回 值  : int
 调用函数  : 
 被调函数  : 
 
 修改历史      :
  1.日    期   : Sunday, July 24, 2016
    作    者   : bseazeng
    修改内容   : 新生成函数

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
 函 数 名  : getNodeAttrNumber
 功能描述  : 获得节点属性个数
 输入参数  : const char *src
 输出参数  : 无
 返 回 值  : int
 调用函数  : 
 被调函数  : 
 
 修改历史      :
  1.日    期   : Monday, July 25, 2016
    作    者   : bseazeng
    修改内容   : 新生成函数

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
 函 数 名  : getNodeAttrName
 功能描述  : 获取节点的第attr_no个属性名
 输入参数  : const  char *src
             char **attr_name
             int attr_no
 输出参数  : 无
 返 回 值  : int
 调用函数  : 
 被调函数  : 
 
 修改历史      :
  1.日    期   : Sunday, July 24, 2016
    作    者   : bseazeng
    修改内容   : 新生成函数

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
 函 数 名  : processNode
 功能描述  : 处理配置文件中的一个节点
 输入参数  : const char *src
             struct list_head *h
 输出参数  : 无
 返 回 值  : int
 调用函数  : 
 被调函数  : 
 
 修改历史      :
  1.日    期   : Saturday, July 23, 2016
    作    者   : bseazeng
    修改内容   : 新生成函数

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
 函 数 名  : loadFile
 功能描述  : 加载xml配置文件
 输入参数  : const char *file_name  
             struct list_head *h    
 输出参数  : 无
 返 回 值  : 
 调用函数  : 
 被调函数  : 
 
 修改历史      :
  1.日    期   : Saturday, July 23, 2016
    作    者   : bseazeng
    修改内容   : 新生成函数

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
