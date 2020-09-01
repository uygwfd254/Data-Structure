#include <iostream>

using namespace std;


void rotate_left(int arr[], int size) {
    int first = arr[0];

    for (int i = 0; i < size - 1; i++) {
        arr[i] = arr[i + 1];
    }
    arr[size - 1] = first;
}


int find_pivot(int arr[], int low, int high) {
    if (low == high)
        return low;

    int mid = (low + high) / 2;

    if (arr[mid] > arr[mid + 1])
        return mid;

    if (arr[low] < arr[mid])
        return find_pivot(arr, mid + 1, high);

    return find_pivot(arr, low, mid);
}

int half_search(int arr[], int low, int high, int key) {
    if (low == high)
        return arr[low];

    int mid = (low + high) / 2;

    if (arr[mid] == key)
        return mid;

    if (arr[mid] > key)
        return half_search(arr, low, mid, key);

    return half_search(arr, mid + 1, high, key);

}

int pivot_binary_search(int arr[], int n, int pivot, int key) {
    
    if (arr[0] < key)
        return half_search(arr, 0, pivot, key);

    return half_search(arr, pivot + 1, n - 1, key);
}

int* pivot_sum_binary_search(int arr[], int n, int right, int left, int sum) {
    int keys[2] = {right, left};
    int curr_sum = arr[left] + arr[right];

    // edge case
    if (left == n || right == -1) {
        cout << "-1 -1";
    }

    if (curr_sum == sum)
        cout << right << " " << left;

    if (curr_sum > sum)
        return pivot_sum_binary_search(arr, n, right - 1, left, sum);

    return pivot_sum_binary_search(arr, n, right, left + 1, sum);
}





int main() {
    int arr[10] = {40, 49, 53, 2, 5, 8, 17, 21, 28, 36};
    int n = 10;

    int sum = 51;
    int key = 49;
    int pivot = find_pivot(arr, 0, 10);

    // find numbers 
    int key_at = pivot_binary_search(arr, n, pivot, key);

    cout << key << " is at index " << key_at << endl;

    // find sums of two numbers
    int* keys = pivot_sum_binary_search(arr, n, pivot, pivot + 1, sum);

    //cout << keys[0] << " " << keys[1] << endl;



    return 0;
}
