 /******************************************************************************
 *
 * Module: Port
 *
 * File Name: Port.h
 *
 * Description: Header file for TM4C123GH6PM Microcontroller - Port Driver.
 *
 * Author: Aya Ashraf
 ******************************************************************************/

#ifndef PORT_H
#define PORT_H


/* Id for the company in the AUTOSAR
 * for example Aya Ashraf's ID = 1000 */
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

/* AUTOSAR checking between Std Types and port Modules */
#if ((STD_TYPES_AR_RELEASE_MAJOR_VERSION != PORT_AR_RELEASE_MAJOR_VERSION)\
 ||  (STD_TYPES_AR_RELEASE_MINOR_VERSION != PORT_AR_RELEASE_MINOR_VERSION)\
 ||  (STD_TYPES_AR_RELEASE_PATCH_VERSION != PORT_AR_RELEASE_PATCH_VERSION))
  #error "The AR version of Std_Types.h does not match the expected version"
#endif

/* Port Pre-Compile Configuration Header file */
#include "Port_Cfg.h"

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


/*******************************************************************************
 *                              Module Definitions                             *
 *******************************************************************************/

/* GPIO Registers base addresses */
#define GPIO_PORTA_BASE_ADDRESS           0x40004000
#define GPIO_PORTB_BASE_ADDRESS           0x40005000
#define GPIO_PORTC_BASE_ADDRESS           0x40006000
#define GPIO_PORTD_BASE_ADDRESS           0x40007000
#define GPIO_PORTE_BASE_ADDRESS           0x40024000
#define GPIO_PORTF_BASE_ADDRESS           0x40025000

/* GPIO Registers offset addresses */
#define PORT_DATA_REG_OFFSET              0x3FC
#define PORT_DIR_REG_OFFSET               0x400
#define PORT_ALT_FUNC_REG_OFFSET          0x420
#define PORT_PULL_UP_REG_OFFSET           0x510
#define PORT_PULL_DOWN_REG_OFFSET         0x514
#define PORT_DIGITAL_ENABLE_REG_OFFSET    0x51C
#define PORT_LOCK_REG_OFFSET              0x520
#define PORT_COMMIT_REG_OFFSET            0x524
#define PORT_ANALOG_MODE_SEL_REG_OFFSET   0x528
#define PORT_CTL_REG_OFFSET               0x52C

/*******************************************************************************
 *                            API Service Id Macros                         *
 *******************************************************************************/

#define Port_Init_service_ID                     (uint8)0x00
#define Port_SetPinDirection_service_ID          (uint8)0x01
#define Port_RefreshPortDirection_service_ID     (uint8)0x02
#define Port_GetVersionInfo_service_ID           (uint8)0x03
#define Port_SetPinMode_service_ID               (uint8)0x04

/*******************************************************************************
 *                              DET Error Codes                           *
 *******************************************************************************/

/* DET code to report Invalid Port Pin ID requested  */
#define PORT_E_PARAM_PIN                          (uint8)0x0A

/* DET code to report Port Pin not configured as changeable */
#define PORT_E_DIRECTION_UNCHANGEABLE             (uint8)0x0B

/* DET code to report API Port_Init service called with wrong parameter.*/
#define PORT_E_PARAM_CONFIG                       (uint8)0x0C

/* DET code to report invalid port mode requested.*/
#define PORT_E_PARAM_INVALID_MODE                 (uint8)0x0D

/* DET code to report when API Port_SetPinMode service called while mode is unchangeable.*/
#define PORT_E_MODE_UNCHANGEABLE                  (uint8)0x0E

/* DET code to report when API service called without module initialization.*/
#define PORT_E_UNINIT                             (uint8)0x0F

/* DET code to report when APIs called with a Null Pointer*/
#define PORT_E_PARAM_POINTER                      (uint8)0x10

/*******************************************************************************
 *                              Module Data Types                              *
 *******************************************************************************/

/* Description: Enum to hold PIN direction */
typedef enum
{
    PORT_PIN_IN ,PORT_PIN_OUT
}Port_PinDirection;

/* Description: Enum to hold internal resistor type for PIN */
typedef enum
{
    OFF,PULL_UP,PULL_DOWN
}Port_InternalResistor;

/* Description: uint to hold the symbolic name of the port pin(index to its element in structure) */
typedef uint8 Port_PinType;

/* Type definition for PORT_PortType used by the PORT APIs */
typedef uint8 Port_PortType;

/* Description: uint to hold the mode of the port pin*/
typedef uint8 Port_PinModeType;

/* Description: Structure to configure each individual PIN:
 *    	1. the PORT Which the pin belongs to. 0, 1, 2, 3, 4 or 5
 *     	2. the number of the pin in the PORT.
 *      3. the direction of pin --> INPUT or OUTPUT
 *      4. the internal resistor --> Disable, Pull up or Pull down
 *      5. Pin Mode (DIO, Analog, CAN, PWM,...)
 *      6. Pin Mode Changeability (changeable, not changeable)
 *      7. Pin direction changeability
 *      8. Pin initial value
 */
typedef struct 
{
    Port_PortType port_num;
    Port_PinType pin_num;
    Port_PinDirection direction;
    Port_InternalResistor resistor;
    uint8 initial_value;
    Port_PinModeType pin_mode;
    boolean pin_direction_changeable;
    boolean pin_mode_changeable;
}Port_ConfigType;

/* Description:structure to configure an array of Port_ConfigType to configure all
 * the pins in the each port.
 */
typedef struct
{
    Port_ConfigType Port_pins[PORT_CONFIGURED_PINS];
}Port_config_pins;

/*******************************************************************************
 *                      Function Prototypes                                    *
 *******************************************************************************/


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

void Port_Init(const Port_config_pins* ConfigPtr);


/************************************************************************************
* Service Name: Port_SetPinDirection
* Sync/Async: Synchronous
* Reentrancy: Reentrant
* Parameters (in): - Pin  - Port Pin ID number.
*                  - Direction  -Port Pin Direction
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Sets the port pin direction.
************************************************************************************/

#if (PORT_SET_PIN_DIRECTION_API == STD_ON)
void Port_SetPinDirection( Port_PinType Pin, Port_PinDirection Direction);
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

void Port_RefreshPortDirection(void);

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
void Port_GetVersionInfo( Std_VersionInfoType* versioninfo);
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

void Port_SetPinMode( Port_PinType Pin,Port_PinModeType Mode);

/*******************************************************************************
 *                       External Variables                                    *
 *******************************************************************************/

/* Extern PB structures to be used by Port and other modules */
extern const Port_config_pins Port_Configuration;

extern

#endif /* PORT_H */
