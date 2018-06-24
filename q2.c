void Eat();
void Think();
int i;
int TRUE;

#define FALSE 0
void takeForks(int i);
int tryToTakeForks(int i);
void putForks(int i);
void synchronized(int*);
void wait(int*);
void notify(int*);

#include <stdio.h>

#define N 5
#define LEFT ((i+N-1)%N)
#define RIGHT ((i+1)%N)

enum {THINKING,HUNGRY,EATING};
int criticalRange;
int state[N];
int philosopher[N];

int main() {

    while (TRUE){
        Think();
        /*  philosopher is hungry.
         *  try to acquire 2 forks.
         *  block otherwise*/
        takeForks(i);
        Eat();
        /*return forks to table*/
        putForks(i);
    }
}

void putForks(int i) {
    /*  enter CR    */
    synchronized(&criticalRange){
        state[i] = THINKING;

        /*  check if right philosopher is waiting.
         *  if yes, let him eat */
        tryToTakeForks(RIGHT);

        /*  check if left philosopher is waiting.
         *  if yes, let him eat */
        tryToTakeForks(LEFT);
    }
}

void takeForks(int i){
    int tookForks = FALSE;
    /*  enter CR    */
    synchronized(&criticalRange){

        state[i] = HUNGRY;
        /*  TRY to take forks   */
        tookForks = tryToTakeForks(i);

        /*  exit CR    */

    }
    synchronized(&philosopher[i]){
        if (!tookForks){
            wait(&philosopher[i]);
        }
    }
}

int tryToTakeForks(int i) {
    if (state[i] == HUNGRY
            && state[LEFT] != EATING
            && state[RIGHT] != EATING){
        state[i] = EATING;

        synchronized(&philosopher[i]){
            notify(&philosopher[i]);
        }

        return TRUE;
    }
    return FALSE;
}
