/******************************************************************************
*
* Module: Port
*
* File Name: Port_Cfg.h
*
* Description: Pre-Compile Configuration Header file for TM4C123GH6PM Microcontroller - Port Driver
*
* Author: Yasmin Khaled
******************************************************************************/

#ifndef PORT_CFG_H
#define PORT_CFG_H

/*
* Module Version 1.0.0
*/
#define PORT_CFG_SW_MAJOR_VERSION              (1U)
#define PORT_CFG_SW_MINOR_VERSION              (0U)
#define PORT_CFG_SW_PATCH_VERSION              (0U)

/*
* AUTOSAR Version 4.0.3
*/
#define PORT_CFG_AR_RELEASE_MAJOR_VERSION     (4U)
#define PORT_CFG_AR_RELEASE_MINOR_VERSION     (0U)
#define PORT_CFG_AR_RELEASE_PATCH_VERSION     (3U)

/* Pre-compile option for Development Error Detect */
#define PORT_DEV_ERROR_DETECT                (STD_ON)

/* Pre-compile option for Version Info API */
#define PORT_VERSION_INFO_API                (STD_ON)

/* Pre-compile option for presence of Port_SetPinDirection API */
#define PORT_SET_PIN_DIRECTION_API           (STD_ON)

/* Pre-compile option for presence of Port_SetPinMode API */
#define PORT_SET_PIN_MODE_API                (STD_ON)

/* Pre-compile option for change Pin Mode */
#define PORT_PIN_MODE_CHANGEABLE             (STD_ON)

/* Pre-compile option change Pin Direction */
#define PORT_PIN_DIRECTION_CHANGEABLE        (STD_ON)

/* Number of the configured Port Channels */
#define PORT_CONFIGURED_CHANNLES 43

/*
* PortContainer Container
*  Macro Configurations
*/
#define PORT_A  0
#define PORT_B  1
#define PORT_C  2
#define PORT_D  3
#define PORT_E  4
#define PORT_F  5

/*
* PortPin Container
*  Macro Configurations
*/
#define PORTA_Pin0  0
#define PORTA_Pin1  1
#define PORTA_Pin2  2
#define PORTA_Pin3  3
#define PORTA_Pin4  4
#define PORTA_Pin5  5
#define PORTA_Pin6  6
#define PORTA_Pin7  7

#define PORTB_Pin0  0
#define PORTB_Pin1  1
#define PORTB_Pin2  2
#define PORTB_Pin3  3
#define PORTB_Pin4  4
#define PORTB_Pin5  5
#define PORTB_Pin6  6
#define PORTB_Pin7  7

#define PORTC_Pin0  0
#define PORTC_Pin1  1
#define PORTC_Pin2  2
#define PORTC_Pin3  3
#define PORTC_Pin4  4
#define PORTC_Pin5  5
#define PORTC_Pin6  6
#define PORTC_Pin7  7

#define PORTD_Pin0  0
#define PORTD_Pin1  1
#define PORTD_Pin2  2
#define PORTD_Pin3  3
#define PORTD_Pin4  4
#define PORTD_Pin5  5
#define PORTD_Pin6  6
#define PORTD_Pin7  7

#define PORTE_Pin0  0
#define PORTE_Pin1  1
#define PORTE_Pin2  2
#define PORTE_Pin3  3
#define PORTE_Pin4  4
#define PORTE_Pin5  5

#define PORTF_Pin0  0
#define PORTF_Pin1  1
#define PORTF_Pin2  2
#define PORTF_Pin3  3
#define PORTF_Pin4   4  

#endif /* PORT_CFG_H */
