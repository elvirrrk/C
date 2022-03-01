// Copyright 2022 by elvirrrk

#include <stdio.h>
#define NMAX 10

int input(int *a, int *n);
void output(int *a, int n);
void squaring(int *a, int n);

int main() {
    int n, data[NMAX];
    input(data, &n);
    squaring(data, n);
    output(data, n);
    return 0;
}

int input(int *a, int *n) {
    char c;
    if(scanf("%d", n) && ((scanf("%c", &c) == 1 || c == ' ') && c != '.'));
        else {
           int z = printf("n/a\n");
           return z;
        }
    for(int *p = a; p - a < *n; p++){
        scanf("%d", p);
    }
    return 0;
}

void output(int *a, int n) {
    for(int *p = a; p - a < n; p++) {
        printf("%d ", *p);
    }
}

void squaring(int *a, int n) {
    for(int *p = a; p - a < n; p++) {
            if (n >= 0)
            *p = *p * *p;
    }
}



