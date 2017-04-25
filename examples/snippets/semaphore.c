/* semaphore.c - POSIX sempaphor example. 

   Copyright (c) 2015, Monaco F. J. <moanco@icmc.usp.br>

   This file is part of POSIX.

   POSIX is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.
   
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   
   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.

*/

  /* Note. Execute several times and verify that results are not consistent.
     Depending on the order in which the scheduler swtich between threads,
     results may differ.  Change the value of macro SYNCH from zero to one
     and compare the outcome. */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include <posixeg/debug.h>

/* If this macro is 0, no syncrhonization is performed.
   If its 1, a mutex is used to protect critical regions. */

#define SYNCH 0

int current = 21;     /* Global variables are accessible by all threads. */
int ct1, ct2;		     

#if SYNCH == 1
sem_t sem;			/* This is a POSIX semaphore. */
#endif

/* This is the function to be executed in the new thread. */

void *foo (void *arg)
{
  int count;
  int *p;

  p = malloc (sizeof(int));
  *p = 100;

  /* This is how we handle the argument passed to the thread
     by pthread_create ().*/

  count= * (int *) arg;		

  while (count)
    {
            
#if SYNCH == 1
      sem_wait (&sem);
#endif

      ct2 = --current;

      printf ("  My thread   count=%d (global=%d)  %s\n", count, current, 
	      ct1 == ct2 ? "Not changed" : "");

      count--;

#if SYNCH == 1
      sem_post (&sem);
#endif

      sleep (1);
    }

  /* Terminate the thread with its return value.
     This value is received by pthread_join(), if this is called. */

  pthread_exit (p);		

} 

/* The main function. */

int main (int argc, char **argv)
{
  int count, count2, rs;
  pthread_t mythread;
  int *val;
  printf ("Hello Threads\n");

  count2 = 10;	   /* Will will pass the thread a reference to this variable. */


#if SYNCH == 1
  sem_init (&sem, 0, 1);
#endif

  /* Create a new thread and execute foo with argument count2.
     The second parameter NULL means 'default attributes'.*/

  rs = pthread_create (&mythread, NULL, foo, &count2);
  sysfatal (rs);

  /* This loop is executed in the main thread. */

  count=10;
  while (count)
    {
      /* Count is local, current is global. */
      

#if SYNCH == 1
      sem_wait (&sem);
#endif

      ct1 = --current;


      printf ("Main thread   count=%d (global=%d)  %s\n", count, current, 
	      ct1 == ct2 ? "Not changed" : "");

      count--;

#if SYNCH == 1
      sem_post (&sem);
#endif

      sleep (1);
    }

  /* If this function is issued, the calling thread will block
     until the other thread terminates.  The terminated thread's
     return value is stored in val.*/

  pthread_join (mythread, (void *) &val);

  printf ("Main done\n");
  printf ("Mythread returned %d\n", *val);


  return EXIT_SUCCESS;
}
