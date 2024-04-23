#include <iostream>
#include <random>
#include <vector>
#include <algorithm>

template<typename T>
std::vector<T> createRandomArray(size_t n_elements, T min, T max) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<T> distribution(min, max);
    std::vector<T> arr(n_elements);
    for (size_t i = 0; i < n_elements; i++)
        arr[i] = distribution(gen);
    return arr;
}

void checker(std::vector<int>& arr, std::string sort_type) {
    for(int i=0; i<arr.size()-1; i++)
        if(arr[i] > arr[i+1]) {
            std::cout << sort_type << " sorting is incorrect!" << std::endl;
            return;
        }
    std::cout << sort_type << " sorting is correct!" << std::endl;
}

template<typename T>
static int partition(std::vector<T>& arr, int left, int right) {
    int x = arr[right];
    int i = left;
    for(int j=left; j<=right; j++) { // < or <=?
        if(arr[j] < x) {
            std::swap(arr[i], arr[j]);
            i++;
        }
    }
    std::swap(arr[i], arr[right]);
    return i;
}

template<typename T>
void quicksort(std::vector<T>& arr, int left, int right) {
    if(left <= right) {
        int  pivot = partition(arr, left, right);
        quicksort(arr, left, pivot-1);
        quicksort(arr, pivot+1, right);
    }
}

template<typename T>
static void _merge(std::vector<T>& arr, std::vector<T>& cpy, int left, int right) {
    int mid = (left+right)/2;
    int l = left;
    int r = mid+1;
    int a = 0;
    
    while(l <= mid && r <= right)
        cpy[a++] = arr[l] < arr[r] ? arr[l++] : arr[r++];
    while(l <= mid)
        cpy[a++] = arr[l++];
    while(r <= right)
        cpy[a++] = arr[r++];
    std::copy(cpy.begin(), cpy.begin()+(right-left+1), arr.begin()+left);
}

template<typename T>
static void _mergesort(std::vector<T>& arr, std::vector<T>& cpy, int left, int right) {
    if(left < right) {
        int mid = (left+right)/2;
        _mergesort(arr, cpy, left, mid);
        _mergesort(arr, cpy, mid+1, right);
        _merge(arr, cpy, left, right);
    }
}

template<typename T>
void mergesort(std::vector<T>& arr, int left, int right) {
    std::vector<T> cpy(arr);
    _mergesort(arr, cpy, left, right);
}

/**
 * @brief _heapify_maxheap the subtree rooted at node i
 */
template<typename T>
static void _heapify_maxheap(std::vector<T>& arr, int n, const int i) {
    int left = 2*i;      // left child index
    int right = 2*i + 1; // right child index
    int max_i = i;       // index of max(arr[left], arr[right], arr[i])
    if(left <= n && arr[left] > arr[max_i])
        max_i = left;
    if(right <=n && arr[right] > arr[max_i])
        max_i = right;

    if(max_i != i) {
        std::swap(arr[i], arr[max_i]);
        _heapify_maxheap(arr, n, max_i);
    }
}

/**
 * @brief Build a max heap from an array
 */
template<typename T>
static void _buildMaxHeap(std::vector<T>& arr) {
    int n = arr.size()-1;
    for(int i=n/2; i>=0; i--)
        _heapify_maxheap(arr, n, i);
}

/**
 * Based on https://youtu.be/2DmK_H7IdTo?si=SjUk-w-kQMkcxmgm
 */
template<typename T>
void heapsort(std::vector<T>& arr) {
    _buildMaxHeap(arr);
    for(int i=arr.size()-1; i>=0; i--) {
        std::swap(arr[0], arr[i]);
        _heapify_maxheap(arr, i-1, 0);
    }
}

int main() {
    const int n_elem = 100;
    std::vector<int> arr = createRandomArray<int>(n_elem, 0, 50);
    std::vector<int> arr_truth {arr};
    std::sort(arr_truth.begin(), arr_truth.end());

    std::vector<int> cpy(arr);
    quicksort(cpy, 0, n_elem-1);
    checker(cpy, "Quicksort ");

    cpy = arr;
    mergesort(cpy, 0, n_elem-1);
    checker(cpy, "Mergesort ");

    cpy = arr;
    heapsort(cpy);
    checker(cpy, "Heapsort  ");
}