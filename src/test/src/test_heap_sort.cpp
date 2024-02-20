#include <iostream>
#include <vector>
#include "test/test.h"
class HeapSort {
public:
    void sort(std::vector<int>& arr) {
        int n = arr.size();

        // Build heap (rearrange array)
        for (int i = n / 2 - 1; i >= 0; i--) {
            heapify(arr, n, i);
        }

        // One by one extract an element from heap
        for (int i = n - 1; i >= 0; i--) {
            // Move current root to end
            std::swap(arr[0], arr[i]);

            // Call max heapify on the reduced heap
            heapify(arr, i, 0);
        }
    }

private:
    void heapify(std::vector<int>& arr, int n, int i) {
        int largest = i;  // Initialize largest as root
        int left = 2 * i + 1;
        int right = 2 * i + 2;

        // If left child is larger than root
        if (left < n && arr[left] > arr[largest]) {
            largest = left;
        }

        // If right child is larger than largest so far
        if (right < n && arr[right] > arr[largest]) {
            largest = right;
        }

        // If largest is not root
        if (largest != i) {
            std::swap(arr[i], arr[largest]);

            // Recursively heapify the affected sub-tree
            heapify(arr, n, largest);
        }
    }
};

void test_heap_sort() {
    std::vector<int> arr = {12, 11, 13, 5, 6, 7};

    HeapSort heapSort;
    heapSort.sort(arr);

    std::cout << "排序后的数组为: ";
    for (int i = 0; i < arr.size(); ++i) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;

}
