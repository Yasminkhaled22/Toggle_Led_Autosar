/******************************************************************************
*
* Module: Port
*
* File Name: Port_PBcfg.c
*
* Description: Post Build Configuration Source file for TM4C123GH6PM Microcontroller - Port Driver
*
* Author: Yasmin Khaled
******************************************************************************/
#include "Port.h"
/*
* Module Version 1.0.0
*/
#define PORT_PBCFG_SW_MAJOR_VERSION              (1U)
#define PORT_PBCFG_SW_MINOR_VERSION              (0U)
#define PORT_PBCFG_SW_PATCH_VERSION              (0U)

/*
* AUTOSAR Version 4.0.3 
*/
#define PORT_PBCFG_AR_RELEASE_MAJOR_VERSION     (4U)
#define PORT_PBCFG_AR_RELEASE_MINOR_VERSION     (0U)
#define PORT_PBCFG_AR_RELEASE_PATCH_VERSION     (3U)

/* AUTOSAR Version checking between Dio_PBcfg.c and Dio.h files */
#if ((PORT_PBCFG_AR_RELEASE_MAJOR_VERSION != PORT_AR_RELEASE_MAJOR_VERSION)\
||  (PORT_PBCFG_AR_RELEASE_MINOR_VERSION != PORT_AR_RELEASE_MINOR_VERSION)\
  ||  (PORT_PBCFG_AR_RELEASE_PATCH_VERSION != PORT_AR_RELEASE_PATCH_VERSION))
#error "The AR version of PBcfg.c does not match the expected version"
#endif

/* Software Version checking between Dio_PBcfg.c and Dio.h files */
#if ((PORT_PBCFG_SW_MAJOR_VERSION != PORT_SW_MAJOR_VERSION)\
||  (PORT_PBCFG_SW_MINOR_VERSION != PORT_SW_MINOR_VERSION)\
  ||  (PORT_PBCFG_SW_PATCH_VERSION != PORT_SW_PATCH_VERSION))
#error "The SW version of PBcfg.c does not match the expected version"
#endif


/* Description: PB Array of structures used with Port_Init API
 *	1. the PORT Which the pin belongs to. 0, 1, 2, 3, 4 or 5
 *	2. the number of the pin in the PORT.
 *      3. the pin intial mode in the port, GPIO or other Alternative mode.
 *      4. the direction of pin --> INPUT or OUTPUT
 *      5. the initial value of the pin -> STD_HIGH / STD_LOW
 *      6. the status of the pin mode changeability -> STD_ON/STD_OFF
 *      7. the status of the pin direction changeability -> STD_ON/STD_OFF
 *      8. the internal resistor --> Disable, Pull up or Pull down
 *      8. the pin mode in the port, GPIO or other Alternative mode.
 */

Port_ConfigType Port_Configuration[PORT_CONFIGURED_CHANNLES] = 
{ 
  /* Port A configuration*/
  {
    PORT_A,
    PORTA_Pin0,
    PORT_PIN_MODE_CAN_I,
    PORT_PIN_OUT,
    PORT_PIN_LEVEL_LOW,
    STD_LOW,
    STD_LOW,
    PULL_UP
  },
  {
    PORT_A,
    PORTA_Pin1,
    PORT_PIN_MODE_CAN_I,
    PORT_PIN_IN,
    PORT_PIN_LEVEL_LOW,
    STD_LOW,
    STD_LOW,
    PULL_UP
  },
  {
    PORT_A,
    PORTA_Pin2,
    PORT_PIN_MODE_DIO_I,
    PORT_PIN_IN,
    PORT_PIN_LEVEL_LOW,
    STD_LOW,
    STD_LOW,
    PULL_UP
  },
  {
    PORT_A,
    PORTA_Pin3,
    PORT_PIN_MODE_DIO_I,
    PORT_PIN_IN,
    PORT_PIN_LEVEL_LOW,
    STD_LOW,
    STD_LOW,
    PULL_UP
  },
  {
    PORT_A,
    PORTA_Pin4,
    PORT_PIN_MODE_DIO_I,
    PORT_PIN_IN,
    PORT_PIN_LEVEL_LOW,
    STD_LOW,
    STD_LOW,
    PULL_UP
  },
  {
    PORT_A,
    PORTA_Pin5,
    PORT_PIN_MODE_DIO_I,
    PORT_PIN_IN,
    PORT_PIN_LEVEL_LOW,
    STD_LOW,
    STD_LOW,
    PULL_UP
  },
  {
    PORT_A,
    PORTA_Pin6,
    PORT_PIN_MODE_DIO_I,
    PORT_PIN_IN,
    PORT_PIN_LEVEL_LOW,
    STD_LOW,
    STD_LOW,
    PULL_UP
  },
  {
    PORT_A,
    PORTA_Pin7,
    PORT_PIN_MODE_DIO_I,
    PORT_PIN_IN,
    PORT_PIN_LEVEL_LOW,
    STD_LOW,
    STD_LOW,
    PULL_UP
  },
  
  /* Port B configuration*/
  {
    PORT_B,
    PORTB_Pin0,
    PORT_PIN_MODE_DIO_I,
    PORT_PIN_IN,
    PORT_PIN_LEVEL_LOW,
    STD_LOW,
    STD_LOW,
    PULL_UP
  },
  {
    PORT_B,
    PORTB_Pin1,
    PORT_PIN_MODE_DIO_I,
    PORT_PIN_IN,
    PORT_PIN_LEVEL_LOW,
    STD_LOW,
    STD_LOW,
    PULL_UP
  },
  {
    PORT_B,
    PORTB_Pin2,
    PORT_PIN_MODE_DIO_I,
    PORT_PIN_IN,
    PORT_PIN_LEVEL_LOW,
    STD_LOW,
    STD_LOW,
    PULL_UP
  },
  {
    PORT_B,
    PORTB_Pin3,
    PORT_PIN_MODE_DIO_I,
    PORT_PIN_IN,
    PORT_PIN_LEVEL_LOW,
    STD_LOW,
    STD_LOW,
    PULL_UP
  },
  {
    PORT_B,
    PORTB_Pin4,
    PORT_PIN_MODE_DIO_I,
    PORT_PIN_IN,
    PORT_PIN_LEVEL_LOW,
    STD_LOW,
    STD_LOW,
    PULL_UP
  },
  {
    PORT_B,
    PORTB_Pin5,
    PORT_PIN_MODE_DIO_I,
    PORT_PIN_IN,
    PORT_PIN_LEVEL_LOW,
    STD_LOW,
    STD_LOW,
    PULL_UP
  },
  {
    PORT_B,
    PORTB_Pin6,
    PORT_PIN_MODE_DIO_I,
    PORT_PIN_IN,
    PORT_PIN_LEVEL_LOW,
    STD_LOW,
    STD_LOW,
    PULL_UP
  },
  {
    PORT_B,
    PORTB_Pin7,
    PORT_PIN_MODE_DIO_I,
    PORT_PIN_IN,
    PORT_PIN_LEVEL_LOW,
    STD_LOW,
    STD_LOW,
    PULL_UP
  },
  
  /* Port C configuration*/
  {
    PORT_C,
    PORTA_Pin0,
    PORT_PIN_MODE_DIO_I,
    PORT_PIN_IN,
    PORT_PIN_LEVEL_LOW,
    STD_LOW,
    STD_LOW,
    PULL_UP
  },
  {
    PORT_C,PORTC_Pin1,
    PORT_PIN_MODE_DIO_I,
    PORT_PIN_IN,
    PORT_PIN_LEVEL_LOW,
    STD_LOW,
    STD_LOW,
    PULL_UP
  },
  {
    PORT_C,
    PORTC_Pin2,
    PORT_PIN_MODE_DIO_I,
    PORT_PIN_IN,
    PORT_PIN_LEVEL_LOW,
    STD_LOW,
    STD_LOW,
    PULL_UP
  },
  {
    PORT_C,
    PORTC_Pin3,
    PORT_PIN_MODE_DIO_I,
    PORT_PIN_IN,
    PORT_PIN_LEVEL_LOW,
    STD_LOW,
    STD_LOW,
    PULL_UP
  },
  
  {
    PORT_C,
    PORTC_Pin4,
    PORT_PIN_MODE_UART_I,
    PORT_PIN_OUT,
    PORT_PIN_LEVEL_LOW,
    STD_ON,
    STD_LOW,
    PULL_UP
  },
  {
    PORT_C,
    PORTC_Pin5,
    PORT_PIN_MODE_UART_I,
    PORT_PIN_IN,
    PORT_PIN_LEVEL_LOW,
    STD_LOW,
    STD_LOW,
    PULL_UP
  },
  {
    PORT_C,
    PORTC_Pin6,
    PORT_PIN_MODE_DIO_I,
    PORT_PIN_IN,
    PORT_PIN_LEVEL_LOW,
    STD_LOW,
    STD_LOW,
    PULL_UP
  },
  {
    PORT_C,
    PORTC_Pin7,
    PORT_PIN_MODE_DIO_I,
    PORT_PIN_IN,
    PORT_PIN_LEVEL_LOW,
    STD_LOW,
    STD_LOW,
    PULL_UP
  },
   
  /* Port D configuration*/
  {
    PORT_D,
    PORTD_Pin0,
    PORT_PIN_MODE_DIO_I,
    PORT_PIN_IN,
    PORT_PIN_LEVEL_LOW,
    STD_LOW,
    STD_LOW,
    PULL_UP
  },
  {
    PORT_D,
    PORTD_Pin1,
    PORT_PIN_MODE_DIO_I,
    PORT_PIN_IN,
    PORT_PIN_LEVEL_LOW,
    STD_LOW,
    STD_LOW,
    PULL_UP
  },
  {
    PORT_D,
    PORTD_Pin2,
    PORT_PIN_MODE_DIO_I,
    PORT_PIN_IN,
    PORT_PIN_LEVEL_LOW,
    STD_LOW,
    STD_LOW,
    PULL_UP
  },
  {
    PORT_D,
    PORTD_Pin3,
    PORT_PIN_MODE_DIO_I,
    PORT_PIN_IN,
    PORT_PIN_LEVEL_LOW,
    STD_LOW,
    STD_LOW,
    PULL_UP
  },
  {
    PORT_D,
    PORTD_Pin4,
    PORT_PIN_MODE_DIO_I,
    PORT_PIN_IN,
    PORT_PIN_LEVEL_LOW,
    STD_LOW,
    STD_LOW,
    PULL_UP
  },
  {
    PORT_D,
    PORTD_Pin5,
    PORT_PIN_MODE_DIO_I,
    PORT_PIN_IN,
    PORT_PIN_LEVEL_LOW,
    STD_LOW,
    STD_LOW,
    PULL_UP
  },
  {
    PORT_D,
    PORTD_Pin6,
    PORT_PIN_MODE_DIO_I,
    PORT_PIN_IN,
    PORT_PIN_LEVEL_LOW,
    STD_LOW,
    STD_LOW,
    PULL_UP
  },
  {
    PORT_D,
    PORTD_Pin7,
    PORT_PIN_MODE_DIO_I,
    PORT_PIN_IN,
    PORT_PIN_LEVEL_LOW,
    STD_LOW,
    STD_LOW,
    PULL_UP
  },
  
  /* Port E configuration*/
  {
    PORT_E,
    PORTE_Pin0,
    PORT_PIN_MODE_DIO_I,
    PORT_PIN_IN,
    PORT_PIN_LEVEL_LOW,
    STD_LOW,
    STD_LOW,
    PULL_UP
  },
  {
    PORT_E,
    PORTE_Pin1,
    PORT_PIN_MODE_DIO_I,
    PORT_PIN_IN,
    PORT_PIN_LEVEL_LOW,
    STD_LOW,
    STD_LOW,
    PULL_UP
  },
  {
    PORT_E,
    PORTE_Pin2,
    PORT_PIN_MODE_DIO_I,
    PORT_PIN_IN,
    PORT_PIN_LEVEL_LOW,
    STD_LOW,
    STD_LOW,
    PULL_UP
  },
  {
    PORT_E,
    PORTE_Pin3,
    PORT_PIN_MODE_ADC_I,
    PORT_PIN_IN,
    PORT_PIN_LEVEL_LOW,
    STD_LOW,
    STD_LOW,
    PULL_UP
  },
  {
    PORT_E,
    PORTE_Pin4,
    PORT_PIN_MODE_DIO_I,
    PORT_PIN_IN,
    PORT_PIN_LEVEL_LOW,
    STD_LOW,
    STD_LOW,
    PULL_UP
  },
  {
    PORT_E,
    PORTE_Pin5,
    PORT_PIN_MODE_DIO_I,
    PORT_PIN_IN,
    PORT_PIN_LEVEL_LOW,
    STD_LOW,
    STD_LOW,
    PULL_UP
  },
  
  /* Port F configuration*/
  {
    PORT_F,
    PORTF_Pin0,
    PORT_PIN_MODE_DIO_I,
    PORT_PIN_IN,
    PORT_PIN_LEVEL_LOW,
    STD_LOW,
    STD_LOW,
    PULL_UP
  },
  {
    PORT_F,
    PORTF_Pin1,
    PORT_PIN_MODE_DIO_I,
    PORT_PIN_OUT,
    PORT_PIN_LEVEL_LOW,
    STD_LOW,
    STD_LOW,
    OFF
  },
  {
    PORT_F,
    PORTF_Pin2,
    PORT_PIN_MODE_DIO_I,
    PORT_PIN_OUT,
    PORT_PIN_LEVEL_LOW,
    STD_LOW,
    STD_LOW,
    OFF
  },
  {
    PORT_F,
    PORTF_Pin3,
    PORT_PIN_MODE_DIO_I,
    PORT_PIN_OUT,
    PORT_PIN_LEVEL_LOW,
    STD_LOW,
    STD_ON,
    OFF
  },
  {
    PORT_F,
    PORTF_Pin4,
    PORT_PIN_MODE_DIO_I,
    PORT_PIN_IN,
    PORT_PIN_LEVEL_LOW,
    STD_LOW,
    STD_LOW,
    PULL_UP
  }
};