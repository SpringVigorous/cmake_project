#include <vector>
#include <iostream>
#include "test/test.h"
using namespace std;

class MergeSort {
private:
    // 辅助函数，用于合并两个已排序的子数组
    void merge(vector<int>& arr, int left, int mid, int right) {
        vector<int> temp(right - left + 1);
        int i = left, j = mid + 1, k = 0;

        while (i <= mid && j <= right) {
            if (arr[i] <= arr[j]) {
                temp[k++] = arr[i++];
            }
            else {
                temp[k++] = arr[j++];
            }
        }

        while (i <= mid) {
            temp[k++] = arr[i++];
        }

        while (j <= right) {
            temp[k++] = arr[j++];
        }

        for (i = left; i <= right; i++) {
            arr[i] = temp[i - left];
        }
        cout << "归并：" << left << "," << right << endl;
    }

    // 递归实现归并排序
    void sort(vector<int>& arr, int left, int right) {
        cout << "开始：" << left << "," << right << endl;
        if (left < right) {
            int mid = left + (right - left) / 2;
            sort(arr, left, mid);
            sort(arr, mid + 1, right);
            merge(arr, left, mid, right);
        }
        cout << "结束：" << left << "," << right << endl;
    }

public:
    // 对整个数组进行排序
    void sortArray(vector<int>& arr) {
        if (arr.size() > 1)
            sort(arr, 0, arr.size() - 1);
    }

    MergeSort(bool is_decrease = false) : is_descending_(is_decrease) {}
private:
    bool is_descending_{ false };
};

void test_merge_sort() {
    vector<int> arr = { 5, 2, 8, 3, 9, 1 };
    MergeSort ms; // 默认升序排序
    ms.sortArray(arr);
    for (int num : arr) {
        cout << num << " ";
    }

}