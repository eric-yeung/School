#include<stdio.h>
#include<pthread.h>
#include<unistd.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>


double COUNT = 1000000;

double random_double()
{
    return random() / ((double)RAND_MAX + 1);
}

int hit_count = 0;

void *thread1(void *vargp)
{
    for(int i = 0; i < COUNT; i++)
    {

        double x = random_double() * 2.0 - 1.0;
        double y = random_double() * 2.0 - 1.0;

        if(sqrt(x*x + y*y) < 1.0)
        {
            ++hit_count;
        }
    }
    return 0;
}

int main(int argc, char const* argv[])
{
    time_t t;
    srand((unsigned)time(&t));
    
    clock_t start, end;
    double cpu_time_used;

    pthread_t tid;
    int id, result_code;
    start = clock();
    
    pthread_create(&tid, NULL, thread1, NULL);
    pthread_join(tid, NULL);

    double pi = (4 * hit_count) / COUNT;
    end = clock();
    cpu_time_used = ((double) (end - start));
    double time_taken = ((double)cpu_time_used)/CLOCKS_PER_SEC;
    printf("pi = %lf\n", pi);
    printf("Time taken = %f\n", time_taken);
    
    //pthread_exit(NULL);
    return 0;
}
