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


#include <libc/stdlib.h>
#include <libc/stdio.h>
#include <core/thread.h>
#include <core/semaphore.h>
#include <types.h>
#include <core/partition.h>
#define SCHED_WRR 1
//#define SCHED_RR 1

extern uint8_t sid;
uint8_t val;

void* pinger_job2 ();

void* pinger_job ()
{
  pok_ret_t ret;
  uint8_t tid;
  pok_thread_attr_t     tattr;

   while (1)
   {
      //pok_partition_set_mode (POK_PARTITION_MODE_INIT_WARM);
      printf ("P1T1: it is my turn\n");
      tattr.priority = rand() % 255;
      tattr.deadline = (rand() % 20)*1000000;
      tattr.entry = pinger_job2;
      tattr.period = 150000000;
      
      // weight cannot be 0
      while(1){
         tattr.weight = rand() % 5;
         if(tattr.weight != 0) break;
      }      

      ret = pok_thread_create(&tid , &tattr);
      printf("[P1] pok_thread_create (1) return=%d\n", ret);

      //ret = pok_partition_set_mode (POK_PARTITION_MODE_NORMAL);
      //printf("[P1] pok_partition_set_mode (1) return=%d\n", ret);
      pok_thread_sleep (2000000);
   }
}

void* pinger_job2 ()
{
   pok_ret_t ret;
   uint32_t id;
   pok_thread_attr_t attr;
   while (1)
   {
#if defined (SCHED_WRR) || defined (SCHED_RR)
      while(1){}
#endif
      pok_thread_id (&id);
      pok_thread_status(id, &attr);
      //printf ("P1T2: it is my turn; id=%d  priority=%d\n", attr.id, attr.priority);
      printf ("P1T2: it is my turn; id=%d deadline=%d\n ", attr.id, attr.deadline);
      //printf(" weight=%d\n", attr.weight);
      pok_thread_sleep (2000000);
   }
}

void* pinger_job3 ()
{
   pok_ret_t ret;
   while (1)
   {
      printf ("P1T3: I will wait for the semaphores\n");
      //ret = pok_sem_wait (sid, 0);
      //printf ("P1T2: pok_sem_wait, ret=%d\n", ret);
      //ret = pok_sem_wait (sid, 0);
      //printf ("P1T2: pok_sem_wait, ret=%d\n", ret);
      pok_thread_sleep (2000000);
   }
}
