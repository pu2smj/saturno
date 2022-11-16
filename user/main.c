/*----------------------------------------------------------
   Copyright (c)
   file.........: main.c
   description..: Main Module System
   user.........: 
   SO...........: RTX
   target.......: STM32F103ZE
   board........: PCB E01 REV B LOTE II 21C13
  --------------------------------------------------------*/

   #include <rtl.h> 
   #include "GUI.h" 
   #include "board.h"
   #include "stm32f10x.h"   
   #include "definicoes.h"
   #include "main.h"
   #include "level0.h"

   /*Private variables -----------------------------------*/
   
   /*extern variables -----------------------------------*/
   
    /*----[task auto run]-----------------------------------*/
   __task void tInit(void);
   __task void task_main(void);


/*----------------------------------------------------------
 task.........: main
 description..: Initialize and start RTX Kernel
 *---------------------------------------------------------*/
int main(void){
   SystemInit();
   os_sys_init(tInit);
}
/*----------------------------------------------------------
 task.........: task_init
 description..: Initializes and starts other tasks
 *---------------------------------------------------------*/
__task void tInit(void){
   BoardInit();
   os_tsk_create(task_main, 4);
   os_tsk_delete_self();
}
/*----------------------------------------------------------
     
*---------------------------------------------------------*/
__task void task_main(void){
   GUI_Init();
   wintro();
   while (1) { 
      GUI_Exec();
      GUI_X_ExecIdle(); 
   }
}
/*--------------------------------------------------------------
 Function Name  : assert_failed
 Description    : called on failed assertion if compiled with USE_FULL_ASSERT
 Input          : pointers to char-arrays/strings: filename, function-name, line in file
 Output         : via xprintf
 Return         : None
--------------------------------------------------------------*/
#ifdef USE_FULL_ASSERT
   void assert_failed(uint8_t* file, uint32_t line){ 
      while(1){}
   }
#endif

/*------------------------------------------------------------
   eof
--------------------------------------------------------------*/