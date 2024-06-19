// The user must define CLA_C in the project linker settings if using the
// CLA C compiler
// Project Properties -> C2000 Linker -> Advanced Options -> Command File 
// Preprocessing -> --define
#ifdef CLA_C
// Define a size for the CLA scratchpad area that will be used
// by the CLA compiler for local symbols and temps
// Also force references to the special symbols that mark the
// scratchpad are. 
CLA_SCRATCHPAD_SIZE = 0x100;
--undef_sym=__cla_scratchpad_end
--undef_sym=__cla_scratchpad_start
#endif //CLA_C

MEMORY
{
PAGE 0 :  /* Program Memory */
          /* Memory (RAM/FLASH) blocks can be moved to PAGE1 for data allocation */
   /* BEGIN is used for the "boot to Flash" bootloader mode   */
   BEGIN            : origin = 0x080000, length = 0x000002
   RAMM0            : origin = 0x0001B1, length = 0x00024F
//   RAMM1_RSVD       : origin = 0x0007F8, length = 0x000008     /* Reserve and do not use for code as per the errata advisory "Memory: Prefetching Beyond Valid Memory" */
   RAMD0            : origin = 0x00C000, length = 0x000800
   RAMLS01          : origin = 0x008000, length = 0x001000        // CPU1 Ram Function
//   RAMLS0          	: origin = 0x008000, length = 0x000800    // CPU1 Ram Function
//   RAMLS1          	: origin = 0x008800, length = 0x000800    // CPU1 Ram Function

   RAMLS34          : origin = 0x009000, length = 0x000800        // CLA Ram Function
//   RAMLS3           : origin = 0x009800, length = 0x000800      // CLA Ram Function
//   RAMLS4           : origin = 0x00A000, length = 0x000800      // CLA Ram Function
   RAMGS0           : origin = 0x00D000, length = 0x001000
   RAMGS1           : origin = 0x00E000, length = 0x001000

   RAMGS14          : origin = 0x01B000, length = 0x001000     // .fapi_ram for CPU1
//   RAMGS15_RSVD     : origin = 0x01CFF8, length = 0x000008     /* Reserve and do not use for code as per the errata advisory "Memory: Prefetching Beyond Valid Memory" */


   RESET            : origin = 0x3FFFC0, length = 0x000002
   /* Flash sectors */
   FLASH0           : origin = 0x080002, length = 0x001FFE  /* on-chip Flash */ // .cinit  .pinit
   FLASH1           : origin = 0x082000, length = 0x002000  /* on-chip Flash */ // .text
   FLASH2           : origin = 0x084000, length = 0x002000  /* on-chip Flash */ // .text
   FLASH3           : origin = 0x086000, length = 0x002000  /* on-chip Flash */ // .text, .TI.ramfunc
   FLASH4           : origin = 0x088000, length = 0x008000  /* on-chip Flash */ // .switch
   FLASH5           : origin = 0x090000, length = 0x008000  /* on-chip Flash */ // .init_array
   FLASH6           : origin = 0x098000, length = 0x008000  /* on-chip Flash */ // .const
   FLASH7           : origin = 0x0A0000, length = 0x008000  /* on-chip Flash */ // Cla1Prog
   FLASH8           : origin = 0x0A8000, length = 0x008000  /* on-chip Flash */
   FLASH9           : origin = 0x0B0000, length = 0x008000  /* on-chip Flash */
   FLASH10          : origin = 0x0B8000, length = 0x002000  /* on-chip Flash */
   FLASH11          : origin = 0x0BA000, length = 0x002000  /* on-chip Flash */ // .fapi_ram
   FLASH12          : origin = 0x0BC000, length = 0x002000  /* on-chip Flash */ // C28_STORE_ADDRESS
   FLASH13          : origin = 0x0BE000, length = 0x001FF0  /* on-chip Flash */
//   FLASH13_RSVD     : origin = 0x0BFFF0, length = 0x000010  /* Reserve and do not use for code as per the errata advisory "Memory: Prefetching Beyond Valid Memory" */

PAGE 1 : /* Data Memory */
         /* Memory (RAM/FLASH) blocks can be moved to PAGE0 for program allocation */

   BOOT_RSVD        : origin = 0x000002, length = 0x0001AF     /* Part of M0, BOOT rom will use this for stack */
   RAMM1            : origin = 0x000400, length = 0x0003F8     /* on-chip RAM block M1 */
//   RAMM1_RSVD       : origin = 0x0007F8, length = 0x000008     /* Reserve and do not use for code as per the errata advisory "Memory: Prefetching Beyond Valid Memory" */

   RAMD1            : origin = 0x00C800, length = 0x000800


   RAMLS2           : origin = 0x009000, length = 0x000800    // CPU1 Ram Data

   RAMLS5           : origin = 0x00A800, length = 0x000800    // CLA Ram Data


   RAMGS2           : origin = 0x00F000, length = 0x001000
   RAMGS3           : origin = 0x010000, length = 0x001000
   RAMGS4           : origin = 0x011000, length = 0x001000


//   RAMGS10          : origin = 0x017000, length = 0x001000
//   RAMGS11          : origin = 0x018000, length = 0x001000
   RAMGS10_11       : origin = 0x017000, length = 0x002000     
//   RAMGS12          : origin = 0x019000, length = 0x001000
//   RAMGS13          : origin = 0x01A000, length = 0x001000
   RAMGS12_13       : origin = 0x019000, length = 0x002000

   CPU1TOCPU2RAM    : origin = 0x03A000, length = 0x000800
   CPU2TOCPU1RAM    : origin = 0x03B000, length = 0x000800

   CPUTOCMRAM       : origin = 0x039000, length = 0x000800
   CMTOCPURAM       : origin = 0x038000, length = 0x000800

   CANA_MSG_RAM     : origin = 0x049000, length = 0x000800
   CANB_MSG_RAM     : origin = 0x04B000, length = 0x000800

   CLA1_MSGRAMLOW   : origin = 0x001480,   length = 0x000080
   CLA1_MSGRAMHIGH  : origin = 0x001500,   length = 0x000080
   CLA1_DMA_MSGRAM  : origin = 0x001680,   length = 0x000080
   DMA_CLA1_MSGRAM  : origin = 0x001700,   length = 0x000080

}

SECTIONS
{
   /* Allocate program areas: */
   .cinit              : > FLASH0      PAGE = 0,    ALIGN(8)
   .pinit              : > FLASH0      PAGE = 0,    ALIGN(8)
   .text               : >>  FLASH1 | FLASH2 | FLASH3      PAGE = 0, ALIGN(8)
   codestart           : > BEGIN       PAGE = 0,    ALIGN(8)
   /* Allocate uninitalized data sections: */
   .stack              : > RAMM1       PAGE = 1
   .switch             : > FLASH4      PAGE = 0,    ALIGN(8)
   .reset              : > RESET,      PAGE = 0,    TYPE = DSECT /* not used, */


   .init_array      : > FLASH5,        PAGE = 0,    ALIGN(8)
   .bss                : > RAMLS2,     PAGE = 1
   .bss:output         : > RAMLS2,     PAGE = 1
   .bss:cio            : > RAMLS2,     PAGE = 1
   .data               : > RAMLS2,     PAGE = 1
   .sysmem             : > RAMLS2,     PAGE = 1
   /* Initalized sections go in Flash */
   .const              : > FLASH6,     PAGE = 0,    ALIGN(8)

   MSGRAM_CPU1_TO_CPU2 : > CPU1TOCPU2RAM, type=NOINIT
   MSGRAM_CPU2_TO_CPU1 : > CPU2TOCPU1RAM, type=NOINIT
   MSGRAM_CPU_TO_CM    : > CPUTOCMRAM, type=NOINIT
   MSGRAM_CM_TO_CPU    : > CMTOCPURAM, type=NOINIT

   .TI.ramfunc : {} LOAD = FLASH3,
                    RUN = RAMLS01,
                    LOAD_START(RamfuncsLoadStart),
                    LOAD_SIZE(RamfuncsLoadSize),
                    LOAD_END(RamfuncsLoadEnd),
                    RUN_START(RamfuncsRunStart),
                    RUN_SIZE(RamfuncsRunSize),
                    RUN_END(RamfuncsRunEnd),
                    PAGE = 0, ALIGN(8)

    .fapi_ram : {
    	-l F2838x_C28x_FlashAPI.lib

    } LOAD = FLASH11,
      RUN = RAMGS14,
      LOAD_START(fapi_ram_LoadStart),
      LOAD_SIZE(fapi_ram_LoadSize),
      LOAD_END(fapi_ram_LoadEnd),
      RUN_START(fapi_ram_RunStart),
      RUN_SIZE(fapi_ram_RunSize),
      RUN_END(fapi_ram_RunEnd),
      PAGE = 0, ALIGN(8)


    RD_CPU2         : > RAMGS10_11,           PAGE = 1
    RW_CPU1         : > RAMGS12_13,           PAGE = 1

   /* CLA specific sections */
   Cla1Prog    :    LOAD = FLASH7,
                    RUN = RAMLS34,
                    LOAD_START(Cla1funcsLoadStart),
                    RUN_START(Cla1funcsRunStart),
                    LOAD_SIZE(Cla1funcsLoadSize),
                    PAGE = 0, ALIGN(8)


   CLADataLS0       : > RAMLS5
   CLADataLS1       : > RAMLS5

   Cla1ToCpuMsgRAM  : > CLA1_MSGRAMLOW, type=NOINIT
   CpuToCla1MsgRAM  : > CLA1_MSGRAMHIGH, type=NOINIT
   Cla1ToDmaMsgRAM  : > CLA1_DMA_MSGRAM, type=NOINIT
   DmaToCla1MsgRAM  : > DMA_CLA1_MSGRAM, type=NOINIT

   Cla1DataRam      : > RAMLS5

#ifdef CLA_C
   /* CLA C compiler sections */
   //
   // Must be allocated to memory the CLA has write access to
   //
   CLAscratch       :
                     { *.obj(CLAscratch)
                     . += CLA_SCRATCHPAD_SIZE;
                     *.obj(CLAscratch_end) } > RAMLS5,  PAGE = 1

   .scratchpad      : > RAMLS5,       PAGE = 1
   .bss_cla		    : > RAMLS5,       PAGE = 1
   cla_shared	    : > RAMLS5,       PAGE = 1
   .const_cla  :    LOAD = FLASHH,
                    RUN = RAMLS5,
                    RUN_START(Cla1ConstRunStart),
                    LOAD_START(Cla1ConstLoadStart),
                    LOAD_SIZE(Cla1ConstLoadSize),
                    PAGE = 1, ALIGN(8)

#endif //CLA_C
}

/*
//===========================================================================
// End of file.
//===========================================================================
*/
