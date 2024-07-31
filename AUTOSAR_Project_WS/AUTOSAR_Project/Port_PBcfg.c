/******************************************************************************
 *
 * Module: Port
 *
 * File Name: Port_PBcfg.c
 *
 * Description: Post Build Configuration Source file for TM4C123GH6PM Microcontroller - Port Driver
 *
 * Author: Aya Ashraf
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

/* AUTOSAR Version checking between Port_PBcfg.c and Port.h files */
#if ((PORT_PBCFG_AR_RELEASE_MAJOR_VERSION != PORT_AR_RELEASE_MAJOR_VERSION)\
        ||  (PORT_PBCFG_AR_RELEASE_MINOR_VERSION != PORT_AR_RELEASE_MINOR_VERSION)\
        ||  (PORT_PBCFG_AR_RELEASE_PATCH_VERSION != PORT_AR_RELEASE_PATCH_VERSION))
#error "The AR version of PBcfg.c does not match the expected version"
#endif

/* Software Version checking between Port_PBcfg.c and Port.h files */
#if ((PORT_PBCFG_SW_MAJOR_VERSION != PORT_SW_MAJOR_VERSION)\
        ||  (PORT_PBCFG_SW_MINOR_VERSION != PORT_SW_MINOR_VERSION)\
        ||  (PORT_PBCFG_SW_PATCH_VERSION != PORT_SW_PATCH_VERSION))
#error "The SW version of PBcfg.c does not match the expected version"
#endif

/* PB structure used with Port_Init API */

const Port_config_pins Port_Configuration =
{
 /*********** Port_A_PIN_0 ************/

  PORT_A,
  PIN_0,
  PORT_PIN_IN,
  PULL_UP,
  STD_LOW,
  PORT_DIO_MODE,
  STD_ON,
  STD_ON,


 /*********** Port_A_PIN_1 ************/

  PORT_A,
  PIN_1,
  PORT_PIN_IN,
  PULL_UP,
  STD_LOW,
  PORT_DIO_MODE,
  STD_ON,
  STD_ON,

 /*********** Port_A_PIN_2 ************/

  PORT_A,
  PIN_2,
  PORT_PIN_IN,
  PULL_UP,
  STD_LOW,
  PORT_DIO_MODE,
  STD_ON,
  STD_ON,


 /*********** Port_A_PIN_3 ************/

  PORT_A,
  PIN_3,
  PORT_PIN_IN,
  PULL_UP,
  STD_LOW,
  PORT_DIO_MODE,
  STD_ON,
  STD_ON,


 /*********** Port_A_PIN_4 ************/

  PORT_A,
  PIN_4,
  PORT_PIN_IN,
  PULL_UP,
  STD_LOW,
  PORT_DIO_MODE,
  STD_ON,
  STD_ON,


 /*********** Port_A_PIN_5 ************/

  PORT_A,
  PIN_5,
  PORT_PIN_IN,
  PULL_UP,
  STD_LOW,
  PORT_DIO_MODE,
  STD_ON,
  STD_ON,


 /*********** Port_A_PIN_6 ************/

  PORT_A,
  PIN_6,
  PORT_PIN_IN,
  PULL_UP,
  STD_LOW,
  PORT_DIO_MODE,
  STD_ON,
  STD_ON,


 /*********** Port_A_PIN_7 ************/

  PORT_A,
  PIN_7,
  PORT_PIN_IN,
  PULL_UP,
  STD_LOW,
  PORT_DIO_MODE,
  STD_ON,
  STD_ON,


 /*********** Port_B_PIN_0 ************/

  PORT_B,
  PIN_0,
  PORT_PIN_IN,
  PULL_UP,
  STD_LOW,
  PORT_DIO_MODE,
  STD_ON,
  STD_ON,


 /*********** Port_B_PIN_1 ************/

  PORT_B,
  PIN_1,
  PORT_PIN_IN,
  PULL_UP,
  STD_LOW,
  PORT_DIO_MODE,
  STD_ON,
  STD_ON,


 /*********** Port_B_PIN_2 ************/

  PORT_B,
  PIN_2,
  PORT_PIN_IN,
  PULL_UP,
  STD_LOW,
  PORT_DIO_MODE,
  STD_ON,
  STD_ON,


 /*********** Port_B_PIN_3 ************/

  PORT_B,
  PIN_3,
  PORT_PIN_IN,
  PULL_UP,
  STD_LOW,
  PORT_DIO_MODE,
  STD_ON,
  STD_ON,


 /*********** Port_B_PIN_4 ************/

  PORT_B,
  PIN_4,
  PORT_PIN_IN,
  PULL_UP,
  STD_LOW,
  PORT_DIO_MODE,
  STD_ON,
  STD_ON,


 /*********** Port_B_PIN_5 ************/

  PORT_B,
  PIN_5,
  PORT_PIN_IN,
  PULL_UP,
  STD_LOW,
  PORT_DIO_MODE,
  STD_ON,
  STD_ON,


 /*********** Port_B_PIN_6 ************/

  PORT_B,
  PIN_6,
  PORT_PIN_IN,
  PULL_UP,
  STD_LOW,
  PORT_DIO_MODE,
  STD_ON,
  STD_ON,


 /*********** Port_B_PIN_7 ************/

  PORT_B,
  PIN_7,
  PORT_PIN_IN,
  PULL_UP,
  STD_LOW,
  PORT_DIO_MODE,
  STD_ON,
  STD_ON,


 /*********** Port_C_PIN_4 ************/

  PORT_C,
  PIN_4,
  PORT_PIN_IN,
  PULL_UP,
  STD_LOW,
  PORT_DIO_MODE,
  STD_ON,
  STD_ON,


 /*********** Port_C_PIN_5 ************/

  PORT_C,
  PIN_5,
  PORT_PIN_IN,
  PULL_UP,
  STD_LOW,
  PORT_DIO_MODE,
  STD_ON,
  STD_ON,


 /*********** Port_C_PIN_6 ************/

  PORT_C,
  PIN_6,
  PORT_PIN_IN,
  PULL_UP,
  STD_LOW,
  PORT_DIO_MODE,
  STD_ON,
  STD_ON,


 /*********** Port_C_PIN_7 ************/

  PORT_C,
  PIN_7,
  PORT_PIN_IN,
  PULL_UP,
  STD_LOW,
  PORT_DIO_MODE,
  STD_ON,
  STD_ON,


 /*********** Port_D_PIN_0 ************/

  PORT_D,
  PIN_0,
  PORT_PIN_IN,
  PULL_UP,
  STD_LOW,
  PORT_DIO_MODE,
  STD_ON,
  STD_ON,

 /*********** Port_D_PIN_1 ************/

  PORT_D,
  PIN_1,
  PORT_PIN_IN,
  PULL_UP,
  STD_LOW,
  PORT_DIO_MODE,
  STD_ON,
  STD_ON,


 /*********** Port_D_PIN_2 ************/

  PORT_D,
  PIN_2,
  PORT_PIN_IN,
  PULL_UP,
  STD_LOW,
  PORT_DIO_MODE,
  STD_ON,
  STD_ON,


 /*********** Port_D_PIN_3 ************/

  PORT_D,
  PIN_3,
  PORT_PIN_IN,
  PULL_UP,
  STD_LOW,
  PORT_DIO_MODE,
  STD_ON,
  STD_ON,


 /*********** Port_D_PIN_4 ************/

  PORT_D,
  PIN_4,
  PORT_PIN_IN,
  PULL_UP,
  STD_LOW,
  PORT_DIO_MODE,
  STD_ON,
  STD_ON,


 /*********** Port_D_PIN_5 ************/

  PORT_D,
  PIN_5,
  PORT_PIN_IN,
  PULL_UP,
  STD_LOW,
  PORT_DIO_MODE,
  STD_ON,
  STD_ON,


 /*********** Port_D_PIN_6 ************/

  PORT_D,
  PIN_6,
  PORT_PIN_IN,
  PULL_UP,
  STD_LOW,
  PORT_DIO_MODE,
  STD_ON,
  STD_ON,


 /*********** Port_D_PIN_7 ************/

  PORT_D,
  PIN_7,
  PORT_PIN_IN,
  PULL_UP,
  STD_LOW,
  PORT_DIO_MODE,
  STD_ON,
  STD_ON,


 /*********** Port_E_PIN_0 ************/

  PORT_E,
  PIN_0,
  PORT_PIN_IN,
  PULL_UP,
  STD_LOW,
  PORT_DIO_MODE,
  STD_ON,
  STD_ON,


 /*********** Port_E_PIN_1 ************/

  PORT_E,
  PIN_1,
  PORT_PIN_IN,
  PULL_UP,
  STD_LOW,
  PORT_DIO_MODE,
  STD_ON,
  STD_ON,

 /*********** Port_E_PIN_2 ************/

  PORT_E,
  PIN_2,
  PORT_PIN_IN,
  PULL_UP,
  STD_LOW,
  PORT_DIO_MODE,
  STD_ON,
  STD_ON,


 /*********** Port_E_PIN_3 ************/

  PORT_E,
  PIN_3,
  PORT_PIN_IN,
  PULL_UP,
  STD_LOW,
  PORT_DIO_MODE,
  STD_ON,
  STD_ON,


 /*********** Port_E_PIN_4 ************/

  PORT_E,
  PIN_4,
  PORT_PIN_IN,
  PULL_UP,
  STD_LOW,
  PORT_DIO_MODE,
  STD_ON,
  STD_ON,


 /*********** Port_E_PIN_5 ************/

  PORT_E,
  PIN_5,
  PORT_PIN_IN,
  PULL_UP,
  STD_LOW,
  PORT_DIO_MODE,
  STD_ON,
  STD_ON,


 /*********** Port_F_PIN_0 ************/

  PORT_F,
  PIN_0,
  PORT_PIN_IN,
  PULL_UP,
  STD_LOW,
  PORT_DIO_MODE,
  STD_ON,
  STD_ON,


 /*********** Port_F_PIN_1(LED1) ************/

  PORT_F,
  PIN_1,
  PORT_PIN_OUT,
  OFF,
  STD_LOW,
  PORT_DIO_MODE,
  STD_OFF,
  STD_OFF,

 /*********** Port_F_PIN_2 ************/

  PORT_F,
  PIN_2,
  PORT_PIN_IN,
  PULL_UP,
  STD_LOW,
  PORT_DIO_MODE,
  STD_ON,
  STD_ON,


 /*********** Port_F_PIN_3 ************/

  PORT_F,
  PIN_3,
  PORT_PIN_IN,
  PULL_UP,
  STD_LOW,
  PORT_DIO_MODE,
  STD_ON,
  STD_ON,


 /*********** Port_F_PIN_4 (SW1)************/

  PORT_F,
  PIN_4,
  PORT_PIN_IN,
  PULL_UP,
  STD_HIGH,
  PORT_DIO_MODE,
  STD_ON,
  STD_ON,

};

