#include <stdio.h>

typedef int Semaphore;

Semaphore mutex1 = 1;
Semaphore mutex2 = 1;
int n=5;


int main(){

    down(&mutex1);
    if (n == 0){
        up(&mutex1);
        down(&mutex2); //6,7
        n--;
        up(mutex2);
    } else{
        n--;
        up(&mutex1);
    }

    /*  entrance    */

    /******************************/
    /******************************/
    /******************************/
    /******************************/
    /*      critical section      */
    /******************************/
    /******************************/
    /******************************/
    /******************************/

    /*  exit    */
    down(&mutex1);
    n++;
    if (n==1){
        up(&mutex2);
        down(mutex2);
    }
    up(&mutex1);
    return 0;
}



