#include <stdio.h>


int largest(int myArray[], int size) {
    int maxValue = myArray[0];

    for (int i = 1; i < size; ++i) {
        if ( myArray[i] > maxValue ) {
            maxValue = myArray[i];
        }
    }
    return maxValue;
}
int main()
{
    int x[] = {1, 30, 5, 2, 7,10};
    printf("maximum is %d\n",largest(x,5));
    return 0;
}
