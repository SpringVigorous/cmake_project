#include <iostream>
#include "test/test.h"

class InsertSort {
public:
    void sort(int arr[], int n) {
        sort_gap(arr, n, 1);
    }

    //间隔排序，扩展到 希尔排序算法调用
    void sort_gap(int arr[], int n, int gap = 1)
    {
        for (int i = gap; i < n; i++) {
            int temp = arr[i];
            int j = i - gap;

            while (j >= 0 && arr[j] > temp)
            {
                arr[j + gap] = arr[j];
                j -= gap;
            }
            arr[j + gap] = temp;
        }
    }
};

void test_insert_sort() {
    int arr[] = {12, 11, 13, 5, 6};
    int n = sizeof(arr) / sizeof(arr[0]);

    InsertSort insertSort;
    insertSort.sort(arr, n);

    std::cout << "排序后的数组为: ";
    for (int i = 0; i < n; ++i) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;

}
