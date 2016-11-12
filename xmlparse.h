/******************************************************************************

                  ��Ȩ���� (C), 2016-2200, ����bsea

 ******************************************************************************
  �� �� ��   : xmlparse.h
  �� �� ��   : ����
  ��    ��   : bseazeng
  ��������   : Saturday, July 23, 2016
  ����޸�   :
  ��������   : xmlparse.c ��ͷ�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : Saturday, July 23, 2016
    ��    ��   : bseazeng
    �޸�����   : �����ļ�

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
    unsigned int node_depth;//�ڵ����
    struct list_head *attr_list;//�ڵ���������
    struct list_head *brother_list;//�ֵܽڵ�    
    struct list_head *child_list;//�ֵܽڵ�    
}xml_node_struct;

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */


#endif /* __XMLPARSE_H__ */
