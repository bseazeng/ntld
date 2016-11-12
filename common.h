/******************************************************************************

                  版权所有 (C), 2016-2200, 个人bsea

 ******************************************************************************
  文 件 名   : common.h
  版 本 号   : 初稿
  作    者   : bseazeng
  生成日期   : Saturday, July 23, 2016
  最近修改   :
  功能描述   : common.h 的头文件
  函数列表   :
  修改历史   :
  1.日    期   : Saturday, July 23, 2016
    作    者   : bseazeng
    修改内容   : 创建文件

******************************************************************************/

#ifndef __COMMON_H__
#define __COMMON_H__


#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */

#define RETURN_TYPE                 (0)
#define RETURN_ERR                  (RETURN_TYPE - 1)
#define RETURN_OK                   (RETURN_TYPE + 0)
#define RETURN_NULL                 (RETURN_TYPE + 1) //指针空
#define RETURN_BUFFER_NOT_ENOUGH    (RETURN_TYPE + 2) //BUFFER长度不够
#define RETURN_ERROR_BUFFER         (RETURN_TYPE + 3) //接收的消息错误
#define RETURN_FILLED               (RETURN_TYPE + 4) //已经填充
#define RETURN_XML_FORMAT_ERR       (RETURN_TYPE + 5) //xml文件格式错误
#define RETURN_XML_NODE_START       (RETURN_TYPE + 6) //xml文节点开始
#define RETURN_XML_NODE_END         (RETURN_TYPE + 7) //xml文节点开始
#define RETURN_XML_NODE_END2        (RETURN_TYPE + 8) //xml文节点开始


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */


#endif /* __COMMON_H__ */
