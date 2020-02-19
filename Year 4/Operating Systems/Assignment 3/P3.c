#include<stdio.h>
#include<pthread.h>
#include<unistd.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>



double COUNT = 1000000;
int hit_count = 0;
#define NUMBER_OF_SLAVES 100
pthread_mutex_t lock;
pthread_t tid[0];

double random_double()
{
    return random() / ((double)RAND_MAX + 1);
}

void *thread(void *vargp)
{
    pthread_mutex_lock(&lock);

    for(int i = 0; i < COUNT; i++)
    {

        double x = random_double() * 2.0 - 1.0;
        double y = random_double() * 2.0 - 1.0;

        if(sqrt(x*x + y*y) < 1.0)
        {
            ++hit_count;
        }
    }

    pthread_mutex_unlock(&lock);
    return 0;
}

int main(int argc, char const* argv[])
{
    time_t t;
    srand((unsigned)time(&t));
    
    clock_t start, end;
    double cpu_time_used;

    if (pthread_mutex_init(&lock, NULL) != 0) 
    { 
        printf("\n mutex init has failed\n"); 
        return 1; 
    } 

    int i = 0;

    int id, result_code;
    start = clock();
    
    while (i < NUMBER_OF_SLAVES)
    {
        result_code = pthread_create(&(tid[i]), NULL, thread, NULL);
        pthread_join(tid[i], NULL);
        i++;
    }

    int hitcounter = hit_count;
    hitcounter /= NUMBER_OF_SLAVES;

    double pi = (4 * hitcounter) / COUNT;
    end = clock();
    
    cpu_time_used = ((double) (end - start));
    
    double time_taken = ((double)cpu_time_used)/CLOCKS_PER_SEC;
    
    printf("pi = %lf\n", pi);
    printf("Time taken = %f\n", time_taken);
    
    pthread_mutex_destroy(&lock);
    return 0;
}
