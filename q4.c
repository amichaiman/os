void down(int*);
void up(int*);
void release(int*);

void B();

void C();

int D();

#include <zconf.h>

void barrier();

#include <stdio.h>

typedef int semaphore;
int X[20];
int sum1;
int sum2;
semaphore mutex=0;
semaphore countLock=1;
int count=0;


int main(){
    int pid;

    pid = fork();
    if (pid==0){
        B();
    }
    pid = fork();
    if (pid==0){
        C();
    }
    if (pid!=0){
        D();
    }
    return 0;
}

void B(){
    sum1=0;
    for (int i=0; i<20; i+=2){
        sum1+=X[i];
    }
    barrier();
}

void C(){
    sum2=0;
    for (int i=1; i<20; i+=2){
        sum2+=X[i];
    }
    barrier();
}

int D(){
    barrier();
    return sum1+sum2;
}

void barrier(){
    down(&countLock);
    count++;
    if (count==3){
        up(&mutex);
        up(&mutex);
        up(&mutex);

    } else {
        down(&mutex);
    }
    up(&countLock);
}