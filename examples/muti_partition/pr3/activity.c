/*
 *                               POK header
 * 
 * The following file is a part of the POK project. Any modification should
 * made according to the POK licence. You CANNOT use this file or a part of
 * this file is this part of a file for your own project
 *
 * For more information on the POK licence, please see our LICENCE FILE
 *
 * Please follow the coding guidelines described in doc/CODING_GUIDELINES
 *
 *                                      Copyright (c) 2007-2009 POK team 
 *
 * Created by julien on Thu Jan 15 23:34:13 2009 
 */


#include <libc/stdio.h>
#include <core/thread.h>
#include <core/semaphore.h>
#include <types.h>
#define PARTITON_WRR 1

extern uint8_t sid;
uint8_t val;

void* pinger_job ()
{
   pok_ret_t ret;
   while (1)
   {
#ifdef PARTITON_WRR
	continue;
#endif
      printf ("P3T1: it is my turn\n");
      pok_thread_sleep (2000000);
   }
}

void* pinger_job2 ()
{
   pok_ret_t ret;
   while (1)
   {
      printf ("P1T2: I will wait for the semaphores\n");
      pok_thread_sleep (2000000);
   }
}

void* pinger_job3 ()
{
   pok_ret_t ret;
   while (1)
   {
      printf ("P1T3: I will wait for the semaphores\n");
      pok_thread_sleep (2000000);
   }
}
