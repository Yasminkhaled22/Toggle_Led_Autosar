/******************************************************************************
*
* Module: Port
*
* File Name: Port_Types.h
*
* Description: Types Header file for TM4C123GH6PM Microcontroller - Port Driver
*
* Author: Yasmin Khaled
******************************************************************************/

#ifndef PORT_TYPES_H
#define PORT_TYPES_H


/* Type definition for Port_PinType used by the PORT APIs */
typedef uint8 Port_PinType;

/* Type definition for Port_PinModeType used by the PORT APIs */
typedef uint8 Port_PinModeType;

/* Description: Enum to hold PIN Internal Resistor */

typedef enum
{
    OFF,
    PULL_UP,
    PULL_DOWN
}Port_InternalResistor;

/* Description: Enum to hold PIN direction */
typedef enum
{
    PORT_PIN_IN,PORT_PIN_OUT
}Port_PinDirectionType;

/* Description: Enum to hold PIN Initial Value */
typedef enum
{
  PORT_PIN_LEVEL_LOW,
  PORT_PIN_LEVEL_HIGH 
}Port_PinLevel;

/* Description: Enum to hold PIN Mode */
typedef enum
{
  PORT_PIN_MODE_ADC,
  PORT_PIN_MODE_CAN,
  PORT_PIN_MODE_DIO,
  PORT_PIN_MODE_DIO_GPT,
  PORT_PIN_MODE_DIO_WDG,
  PORT_PIN_MODE_USB,
  PORT_PIN_MODE_TWI,
  PORT_PIN_MODE_SSI,
  PORT_PIN_MODE_NMI,
  PORT_PIN_MODE_PWM,
  PORT_PIN_MODE_UART,
}PORT_PIN_MODE;

/* Description: Enum to hold PIN Initial Mode */
typedef enum
{
  PORT_PIN_MODE_ADC_I,
  PORT_PIN_MODE_CAN_I,
  PORT_PIN_MODE_DIO_I,
  PORT_PIN_MODE_DIO_GPT_I,
  PORT_PIN_MODE_DIO_WDG_I,
  PORT_PIN_MODE_USB_I,
  PORT_PIN_MODE_TWI_I,
  PORT_PIN_MODE_SSI_I,
  PORT_PIN_MODE_NMI_I,
  PORT_PIN_MODE_PWM_I,
  PORT_PIN_MODE_UART_I,
}PORT_PIN_INITIAL_MODE;

#endif /* PORT_TYPES_H */
