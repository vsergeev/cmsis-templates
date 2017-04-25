## CMSIS v3.20 Templates for GNU ARM Tools

* CMSIS v3.20 core support from ARM in `core/`

* Vendor chip support from NXP's ["lpc175x_6x_cmsis_driver_library.zip"](http://lpcware.com/content/nxpfile/lpc175x6x-cmsis-compliant-standard-peripheral-firmware-driver-library-keil-iar-gnu) package in `lpc17xx/`

* Makefile, linker script, and all code in the root directory are 100% public domain.

* `system_LPC17xx.c` configured to use an external 12MHz crystal, a 100MHz system clock from PLL0, and a 48MHz clock from PLL1.

See http://sergeev.io/notes/cortex_cmsis/ for more information.

Check out the lpc8xx, lpc11xx, lpc13xx, and lpc17xx branches for other templates.

