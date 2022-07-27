#include "utils.h"


int Merge(std::vector<int>& arr, int left, int mid, int right, std::vector<int>& tmp)
{
    for (int i = left; i <= right; i++){
        tmp[i] = arr[i];
    }

    int cnt = 0;
    int i = left, j = mid + 1;
    for (int p = left; p <= right; p++) {
        if (i == mid + 1) {
            arr[p] = tmp[j++];
        } else if (j == right + 1) {
            arr[p] = tmp[i++];
            // alternative 1
            cnt += (j - mid - 1);
        } else if (tmp[i] > tmp[j]) {
            arr[p] = tmp[j++];
            // then arr[i...] > arr[j], solution #2
            //cnt += (mid - i + 1);
        } else {
            arr[p] = tmp[i++];
            // alternative 1: all arr[mid+1, ..., j-1] are smaller than arr[i]
            // because arr[i] will be chosen to be next on position 'p'
            cnt += (j - mid - 1);
        }
    }
    //std::cout << cnt << "\n";
    return cnt;
}

int MergeSort(std::vector<int>& arr, int left, int right, std::vector<int>& tmp)
{
    if (left == right) {
        return 0;
    }
    int mid = left + (right - left) / 2;
    int cnt = MergeSort(arr, left, mid, tmp);
    cnt += MergeSort(arr, mid+1, right, tmp);
    cnt += Merge(arr, left, mid, right, tmp);
    return cnt;
}

int InversionNum(std::vector<int>& arr)
{
    std::vector<int> tmp(arr);
    return MergeSort(arr, 0, arr.size()-1, tmp);
}

int main()
{
    {
        std::vector<int> arr = { 4, 1, 3, 2 };
        std::cout << InversionNum(arr) << "\n";  // 4
    }
    {
        std::vector<int> arr = { 4, 3, 2, 1 };
        std::cout << InversionNum(arr) << "\n";  // 6
    }
    {
        std::vector<int> arr = { 1, 2, 3, 4 };
        std::cout << InversionNum(arr) << "\n";  // 0
    }

}
