/******************************************************************************
*
* Module: Gpt
*
* File Name: Gpt_Cfg.h
*
* Description: Pre-Compile Configuration Header file for TM4C123GH6PM Microcontroller - Gpt Driver
*
* Author: Yasmin Khaled
******************************************************************************/

#ifndef GPT_CFG_H
#define GPT_CFG_H

/*
* Module Version 1.0.0
*/
#define GPT_CFG_SW_MAJOR_VERSION              (1U)
#define GPT_CFG_SW_MINOR_VERSION              (0U)
#define GPT_CFG_SW_PATCH_VERSION              (0U)

/*
* AUTOSAR Version 4.0.3
*/
#define GPT_CFG_AR_RELEASE_MAJOR_VERSION     (4U)
#define GPT_CFG_AR_RELEASE_MINOR_VERSION     (0U)
#define GPT_CFG_AR_RELEASE_PATCH_VERSION     (3U)

/* Pre-compile option for Development Error Detect */
#define GPT_DEV_ERROR_DETECT                (STD_ON)

/* Pre-compile option for Version Info API */
#define GPT_VERSION_INFO_API                (STD_ON)

#define GPT_REPORT_WAKEUP_SOURCE            (STD_ON)

#define GPT_ENABLE_WAKEUP                   (STD_ON)

#define GPT_DEINIT_API                      (STD_ON)

#define GPT_ENABLE_DISABLE_NOTIFICATION_API (STD_ON)

#define GPT_TIME_ELAPSED_API                (STD_ON)

#define GPT_TIME_REMAINING_API              (STD_ON)

#define GPT_WAKEUP_FUNCTIONALITY_API        (STD_ON)

#endif /* GPT_CFG_H */
