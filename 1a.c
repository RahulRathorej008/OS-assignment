#include <pthread.h>

#include <stdio.h>

#include <stdlib.h>

pthread_mutex_t mutex;

int fib[10]; 

int in = 0;

void *genFibo(void *param); 

int main(int argc, char *argv[])

{

   pthread_attr_t attr;  

   if (argc != 2) {

   fprintf(stderr,"usage: fibthread <integer value>\n");

   return -1;

   }

   int count = atoi(argv[1]);
   if (count < 1) {

   fprintf(stderr,"%d must be>= 1\n", count);

   return -1;

   }

   pthread_attr_init(&attr);

   pthread_mutex_init(&mutex, NULL);

   for(int i = 1;i <= count;i++) {

   pthread_t thread;

   pthread_create(&thread, &attr, genFibo, (void*)i);

   pthread_join(thread, NULL);    

   }    

   for (int i = 0; i < in;i++) {

   printf("%d ", fib[i]);

   }

   printf("\n");

   pthread_mutex_destroy(&mutex);

}

void *genFibo(void *param)

{

   pthread_mutex_lock(&mutex);

   fib[in++] = fibonacci((int)param);
   pthread_mutex_unlock(&mutex);

   pthread_exit(0);

}

int fibonacci (int x)

{

   if (x <= 1) {

   return 1;

   }

   return fibonacci(x-1) + fibonacci(x-2);

}
