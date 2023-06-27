#include <stdio.h>

#define N 10

void merge(int* arr, int p, int q, int r) {
    int m = p;
    int n = r + 1;
    int k = 0;
    int tmp[N] = {};

    while (m <= r && n <= q) {
        if (arr[m] <= arr[n]) {
            tmp[k++] = arr[m++];
        } else {
            tmp[k++] = arr[n++];
        }
    }

    while (m <= r) {
        tmp[k++] = arr[m++];
    }

    while (n <= q) {
        tmp[k++] = arr[n++];
    }

    for (int i = 0; i <= q - p; i++) {
        arr[p + i] = tmp[i];
    }
}

void mergeSort(int* arr, int p, int q) {
    if (p < q) {
        int r = (p + q) / 2;
        mergeSort(arr, p, r);
        mergeSort(arr, r + 1, q);
        merge(arr, p, q, r);
    }
}

int main() {
    int arr[N] = {23, 54, 1, 4, 90, 43, 64, 21, 4, 23};
    mergeSort(arr, 0, N - 1);

    for (int i = 0; i < N; i++) {
        printf("%d\t", arr[i]);
    }
    printf("\n");
    return 0;
}