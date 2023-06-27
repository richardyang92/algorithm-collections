#include <stdio.h>

int zero_one_packet(int W, int* wt, int* val, int n);
int max(int a, int b);

int main() {
    int val[] = { 60, 100, 120 };
    int wt[] = { 10, 20, 30 };
    int W = 50;

    int n = sizeof(val) / sizeof(int);
    printf("Maximum value=%d\n", zero_one_packet(W, wt, val, n));

    return 0;
}

int zero_one_packet(int W, int* wt, int* val, int n) {
    int i, w;
    int K[n + 1][W + 1];

    for (i = 0; i <= n; i++) {
        for (w = 0; w <= W; w++) {
            if (i == 0 || w == 0) {
                K[i][w] = 0;
            } else if (wt[i - 1] <= w) {
                K[i][w] = max(K[i - 1][w], K[i - 1][w - wt[i - 1]] + val[i - 1]);
            } else {
                K[i][w] = K[i - 1][w];
            }
        }
    }

    int maxVal = K[n][W];
    int totalWeight = W;

    for (i = n; i >= 1; i--) {
        if (K[i][totalWeight] > K[i - 1][totalWeight]) {
            printf("%d %d\n", wt[i - 1], val[i - 1]);
            totalWeight -= wt[i - 1];
        }
    }
    return maxVal;
}

int max(int a, int b) {
    return a > b ? a : b;
}