/******************************************************************************

                  版权所有 (C), 2016-2200, 个人bsea

 ******************************************************************************
  文 件 名   : xmlparse.h
  版 本 号   : 初稿
  作    者   : bseazeng
  生成日期   : Saturday, July 23, 2016
  最近修改   :
  功能描述   : xmlparse.c 的头文件
  函数列表   :
  修改历史   :
  1.日    期   : Saturday, July 23, 2016
    作    者   : bseazeng
    修改内容   : 创建文件

******************************************************************************/

#ifndef __XMLPARSE_H__
#define __XMLPARSE_H__


#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */
#include "list.h"

#define XML_LINE_MAX_SIZE 2048
#define XML_NODE_NAME_SIZE 128

typedef struct xml_node_attr_struct_
{
    char *attr_name;
    char *attr_value;
    struct list_head *attr_next;
}xml_node_attr_struct;

typedef struct xml_node_struct_
{
    char *node_name;
    unsigned int node_depth;//节点深度
    struct list_head *attr_list;//节点属性链表
    struct list_head *brother_list;//兄弟节点    
    struct list_head *child_list;//兄弟节点    
}xml_node_struct;

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */


#endif /* __XMLPARSE_H__ */
