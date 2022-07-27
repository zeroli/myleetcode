#include "utils.h"

void Merge(std::vector<int>& arr, int left, int mid, int right, std::vector<int>& tmp)
{
    for (int i = left; i <= right; i++) {
        tmp[i] = arr[i];
    }

    int i = left, j = mid + 1;
    for (int idx = left; idx <= right; idx++) {
        if (i == mid+1) {
            arr[idx] = tmp[j++];
        } else if (j == right + 1) {
            arr[idx] = tmp[i++];
        } else if (tmp[i] < tmp[j]) {
            arr[idx] = tmp[i++];
        } else {
            arr[idx] = tmp[j++];
        }
    }
}

void MergeSort(std::vector<int>& arr, int left, int right, std::vector<int>& tmp)
{
    if (left >= right) return;
    int mid = left + (right - left) / 2;
    MergeSort(arr, left, mid, tmp);
    MergeSort(arr, mid+1, right, tmp);
    Merge(arr, left, mid, right, tmp);
}

void MergeSort(std::vector<int>& arr)
{
    std::vector<int> tmp_arr(arr);
    MergeSort(arr, 0, arr.size()-1, tmp_arr);
}

int main()
{
    std::vector<int> arr = { 1, 0, 3, 2, 5, 4, 7, 9, 8, 10 };
    std::cout << arr << "\n";
    MergeSort(arr);
    std::cout << "merged sorted: " << arr <<"\n";
}
