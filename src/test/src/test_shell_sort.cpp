
#include <iostream>
#include "test/test.h"
using namespace std;
#include <iostream>

class ShellSort {
public:
    void sort(int arr[], int n) {
        for (int gap = n / 2; gap > 0; gap /= 2) {
            for (int i = gap; i < n; i++) {
                int temp = arr[i];
                int j = i - gap;

                while (j >= 0 && arr[j] > temp)
                {
                    arr[j+gap] = arr[j ];
                    j -= gap;
                }
                arr[j+gap] = temp;
            }
        }
    }
};

void test_shell_sort() {
    int arr[] = { 12, 11, 13, 5, 6,10 };
    int n = sizeof(arr) / sizeof(arr[0]);

    ShellSort shellSort;
    shellSort.sort(arr, n);

    std::cout << "排序后的数组为: ";
    for (int i = 0; i < n; ++i) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;

}

