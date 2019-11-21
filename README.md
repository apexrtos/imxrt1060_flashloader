# IMXRT1060 Flashloader

## Description
Flashloader for the i.MXRT1060 series microcontroller.

Initially imported from NXP SDK Version 2.6.2 with changes to include the ability to assign a uSDHC instance when interfacing with SD cards and MMC devices.

## Changes
Original source has the following hard coded assignments:

Memory Device | uSDHC Instance
------------- | :-----------:
SD Card       | 1
MMC Device    | 2

Changes in this repository allows for the following:

1. Initialisation of the external memory device(s) using the selected uSDHC instance set in the OTP Fuses.
2. User selection of uSDHC instance when executing the `blhost -- configure-memory` command for both SD cards and MMC devices.

## Tools
Built and tested using:
* MCUXpresso IDE v11.0.1 [Build 2563]
  * arm-none-eabi-gcc v8.2.1

Designed to work in conjunction with the NXP provided PC host tool:
* blhost (V2.2.0)

## Building
1. Build within MCUXpresso IDE
* 'Release' Build Configuration
* Project -> Build All
2. Generate bootable image using the NXP provided PC tool - elftosb:
* `./elftosb -f imx -V -c imxrt1060_flashloader.bd -o ivt_flashloader.bin Release/imxrt1060_flashloader.s19`
