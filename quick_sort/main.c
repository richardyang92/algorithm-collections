#include <stdio.h>

#define N 10

void quick_sort(int* arr, int left, int right);

int main() {
    int arr[N] = {23, 54, 1, 4, 90, 43, 64, 21, 4, 23};
    quick_sort(arr, 0, N - 1);
     for (int i = 0; i < N; i++) {
        printf("%d\t", arr[i]);
    }
    printf("\n");
    return 0;
}

void quick_sort(int* arr, int left, int right) {
    if (left >= right) return;
    int i = left, j = right;
    int p = arr[i];
    while (i < j) {
        while (i < j && arr[j] >= p) {
            j--;
        }
        arr[i] = arr[j];
        while (i < j && arr[i] <= p) {
            i++;
        }
        arr[j] = arr[i];
    }
    arr[i] = p;
    quick_sort(arr, left, i - 1);
    quick_sort(arr, i + 1, right);
}