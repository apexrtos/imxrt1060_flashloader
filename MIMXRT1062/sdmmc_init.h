/*
* Copyright 2017-2018 NXP
* All rights reserved.
*
* SPDX-License-Identifier: BSD-3-Clause
*/
#if !defined(__SDMMC_INIT_H__)
#define __SDMMC_INIT_H__

#include "fsl_iomuxc.h"
#if FSL_FEATURE_SOC_GPIO_COUNT
#include "gpio/fsl_gpio.h"
#elif FSL_FEATURE_SOC_IGPIO_COUNT
#include "igpio/fsl_gpio.h"
#endif
#if FSL_FEATURE_SOC_PORT_COUNT
#include "port/fsl_port.h"
#endif
#include "bootloader_common.h"

/******************************************************************************
 * Definitions.
 *****************************************************************************/
enum
{
    kSDMMC_PWR_DOWN_20MS = 0,
    kSDMMC_PWR_DOWN_10MS = 1,
    kSDMMC_PWR_DOWN_5MS = 2,
    kSDMMC_PWR_DOWN_2D5MS = 3,

    kSDMMC_PWR_UP_5MS = 0,
    kSDMMC_PWR_UP_2D5MS = 1,

    kSDMMC_USDHC_INSTANCE_1 = 0,
    kSDMMC_USDHC_INSTANCE_2 = 1,
};

////////////////////////////////////////////////////////////////////////////////
// Basic Definitions
////////////////////////////////////////////////////////////////////////////////
/*! @brief USDHC base address. */
#define BOARD_USDHC1_BASEADDR USDHC1
#define BOARD_USDHC2_BASEADDR USDHC2
/*! @brief USDHC frequency. */
#define BOARD_USDHC1_CLK_FREQ (CLOCK_GetFreq(kCLOCK_SysPllPfd0Clk) / (CLOCK_GetDiv(kCLOCK_Usdhc1Div) + 1U))
#define BOARD_USDHC2_CLK_FREQ (CLOCK_GetFreq(kCLOCK_SysPllPfd0Clk) / (CLOCK_GetDiv(kCLOCK_Usdhc2Div) + 1U))
/*! @brief USDHC pin port. */
#define BOARD_USDHC1_CD_GPIO_BASE (GPIO2)
#define BOARD_USDHC1_CD_GPIO_PIN (28)
#define BOARD_USDHC1_CD_GPIO_IOMUXC IOMUXC_GPIO_B1_12_GPIO2_IO28
#define BOARD_USDHC1_CMD_IOMUXC IOMUXC_GPIO_SD_B0_00_USDHC1_CMD
#define BOARD_USDHC1_CLK_IOMUXC IOMUXC_GPIO_SD_B0_01_USDHC1_CLK
#define BOARD_USDHC1_DATA0_IOMUXC IOMUXC_GPIO_SD_B0_02_USDHC1_DATA0
#define BOARD_USDHC1_DATA1_IOMUXC IOMUXC_GPIO_SD_B0_03_USDHC1_DATA1
#define BOARD_USDHC1_DATA2_IOMUXC IOMUXC_GPIO_SD_B0_04_USDHC1_DATA2
#define BOARD_USDHC1_DATA3_IOMUXC IOMUXC_GPIO_SD_B0_05_USDHC1_DATA3
#define BOARD_USDHC1_VSELECT_IOMUXC IOMUXC_GPIO_B1_14_USDHC1_VSELECT
#define BOARD_USDHC1_RESET_B_GPIO_BASE (GPIO2)
#define BOARD_USDHC1_RESET_B_GPIO_PIN (31)
#define BOARD_USDHC1_RESET_B_GPIO_IOMUXC IOMUXC_GPIO_B1_15_GPIO2_IO31

#define BOARD_USDHC2_CD_GPIO_BASE (GPIO3)
#define BOARD_USDHC2_CD_GPIO_PIN (25)
#define BOARD_USDHC2_CD_GPIO_IOMUXC IOMUXC_GPIO_EMC_39_GPIO3_IO25
#define BOARD_USDHC2_CMD_IOMUXC IOMUXC_GPIO_SD_B1_05_USDHC2_CMD
#define BOARD_USDHC2_CLK_IOMUXC IOMUXC_GPIO_SD_B1_04_USDHC2_CLK
#define BOARD_USDHC2_DATA0_IOMUXC IOMUXC_GPIO_SD_B1_03_USDHC2_DATA0
#define BOARD_USDHC2_DATA1_IOMUXC IOMUXC_GPIO_SD_B1_02_USDHC2_DATA1
#define BOARD_USDHC2_DATA2_IOMUXC IOMUXC_GPIO_SD_B1_01_USDHC2_DATA2
#define BOARD_USDHC2_DATA3_IOMUXC IOMUXC_GPIO_SD_B1_00_USDHC2_DATA3
#define BOARD_USDHC2_DATA4_IOMUXC IOMUXC_GPIO_SD_B1_08_USDHC2_DATA4
#define BOARD_USDHC2_DATA5_IOMUXC IOMUXC_GPIO_SD_B1_09_USDHC2_DATA5
#define BOARD_USDHC2_DATA6_IOMUXC IOMUXC_GPIO_SD_B1_10_USDHC2_DATA6
#define BOARD_USDHC2_DATA7_IOMUXC IOMUXC_GPIO_SD_B1_11_USDHC2_DATA7
#define BOARD_USDHC2_VSELECT_IOMUXC IOMUXC_GPIO_EMC_38_USDHC2_VSELECT
#define BOARD_USDHC2_RESET_B_GPIO_BASE (GPIO3)
#define BOARD_USDHC2_RESET_B_GPIO_PIN (6)
#define BOARD_USDHC2_RESET_B_GPIO_IOMUXC IOMUXC_GPIO_SD_B1_06_GPIO3_IO06

#if BL_FEATURE_SD_MODULE && BL_FEATURE_SD_MODULE_HAS_CARD_DETECT
#if defined(BL_FEATURE_SD_MODULE_CARD_DETECT_LEVEL)
#define BOARD_USDHC_CARD_INSERT_CD_LEVEL (BL_FEATURE_SD_MODULE_CARD_DETECT_LEVEL)
#endif
#if defined(BL_FEATURE_SD_MODULE_CARD_DETECT_TIMEOUT)
#define BOARD_TIMEOUT_CARD_DETECT (BL_FEATURE_SD_MODULE_CARD_DETECT_TIMEOUT)
#else
#define BOARD_TIMEOUT_CARD_DETECT 0
#endif
#endif
////////////////////////////////////////////////////////////////////////////////
// Board Definitions
////////////////////////////////////////////////////////////////////////////////

#define BOARD_SD_SUPPORT_180V (BL_FEATURE_SD_MODULE_SUPPORT_1V8)
////////////////////////////////////////////////////////////////////////////////
// Board FUNC Definitions
////////////////////////////////////////////////////////////////////////////////
#if BL_FEATURE_SD_MODULE_HAS_CARD_DETECT
#define BOARD_USDHC_CD_GPIO_INIT()                                             \
    {                                                                          \
        IOMUXC_SetPinMux(BOARD_SD_CD_GPIO_IOMUXC, false);                      \
        gpio_pin_config_t sw_config = { kGPIO_DigitalInput, 0 };               \
        GPIO_PinInit(BOARD_SD_CD_GPIO_BASE, BOARD_SD_CD_GPIO_PIN, &sw_config); \
    }
#define BOARD_USDHC_CD_STATUS() (GPIO_ReadPinInput(BOARD_SD_CD_GPIO_BASE, BOARD_SD_CD_GPIO_PIN))
#else // #if BL_FEATURE_SD_MODULE_HAS_CARD_DETECT
#define BOARD_USDHC_CD_GPIO_INIT()
#define BOARD_USDHC_CD_STATUS() (0)
#endif // #if BL_FEATURE_SD_MODULE_HAS_CARD_DETECT

#if BL_FEATURE_SD_MODULE
/*! @brief SD power control function. */
#define BOARD_USDHC_SDCARD_POWER_CONTROL_INIT(base)                                                  \
    {                                                                                                \
        gpio_pin_config_t sw_config = {                                                              \
            kGPIO_DigitalOutput, 0, kGPIO_NoIntmode,                                                 \
        };                                                                                           \
        if( base == USDHC1 )                                                                         \
        {                                                                                            \
            IOMUXC_SetPinMux(BOARD_USDHC1_RESET_B_GPIO_IOMUXC, false);                               \
            GPIO_PinInit(BOARD_USDHC1_RESET_B_GPIO_BASE, BOARD_USDHC1_RESET_B_GPIO_PIN, &sw_config); \
        }                                                                                            \
        else if( base == USDHC2 )                                                                    \
        {                                                                                            \
            IOMUXC_SetPinMux(BOARD_USDHC2_RESET_B_GPIO_IOMUXC, false);                               \
            GPIO_PinInit(BOARD_USDHC2_RESET_B_GPIO_BASE, BOARD_USDHC2_RESET_B_GPIO_PIN, &sw_config); \
        }                                                                                            \
    }
#define BOARD_USDHC_SDCARD_POWER_CONTROL(base, state)                                                 \
    {                                                                                                 \
        if( base == USDHC1 )                                                                          \
        {                                                                                             \
            GPIO_WritePinOutput(BOARD_USDHC1_RESET_B_GPIO_BASE, BOARD_USDHC1_RESET_B_GPIO_PIN, state);\
        }                                                                                             \
        else if( base == USDHC2 )                                                                     \
        {                                                                                             \
            GPIO_WritePinOutput(BOARD_USDHC2_RESET_B_GPIO_BASE, BOARD_USDHC2_RESET_B_GPIO_PIN, state);\
        }                                                                                             \
    }

/*! @brief SD vselect function. */
#define BOARD_USDHC_SDCARD_VSELECT_INIT(base)                                                                                  \
    {                                                                                                                          \
        if( base == USDHC1 )                                                                                                   \
        {                                                                                                                      \
            IOMUXC_SetPinMux(BOARD_USDHC1_VSELECT_IOMUXC, false);                                                              \
            IOMUXC_SetPinConfig(BOARD_USDHC1_VSELECT_IOMUXC, IOMUXC_SW_PAD_CTL_PAD_SRE_MASK | IOMUXC_SW_PAD_CTL_PAD_PKE_MASK | \
                                                             IOMUXC_SW_PAD_CTL_PAD_PUE_MASK |                                  \
                                                             IOMUXC_SW_PAD_CTL_PAD_HYS_MASK |                                  \
                                                             IOMUXC_SW_PAD_CTL_PAD_SPEED(2) |                                  \
                                                             IOMUXC_SW_PAD_CTL_PAD_PUS(1) | IOMUXC_SW_PAD_CTL_PAD_DSE(1));     \
        }                                                                                                                      \
        else if( base == USDHC2 )                                                                                              \
        {                                                                                                                      \
            IOMUXC_SetPinMux(BOARD_USDHC2_VSELECT_IOMUXC, false);                                                              \
            IOMUXC_SetPinConfig(BOARD_USDHC2_VSELECT_IOMUXC, IOMUXC_SW_PAD_CTL_PAD_SRE_MASK | IOMUXC_SW_PAD_CTL_PAD_PKE_MASK | \
                                                             IOMUXC_SW_PAD_CTL_PAD_PUE_MASK |                                  \
                                                             IOMUXC_SW_PAD_CTL_PAD_HYS_MASK |                                  \
                                                             IOMUXC_SW_PAD_CTL_PAD_SPEED(2) |                                  \
                                                             IOMUXC_SW_PAD_CTL_PAD_PUS(1) | IOMUXC_SW_PAD_CTL_PAD_DSE(1));     \
        }                                                                                                                      \
    }

#define BOARD_SD_MUX_CONFIG(base, busWidth)                                                                   \
    {                                                                                                         \
        if( base == USDHC1 )                                                                                  \
        {                                                                                                     \
            switch (busWidth)                                                                                 \
            {                                                                                                 \
                case kSD_DataBusWidth4Bit:                                                                    \
                    IOMUXC_SetPinMux(BOARD_USDHC1_DATA1_IOMUXC, false);                                       \
                    IOMUXC_SetPinMux(BOARD_USDHC1_DATA2_IOMUXC, false);                                       \
                    IOMUXC_SetPinMux(BOARD_USDHC1_DATA3_IOMUXC, false);                                       \
                    IOMUXC_SetPinConfig(BOARD_USDHC1_DATA1_IOMUXC,                                            \
                                        IOMUXC_SW_PAD_CTL_PAD_SRE_MASK | IOMUXC_SW_PAD_CTL_PAD_PKE_MASK |     \
                                            IOMUXC_SW_PAD_CTL_PAD_PUE_MASK | IOMUXC_SW_PAD_CTL_PAD_HYS_MASK | \
                                            IOMUXC_SW_PAD_CTL_PAD_SPEED(2) | IOMUXC_SW_PAD_CTL_PAD_PUS(1) |   \
                                            IOMUXC_SW_PAD_CTL_PAD_DSE(1));                                    \
                    IOMUXC_SetPinConfig(BOARD_USDHC1_DATA2_IOMUXC,                                            \
                                        IOMUXC_SW_PAD_CTL_PAD_SRE_MASK | IOMUXC_SW_PAD_CTL_PAD_PKE_MASK |     \
                                            IOMUXC_SW_PAD_CTL_PAD_PUE_MASK | IOMUXC_SW_PAD_CTL_PAD_HYS_MASK | \
                                            IOMUXC_SW_PAD_CTL_PAD_SPEED(2) | IOMUXC_SW_PAD_CTL_PAD_PUS(1) |   \
                                            IOMUXC_SW_PAD_CTL_PAD_DSE(1));                                    \
                    IOMUXC_SetPinConfig(BOARD_USDHC1_DATA3_IOMUXC,                                            \
                                        IOMUXC_SW_PAD_CTL_PAD_SRE_MASK | IOMUXC_SW_PAD_CTL_PAD_PKE_MASK |     \
                                            IOMUXC_SW_PAD_CTL_PAD_PUE_MASK | IOMUXC_SW_PAD_CTL_PAD_HYS_MASK | \
                                            IOMUXC_SW_PAD_CTL_PAD_SPEED(2) | IOMUXC_SW_PAD_CTL_PAD_PUS(1) |   \
                                            IOMUXC_SW_PAD_CTL_PAD_DSE(1));                                    \
                case kSD_DataBusWidth1Bit:                                                                    \
                    IOMUXC_SetPinMux(BOARD_USDHC1_CMD_IOMUXC, true);                                          \
                    IOMUXC_SetPinMux(BOARD_USDHC1_CLK_IOMUXC, false);                                         \
                    IOMUXC_SetPinMux(BOARD_USDHC1_DATA0_IOMUXC, false);                                       \
                    IOMUXC_SetPinConfig(BOARD_USDHC1_CMD_IOMUXC,                                              \
                                        IOMUXC_SW_PAD_CTL_PAD_SRE_MASK | IOMUXC_SW_PAD_CTL_PAD_PKE_MASK |     \
                                            IOMUXC_SW_PAD_CTL_PAD_PUE_MASK | IOMUXC_SW_PAD_CTL_PAD_HYS_MASK | \
                                            IOMUXC_SW_PAD_CTL_PAD_SPEED(2) | IOMUXC_SW_PAD_CTL_PAD_PUS(1) |   \
                                            IOMUXC_SW_PAD_CTL_PAD_DSE(1));                                    \
                    IOMUXC_SetPinConfig(BOARD_USDHC1_CLK_IOMUXC,                                              \
                                        IOMUXC_SW_PAD_CTL_PAD_SRE_MASK | IOMUXC_SW_PAD_CTL_PAD_HYS_MASK |     \
                                            IOMUXC_SW_PAD_CTL_PAD_SPEED(1) | IOMUXC_SW_PAD_CTL_PAD_PUS(1) |   \
                                            IOMUXC_SW_PAD_CTL_PAD_DSE(1));                                    \
                    IOMUXC_SetPinConfig(BOARD_USDHC1_DATA0_IOMUXC,                                            \
                                        IOMUXC_SW_PAD_CTL_PAD_SRE_MASK | IOMUXC_SW_PAD_CTL_PAD_PKE_MASK |     \
                                            IOMUXC_SW_PAD_CTL_PAD_PUE_MASK | IOMUXC_SW_PAD_CTL_PAD_HYS_MASK | \
                                            IOMUXC_SW_PAD_CTL_PAD_SPEED(2) | IOMUXC_SW_PAD_CTL_PAD_PUS(1) |   \
                                            IOMUXC_SW_PAD_CTL_PAD_DSE(1));                                    \
            }                                                                                                 \
        }                                                                                                     \
        else if( base == USDHC2 )                                                                             \
        {                                                                                                     \
            switch (busWidth)                                                                                 \
            {                                                                                                 \
                case kSD_DataBusWidth4Bit:                                                                    \
                    IOMUXC_SetPinMux(BOARD_USDHC2_DATA1_IOMUXC, false);                                       \
                    IOMUXC_SetPinMux(BOARD_USDHC2_DATA2_IOMUXC, false);                                       \
                    IOMUXC_SetPinMux(BOARD_USDHC2_DATA3_IOMUXC, false);                                       \
                    IOMUXC_SetPinConfig(BOARD_USDHC2_DATA1_IOMUXC,                                            \
                                        IOMUXC_SW_PAD_CTL_PAD_SRE_MASK | IOMUXC_SW_PAD_CTL_PAD_PKE_MASK |     \
                                            IOMUXC_SW_PAD_CTL_PAD_PUE_MASK | IOMUXC_SW_PAD_CTL_PAD_HYS_MASK | \
                                            IOMUXC_SW_PAD_CTL_PAD_SPEED(2) | IOMUXC_SW_PAD_CTL_PAD_PUS(1) |   \
                                            IOMUXC_SW_PAD_CTL_PAD_DSE(1));                                    \
                    IOMUXC_SetPinConfig(BOARD_USDHC2_DATA2_IOMUXC,                                            \
                                        IOMUXC_SW_PAD_CTL_PAD_SRE_MASK | IOMUXC_SW_PAD_CTL_PAD_PKE_MASK |     \
                                            IOMUXC_SW_PAD_CTL_PAD_PUE_MASK | IOMUXC_SW_PAD_CTL_PAD_HYS_MASK | \
                                            IOMUXC_SW_PAD_CTL_PAD_SPEED(2) | IOMUXC_SW_PAD_CTL_PAD_PUS(1) |   \
                                            IOMUXC_SW_PAD_CTL_PAD_DSE(1));                                    \
                    IOMUXC_SetPinConfig(BOARD_USDHC2_DATA3_IOMUXC,                                            \
                                        IOMUXC_SW_PAD_CTL_PAD_SRE_MASK | IOMUXC_SW_PAD_CTL_PAD_PKE_MASK |     \
                                            IOMUXC_SW_PAD_CTL_PAD_PUE_MASK | IOMUXC_SW_PAD_CTL_PAD_HYS_MASK | \
                                            IOMUXC_SW_PAD_CTL_PAD_SPEED(2) | IOMUXC_SW_PAD_CTL_PAD_PUS(1) |   \
                                            IOMUXC_SW_PAD_CTL_PAD_DSE(1));                                    \
                case kSD_DataBusWidth1Bit:                                                                    \
                    IOMUXC_SetPinMux(BOARD_USDHC2_CMD_IOMUXC, true);                                          \
                    IOMUXC_SetPinMux(BOARD_USDHC2_CLK_IOMUXC, false);                                         \
                    IOMUXC_SetPinMux(BOARD_USDHC2_DATA0_IOMUXC, false);                                       \
                    IOMUXC_SetPinConfig(BOARD_USDHC2_CMD_IOMUXC,                                              \
                                        IOMUXC_SW_PAD_CTL_PAD_SRE_MASK | IOMUXC_SW_PAD_CTL_PAD_PKE_MASK |     \
                                            IOMUXC_SW_PAD_CTL_PAD_PUE_MASK | IOMUXC_SW_PAD_CTL_PAD_HYS_MASK | \
                                            IOMUXC_SW_PAD_CTL_PAD_SPEED(2) | IOMUXC_SW_PAD_CTL_PAD_PUS(1) |   \
                                            IOMUXC_SW_PAD_CTL_PAD_DSE(1));                                    \
                    IOMUXC_SetPinConfig(BOARD_USDHC2_CLK_IOMUXC,                                              \
                                        IOMUXC_SW_PAD_CTL_PAD_SRE_MASK | IOMUXC_SW_PAD_CTL_PAD_HYS_MASK |     \
                                            IOMUXC_SW_PAD_CTL_PAD_SPEED(1) | IOMUXC_SW_PAD_CTL_PAD_PUS(1) |   \
                                            IOMUXC_SW_PAD_CTL_PAD_DSE(1));                                    \
                    IOMUXC_SetPinConfig(BOARD_USDHC2_DATA0_IOMUXC,                                            \
                                        IOMUXC_SW_PAD_CTL_PAD_SRE_MASK | IOMUXC_SW_PAD_CTL_PAD_PKE_MASK |     \
                                            IOMUXC_SW_PAD_CTL_PAD_PUE_MASK | IOMUXC_SW_PAD_CTL_PAD_HYS_MASK | \
                                            IOMUXC_SW_PAD_CTL_PAD_SPEED(2) | IOMUXC_SW_PAD_CTL_PAD_PUS(1) |   \
                                            IOMUXC_SW_PAD_CTL_PAD_DSE(1));                                    \
            }                                                                                                 \
        }                                                                                                     \
    }

#define BOARD_SD_PIN_CONFIG(speed, strength)

/* define for SD config IO driver strength dynamic */
#define BOARD_SD_IO_UPDATE(base, busWidth, speed, strength)                                                     \
    {                                                                                                           \
        if( base == USDHC1 )                                                                                    \
        {                                                                                                       \
            switch (busWidth)                                                                                   \
            {                                                                                                   \
                case kSD_DataBusWidth4Bit:                                                                      \
                    IOMUXC_SetPinConfig(BOARD_USDHC1_DATA1_IOMUXC,                                              \
                                        IOMUXC_SW_PAD_CTL_PAD_SRE_MASK | IOMUXC_SW_PAD_CTL_PAD_PKE_MASK |       \
                                            IOMUXC_SW_PAD_CTL_PAD_PUE_MASK | IOMUXC_SW_PAD_CTL_PAD_HYS_MASK |   \
                                            IOMUXC_SW_PAD_CTL_PAD_SPEED(speed) | IOMUXC_SW_PAD_CTL_PAD_PUS(1) | \
                                            IOMUXC_SW_PAD_CTL_PAD_DSE(strength));                               \
                    IOMUXC_SetPinConfig(BOARD_USDHC1_DATA2_IOMUXC,                                              \
                                        IOMUXC_SW_PAD_CTL_PAD_SRE_MASK | IOMUXC_SW_PAD_CTL_PAD_PKE_MASK |       \
                                            IOMUXC_SW_PAD_CTL_PAD_PUE_MASK | IOMUXC_SW_PAD_CTL_PAD_HYS_MASK |   \
                                            IOMUXC_SW_PAD_CTL_PAD_SPEED(speed) | IOMUXC_SW_PAD_CTL_PAD_PUS(1) | \
                                            IOMUXC_SW_PAD_CTL_PAD_DSE(strength));                               \
                    IOMUXC_SetPinConfig(BOARD_USDHC1_DATA3_IOMUXC,                                              \
                                        IOMUXC_SW_PAD_CTL_PAD_SRE_MASK | IOMUXC_SW_PAD_CTL_PAD_PKE_MASK |       \
                                            IOMUXC_SW_PAD_CTL_PAD_PUE_MASK | IOMUXC_SW_PAD_CTL_PAD_HYS_MASK |   \
                                            IOMUXC_SW_PAD_CTL_PAD_SPEED(speed) | IOMUXC_SW_PAD_CTL_PAD_PUS(1) | \
                                            IOMUXC_SW_PAD_CTL_PAD_DSE(strength));                               \
                case kSD_DataBusWidth1Bit:                                                                      \
                    IOMUXC_SetPinConfig(BOARD_USDHC1_CMD_IOMUXC,                                                \
                                        IOMUXC_SW_PAD_CTL_PAD_SRE_MASK | IOMUXC_SW_PAD_CTL_PAD_PKE_MASK |       \
                                            IOMUXC_SW_PAD_CTL_PAD_PUE_MASK | IOMUXC_SW_PAD_CTL_PAD_HYS_MASK |   \
                                            IOMUXC_SW_PAD_CTL_PAD_SPEED(speed) | IOMUXC_SW_PAD_CTL_PAD_PUS(1) | \
                                            IOMUXC_SW_PAD_CTL_PAD_DSE(strength));                               \
                    IOMUXC_SetPinConfig(BOARD_USDHC1_CLK_IOMUXC,                                                \
                                        IOMUXC_SW_PAD_CTL_PAD_SRE_MASK | IOMUXC_SW_PAD_CTL_PAD_HYS_MASK |       \
                                            IOMUXC_SW_PAD_CTL_PAD_SPEED(speed) | IOMUXC_SW_PAD_CTL_PAD_PUS(1) | \
                                            IOMUXC_SW_PAD_CTL_PAD_DSE(strength));                               \
                    IOMUXC_SetPinConfig(BOARD_USDHC1_DATA0_IOMUXC,                                              \
                                        IOMUXC_SW_PAD_CTL_PAD_SRE_MASK | IOMUXC_SW_PAD_CTL_PAD_PKE_MASK |       \
                                            IOMUXC_SW_PAD_CTL_PAD_PUE_MASK | IOMUXC_SW_PAD_CTL_PAD_HYS_MASK |   \
                                            IOMUXC_SW_PAD_CTL_PAD_SPEED(speed) | IOMUXC_SW_PAD_CTL_PAD_PUS(1) | \
                                            IOMUXC_SW_PAD_CTL_PAD_DSE(strength));                               \
            }                                                                                                   \
        }                                                                                                       \
        else if( base == USDHC2 )                                                                               \
        {                                                                                                       \
            switch (busWidth)                                                                                   \
            {                                                                                                   \
                case kSD_DataBusWidth4Bit:                                                                      \
                    IOMUXC_SetPinConfig(BOARD_USDHC2_DATA1_IOMUXC,                                              \
                                        IOMUXC_SW_PAD_CTL_PAD_SRE_MASK | IOMUXC_SW_PAD_CTL_PAD_PKE_MASK |       \
                                            IOMUXC_SW_PAD_CTL_PAD_PUE_MASK | IOMUXC_SW_PAD_CTL_PAD_HYS_MASK |   \
                                            IOMUXC_SW_PAD_CTL_PAD_SPEED(speed) | IOMUXC_SW_PAD_CTL_PAD_PUS(1) | \
                                            IOMUXC_SW_PAD_CTL_PAD_DSE(strength));                               \
                    IOMUXC_SetPinConfig(BOARD_USDHC2_DATA2_IOMUXC,                                              \
                                        IOMUXC_SW_PAD_CTL_PAD_SRE_MASK | IOMUXC_SW_PAD_CTL_PAD_PKE_MASK |       \
                                            IOMUXC_SW_PAD_CTL_PAD_PUE_MASK | IOMUXC_SW_PAD_CTL_PAD_HYS_MASK |   \
                                            IOMUXC_SW_PAD_CTL_PAD_SPEED(speed) | IOMUXC_SW_PAD_CTL_PAD_PUS(1) | \
                                            IOMUXC_SW_PAD_CTL_PAD_DSE(strength));                               \
                    IOMUXC_SetPinConfig(BOARD_USDHC2_DATA3_IOMUXC,                                              \
                                        IOMUXC_SW_PAD_CTL_PAD_SRE_MASK | IOMUXC_SW_PAD_CTL_PAD_PKE_MASK |       \
                                            IOMUXC_SW_PAD_CTL_PAD_PUE_MASK | IOMUXC_SW_PAD_CTL_PAD_HYS_MASK |   \
                                            IOMUXC_SW_PAD_CTL_PAD_SPEED(speed) | IOMUXC_SW_PAD_CTL_PAD_PUS(1) | \
                                            IOMUXC_SW_PAD_CTL_PAD_DSE(strength));                               \
                case kSD_DataBusWidth1Bit:                                                                      \
                    IOMUXC_SetPinConfig(BOARD_USDHC2_CMD_IOMUXC,                                                \
                                        IOMUXC_SW_PAD_CTL_PAD_SRE_MASK | IOMUXC_SW_PAD_CTL_PAD_PKE_MASK |       \
                                            IOMUXC_SW_PAD_CTL_PAD_PUE_MASK | IOMUXC_SW_PAD_CTL_PAD_HYS_MASK |   \
                                            IOMUXC_SW_PAD_CTL_PAD_SPEED(speed) | IOMUXC_SW_PAD_CTL_PAD_PUS(1) | \
                                            IOMUXC_SW_PAD_CTL_PAD_DSE(strength));                               \
                    IOMUXC_SetPinConfig(BOARD_USDHC2_CLK_IOMUXC,                                                \
                                        IOMUXC_SW_PAD_CTL_PAD_SRE_MASK | IOMUXC_SW_PAD_CTL_PAD_HYS_MASK |       \
                                            IOMUXC_SW_PAD_CTL_PAD_SPEED(speed) | IOMUXC_SW_PAD_CTL_PAD_PUS(1) | \
                                            IOMUXC_SW_PAD_CTL_PAD_DSE(strength));                               \
                    IOMUXC_SetPinConfig(BOARD_USDHC2_DATA0_IOMUXC,                                              \
                                        IOMUXC_SW_PAD_CTL_PAD_SRE_MASK | IOMUXC_SW_PAD_CTL_PAD_PKE_MASK |       \
                                            IOMUXC_SW_PAD_CTL_PAD_PUE_MASK | IOMUXC_SW_PAD_CTL_PAD_HYS_MASK |   \
                                            IOMUXC_SW_PAD_CTL_PAD_SPEED(speed) | IOMUXC_SW_PAD_CTL_PAD_PUS(1) | \
                                            IOMUXC_SW_PAD_CTL_PAD_DSE(strength));                               \
            }                                                                                                   \
        }                                                                                                       \
    }
#else
#define BOARD_USDHC_SDCARD_POWER_CONTROL_INIT()
#define BOARD_USDHC_SDCARD_POWER_CONTROL(state)
#define BOARD_USDHC_SDCARD_VSELECT_INIT()
#define BOARD_SD_MUX_CONFIG(base, busWidth)
#define BOARD_SD_PIN_CONFIG(speed, strength)
#define BOARD_SD_IO_UPDATE(base, busWidth, speed, strength)
#endif

#if BL_FEATURE_MMC_MODULE
/*! @brief MMC power control function. */
#define BOARD_USDHC_MMCCARD_POWER_CONTROL_INIT(base)                                                  \
    {                                                                                                 \
        gpio_pin_config_t sw_config = {                                                               \
            kGPIO_DigitalOutput, 0, kGPIO_NoIntmode,                                                  \
        };                                                                                            \
        if( base == USDHC1 )                                                                          \
        {                                                                                             \
            IOMUXC_SetPinMux(BOARD_USDHC1_RESET_B_GPIO_IOMUXC, false);                                \
            GPIO_PinInit(BOARD_USDHC1_RESET_B_GPIO_BASE, BOARD_USDHC1_RESET_B_GPIO_PIN, &sw_config);  \
            GPIO_WritePinOutput(BOARD_USDHC1_RESET_B_GPIO_BASE, BOARD_USDHC1_RESET_B_GPIO_PIN, true); \
        }                                                                                             \
        else if( base == USDHC2 )                                                                     \
        {                                                                                             \
            IOMUXC_SetPinMux(BOARD_USDHC2_RESET_B_GPIO_IOMUXC, false);                                \
            GPIO_PinInit(BOARD_USDHC2_RESET_B_GPIO_BASE, BOARD_USDHC2_RESET_B_GPIO_PIN, &sw_config);  \
            GPIO_WritePinOutput(BOARD_USDHC2_RESET_B_GPIO_BASE, BOARD_USDHC2_RESET_B_GPIO_PIN, true); \
        }                                                                                             \
    }
#define BOARD_USDHC_MMCCARD_POWER_CONTROL(base, state)                                                \
    {                                                                                                 \
        if( base == USDHC1 )                                                                          \
        {                                                                                             \
            GPIO_WritePinOutput(BOARD_USDHC1_RESET_B_GPIO_BASE, BOARD_USDHC1_RESET_B_GPIO_PIN, state);\
        }                                                                                             \
        else if( base == USDHC2 )                                                                     \
        {                                                                                             \
            GPIO_WritePinOutput(BOARD_USDHC2_RESET_B_GPIO_BASE, BOARD_USDHC2_RESET_B_GPIO_PIN, state);\
        }                                                                                             \
    }

/*! @brief MMC vselect function. */
#define BOARD_USDHC_MMCCARD_VSELECT_INIT(base)                                                    \
    {                                                                                             \
        if( base == USDHC1 )                                                                      \
        {                                                                                         \
            IOMUXC_SetPinMux(BOARD_USDHC1_VSELECT_IOMUXC, false);                                 \
            IOMUXC_SetPinConfig(BOARD_USDHC1_VSELECT_IOMUXC,                                      \
                                IOMUXC_SW_PAD_CTL_PAD_SRE_MASK | IOMUXC_SW_PAD_CTL_PAD_PKE_MASK | \
                                IOMUXC_SW_PAD_CTL_PAD_PUE_MASK | IOMUXC_SW_PAD_CTL_PAD_HYS_MASK | \
                                IOMUXC_SW_PAD_CTL_PAD_SPEED(2) | IOMUXC_SW_PAD_CTL_PAD_PUS(1) |   \
                                IOMUXC_SW_PAD_CTL_PAD_DSE(1));                                    \
        }                                                                                         \
        else if( base == USDHC2 )                                                                 \
        {                                                                                         \
            IOMUXC_SetPinMux(BOARD_USDHC2_VSELECT_IOMUXC, false);                                 \
            IOMUXC_SetPinConfig(BOARD_USDHC2_VSELECT_IOMUXC,                                      \
                                IOMUXC_SW_PAD_CTL_PAD_SRE_MASK | IOMUXC_SW_PAD_CTL_PAD_PKE_MASK | \
                                IOMUXC_SW_PAD_CTL_PAD_PUE_MASK | IOMUXC_SW_PAD_CTL_PAD_HYS_MASK | \
                                IOMUXC_SW_PAD_CTL_PAD_SPEED(2) | IOMUXC_SW_PAD_CTL_PAD_PUS(1) |   \
                                IOMUXC_SW_PAD_CTL_PAD_DSE(1));                                    \
        }                                                                                         \
    }

#define BOARD_MMC_MUX_CONFIG(base, busWidth)                                                                  \
    {                                                                                                         \
        if( base == USDHC1 )                                                                                  \
        {                                                                                                     \
            switch (busWidth)                                                                                 \
            {                                                                                                 \
                case kMMC_DataBusWidth8bitDDR:                                                                \
                case kMMC_DataBusWidth8bit:                                                                   \
                case kMMC_DataBusWidth4bitDDR:                                                                \
                case kMMC_DataBusWidth4bit:                                                                   \
                    IOMUXC_SetPinMux(BOARD_USDHC1_DATA1_IOMUXC, false);                                       \
                    IOMUXC_SetPinMux(BOARD_USDHC1_DATA2_IOMUXC, false);                                       \
                    IOMUXC_SetPinMux(BOARD_USDHC1_DATA3_IOMUXC, false);                                       \
                    IOMUXC_SetPinConfig(BOARD_USDHC1_DATA1_IOMUXC,                                            \
                                        IOMUXC_SW_PAD_CTL_PAD_SRE_MASK | IOMUXC_SW_PAD_CTL_PAD_PKE_MASK |     \
                                            IOMUXC_SW_PAD_CTL_PAD_PUE_MASK | IOMUXC_SW_PAD_CTL_PAD_HYS_MASK | \
                                            IOMUXC_SW_PAD_CTL_PAD_SPEED(2) | IOMUXC_SW_PAD_CTL_PAD_PUS(1) |   \
                                            IOMUXC_SW_PAD_CTL_PAD_DSE(1));                                    \
                    IOMUXC_SetPinConfig(BOARD_USDHC1_DATA2_IOMUXC,                                            \
                                        IOMUXC_SW_PAD_CTL_PAD_SRE_MASK | IOMUXC_SW_PAD_CTL_PAD_PKE_MASK |     \
                                            IOMUXC_SW_PAD_CTL_PAD_PUE_MASK | IOMUXC_SW_PAD_CTL_PAD_HYS_MASK | \
                                            IOMUXC_SW_PAD_CTL_PAD_SPEED(2) | IOMUXC_SW_PAD_CTL_PAD_PUS(1) |   \
                                            IOMUXC_SW_PAD_CTL_PAD_DSE(1));                                    \
                    IOMUXC_SetPinConfig(BOARD_USDHC1_DATA3_IOMUXC,                                            \
                                        IOMUXC_SW_PAD_CTL_PAD_SRE_MASK | IOMUXC_SW_PAD_CTL_PAD_PKE_MASK |     \
                                            IOMUXC_SW_PAD_CTL_PAD_PUE_MASK | IOMUXC_SW_PAD_CTL_PAD_HYS_MASK | \
                                            IOMUXC_SW_PAD_CTL_PAD_SPEED(2) | IOMUXC_SW_PAD_CTL_PAD_PUS(1) |   \
                                            IOMUXC_SW_PAD_CTL_PAD_DSE(1));                                    \
                case kMMC_DataBusWidth1bit:                                                                   \
                default:                                                                                      \
                    IOMUXC_SetPinMux(BOARD_USDHC1_CMD_IOMUXC, true);                                          \
                    IOMUXC_SetPinMux(BOARD_USDHC1_CLK_IOMUXC, false);                                         \
                    IOMUXC_SetPinMux(BOARD_USDHC1_DATA0_IOMUXC, false);                                       \
                    IOMUXC_SetPinConfig(BOARD_USDHC1_CMD_IOMUXC,                                              \
                                        IOMUXC_SW_PAD_CTL_PAD_SRE_MASK | IOMUXC_SW_PAD_CTL_PAD_PKE_MASK |     \
                                            IOMUXC_SW_PAD_CTL_PAD_PUE_MASK | IOMUXC_SW_PAD_CTL_PAD_HYS_MASK | \
                                            IOMUXC_SW_PAD_CTL_PAD_SPEED(2) | IOMUXC_SW_PAD_CTL_PAD_PUS(1) |   \
                                            IOMUXC_SW_PAD_CTL_PAD_DSE(1));                                    \
                    IOMUXC_SetPinConfig(BOARD_USDHC1_CLK_IOMUXC,                                              \
                                        IOMUXC_SW_PAD_CTL_PAD_SRE_MASK | IOMUXC_SW_PAD_CTL_PAD_HYS_MASK |     \
                                            IOMUXC_SW_PAD_CTL_PAD_SPEED(1) | IOMUXC_SW_PAD_CTL_PAD_PUS(1) |   \
                                            IOMUXC_SW_PAD_CTL_PAD_DSE(4));                                    \
                    IOMUXC_SetPinConfig(BOARD_USDHC1_DATA0_IOMUXC,                                            \
                                        IOMUXC_SW_PAD_CTL_PAD_SRE_MASK | IOMUXC_SW_PAD_CTL_PAD_PKE_MASK |     \
                                            IOMUXC_SW_PAD_CTL_PAD_PUE_MASK | IOMUXC_SW_PAD_CTL_PAD_HYS_MASK | \
                                            IOMUXC_SW_PAD_CTL_PAD_SPEED(2) | IOMUXC_SW_PAD_CTL_PAD_PUS(1) |   \
                                            IOMUXC_SW_PAD_CTL_PAD_DSE(1));                                    \
            }                                                                                                 \
        }                                                                                                     \
        else if( base == USDHC2 )                                                                             \
        {                                                                                                     \
            switch (busWidth)                                                                                 \
            {                                                                                                 \
                case kMMC_DataBusWidth8bitDDR:                                                                \
                case kMMC_DataBusWidth8bit:                                                                   \
                        IOMUXC_SetPinMux(BOARD_USDHC2_DATA4_IOMUXC, false);                                   \
                        IOMUXC_SetPinMux(BOARD_USDHC2_DATA5_IOMUXC, false);                                   \
                        IOMUXC_SetPinMux(BOARD_USDHC2_DATA6_IOMUXC, false);                                   \
                        IOMUXC_SetPinMux(BOARD_USDHC2_DATA7_IOMUXC, false);                                   \
                        IOMUXC_SetPinConfig(BOARD_USDHC2_DATA4_IOMUXC,                                        \
                                    IOMUXC_SW_PAD_CTL_PAD_SRE_MASK | IOMUXC_SW_PAD_CTL_PAD_PKE_MASK |         \
                                        IOMUXC_SW_PAD_CTL_PAD_PUE_MASK | IOMUXC_SW_PAD_CTL_PAD_HYS_MASK |     \
                                        IOMUXC_SW_PAD_CTL_PAD_SPEED(2) | IOMUXC_SW_PAD_CTL_PAD_PUS(1) |       \
                                        IOMUXC_SW_PAD_CTL_PAD_DSE(1));                                        \
                        IOMUXC_SetPinConfig(BOARD_USDHC2_DATA5_IOMUXC,                                        \
                                    IOMUXC_SW_PAD_CTL_PAD_SRE_MASK | IOMUXC_SW_PAD_CTL_PAD_PKE_MASK |         \
                                        IOMUXC_SW_PAD_CTL_PAD_PUE_MASK | IOMUXC_SW_PAD_CTL_PAD_HYS_MASK |     \
                                        IOMUXC_SW_PAD_CTL_PAD_SPEED(2) | IOMUXC_SW_PAD_CTL_PAD_PUS(1) |       \
                                        IOMUXC_SW_PAD_CTL_PAD_DSE(1));                                        \
                        IOMUXC_SetPinConfig(BOARD_USDHC2_DATA6_IOMUXC,                                        \
                                    IOMUXC_SW_PAD_CTL_PAD_SRE_MASK | IOMUXC_SW_PAD_CTL_PAD_PKE_MASK |         \
                                        IOMUXC_SW_PAD_CTL_PAD_PUE_MASK | IOMUXC_SW_PAD_CTL_PAD_HYS_MASK |     \
                                        IOMUXC_SW_PAD_CTL_PAD_SPEED(2) | IOMUXC_SW_PAD_CTL_PAD_PUS(1) |       \
                                        IOMUXC_SW_PAD_CTL_PAD_DSE(1));                                        \
                        IOMUXC_SetPinConfig(BOARD_USDHC2_DATA7_IOMUXC,                                        \
                                    IOMUXC_SW_PAD_CTL_PAD_SRE_MASK | IOMUXC_SW_PAD_CTL_PAD_PKE_MASK |         \
                                        IOMUXC_SW_PAD_CTL_PAD_PUE_MASK | IOMUXC_SW_PAD_CTL_PAD_HYS_MASK |     \
                                        IOMUXC_SW_PAD_CTL_PAD_SPEED(2) | IOMUXC_SW_PAD_CTL_PAD_PUS(1) |       \
                                        IOMUXC_SW_PAD_CTL_PAD_DSE(1));                                        \
                case kMMC_DataBusWidth4bitDDR:                                                                \
                case kMMC_DataBusWidth4bit:                                                                   \
                    IOMUXC_SetPinMux(BOARD_USDHC2_DATA1_IOMUXC, false);                                       \
                    IOMUXC_SetPinMux(BOARD_USDHC2_DATA2_IOMUXC, false);                                       \
                    IOMUXC_SetPinMux(BOARD_USDHC2_DATA3_IOMUXC, false);                                       \
                    IOMUXC_SetPinConfig(BOARD_USDHC2_DATA1_IOMUXC,                                            \
                                        IOMUXC_SW_PAD_CTL_PAD_SRE_MASK | IOMUXC_SW_PAD_CTL_PAD_PKE_MASK |     \
                                            IOMUXC_SW_PAD_CTL_PAD_PUE_MASK | IOMUXC_SW_PAD_CTL_PAD_HYS_MASK | \
                                            IOMUXC_SW_PAD_CTL_PAD_SPEED(2) | IOMUXC_SW_PAD_CTL_PAD_PUS(1) |   \
                                            IOMUXC_SW_PAD_CTL_PAD_DSE(1));                                    \
                    IOMUXC_SetPinConfig(BOARD_USDHC2_DATA2_IOMUXC,                                            \
                                        IOMUXC_SW_PAD_CTL_PAD_SRE_MASK | IOMUXC_SW_PAD_CTL_PAD_PKE_MASK |     \
                                            IOMUXC_SW_PAD_CTL_PAD_PUE_MASK | IOMUXC_SW_PAD_CTL_PAD_HYS_MASK | \
                                            IOMUXC_SW_PAD_CTL_PAD_SPEED(2) | IOMUXC_SW_PAD_CTL_PAD_PUS(1) |   \
                                            IOMUXC_SW_PAD_CTL_PAD_DSE(1));                                    \
                    IOMUXC_SetPinConfig(BOARD_USDHC2_DATA3_IOMUXC,                                            \
                                        IOMUXC_SW_PAD_CTL_PAD_SRE_MASK | IOMUXC_SW_PAD_CTL_PAD_PKE_MASK |     \
                                            IOMUXC_SW_PAD_CTL_PAD_PUE_MASK | IOMUXC_SW_PAD_CTL_PAD_HYS_MASK | \
                                            IOMUXC_SW_PAD_CTL_PAD_SPEED(2) | IOMUXC_SW_PAD_CTL_PAD_PUS(1) |   \
                                            IOMUXC_SW_PAD_CTL_PAD_DSE(1));                                    \
                case kMMC_DataBusWidth1bit:                                                                   \
                default:                                                                                      \
                    IOMUXC_SetPinMux(BOARD_USDHC2_CMD_IOMUXC, true);                                          \
                    IOMUXC_SetPinMux(BOARD_USDHC2_CLK_IOMUXC, false);                                         \
                    IOMUXC_SetPinMux(BOARD_USDHC2_DATA0_IOMUXC, false);                                       \
                    IOMUXC_SetPinConfig(BOARD_USDHC2_CMD_IOMUXC,                                              \
                                        IOMUXC_SW_PAD_CTL_PAD_SRE_MASK | IOMUXC_SW_PAD_CTL_PAD_PKE_MASK |     \
                                            IOMUXC_SW_PAD_CTL_PAD_PUE_MASK | IOMUXC_SW_PAD_CTL_PAD_HYS_MASK | \
                                            IOMUXC_SW_PAD_CTL_PAD_SPEED(2) | IOMUXC_SW_PAD_CTL_PAD_PUS(1) |   \
                                            IOMUXC_SW_PAD_CTL_PAD_DSE(1));                                    \
                    IOMUXC_SetPinConfig(BOARD_USDHC2_CLK_IOMUXC,                                              \
                                        IOMUXC_SW_PAD_CTL_PAD_SRE_MASK | IOMUXC_SW_PAD_CTL_PAD_HYS_MASK |     \
                                            IOMUXC_SW_PAD_CTL_PAD_SPEED(1) | IOMUXC_SW_PAD_CTL_PAD_PUS(1) |   \
                                            IOMUXC_SW_PAD_CTL_PAD_DSE(4));                                    \
                    IOMUXC_SetPinConfig(BOARD_USDHC2_DATA0_IOMUXC,                                            \
                                        IOMUXC_SW_PAD_CTL_PAD_SRE_MASK | IOMUXC_SW_PAD_CTL_PAD_PKE_MASK |     \
                                            IOMUXC_SW_PAD_CTL_PAD_PUE_MASK | IOMUXC_SW_PAD_CTL_PAD_HYS_MASK | \
                                            IOMUXC_SW_PAD_CTL_PAD_SPEED(2) | IOMUXC_SW_PAD_CTL_PAD_PUS(1) |   \
                                            IOMUXC_SW_PAD_CTL_PAD_DSE(1));                                    \
            }                                                                                                 \
        }                                                                                                     \
    }

#define BOARD_MMC_PIN_CONFIG(speed, strength)
/* define for MMC config IO driver strength dynamic */
#define BOARD_MMC_IO_UPDATE(base, busWidth, speed, strength)                                                    \
    {                                                                                                           \
        if( base == USDHC1 )                                                                                    \
        {                                                                                                       \
            switch (busWidth)                                                                                   \
            {                                                                                                   \
                case kMMC_DataBusWidth8bitDDR:                                                                  \
                case kMMC_DataBusWidth8bit:                                                                     \
                case kMMC_DataBusWidth4bitDDR:                                                                  \
                case kMMC_DataBusWidth4bit:                                                                     \
                    IOMUXC_SetPinConfig(BOARD_USDHC1_DATA1_IOMUXC,                                              \
                                        IOMUXC_SW_PAD_CTL_PAD_SRE_MASK | IOMUXC_SW_PAD_CTL_PAD_PKE_MASK |       \
                                            IOMUXC_SW_PAD_CTL_PAD_PUE_MASK | IOMUXC_SW_PAD_CTL_PAD_HYS_MASK |   \
                                            IOMUXC_SW_PAD_CTL_PAD_SPEED(speed) | IOMUXC_SW_PAD_CTL_PAD_PUS(1) | \
                                            IOMUXC_SW_PAD_CTL_PAD_DSE(strength));                               \
                    IOMUXC_SetPinConfig(BOARD_USDHC1_DATA2_IOMUXC,                                              \
                                        IOMUXC_SW_PAD_CTL_PAD_SRE_MASK | IOMUXC_SW_PAD_CTL_PAD_PKE_MASK |       \
                                            IOMUXC_SW_PAD_CTL_PAD_PUE_MASK | IOMUXC_SW_PAD_CTL_PAD_HYS_MASK |   \
                                            IOMUXC_SW_PAD_CTL_PAD_SPEED(speed) | IOMUXC_SW_PAD_CTL_PAD_PUS(1) | \
                                            IOMUXC_SW_PAD_CTL_PAD_DSE(strength));                               \
                    IOMUXC_SetPinConfig(BOARD_USDHC1_DATA3_IOMUXC,                                              \
                                        IOMUXC_SW_PAD_CTL_PAD_SRE_MASK | IOMUXC_SW_PAD_CTL_PAD_PKE_MASK |       \
                                            IOMUXC_SW_PAD_CTL_PAD_PUE_MASK | IOMUXC_SW_PAD_CTL_PAD_HYS_MASK |   \
                                            IOMUXC_SW_PAD_CTL_PAD_SPEED(speed) | IOMUXC_SW_PAD_CTL_PAD_PUS(1) | \
                                            IOMUXC_SW_PAD_CTL_PAD_DSE(strength));                               \
                case kMMC_DataBusWidth1bit:                                                                     \
                default:                                                                                        \
                    IOMUXC_SetPinConfig(BOARD_USDHC1_CMD_IOMUXC,                                                \
                                        IOMUXC_SW_PAD_CTL_PAD_SRE_MASK | IOMUXC_SW_PAD_CTL_PAD_PKE_MASK |       \
                                            IOMUXC_SW_PAD_CTL_PAD_PUE_MASK | IOMUXC_SW_PAD_CTL_PAD_HYS_MASK |   \
                                            IOMUXC_SW_PAD_CTL_PAD_SPEED(speed) | IOMUXC_SW_PAD_CTL_PAD_PUS(1) | \
                                            IOMUXC_SW_PAD_CTL_PAD_DSE(strength));                               \
                    IOMUXC_SetPinConfig(BOARD_USDHC1_CLK_IOMUXC,                                                \
                                        IOMUXC_SW_PAD_CTL_PAD_SRE_MASK | IOMUXC_SW_PAD_CTL_PAD_HYS_MASK |       \
                                            IOMUXC_SW_PAD_CTL_PAD_SPEED(speed) | IOMUXC_SW_PAD_CTL_PAD_PUS(1) | \
                                            IOMUXC_SW_PAD_CTL_PAD_DSE(strength));                               \
                    IOMUXC_SetPinConfig(BOARD_USDHC1_DATA0_IOMUXC,                                              \
                                        IOMUXC_SW_PAD_CTL_PAD_SRE_MASK | IOMUXC_SW_PAD_CTL_PAD_PKE_MASK |       \
                                            IOMUXC_SW_PAD_CTL_PAD_PUE_MASK | IOMUXC_SW_PAD_CTL_PAD_HYS_MASK |   \
                                            IOMUXC_SW_PAD_CTL_PAD_SPEED(speed) | IOMUXC_SW_PAD_CTL_PAD_PUS(1) | \
                                            IOMUXC_SW_PAD_CTL_PAD_DSE(strength));                               \
            }                                                                                                   \
        }                                                                                                       \
        else if( base == USDHC2 )                                                                               \
        {                                                                                                       \
            switch (busWidth)                                                                                   \
            {                                                                                                   \
                case kMMC_DataBusWidth8bitDDR:                                                                  \
                case kMMC_DataBusWidth8bit:                                                                     \
                    IOMUXC_SetPinConfig(BOARD_USDHC2_DATA4_IOMUXC,                                              \
                                        IOMUXC_SW_PAD_CTL_PAD_SRE_MASK | IOMUXC_SW_PAD_CTL_PAD_PKE_MASK |       \
                                            IOMUXC_SW_PAD_CTL_PAD_PUE_MASK | IOMUXC_SW_PAD_CTL_PAD_HYS_MASK |   \
                                            IOMUXC_SW_PAD_CTL_PAD_SPEED(speed) | IOMUXC_SW_PAD_CTL_PAD_PUS(1) | \
                                            IOMUXC_SW_PAD_CTL_PAD_DSE(strength));                               \
                    IOMUXC_SetPinConfig(BOARD_USDHC2_DATA5_IOMUXC,                                              \
                                        IOMUXC_SW_PAD_CTL_PAD_SRE_MASK | IOMUXC_SW_PAD_CTL_PAD_PKE_MASK |       \
                                            IOMUXC_SW_PAD_CTL_PAD_PUE_MASK | IOMUXC_SW_PAD_CTL_PAD_HYS_MASK |   \
                                            IOMUXC_SW_PAD_CTL_PAD_SPEED(speed) | IOMUXC_SW_PAD_CTL_PAD_PUS(1) | \
                                            IOMUXC_SW_PAD_CTL_PAD_DSE(strength));                               \
                    IOMUXC_SetPinConfig(BOARD_USDHC2_DATA6_IOMUXC,                                              \
                                        IOMUXC_SW_PAD_CTL_PAD_SRE_MASK | IOMUXC_SW_PAD_CTL_PAD_PKE_MASK |       \
                                            IOMUXC_SW_PAD_CTL_PAD_PUE_MASK | IOMUXC_SW_PAD_CTL_PAD_HYS_MASK |   \
                                            IOMUXC_SW_PAD_CTL_PAD_SPEED(speed) | IOMUXC_SW_PAD_CTL_PAD_PUS(1) | \
                                            IOMUXC_SW_PAD_CTL_PAD_DSE(strength));                               \
                    IOMUXC_SetPinConfig(BOARD_USDHC2_DATA7_IOMUXC,                                              \
                                        IOMUXC_SW_PAD_CTL_PAD_SRE_MASK | IOMUXC_SW_PAD_CTL_PAD_PKE_MASK |       \
                                            IOMUXC_SW_PAD_CTL_PAD_PUE_MASK | IOMUXC_SW_PAD_CTL_PAD_HYS_MASK |   \
                                            IOMUXC_SW_PAD_CTL_PAD_SPEED(speed) | IOMUXC_SW_PAD_CTL_PAD_PUS(1) | \
                                            IOMUXC_SW_PAD_CTL_PAD_DSE(strength));                               \
                case kMMC_DataBusWidth4bitDDR:                                                                  \
                case kMMC_DataBusWidth4bit:                                                                     \
                    IOMUXC_SetPinConfig(BOARD_USDHC2_DATA1_IOMUXC,                                              \
                                        IOMUXC_SW_PAD_CTL_PAD_SRE_MASK | IOMUXC_SW_PAD_CTL_PAD_PKE_MASK |       \
                                            IOMUXC_SW_PAD_CTL_PAD_PUE_MASK | IOMUXC_SW_PAD_CTL_PAD_HYS_MASK |   \
                                            IOMUXC_SW_PAD_CTL_PAD_SPEED(speed) | IOMUXC_SW_PAD_CTL_PAD_PUS(1) | \
                                            IOMUXC_SW_PAD_CTL_PAD_DSE(strength));                               \
                    IOMUXC_SetPinConfig(BOARD_USDHC2_DATA2_IOMUXC,                                              \
                                        IOMUXC_SW_PAD_CTL_PAD_SRE_MASK | IOMUXC_SW_PAD_CTL_PAD_PKE_MASK |       \
                                            IOMUXC_SW_PAD_CTL_PAD_PUE_MASK | IOMUXC_SW_PAD_CTL_PAD_HYS_MASK |   \
                                            IOMUXC_SW_PAD_CTL_PAD_SPEED(speed) | IOMUXC_SW_PAD_CTL_PAD_PUS(1) | \
                                            IOMUXC_SW_PAD_CTL_PAD_DSE(strength));                               \
                    IOMUXC_SetPinConfig(BOARD_USDHC2_DATA3_IOMUXC,                                              \
                                        IOMUXC_SW_PAD_CTL_PAD_SRE_MASK | IOMUXC_SW_PAD_CTL_PAD_PKE_MASK |       \
                                            IOMUXC_SW_PAD_CTL_PAD_PUE_MASK | IOMUXC_SW_PAD_CTL_PAD_HYS_MASK |   \
                                            IOMUXC_SW_PAD_CTL_PAD_SPEED(speed) | IOMUXC_SW_PAD_CTL_PAD_PUS(1) | \
                                            IOMUXC_SW_PAD_CTL_PAD_DSE(strength));                               \
                case kMMC_DataBusWidth1bit:                                                                     \
                default:                                                                                        \
                    IOMUXC_SetPinConfig(BOARD_USDHC2_CMD_IOMUXC,                                                \
                                        IOMUXC_SW_PAD_CTL_PAD_SRE_MASK | IOMUXC_SW_PAD_CTL_PAD_PKE_MASK |       \
                                            IOMUXC_SW_PAD_CTL_PAD_PUE_MASK | IOMUXC_SW_PAD_CTL_PAD_HYS_MASK |   \
                                            IOMUXC_SW_PAD_CTL_PAD_SPEED(speed) | IOMUXC_SW_PAD_CTL_PAD_PUS(1) | \
                                            IOMUXC_SW_PAD_CTL_PAD_DSE(strength));                               \
                    IOMUXC_SetPinConfig(BOARD_USDHC2_CLK_IOMUXC,                                                \
                                        IOMUXC_SW_PAD_CTL_PAD_SRE_MASK | IOMUXC_SW_PAD_CTL_PAD_HYS_MASK |       \
                                            IOMUXC_SW_PAD_CTL_PAD_SPEED(speed) | IOMUXC_SW_PAD_CTL_PAD_PUS(1) | \
                                            IOMUXC_SW_PAD_CTL_PAD_DSE(strength));                               \
                    IOMUXC_SetPinConfig(BOARD_USDHC2_DATA0_IOMUXC,                                              \
                                        IOMUXC_SW_PAD_CTL_PAD_SRE_MASK | IOMUXC_SW_PAD_CTL_PAD_PKE_MASK |       \
                                            IOMUXC_SW_PAD_CTL_PAD_PUE_MASK | IOMUXC_SW_PAD_CTL_PAD_HYS_MASK |   \
                                            IOMUXC_SW_PAD_CTL_PAD_SPEED(speed) | IOMUXC_SW_PAD_CTL_PAD_PUS(1) | \
                                            IOMUXC_SW_PAD_CTL_PAD_DSE(strength));                               \
            }                                                                                                   \
        }                                                                                                       \
    }
#else
#define BOARD_USDHC_MMCCARD_POWER_CONTROL_INIT()
#define BOARD_USDHC_MMCCARD_POWER_CONTROL(state)
#define BOARD_USDHC_MMCCARD_VSELECT_INIT()
#define BOARD_MMC_MUX_CONFIG(base, busWidth)
#define BOARD_MMC_PIN_CONFIG(speed, strength)
#define BOARD_MMC_IO_UPDATE(base, busWidth, speed, strength)
#endif

#endif // __SDMMC_INIT_H__
////////////////////////////////////////////////////////////////////////////////
// EOF
////////////////////////////////////////////////////////////////////////////////
