 /******************************************************************************
 *
 * Module: Port
 *
 * File Name: Port.c
 *
 * Description: Source file for TM4C123GH6PM Microcontroller - Port Driver.
 *
 * Author: Aya Ashraf
 ******************************************************************************/

#include "Port.h"
#include "tm4c123gh6pm_registers.h"


#if (PORT_DEV_ERROR_DETECT == STD_ON)

#include "Det.h"
/* AUTOSAR Version checking between Det and Port Modules */
#if ((DET_AR_MAJOR_VERSION != PORT_AR_RELEASE_MAJOR_VERSION)\
 || (DET_AR_MINOR_VERSION != PORT_AR_RELEASE_MINOR_VERSION)\
 || (DET_AR_PATCH_VERSION != PORT_AR_RELEASE_PATCH_VERSION))
  #error "The AR version of Det.h does not match the expected version"
#endif

#endif


STATIC const Port_ConfigType * Port_array= NULL_PTR;
STATIC uint8 Port_Status = PORT_NOT_INITIALIZED;


/************************************************************************************
* Service Name: Port_ConfigType
* Sync/Async: Synchronous
* Reentrancy: Non Reentrant
* Parameters (in): ConfigPtr - Pointer to configuration set.
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Initializes the Port Driver module.
*              - Setup the pin as Digital GPIO pin
*              - Setup the direction of the GPIO pin
*              - Setup the internal resistor for i/p pin
*              - Setup the pin mode
*              - Setup the pin level initial value
*              - Setup the pin direction changeable
*              - Setup the pin mode changeable
************************************************************************************/

void Port_Init(const Port_config_pins* ConfigPtr){


#if (PORT_DEV_ERROR_DETECT == STD_ON)
    /* check if the input configuration pointer is not a NULL_PTR */
    if (NULL_PTR == ConfigPtr)
    {
        Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, Port_Init_service_ID,
                        PORT_E_PARAM_CONFIG);
    }
    else
#endif
         Port_array = ConfigPtr->Port_pins;                   /* address of the first Port_pins structure --> Port_pins[0] */
         Port_PinType Pins;                                   /* variable to loop on the number of the configured pins */

        for(Pins=0 ; Pins < PORT_CONFIGURED_PINS ; Pins++ )
        {

            volatile uint32  * Port_ptr = NULL_PTR;

        switch(Port_array[Pins].port_num)
           {

               case  0: Port_ptr = (volatile uint32 *)GPIO_PORTA_BASE_ADDRESS; /* PORTA Base Address */
                        break;
               case  1: Port_ptr = (volatile uint32 *)GPIO_PORTB_BASE_ADDRESS; /* PORTB Base Address */
                        break;
               case  2: Port_ptr = (volatile uint32 *)GPIO_PORTC_BASE_ADDRESS; /* PORTC Base Address */
                        break;
               case  3: Port_ptr = (volatile uint32 *)GPIO_PORTD_BASE_ADDRESS; /* PORTD Base Address */
                        break;
               case  4: Port_ptr = (volatile uint32 *)GPIO_PORTE_BASE_ADDRESS; /* PORTE Base Address */
                        break;
               case  5: Port_ptr = (volatile uint32 *)GPIO_PORTF_BASE_ADDRESS; /* PORTF Base Address */
                        break;
           }


           if( ((Port_array[Pins].port_num == PORT_D) && (Port_array[Pins].pin_num == PIN_7)) || ((Port_array[Pins].port_num == PORT_F) && (Port_array[Pins].pin_num == PIN_0)) ) /* PD7 or PF0 */
           {
               *(volatile uint32 *)((volatile uint8 *)Port_ptr + PORT_LOCK_REG_OFFSET) = 0x4C4F434B;                          /* Unlock the GPIOCR register */
               SET_BIT(*(volatile uint32 *)((volatile uint8 *)Port_ptr + PORT_COMMIT_REG_OFFSET) , Port_array[Pins].pin_num);  /* Set the corresponding bit in GPIOCR register to allow changes on this pin */
           }
           else if( (Port_array[Pins].port_num == 2) && (Port_array[Pins].pin_num <= 3)) /* PC0 to PC3 */
           {
               /* Do Nothing ...  this is the JTAG pins */
           }
           else
           {
               /* Do Nothing ... No need to unlock the commit register for this pin */
           }

           volatile uint32 * Port_ctrl_reg_ptr =  (volatile uint32 *)((volatile uint8 *)Port_ptr + PORT_CTL_REG_OFFSET);                           /* A pointer to point to the control register */

           if(Port_array[Pins].pin_mode == PORT_ANALOG_MODE)
           {
               /* Setup the pin mode as analog */
               SET_BIT(*(volatile uint32 *)((volatile uint8 *)Port_ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET) , Port_array[Pins].pin_num);                 /* set the corresponding bit in the GPIOAMSEL register to enable analog functionality on this pin */
               CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)Port_ptr + PORT_ALT_FUNC_REG_OFFSET) , Port_array[Pins].pin_num);                      /* Disable Alternative function for this pin by clear the corresponding bit in GPIOAFSEL register */
               *Port_ctrl_reg_ptr = (  (*Port_ctrl_reg_ptr & ((0xF0 << Port_array[Pins].pin_num * 4))) | (PORT_ANALOG_MODE << (Port_array[Pins].pin_num *4)) );  /* insert the PMCx bits for this pin mode */
               CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)Port_ptr + PORT_DIGITAL_ENABLE_REG_OFFSET) , Port_array[Pins].pin_num);                /* clear the corresponding bit in the GPIODEN register to disable digital functionality on this pin */

           }else if (Port_array[Pins].pin_mode == PORT_DIO_MODE)
           {
               /* Setup the pin mode as GPIO (default) */
               CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)Port_ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET) , Port_array[Pins].pin_num);      /* Clear the corresponding bit in the GPIOAMSEL register to disable analog functionality on this pin */
               CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)Port_ptr + PORT_ALT_FUNC_REG_OFFSET) , Port_array[Pins].pin_num);             /* Disable Alternative function for this pin by clear the corresponding bit in GPIOAFSEL register */
               *(volatile uint32 *)((volatile uint8 *)Port_ptr + PORT_CTL_REG_OFFSET) &= ~(0x0000000F << (Port_array[Pins].pin_num * 4));     /* Clear the PMCx bits for this pin */
               SET_BIT(*(volatile uint32 *)((volatile uint8 *)Port_ptr + PORT_DIGITAL_ENABLE_REG_OFFSET) , Port_array[Pins].pin_num);         /* Set the corresponding bit in the GPIODEN register to enable digital functionality on this pin */

           } else
           {
               /* Setup the pin mode as alternative(PWM/I2C/SSI) */
               CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)Port_ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET) , Port_array[Pins].pin_num);               /* Clear the corresponding bit in the GPIOAMSEL register to disable analog functionality on this pin */
               SET_BIT(*(volatile uint32 *)((volatile uint8 *)Port_ptr + PORT_ALT_FUNC_REG_OFFSET) , Port_array[Pins].pin_num);                        /* enable Alternative function for this pin by setting the corresponding bit in GPIOAFSEL register */
               *Port_ctrl_reg_ptr = (  (*Port_ctrl_reg_ptr & ((0xF0 << Port_array[Pins].pin_num * 4))) | (PORT_ANALOG_MODE << (Port_array[Pins].pin_num *4)) );   /* insert the PMCx bits for this pin mode */
               SET_BIT(*(volatile uint32 *)((volatile uint8 *)Port_ptr + PORT_DIGITAL_ENABLE_REG_OFFSET) , Port_array[Pins].pin_num);                  /* Set the corresponding bit in the GPIODEN register to enable digital functionality on this pin */

           }

           if(Port_array[Pins].direction  == PORT_PIN_OUT)
           {
               SET_BIT(*(volatile uint32 *)((volatile uint8 *)Port_ptr + PORT_DIR_REG_OFFSET) , Port_array[Pins].pin_num);               /* Set the corresponding bit in the GPIODIR register to configure it as output pin */

               if(Port_array[Pins].initial_value == STD_HIGH)
               {
                   SET_BIT(*(volatile uint32 *)((volatile uint8 *)Port_ptr + PORT_DATA_REG_OFFSET) , Port_array[Pins].pin_num);          /* Set the corresponding bit in the GPIODATA register to provide initial value 1 */
               }
               else
               {
                   CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)Port_ptr + PORT_DATA_REG_OFFSET) , Port_array[Pins].pin_num);        /* Clear the corresponding bit in the GPIODATA register to provide initial value 0 */
               }
           }
           else if(Port_array[Pins].direction == PORT_PIN_IN)
           {
               CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)Port_ptr + PORT_DIR_REG_OFFSET) , Port_array[Pins].pin_num);             /* Clear the corresponding bit in the GPIODIR register to configure it as input pin */

               if(Port_array[Pins].resistor == PULL_UP)
               {
                   SET_BIT(*(volatile uint32 *)((volatile uint8 *)Port_ptr + PORT_PULL_UP_REG_OFFSET) ,Port_array[Pins].pin_num);       /* Set the corresponding bit in the GPIOPUR register to enable the internal pull up pin */
               }
               else if(Port_array[Pins].resistor == PULL_DOWN)
               {
                   SET_BIT(*(volatile uint32 *)((volatile uint8 *)Port_ptr + PORT_PULL_DOWN_REG_OFFSET) , Port_array[Pins].pin_num);     /* Set the corresponding bit in the GPIOPDR register to enable the internal pull down pin */
               }
               else
               {
                   CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)Port_ptr + PORT_PULL_UP_REG_OFFSET) , Port_array[Pins].pin_num);     /* Clear the corresponding bit in the GPIOPUR register to disable the internal pull up pin */
                   CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)Port_ptr + PORT_PULL_DOWN_REG_OFFSET) , Port_array[Pins].pin_num);   /* Clear the corresponding bit in the GPIOPDR register to disable the internal pull down pin */
               }
           }
           else
           {
               /* Do Nothing */
           }

        }
        Port_Status = PORT_INITIALIZED ;    /* update the port status after the port is completely initialized*/
}


/************************************************************************************
* Service Name: Port_SetPinDirection
* Sync/Async: Synchronous
* Reentrancy: Reentrant
* Parameters (in): - Pin  - Port Pin ID number.
*                  - Direction  - Port Pin Direction
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Sets the port pin direction.
************************************************************************************/

#if (PORT_SET_PIN_DIRECTION_API == STD_ON)
void Port_SetPinDirection( Port_PinType Pin, Port_PinDirection Direction)
{
#if (PORT_DEV_ERROR_DETECT == STD_ON)
    /* check if the input configuration pointer is not a NULL_PTR */
    if (Port_Status == PORT_NOT_INITIALIZED)
    {
        Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, Port_SetPinDirection_service_ID,PORT_E_UNINIT);
    }
    else
    {
        /* nothing to do */
    }

    if(Pin >= PORT_CONFIGURED_PINS)
    {
        Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, Port_SetPinDirection_service_ID ,PORT_E_PARAM_PIN);
    }
    else
    {
        /* nothing to do */
    }

    if(Port_array[Pin].pin_direction_changeable == STD_OFF )
    {
        Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, Port_SetPinDirection_service_ID ,PORT_E_DIRECTION_UNCHANGEABLE);
    }
    else
    {
        /* nothing to do */
    }
#endif
    volatile uint32  * Port_ptr_direction = NULL_PTR;

           switch(Port_array[Pin].port_num)
              {

                  case  0: Port_ptr_direction = (volatile uint32 *)GPIO_PORTA_BASE_ADDRESS; /* PORTA Base Address */
                           break;
                  case  1: Port_ptr_direction = (volatile uint32 *)GPIO_PORTB_BASE_ADDRESS; /* PORTB Base Address */
                           break;
                  case  2: Port_ptr_direction = (volatile uint32 *)GPIO_PORTC_BASE_ADDRESS; /* PORTC Base Address */
                           break;
                  case  3: Port_ptr_direction = (volatile uint32 *)GPIO_PORTD_BASE_ADDRESS; /* PORTD Base Address */
                           break;
                  case  4: Port_ptr_direction = (volatile uint32 *)GPIO_PORTE_BASE_ADDRESS; /* PORTE Base Address */
                           break;
                  case  5: Port_ptr_direction = (volatile uint32 *)GPIO_PORTF_BASE_ADDRESS; /* PORTF Base Address */
                           break;
              }


           if(Direction  == PORT_PIN_OUT)
           {
               SET_BIT(*(volatile uint32 *)((volatile uint8 *)Port_ptr_direction + PORT_DIR_REG_OFFSET) , Port_array[Pin].pin_num);               /* Set the corresponding bit in the GPIODIR register to configure it as output pin */

           }
           else if(Direction == PORT_PIN_IN)
           {
               CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)Port_ptr_direction + PORT_DIR_REG_OFFSET) , Port_array[Pin].pin_num);             /* Clear the corresponding bit in the GPIODIR register to configure it as input pin */


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
* Description: Refreshes port direction except those port pins from refreshing
*              that are configured as ‘pin direction changeable during runtime‘.
************************************************************************************/

void Port_RefreshPortDirection(void)
{
#if (PORT_DEV_ERROR_DETECT == STD_ON)
    /* check if the input configuration pointer is not a NULL_PTR */
    if (Port_Status == PORT_NOT_INITIALIZED)
    {
        Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, Port_RefreshPortDirection_service_ID,PORT_E_UNINIT);
    }
    else
    {
        /* nothing to do */
    }

#endif
    volatile uint32  * Port_ptr_direction = NULL_PTR;


           Port_PinType Pins;                                   /* variable to loop on the number of the configured pins */

           for(Pins=0 ; Pins < PORT_CONFIGURED_PINS ; Pins++ )
           {
               if(Port_array[Pins].pin_direction_changeable == STD_OFF)
               {
                   switch(Port_array[Pins].port_num)
                                {

                                    case  0: Port_ptr_direction = (volatile uint32 *)GPIO_PORTA_BASE_ADDRESS; /* PORTA Base Address */
                                             break;
                                    case  1: Port_ptr_direction = (volatile uint32 *)GPIO_PORTB_BASE_ADDRESS; /* PORTB Base Address */
                                             break;
                                    case  2: Port_ptr_direction = (volatile uint32 *)GPIO_PORTC_BASE_ADDRESS; /* PORTC Base Address */
                                             break;
                                    case  3: Port_ptr_direction = (volatile uint32 *)GPIO_PORTD_BASE_ADDRESS; /* PORTD Base Address */
                                             break;
                                    case  4: Port_ptr_direction = (volatile uint32 *)GPIO_PORTE_BASE_ADDRESS; /* PORTE Base Address */
                                             break;
                                    case  5: Port_ptr_direction = (volatile uint32 *)GPIO_PORTF_BASE_ADDRESS; /* PORTF Base Address */
                                             break;
                                }
                   if(Port_array[Pins].direction  == PORT_PIN_OUT)
                   {
                       SET_BIT(*(volatile uint32 *)((volatile uint8 *)Port_ptr_direction + PORT_DIR_REG_OFFSET) , Port_array[Pins].pin_num);               /* Set the corresponding bit in the GPIODIR register to configure it as output pin */

                   }
                   else if(Port_array[Pins].direction  == PORT_PIN_IN)
                   {
                       CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)Port_ptr_direction + PORT_DIR_REG_OFFSET) , Port_array[Pins].pin_num);             /* Clear the corresponding bit in the GPIODIR register to configure it as input pin */

                   }
               }
               else
               {
                   /* Do nothing */
               }
           }
}

/************************************************************************************
* Service Name: Port_GetVersionInfo
* Sync/Async: Synchronous
* Reentrancy: Non Reentrant
* Parameters (in): None
* Parameters (inout): None
* Parameters (out): versioninfo - Pointer to where to store the version information of this module.
* Return value: None
* Description: Returns the version information of this module:
*              - Module Id
*              - Vendor Id
*              - Vendor specific version numbers (BSW00407).
************************************************************************************/
#if(PORT_VERSION_INFO_API == STD_ON)
void Port_GetVersionInfo( Std_VersionInfoType* versioninfo)
{
#if (PORT_DEV_ERROR_DETECT == STD_ON)
    /* Check if input pointer is not Null pointer */
    if(NULL_PTR == versioninfo)
    {
        /* Report to DET  */
        Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, Port_GetVersionInfo_service_ID,PORT_E_PARAM_POINTER);

    }
    else
    {
        /* do nothing */
    }
#endif
    {
        /* Copy the vendor Id */
        versioninfo->vendorID = (uint16)PORT_VENDOR_ID;
        /* Copy the module Id */
        versioninfo->moduleID = (uint16)PORT_MODULE_ID;
        /* Copy Software Major Version */
        versioninfo->sw_major_version = (uint8)PORT_SW_MAJOR_VERSION;
        /* Copy Software Minor Version */
        versioninfo->sw_minor_version = (uint8)PORT_SW_MINOR_VERSION;
        /* Copy Software Patch Version */
        versioninfo->sw_patch_version = (uint8)PORT_SW_PATCH_VERSION;
    }

}
#endif

/************************************************************************************
* Service Name: Port_SetPinMode
* Sync/Async: Synchronous
* Reentrancy: Reentrant
* Parameters (in): Pin - Port Pin ID number
*                  Mode - New Port Pin mode to be set on port pin.
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Sets the port pin mode of the referenced pin during runtime.
************************************************************************************/

void Port_SetPinMode( Port_PinType Pin,Port_PinModeType Mode)
{
#if (PORT_DEV_ERROR_DETECT == STD_ON)
    /* check if the input configuration pointer is not a NULL_PTR */
    if (Port_Status == PORT_NOT_INITIALIZED)
    {
        Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, Port_SetPinMode_service_ID,PORT_E_UNINIT);
    }
    else
    {
        /* nothing to do */
    }

    if(Pin >= PORT_CONFIGURED_PINS)
    {
        Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, Port_SetPinMode_service_ID ,PORT_E_PARAM_PIN);
    }
    else
    {
        /* nothing to do */
    }

    if(Port_array[Pin].pin_mode_changeable == STD_OFF )
    {
        Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, Port_SetPinMode_service_ID ,PORT_E_MODE_UNCHANGEABLE);
    }
    else
    {
        /* nothing to do */
    }
    if(Mode != (PORT_DIO_MODE | PORT_ANALOG_MODE | PORT_SSI_MODE | PORT_I2C_MODE | PORT_PWM_MODE | PORT_CAN_MODE ))
    {
        Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, Port_SetPinMode_service_ID ,PORT_E_PARAM_INVALID_MODE);
    }
#endif
    volatile uint32  * Port_ptr_mode = NULL_PTR;

           switch(Port_array[Pin].port_num)
              {

                  case  0: Port_ptr_mode = (volatile uint32 *)GPIO_PORTA_BASE_ADDRESS; /* PORTA Base Address */
                           break;
                  case  1: Port_ptr_mode = (volatile uint32 *)GPIO_PORTB_BASE_ADDRESS; /* PORTB Base Address */
                           break;
                  case  2: Port_ptr_mode = (volatile uint32 *)GPIO_PORTC_BASE_ADDRESS; /* PORTC Base Address */
                           break;
                  case  3: Port_ptr_mode = (volatile uint32 *)GPIO_PORTD_BASE_ADDRESS; /* PORTD Base Address */
                           break;
                  case  4: Port_ptr_mode = (volatile uint32 *)GPIO_PORTE_BASE_ADDRESS; /* PORTE Base Address */
                           break;
                  case  5: Port_ptr_mode = (volatile uint32 *)GPIO_PORTF_BASE_ADDRESS; /* PORTF Base Address */
                           break;
              }

           volatile uint32 * Port_ctrl_reg_ptr =  (volatile uint32 *)((volatile uint8 *)Port_ptr_mode + PORT_CTL_REG_OFFSET);                           /* A pointer to point to the control register */

           if(Port_array[Pin].pin_mode == PORT_ANALOG_MODE)
           {
               /* Setup the pin mode as analog */
               SET_BIT(*(volatile uint32 *)((volatile uint8 *)Port_ptr_mode + PORT_ANALOG_MODE_SEL_REG_OFFSET) , Port_array[Pin].pin_num);                 /* set the corresponding bit in the GPIOAMSEL register to enable analog functionality on this pin */
               CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)Port_ptr_mode + PORT_ALT_FUNC_REG_OFFSET) , Port_array[Pin].pin_num);                      /* Disable Alternative function for this pin by clear the corresponding bit in GPIOAFSEL register */
               *Port_ctrl_reg_ptr = (  (*Port_ctrl_reg_ptr & ((0xF0 << Port_array[Pin].pin_num * 4))) | (PORT_ANALOG_MODE << (Port_array[Pin].pin_num *4)) );    /* insert the PMCx bits for this pin mode */
               CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)Port_ptr_mode + PORT_DIGITAL_ENABLE_REG_OFFSET) , Port_array[Pin].pin_num);                /* clear the corresponding bit in the GPIODEN register to disable digital functionality on this pin */

           }else if (Port_array[Pin].pin_mode == PORT_DIO_MODE)
           {
               /* Setup the pin mode as GPIO (default) */
               CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)Port_ptr_mode + PORT_ANALOG_MODE_SEL_REG_OFFSET) , Port_array[Pin].pin_num);      /* Clear the corresponding bit in the GPIOAMSEL register to disable analog functionality on this pin */
               CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)Port_ptr_mode + PORT_ALT_FUNC_REG_OFFSET) , Port_array[Pin].pin_num);             /* Disable Alternative function for this pin by clear the corresponding bit in GPIOAFSEL register */
               *(volatile uint32 *)((volatile uint8 *)Port_ptr_mode + PORT_CTL_REG_OFFSET) &= ~(0x0000000F << (Port_array[Pin].pin_num * 4));     /* Clear the PMCx bits for this pin */
               SET_BIT(*(volatile uint32 *)((volatile uint8 *)Port_ptr_mode + PORT_DIGITAL_ENABLE_REG_OFFSET) , Port_array[Pin].pin_num);         /* Set the corresponding bit in the GPIODEN register to enable digital functionality on this pin */

           } else
           {
               /* Setup the pin mode as alternative(PWM/I2C/SSI) */
               CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)Port_ptr_mode + PORT_ANALOG_MODE_SEL_REG_OFFSET) , Port_array[Pin].pin_num);               /* Clear the corresponding bit in the GPIOAMSEL register to disable analog functionality on this pin */
               SET_BIT(*(volatile uint32 *)((volatile uint8 *)Port_ptr_mode + PORT_ALT_FUNC_REG_OFFSET) , Port_array[Pin].pin_num);                        /* enable Alternative function for this pin by setting the corresponding bit in GPIOAFSEL register */
               *Port_ctrl_reg_ptr = (  (*Port_ctrl_reg_ptr & ((0xF0 << Port_array[Pin].pin_num * 4))) | (PORT_ANALOG_MODE << (Port_array[Pin].pin_num *4)) );    /* insert the PMCx bits for this pin mode */
               SET_BIT(*(volatile uint32 *)((volatile uint8 *)Port_ptr_mode + PORT_DIGITAL_ENABLE_REG_OFFSET) , Port_array[Pin].pin_num);                  /* Set the corresponding bit in the GPIODEN register to enable digital functionality on this pin */

           }
}


