 /******************************************************************************
 *
 * Module: Port
 *
 * File Name: Port.h
 *
 * Description: Header file for TM4C123GH6PM Microcontroller - Port Driver.
 *
 * Author: Yasmin Khaled
 ******************************************************************************/

#ifndef PORT_H
#define PORT_H


/* Id for the company in the AUTOSAR
 * for example Mohamed Tarek's ID = 1000 :) */
#define PORT_VENDOR_ID    (1000U)

/* Port Module Id */
#define PORT_MODULE_ID    (124U)

/* Port Instance Id */
#define PORT_INSTANCE_ID  (0U)

/*
 * Module Version 1.0.0
 */
#define PORT_SW_MAJOR_VERSION           (1U)
#define PORT_SW_MINOR_VERSION           (0U)
#define PORT_SW_PATCH_VERSION           (0U)

/*
 * AUTOSAR Version 4.0.3
 */
#define PORT_AR_RELEASE_MAJOR_VERSION   (4U)
#define PORT_AR_RELEASE_MINOR_VERSION   (0U)
#define PORT_AR_RELEASE_PATCH_VERSION   (3U)

/*
 * Macros for Port Status
 */
#define PORT_INITIALIZED                (1U)
#define PORT_NOT_INITIALIZED            (0U)


/* Standard AUTOSAR types */
#include "Std_Types.h"

/* AUTOSAR checking between Std Types and Port Modules */
#if ((STD_TYPES_AR_RELEASE_MAJOR_VERSION != PORT_AR_RELEASE_MAJOR_VERSION)\
 ||  (STD_TYPES_AR_RELEASE_MINOR_VERSION != PORT_AR_RELEASE_MINOR_VERSION)\
 ||  (STD_TYPES_AR_RELEASE_PATCH_VERSION != PORT_AR_RELEASE_PATCH_VERSION))
  #error "The AR version of Std_Types.h does not match the expected version"
#endif

/* Port Pre-Compile Configuration Header file */
#include "Port_Cfg.h"
#include "Port_Types.h"

/* AUTOSAR Version checking between Port_Cfg.h and Port.h files */
#if ((PORT_CFG_AR_RELEASE_MAJOR_VERSION != PORT_AR_RELEASE_MAJOR_VERSION)\
 ||  (PORT_CFG_AR_RELEASE_MINOR_VERSION != PORT_AR_RELEASE_MINOR_VERSION)\
 ||  (PORT_CFG_AR_RELEASE_PATCH_VERSION != PORT_AR_RELEASE_PATCH_VERSION))
  #error "The AR version of Port_Cfg.h does not match the expected version"
#endif

/* Software Version checking between Port_Cfg.h and Port.h files */
#if ((PORT_CFG_SW_MAJOR_VERSION != PORT_SW_MAJOR_VERSION)\
 ||  (PORT_CFG_SW_MINOR_VERSION != PORT_SW_MINOR_VERSION)\
 ||  (PORT_CFG_SW_PATCH_VERSION != PORT_SW_PATCH_VERSION))
  #error "The SW version of Port_Cfg.h does not match the expected version"
#endif

   
/* Non AUTOSAR files */
#include "Common_Macros.h"
     
/******************************************************************************
 *                      API Service Id Macros                                 *
 ******************************************************************************/
   
/* Service ID for PORT Init  */
#define PORT_INIT_SID                   (uint8)0x00

/* Service ID for Port Set Pin Direction */
#define PORT_SET_PIN_DIRECTION_SID      (uint8)0x01

/* Service ID for Port Refresh Port Direction */
#define PORT_REFRESH_PORT_DIRECTION_SID (uint8)0x02

/* Service ID for Port Get Version Info */
#define PORT_GET_VERSION_INFO_SID       (uint8)0x03

/* Service ID for Port Set Pin Mode */
#define PORT_SET_PIN_MODE_SID           (uint8)0x04

/*******************************************************************************
 *                      DET Error Codes                                        *
 *******************************************************************************/
/* DET code to report Incorrect Port Pin ID passed  */
#define PORT_E_PARAM_PIN                        (uint8)0x0A

/* DET code to report Port Pin not configured as changeable  */
#define PORT_E_DIRECTION_UNCHANGEABLE           (uint8)0x0B

/* DET code to report Port_Init called with wrong parameter.  */
#define PORT_E_PARAM_CONFIG                     (uint8)0x0C

/* DET code to report Port Pin Mode passed not valid  */
#define PORT_E_PARAM_INVALID_MODE               (uint8)0x0D

/* DET code to report Port_SetPinMode service called when the mode is unchangeable */
#define PORT_E_MODE_UNCHANGEABLE                (uint8)0x0E

/*
 * API service used without module initialization is reported using following
 * error code (Not exist in AUTOSAR 4.0.3 PORT SWS Document.
 */
#define PORT_E_UNINIT                           (uint8)0x0F

/*
 * The API service shall return immediately without any further action,
 * beside reporting this development error.
 */
#define PORT_E_PARAM_POINTER                    (uint8)0x10
   
/*******************************************************************************
 *                              Module Data Types                              *
 *******************************************************************************/

 /* Description: Structure to configure each individual PIN:
 *	1. the PORT Which the pin belongs to. 0, 1, 2, 3, 4 or 5
 *	2. the number of the pin in the PORT.
 *      3. the pin intial mode in the port, GPIO or other Alternative mode.
 *      4. the direction of pin --> INPUT or OUTPUT
 *      5. the initial value of the pin -> STD_HIGH / STD_LOW
 *      6. the status of the pin modechangeability -> STD_ON/STD_OFF
 *      7. the status of the pin direction changeability -> STD_ON/STD_OFF
 *      8. the internal resistor --> Disable, Pull up or Pull down
 *      8. the pin mode in the port, GPIO or other Alternative mode.
 */
typedef struct 
{
    uint8                               Port_Num; 
    uint8                               Pin_Num;
    PORT_PIN_INITIAL_MODE               Pin_InitialMode;
    Port_PinDirectionType               Direction;
    Port_PinLevel                       Pin_InitialValue;
    uint8                               Pin_Direction_Changeable;
    uint8                               Pin_Mode_Changeable;
    Port_InternalResistor               Pin_Resistor;
    PORT_PIN_MODE                       Pin_Mode;
}Port_ConfigType;

/*******************************************************************************
 *                      Function Prototypes                                    *
 *******************************************************************************/   

/* Function for PORT Initialization API */ 
void Port_Init
( 
  const Port_ConfigType* ConfigPtr
);

/* Function for Setting the port pin direction API */

#if (PORT_SET_PIN_DIRECTION_API == STD_ON)
void Port_SetPinDirection
( 
  Port_PinType Pin,
  Port_PinDirectionType Direction 
);
#endif

/* Function for refreshing  PORT direction API */
void Port_RefreshPortDirection
(
  void
);

/* Function for PORT Get Version Info API */

#if (PORT_VERSION_INFO_API == STD_ON)
void Port_GetVersionInfo
(
  Std_VersionInfoType* versioninfo
);
#endif

/* Function for Setting the PORT pin mode API */

#if (PORT_SET_PIN_MODE_API == STD_ON)
void Port_SetPinMode
(
  Port_PinType Pin,
  Port_PinModeType Mode
);
#endif

/*******************************************************************************
 *                       External Variables                                    *
 *******************************************************************************/

/* Extern PB Array of structures to be used by Port and other modules */
extern Port_ConfigType Port_Configuration[PORT_CONFIGURED_CHANNLES];


#endif /* PORT_H */
