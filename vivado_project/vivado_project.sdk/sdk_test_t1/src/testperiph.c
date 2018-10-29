/*
 *
 * Xilinx, Inc.
 * XILINX IS PROVIDING THIS DESIGN, CODE, OR INFORMATION "AS IS" AS A 
 * COURTESY TO YOU.  BY PROVIDING THIS DESIGN, CODE, OR INFORMATION AS
 * ONE POSSIBLE   IMPLEMENTATION OF THIS FEATURE, APPLICATION OR 
 * STANDARD, XILINX IS MAKING NO REPRESENTATION THAT THIS IMPLEMENTATION 
 * IS FREE FROM ANY CLAIMS OF INFRINGEMENT, AND YOU ARE RESPONSIBLE 
 * FOR OBTAINING ANY RIGHTS YOU MAY REQUIRE FOR YOUR IMPLEMENTATION
 * XILINX EXPRESSLY DISCLAIMS ANY WARRANTY WHATSOEVER WITH RESPECT TO 
 * THE ADEQUACY OF THE IMPLEMENTATION, INCLUDING BUT NOT LIMITED TO 
 * ANY WARRANTIES OR REPRESENTATIONS THAT THIS IMPLEMENTATION IS FREE 
 * FROM CLAIMS OF INFRINGEMENT, IMPLIED WARRANTIES OF MERCHANTABILITY 
 * AND FITNESS FOR A PARTICULAR PURPOSE.
 */

/*
 * 
 *
 * This file is a generated sample test application.
 *
 * This application is intended to test and/or illustrate some 
 * functionality of your system.  The contents of this file may
 * vary depending on the IP in your system and may use existing
 * IP driver functions.  These drivers will be generated in your
 * SDK application project when you run the "Generate Libraries" menu item.
 *
 */

#include <stdio.h>
#include "xparameters.h"
#include "xil_cache.h"
#include "xintc.h"
#include "intc_header.h"
#include "xgpio.h"
#include "gpio_header.h"
#include "xtmrctr.h"
#include "tmrctr_header.h"
#include "tmrctr_intr_header.h"
#include "xemaclite.h"
#include "xemaclite_example.h"
#include "emaclite_header.h"
#include "emaclite_intr_header.h"

void mb_reset()
{
  void (*laddr)();


  microblaze_disable_interrupts();
  //*((int*)(0x00)) = 0xB0500008B8; //0xB8080050; // preset the bootloader's reset vector
  /**
  *((int*)(0x00)) = 0x80000000
  *((int*)(0x00)) = 0x8000B0000008B8
  **/

  //printf("Reset_ vector main prog: 0x%x", *((int*)(0x00)));

  print("Reset before");
  putnum(*((int*)(0x00)));
  print ("\r\n");
  putnum(*((int*)(0x08)));
  print ("\r\n");
  putnum(*((int*)(0x10)));
  print ("\r\n");
  putnum(*((int*)(0x20)));
  print ("\r\n");


  //                0xb0000000
  *((int*)(0x00)) = 0xb0000000;
  *((int*)(0x08)) = 0xb0000000;
  *((int*)(0x10)) = 0xb0000000;
  *((int*)(0x20)) = 0xb0000000;

  laddr = (void (*)())0x0;

  print("Reset after");
  putnum(*((int*)(0x00)));
  print ("\r\n");
  putnum(*((int*)(0x08)));
  print ("\r\n");
  putnum(*((int*)(0x10)));
  print ("\r\n");
  putnum(*((int*)(0x20)));
  print ("\r\n");

  (*((void (*)())(0x00)))(); // restart
}

int main () 
{
   static XIntc intc;
   static XTmrCtr axi_timer_0_Timer;
   static XEmacLite axi_ethernetlite_0_EmacLite;
   Xil_ICacheEnable();
   Xil_DCacheEnable();
   print("---Entering main---\n\r");

   {
      int status;

      print("\r\n Running IntcSelfTestExample() for microblaze_0_axi_intc...\r\n");

      status = IntcSelfTestExample(XPAR_MICROBLAZE_0_AXI_INTC_DEVICE_ID);

      if (status == 0) {
         print("IntcSelfTestExample PASSED\r\n");
      }
      else {
         print("IntcSelfTestExample FAILED\r\n");
      }
   }

   {
       int Status;

       Status = IntcInterruptSetup(&intc, XPAR_MICROBLAZE_0_AXI_INTC_DEVICE_ID);
       if (Status == 0) {
          print("Intc Interrupt Setup PASSED\r\n");
       }
       else {
         print("Intc Interrupt Setup FAILED\r\n");
      }
   }



   {
      u32 status;
      
      print("\r\nRunning GpioOutputExample() for axi_gpio_0...\r\n");

      status = GpioOutputExample(XPAR_AXI_GPIO_0_DEVICE_ID,3);
      
      if (status == 0) {
         print("GpioOutputExample PASSED.\r\n");
      }
      else {
         print("GpioOutputExample FAILED.\r\n");
      }
   }



   {
      int status;
      
      print("\r\n Running TmrCtrSelfTestExample() for axi_timer_0...\r\n");
      
      status = TmrCtrSelfTestExample(XPAR_AXI_TIMER_0_DEVICE_ID, 0x0);
      
      if (status == 0) {
         print("TmrCtrSelfTestExample PASSED\r\n");
      }
      else {
         print("TmrCtrSelfTestExample FAILED\r\n");
      }
   }
   {
      int Status;

      print("\r\n Running Interrupt Test  for axi_timer_0...\r\n");
      
      Status = TmrCtrIntrExample(&intc, &axi_timer_0_Timer, \
                                 XPAR_AXI_TIMER_0_DEVICE_ID, \
                                 XPAR_MICROBLAZE_0_AXI_INTC_AXI_TIMER_0_INTERRUPT_INTR, 0);
	
      if (Status == 0) {
         print("Timer Interrupt Test PASSED\r\n");
      } 
      else {
         print("Timer Interrupt Test FAILED\r\n");
      }

   }


   /*
    * Peripheral SelfTest will not be run for axi_uartlite_0
    * because it has been selected as the STDOUT device
    */




   {
      int status;

      print("\r\nRunning EmacLitePolledExample() for axi_ethernetlite_0...\r\n");
      status = EmacLitePolledExample(XPAR_AXI_ETHERNETLITE_0_DEVICE_ID);
      if (status == 0) {
         print("EmacLite Polled Example PASSED\r\n");
      }
      else {
         print("EmacLite Polled Example FAILED\r\n");
      }
   }
   {
      int Status;

      print("\r\n Running Interrupt Test  for axi_ethernetlite_0...\r\n");

      Status = EmacLiteIntrExample(&intc, &axi_ethernetlite_0_EmacLite, \
                               XPAR_AXI_ETHERNETLITE_0_DEVICE_ID, \
                               XPAR_MICROBLAZE_0_AXI_INTC_AXI_ETHERNETLITE_0_IP2INTC_IRPT_INTR);

      if (Status == 0) {
         print("EmacLite Interrupt Test PASSED\r\n");
      }
      else {
         print("EmacLite Interrupt Test FAILED\r\n");
      }

   }


   print("---Exiting main---\n\r");
   Xil_DCacheDisable();
   Xil_ICacheDisable();

   mb_reset();

   return 0;
}