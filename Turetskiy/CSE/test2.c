#include <stdio.h>
#include <time.h>


#define MAX 1000000000


int main(){
    clock_t time;
    int a, b, c, d, i;
    a = 3;
    b = 7;
    c = b-a;
    for(i = 0; i <= MAX; i++){
        d = b-a;
        b = 10;
        b = b-a+d;
        a = b-c;
        b = b-a;
        c = 10;
        d = a+b+c;
    }
    time = clock();
    printf("%d %d %d %d %d\n", a, b, c, d, i);
    printf("%ld ticks - %f sec\n", time, (double)time/CLOCKS_PER_SEC);
    return 0;
}
