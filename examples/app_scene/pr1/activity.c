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
#include <core/time.h>
#include <types.h>
#include <core/partition.h>

extern uint8_t sid;
uint8_t val;

void* pinger_job2 ();
void* pinger_job3 ();

void* pinger_job ()
{
   pok_ret_t ret;
   
   pok_time_t ns; 
   pok_time_get (&ns);
   pok_thread_attr_t     tattr;
   uint8_t tid;
   
   uint32_t id;
   pok_thread_attr_t attr;

   uint32_t time = ns / 1000;

   pok_thread_id (&id);
   pok_thread_status(id, &attr);

   //printf("Thread 1 GPS location work begins at time: %d us, priority=%d\n", time, attr.priority);
   printf("Thread 1 GPS location work begins at time: %d us, deadline=%d\n", time, attr.deadline);
   uint32_t sum = 0;
   for(uint32_t i = 0; i < 200000000; i++)
   {
      if(i == 500000){
      	tattr.priority = rand() % 255;
      	//tattr.deadline = (rand() % 20)*1000000;
        tattr.deadline = 2180000;
        tattr.entry = pinger_job2;
        tattr.period = 150000000;
        //tattr.time_capacity = 100000000;
        // weight cannot be 0
        while(1){
           tattr.weight = rand() % 5;
           if(tattr.weight != 0) break;
        }      

        ret = pok_thread_create(&tid , &tattr);
        //printf("[P1] pok_thread_create (1) return=%d\n", ret);
      }
      sum++;
   }

   pok_time_get (&ns);
   
   time = ns / 1000;
   //printf("Thread 1 GPS location work ends at time: %d us, priority=%d\n", time, attr.priority);
   printf("Thread 1 GPS location work ends at time: %d us, deadline=%d\n", time, attr.deadline);
   pok_thread_sleep (200000000);
}

void* pinger_job2 ()
{
   pok_ret_t ret;   
   pok_time_t ns;

   pok_thread_attr_t     tattr;
   uint8_t tid;

   uint32_t id;
   pok_thread_attr_t attr;

   pok_time_get (&ns);
   
   pok_thread_id (&id);
   pok_thread_status(id, &attr);

   uint32_t time = ns / 1000;
   //printf("Thread 2 turning on light work begins at time: %d us, priority=%d\n", time, attr.priority);
   printf("Thread 2 turning on light work begins at time: %d us, deadline=%d\n", time, attr.deadline);
   uint32_t sum = 0;
   for(uint32_t i = 0; i < 100000000; i++)
   {
      if(i == 5000000){
      	tattr.priority = rand() % 255;
      	tattr.deadline = 400000;
        tattr.entry = pinger_job3;
        tattr.period = 150000000;
        //tattr.time_capacity = 100000000;
        // weight cannot be 0
        while(1){
           tattr.weight = rand() % 5;
           if(tattr.weight != 0) break;
        }      

        ret = pok_thread_create(&tid , &tattr);
        //printf("[P1] pok_thread_create (1) return=%d\n", ret);
      }
      sum++;
   }

   pok_time_get (&ns);
   
   time = ns / 1000;
   //printf("Thread 2 turning on light work ends at time: %d us, priority=%d\n", time, attr.priority);
   printf("Thread 2 turning on light work ends at time: %d us, deadline=%d\n", time, attr.deadline);
   pok_thread_sleep (200000000);
   //while(1){}
}

void* pinger_job3 ()
{
   pok_ret_t ret;

   uint32_t id;
   pok_thread_attr_t attr;
   
   pok_time_t ns; 
   pok_time_get (&ns);

   pok_thread_id (&id);
   pok_thread_status(id, &attr);
   
   uint32_t time = ns / 1000;
   //printf("Thread 3 braking work begins at time: %d us, priority=%d\n", time, attr.priority);
   printf("Thread 3 braking work begins at time: %d us, deadline=%d\n", time, attr.deadline);
   uint32_t sum = 0;
   for(uint32_t i = 0; i < 10000000; i++)
   {
      //pok_thread_sleep (2000000);
      sum++;
   }

   pok_time_get (&ns);
   
   time = ns / 1000;
   //printf("Thread 3 braking work ends at time: %d us\n", time);
   printf("Thread 3 braking work ends at time: %d us, deadline=%d\n", time, attr.deadline);
   pok_thread_sleep (200000000);
   //while(1){}
}
