/******************************************************************************
*
* Module: Port
*
* File Name: Port.c
*
* Description: Source file for TM4C123GH6PM Microcontroller - Port Driver.
*
* Author: Yasmin Khaled
******************************************************************************/

#include "Port.h"
#include "PORT_REGS.h"


#if (PORT_DEV_ERROR_DETECT == STD_ON)

#include "Det.h"
/* AUTOSAR Version checking between Det and Dio Modules */
#if ((DET_AR_MAJOR_VERSION != PORT_AR_RELEASE_MAJOR_VERSION)\
|| (DET_AR_MINOR_VERSION != PORT_AR_RELEASE_MINOR_VERSION)\
  || (DET_AR_PATCH_VERSION != PORT_AR_RELEASE_PATCH_VERSION))
#error "The AR version of Det.h does not match the expected version"
#endif

#endif

STATIC uint8 PORT_Status = PORT_NOT_INITIALIZED;
Port_ConfigType* channels = Port_Configuration;

/************************************************************************************
* Service Name: Port_Init
* Sync/Async: Synchronous
* Reentrancy: Non Reentrant
* Parameters (in): ConfigPtr - Pointer to post-build configuration data
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Function to Initialize the Port Driver module.
*              - Initializes ALL ports and port pins with the configuration set pointed to by the parameter ConfigPtr
*              - If Port_Init function is not called first, then no operation can occur on the MCU ports and port pins.
*              - Initializes all configured resources.
************************************************************************************/

void Port_Init( const Port_ConfigType* ConfigPtr )
{
#if (PORT_DEV_ERROR_DETECT == STD_ON)
  
  /* check if the input configuration pointer is not a NULL_PTR */
  if (NULL_PTR == ConfigPtr)
  {
    Det_ReportError(PORT_MODULE_ID,
                    PORT_INSTANCE_ID, 
                    PORT_INIT_SID,
                    PORT_E_PARAM_CONFIG);
  }
  else
#endif
  {
    uint8 i;
    volatile uint32 * PortGpio_Ptr = NULL_PTR; /* point to the required Port Registers base address */
    volatile uint32 delay = 0;
    for(i=0;i<PORT_CONFIGURED_CHANNLES;i++)
    {
      /* Enable system clock for the configured port */
      SYSCTL_REGCGC2_REG|=(1<<ConfigPtr[i].Port_Num);
      delay = SYSCTL_REGCGC2_REG;
      
      /* check the configured port number*/
      switch(ConfigPtr[i].Port_Num)
      {
      case  0: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTA_BASE_ADDRESS; /* PORTA Base Address */
      break;
      case  1: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTB_BASE_ADDRESS; /* PORTB Base Address */
      break;
      case  2: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTC_BASE_ADDRESS; /* PORTC Base Address */
      break;
      case  3: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTD_BASE_ADDRESS; /* PORTD Base Address */
      break;
      case  4: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTE_BASE_ADDRESS; /* PORTE Base Address */
      break;
      case  5: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTF_BASE_ADDRESS; /* PORTF Base Address */
      break;
      }
      
      /* check the configured pins
      * For Port C pins(4->7), PortF pin 0 unlock and enable commit registers.
      * For Port C pins (0->3) No change J-Tag pins
      * For any other pin no change
      */
      
      if( ((ConfigPtr[i].Port_Num == 3) && (ConfigPtr[i].Pin_Num == 7)) || ((ConfigPtr[i].Port_Num == 5) && (ConfigPtr[i].Pin_Num  == 0)) ) /* PD7 or PF0 */
      {
        *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_LOCK_REG_OFFSET) = 0x4C4F434B;                     /* Unlock the GPIOCR register */   
        SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_COMMIT_REG_OFFSET) , ConfigPtr[i].Pin_Num );  /* Set the corresponding bit in GPIOCR register to allow changes on this pin */
      }
      else if( (ConfigPtr[i].Port_Num == 2) && (ConfigPtr[i].Pin_Num  <= 3) ) /* PC0 to PC3 */
      {
        /* Do Nothing ...  this is the JTAG pins */
      }
      else
      {
        /* Do Nothing ... No need to unlock the commit register for this pin */
      }
      
      /* check the Initial Mode for the configured pins
      * For DIO clear AMSEL,CTL,AFSEL and set DEN registers.
      * For ADC clear DEN,CTL and set AMSEL,AFSEL registers.
      * For any other Mode clear AMSEL and set DEN,CTL,AFSEL registers.
      */   
      
      if((ConfigPtr[i].Pin_InitialMode) == PORT_PIN_MODE_DIO_I)
      {
        CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET) , ConfigPtr[i].Pin_Num);      /* Clear the corresponding bit in the GPIOAMSEL register to disable analog functionality on this pin */
        CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ALT_FUNC_REG_OFFSET) , ConfigPtr[i].Pin_Num);            /* Disable Alternative function for this pin by clear the corresponding bit in GPIOAFSEL register */
        *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET) &= ~(0x0000000F << (ConfigPtr[i].Pin_Num * 4));   /* Clear the PMCx bits for this pin */
        SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET) , ConfigPtr[i].Pin_Num);      /* Set the corresponding bit in the GPIODEN register to enable digital functionality on this pin */
      }
      else if((ConfigPtr[i].Pin_InitialMode) == PORT_PIN_MODE_ADC_I)
      {
        CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET) , ConfigPtr[i].Pin_Num);        /* Clear the corresponding bit in the GPIODEN register to enable digital functionality on this pin */
        SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET) , ConfigPtr[i].Pin_Num);        /* Set the corresponding bit in the GPIOAMSEL register to disable analog functionality on this pin */
        SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ALT_FUNC_REG_OFFSET) , ConfigPtr[i].Pin_Num);              /* Enable Alternative function for this pin by clear the corresponding bit in GPIOAFSEL register */
        *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET) &= ~(0x0000000F << (ConfigPtr[i].Pin_Num * 4));   /* Clear the PMCx bits for this pin */
      }
      else 
      {
        CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET) , ConfigPtr[i].Pin_Num);     /* Clear the corresponding bit in the GPIOAMSEL register to disable analog functionality on this pin */
        SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ALT_FUNC_REG_OFFSET) , ConfigPtr[i].Pin_Num);             /* Enable Alternative function for this pin by clear the corresponding bit in GPIOAFSEL register */
        *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET) |= (0x0000000F << (ConfigPtr[i].Pin_Num * 4));   /* Set the PMCx bits for this pin */
        SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET) , ConfigPtr[i].Pin_Num);     /* Set the corresponding bit in the GPIODEN register to enable digital functionality on this pin */
      }
      
      /* check the Direction for the configured pins
      * For Output pins check the initial value.
      * For Input pins check the internal resistor.
      */            
      if(ConfigPtr[i].Direction == PORT_PIN_OUT )
      {
        SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIR_REG_OFFSET) , ConfigPtr[i].Pin_Num);                /* Set the corresponding bit in the GPIODIR register to configure it as output pin */
        
        if(ConfigPtr[i].Pin_InitialValue == PORT_PIN_LEVEL_HIGH)
        {
          SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DATA_REG_OFFSET) , ConfigPtr[i].Pin_Num);          /* Set the corresponding bit in the GPIODATA register to provide initial value 1 */
        }
        else
        {
          CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DATA_REG_OFFSET) , ConfigPtr[i].Pin_Num);        /* Clear the corresponding bit in the GPIODATA register to provide initial value 0 */
        }
      }
      else if(ConfigPtr[i].Direction == PORT_PIN_IN)
      {
        CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIR_REG_OFFSET) , ConfigPtr[i].Pin_Num);             /* Clear the corresponding bit in the GPIODIR register to configure it as input pin */
        
        if(ConfigPtr[i].Pin_Resistor == PULL_UP)
        {
          SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_PULL_UP_REG_OFFSET) , ConfigPtr[i].Pin_Num);       /* Set the corresponding bit in the GPIOPUR register to enable the internal pull up pin */
        }
        else if(ConfigPtr[i].Pin_Resistor == PULL_DOWN)
        {
          SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_PULL_DOWN_REG_OFFSET) , ConfigPtr[i].Pin_Num);     /* Set the corresponding bit in the GPIOPDR register to enable the internal pull down pin */
        }
        else
        {
          CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_PULL_UP_REG_OFFSET) , ConfigPtr[i].Pin_Num);     /* Clear the corresponding bit in the GPIOPUR register to disable the internal pull up pin */
          CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_PULL_DOWN_REG_OFFSET) , ConfigPtr[i].Pin_Num);   /* Clear the corresponding bit in the GPIOPDR register to disable the internal pull down pin */
        }
      }
      else
      {
        /* Do Nothing */
      }    
      
    }
    /* Set the module state to initialized */
    
    PORT_Status = PORT_INITIALIZED;
    
  }
}

/************************************************************************************
* Service Name: Port_SetPinDirection
* Sync/Async: Synchronous
* Reentrancy: reentrant
* Parameters (in): Pin       - Port Pin ID number
                   Direction - Port Pin Direction
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Sets the port pin direction.
*              - sets the port pin direction during runtime
************************************************************************************/

#if (PORT_SET_PIN_DIRECTION_API == STD_ON)
void Port_SetPinDirection(Port_PinType Pin, Port_PinDirectionType Direction )
{
  boolean error = FALSE;
#if (PORT_DEV_ERROR_DETECT == STD_ON)
  
  /* check if API service called prior to module initialization  */
  if(PORT_Status == PORT_NOT_INITIALIZED)
  {
    Det_ReportError(PORT_MODULE_ID, 
                    PORT_INSTANCE_ID, 
                    PORT_SET_PIN_DIRECTION_SID,
                    PORT_E_UNINIT);
    error = TRUE;
  }
  else
  {
    /* No Action */
  }
  /* check if an incorrect Port Pin ID passed */
  if (Pin > PORT_CONFIGURED_CHANNLES)
  {
    Det_ReportError(PORT_MODULE_ID,
                    PORT_INSTANCE_ID, 
                    PORT_SET_PIN_DIRECTION_SID,
                    PORT_E_PARAM_CONFIG);
    error = TRUE;
  }
  else
  {
    /* No Action */
  }
  
  /* check if Port_SetPinDirection service called when the direction is unchangeable */
  if((channels[Pin].Pin_Direction_Changeable) == STD_OFF)
  {
    Det_ReportError(PORT_MODULE_ID,
                    PORT_INSTANCE_ID, 
                    PORT_SET_PIN_DIRECTION_SID,
                    PORT_E_DIRECTION_UNCHANGEABLE);
    error = TRUE;
  }
  else
  {
    /* No Action */
  }
#endif
  if(FALSE == error)
  {
    uint8 i=0;  
    volatile uint32 * PortGpio_Ptr = NULL_PTR; /* point to the required Port Registers base address */    
    for(i=0;i<PORT_CONFIGURED_CHANNLES;i++)
    {

      /* check the configured port number*/
      switch(channels[i].Port_Num)
      {
      case  0: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTA_BASE_ADDRESS; /* PORTA Base Address */
      break;
      case  1: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTB_BASE_ADDRESS; /* PORTB Base Address */
      break;
      case  2: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTC_BASE_ADDRESS; /* PORTC Base Address */
      break;
      case  3: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTD_BASE_ADDRESS; /* PORTD Base Address */
      break;
      case  4: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTE_BASE_ADDRESS; /* PORTE Base Address */
      break;
      case  5: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTF_BASE_ADDRESS; /* PORTF Base Address */
      break;
      }
      channels[i].Direction = Direction;
      if (channels[i].Direction == PORT_PIN_IN)
      {
        CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIR_REG_OFFSET) , Pin);             /* Clear the corresponding bit in the GPIODIR register to configure it as input pin */
      }
      else if(channels[i].Direction == PORT_PIN_OUT)
      {
        SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIR_REG_OFFSET) , Pin);             /* Clear the corresponding bit in the GPIODIR register to configure it as input pin */
      }
      else
      {
        /* No Action */
      }
    }
  }
}
#endif

/************************************************************************************
* Service Name: Port_RefreshPortDirection
* Sync/Async: Synchronous
* Reentrancy: Non Reentrant
* Parameters (in): None
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Function to Refresh port direction.
*              - refreshs the direction of all configured ports to the configured direction (PortPinDirection).
************************************************************************************/
void Port_RefreshPortDirection(void)
{
  boolean error = FALSE;
#if (PORT_DEV_ERROR_DETECT == STD_ON)
  
  /* check if API service called prior to module initialization  */
  if(PORT_Status == PORT_NOT_INITIALIZED)
  {
    Det_ReportError(PORT_MODULE_ID, 
                    PORT_INSTANCE_ID, 
                    PORT_REFRESH_PORT_DIRECTION_SID,
                    PORT_E_UNINIT);
    error = TRUE;
  }
  else
  {
    /* No Action */
  }
#endif
  if (FALSE == error)
  {
    volatile uint32 * PortGpio_Ptr = NULL_PTR; /* point to the required Port Registers base address */
    volatile uint8 i;
    for (i=0; i < PORT_CONFIGURED_CHANNLES ; i++)
    {
      /* check the configured port number*/
      switch(channels[i].Port_Num)
      {
      case  0: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTA_BASE_ADDRESS; /* PORTA Base Address */
      break;
      case  1: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTB_BASE_ADDRESS; /* PORTB Base Address */
      break;
      case  2: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTC_BASE_ADDRESS; /* PORTC Base Address */
      break;
      case  3: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTD_BASE_ADDRESS; /* PORTD Base Address */
      break;
      case  4: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTE_BASE_ADDRESS; /* PORTE Base Address */
      break;
      case  5: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTF_BASE_ADDRESS; /* PORTF Base Address */
      break;
      }
      
      /* Refresh all port pins direction excluding those port that are configured as ‘pin direction changeable during runtime‘.  */
      if(channels[i].Pin_Direction_Changeable == FALSE)
      {
        if (channels[i].Direction == PORT_PIN_IN)
        {
          CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIR_REG_OFFSET) , channels[i].Pin_Num);             /* Clear the corresponding bit in the GPIODIR register to configure it as input pin */
        }
        else if (channels[i].Direction == PORT_PIN_OUT)
        {
          SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIR_REG_OFFSET) , channels[i].Pin_Num);             /* Clear the corresponding bit in the GPIODIR register to configure it as input pin */
        }
        else
        {
          /* No Action */
        }
      }
      else 
      {
        /* No Action */
      }
    }
  }
}


/************************************************************************************
* Service Name: Port_GetVersionInfo
* Sync/Async: Synchronous
* Reentrancy: None reentrant
* Parameters (in): ConfigPtr - Pointer to post-build configuration data
* Parameters (inout): None
* Parameters (out): versioninfo
* Return value: None
* Description: Function that returns the version information of this module.
*              - returns the version information of this module. The version information includes:
Module Id
Vendor Id
Vendor specific version numbers (BSW00407).
************************************************************************************/
#if (PORT_VERSION_INFO_API == STD_ON)
void Port_GetVersionInfo(Std_VersionInfoType* versioninfo)
{
  boolean error = FALSE;
#if (PORT_DEV_ERROR_DETECT == STD_ON)
  
  /* check if API service called prior to module initialization  */
  if(PORT_Status == PORT_NOT_INITIALIZED)
  {
    Det_ReportError(PORT_MODULE_ID, 
                    PORT_INSTANCE_ID, 
                    PORT_GET_VERSION_INFO_SID,
                    PORT_E_UNINIT);
    error = TRUE;
  }
  else
  {
    /* No Action */
  }
  
  /* check if the input configuration pointer is not a NULL_PTR */
  if (NULL_PTR == versioninfo)
  {
    Det_ReportError(PORT_MODULE_ID,
                    PORT_INSTANCE_ID, 
                    PORT_GET_VERSION_INFO_SID,
                    PORT_E_PARAM_POINTER);
    error = TRUE;
  }
  else
  {
    /* No Action */
  }
  
#endif
  if (FALSE == error)
  {
    /* Copy the module Id */
    versioninfo->moduleID = PORT_MODULE_ID;
    
    /* Copy the vendor Id */
    versioninfo->vendorID = PORT_VENDOR_ID;
    
    /* Copy Software Major Version */
    versioninfo->sw_major_version = PORT_SW_MAJOR_VERSION;
    
    /* Copy Software Minor Version */
    versioninfo->sw_minor_version = PORT_SW_MINOR_VERSION;
    
    /* Copy Software Patch Version */
    versioninfo->sw_patch_version = PORT_SW_PATCH_VERSION;
  }
}
#endif

/************************************************************************************
* Service Name: Port_SetPinMode
* Sync/Async: Synchronous
* Reentrancy: reentrant
* Parameters (in): Pin  - Port Pin ID number
                   Mode - New Port Pin mode to be set on port pin.
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Function to Set the port pin mode.
*              - sets the port pin mode of the referenced pin during runtime.
************************************************************************************/

#if (PORT_SET_PIN_MODE_API == STD_ON)
void Port_SetPinMode(Port_PinType Pin, Port_PinModeType Mode)
{
  boolean error = FALSE;
#if (PORT_DEV_ERROR_DETECT == STD_ON)
  
  /* check if API service called prior to module initialization  */
  if(PORT_Status == PORT_NOT_INITIALIZED)
  {
    Det_ReportError(PORT_MODULE_ID, 
                    PORT_INSTANCE_ID, 
                    PORT_SET_PIN_MODE_SID,
                    PORT_E_UNINIT);
    error = TRUE;
  }
  else
  {
    /* No Action */
  }
  
  /* check if an incorrect Port Pin ID passed */
  if (Pin >PORT_CONFIGURED_CHANNLES )
  {
    Det_ReportError(PORT_MODULE_ID,
                    PORT_INSTANCE_ID, 
                    PORT_SET_PIN_MODE_SID,
                    PORT_E_PARAM_PIN);
    error = TRUE;
  }
  else
  {
    /* No Action */
  }
  
  /* check if Pin Mode is invalid */
  if(Mode >PORT_PIN_MODE_UART || Mode <PORT_PIN_MODE_ADC  )
  {
    Det_ReportError(PORT_MODULE_ID,
                    PORT_INSTANCE_ID, 
                    PORT_SET_PIN_MODE_SID,
                    PORT_E_PARAM_INVALID_MODE);
    error = TRUE;
  }
  else 
  {
    /* No Action */
  }
  
  /* check if Port_SetPinMode service called when the mode is unchangeable */
  if(STD_OFF == (channels[Pin].Pin_Mode_Changeable))
  {
    Det_ReportError(PORT_MODULE_ID,
                    PORT_INSTANCE_ID, 
                    PORT_SET_PIN_MODE_SID,
                    PORT_E_MODE_UNCHANGEABLE);
    error = TRUE;
  }
  else 
  {
    /* No Action */
  }
#endif
  if(FALSE == error)
  {
    volatile uint32 * PortGpio_Ptr = NULL_PTR; /* point to the required Port Registers base address */
    
    /* check the configured port number*/
    switch(channels[Pin].Port_Num)
    {
    case  0: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTA_BASE_ADDRESS; /* PORTA Base Address */
    break;
    case  1: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTB_BASE_ADDRESS; /* PORTB Base Address */
    break;
    case  2: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTC_BASE_ADDRESS; /* PORTC Base Address */
    break;
    case  3: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTD_BASE_ADDRESS; /* PORTD Base Address */
    break;
    case  4: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTE_BASE_ADDRESS; /* PORTE Base Address */
    break;
    case  5: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTF_BASE_ADDRESS; /* PORTF Base Address */
    break;
    }
    
    /* check the Initial Mode for the configured pins
    * For DIO clear AMSEL,CTL,AFSEL and set DEN registers.
    * For ADC clear DEN,CTL and set AMSEL,AFSEL registers.
    * For any other Mode clear AMSEL and set DEN,CTL,AFSEL registers.
    */   
    channels[Pin].Pin_Mode = Mode;
    if((channels[Pin].Pin_Mode) == PORT_PIN_MODE_DIO)
    {
      CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET) , channels[Pin].Pin_Num);      /* Clear the corresponding bit in the GPIOAMSEL register to disable analog functionality on this pin */
      CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ALT_FUNC_REG_OFFSET) , channels[Pin].Pin_Num);            /* Disable Alternative function for this pin by clear the corresponding bit in GPIOAFSEL register */
      *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET) &= ~(0x0000000F << (channels[Pin].Pin_Num * 4));   /* Clear the PMCx bits for this pin */
      SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET) , channels[Pin].Pin_Num);      /* Set the corresponding bit in the GPIODEN register to enable digital functionality on this pin */
    }
    else if((channels[Pin].Pin_Mode) == PORT_PIN_MODE_ADC)
    {
      CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET) , channels[Pin].Pin_Num);        /* Clear the corresponding bit in the GPIODEN register to enable digital functionality on this pin */
      SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET) , channels[Pin].Pin_Num);        /* Set the corresponding bit in the GPIOAMSEL register to disable analog functionality on this pin */
      SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ALT_FUNC_REG_OFFSET) , channels[Pin].Pin_Num);              /* Enable Alternative function for this pin by clear the corresponding bit in GPIOAFSEL register */
      *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET) &= ~(0x0000000F << (channels[Pin].Pin_Num * 4));   /* Clear the PMCx bits for this pin */
    }
    else 
    {
      CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET) , channels[Pin].Pin_Num);     /* Clear the corresponding bit in the GPIOAMSEL register to disable analog functionality on this pin */
      SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ALT_FUNC_REG_OFFSET) , channels[Pin].Pin_Num);             /* Enable Alternative function for this pin by clear the corresponding bit in GPIOAFSEL register */
      *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET) |= (0x0000000F << (channels[Pin].Pin_Num * 4));   /* Set the PMCx bits for this pin */
      SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET) , channels[Pin].Pin_Num);     /* Set the corresponding bit in the GPIODEN register to enable digital functionality on this pin */
    }
  }
  
}
#endif




