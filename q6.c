void down(int*);
void up(int*);

#include <stdio.h>

typedef int semaphore;

semaphore m1=1,m2=1,m3=1;
int c=0;

a_enter(){
    down(&m1);
}

a_exit(){
    up(&m1);
}

b_enter(){
    down(&m3);
    switch (c++){
        case 0:
            down(&m1);
            break;
        case 1:
            down(&m2);
            break;
    }
    up(&m3);
}

b_exit(){
    down(&m3);
    up(&m2);
    if (--c==0){
        up(&m1);
    }
    up(&m3);
}
c_enter(){
    down(&m3);
    switch (c++){
        case 0:
            down(&m1);
            break;
        case 1:
            down(&m2);
            break;
    }
    up(&m3);
}

c_exit(){
    down(&m3);
    up(&m2);
    if (--c==0){
        up(&m1);
    }
    up(&m3);
}

d_enter(){
    down(&m3);
}

d_exit(){
    up(&m3);
}
