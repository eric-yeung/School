/*Eric Yeung and Rikin Katyal
104392784
104762347
Program that calculates pi according to the Monte Carlo method
using multithreads. This one uses parallel threading for computing the number
of points in the circle
*/


#include<stdio.h>
#include<pthread.h>
#include<unistd.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>
#include<omp.h>

double COUNT = 1000000;
#define NUMBER_OF_SLAVES 100
int hit_count = 0;
pthread_mutex_t lock;



double random_double() //num generator
{
    return random() / ((double)RAND_MAX + 1);
}


int main(int argc, char const* argv[])
{
    time_t t; //seeder for random num
    srand((unsigned)time(&t));
    clock_t start, end;
    double cpu_time_used;

    start = clock();
#pragma omp parallel num_threads(100)//this is the parallel thread to be created
    {
        double truecounter = COUNT/NUMBER_OF_SLAVES; //since each slave will do the same amount of work so it totals 1000000 points
        #pragma op sections
        {
            for(int i = 0; i < COUNT; i++)
            {

                double x = random_double() * 2.0 - 1.0;
                double y = random_double() * 2.0 - 1.0;

                if(sqrt(x*x + y*y) < 1.0)
                {
            #pragma omp atomic //vital for race condition
                    ++hit_count;
                }
            }
            #pragma op section // divides the work properly
            {
                // printf("%d\n", hit_count); //checking hit counter if you want 
                double pi = (4 * hit_count) / COUNT;
                cpu_time_used = ((double) (end - start));

                double time_taken = ((double)cpu_time_used)/CLOCKS_PER_SEC;
                end = clock();
                printf("pi = %lf\n", pi);
                printf("Time taken = %f\n", time_taken);
            }   
        }
        
        return 0;
    }
    return 0;
}
