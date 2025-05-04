#include <bits/stdc++.h>
#include <iostream>
using namespace std;

void SelectionSort(int arr[], int n){
    for (int i = 0; i < n-1; i++)
    {
        int minIndex = i;
        for (int j = i+1; j < n; j++)
        {
            if(arr[j] < arr[minIndex]){
                minIndex = j;
            }
        }
        swap(arr[i], arr[minIndex]);
    }
}

void InsertionSort(int arr[], int n){
    for (int i = 1; i < n; i++)
    {
        int key = arr[i];
        int j = i-1;
        while (j >= 0 && arr[j] > key)
        {
            arr[j+1] = arr[j];
            j--;
        }
        arr[j+1] = key;
    }
}

void BubbleSort(int arr[], int n){
    for (int i = 0; i < n-1; i++)
    {
        for (int j = 0; j < n-i-1; j++)
        {
            if(arr[j] > arr[j+1]){
                swap(arr[j], arr[j+1]);
            }
        }
    }
}

void Merge(int arr[], int l, int m, int r){
    int n1 = m - l + 1;
    int n2 = r - m;
    int L[n1], R[n2];
    for (int i = 0; i < n1; i++)
    {
        L[i] = arr[l + i];
    }
    for (int j = 0; j < n2; j++)
    {
        R[j] = arr[m + 1 + j];
    }
    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2)
    {
        if(L[i] <= R[j]){
            arr[k++] = L[i++];
        }else{
            arr[k++] = R[j++];
        }
    }
    while (i < n1)
    {
        arr[k++] = L[i++];
    }
    while (j < n2)
    {
        arr[k++] = R[j++];
    }
}

void MergeSort(int arr[], int l, int r){
    if(l < r){
        int m = l + (r - l) / 2;
        MergeSort(arr, l, m);
        MergeSort(arr, m + 1, r);
        Merge(arr, l, m, r);
    }
}

void QuickSort(int arr[], int low, int high){
    if(low < high){
        int pivot = arr[high];
        int i = low - 1;
        for (int j = low; j < high; j++)
        {
            if(arr[j] < pivot){
                i++;
                swap(arr[i], arr[j]);
            }
        }
        swap(arr[i+1], arr[high]);
        int pi = i + 1;
        QuickSort(arr, low, pi-1);
        QuickSort(arr, pi+1, high);
    }
}

void Heapify(int arr[], int n, int i){
    int largest = i;
    int left = 2*i + 1;
    int right = 2*i + 2;
    if(left < n && arr[left] > arr[largest]){
        largest = left;
    }
    if(right < n && arr[right] > arr[largest]){
        largest = right;
    }
    if(largest != i){
        swap(arr[i], arr[largest]);
        Heapify(arr, n, largest);
    }
}

void HeapSort(int arr[], int n){
    for (int i = n/2 - 1; i >= 0; i--)
    {
        Heapify(arr, n, i);
    }
    for (int i = n-1; i >= 0; i--)
    {
        swap(arr[0], arr[i]);
        Heapify(arr, i, 0);
    }
}

void CountingSort(int arr[], int n, int k){
    int count[k+1] = {0};
    for (int i = 0; i < n; i++)
    {
        count[arr[i]]++;
    }
    for (int i = 1; i <= k; i++)
    {
        count[i] += count[i-1];
    }
    int output[n];
    for (int i = n-1; i >= 0; i--)
    {
        output[count[arr[i]]-1] = arr[i];
        count[arr[i]]--;
    }
    for (int i = 0; i < n; i++)
    {
        arr[i] = output[i];
    }
}

void RadixSort(int arr[], int n){
    int maxVal = *max_element(arr, arr+n);
    for (int exp = 1; maxVal/exp > 0; exp *= 10)
    {
        CountingSort(arr, n, maxVal);
    }
}

void BucketSort(float arr[], int n){
    vector<float> buckets[n];
    for (int i = 0; i < n; i++)
    {
        int index = n * arr[i];
        buckets[index].push_back(arr[i]);
    }
    for (int i = 0; i < n; i++)
    {
        sort(buckets[i].begin(), buckets[i].end());
    }
    int index = 0;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < buckets[i].size(); j++)
        {
            arr[index++] = buckets[i][j];
        }
    }
}

void ShellSort(int arr[], int n){
    for (int gap = n/2; gap > 0; gap /= 2)
    {
        for (int i = gap; i < n; i++)
        {
            int temp = arr[i];
            int j;
            for (j = i; j >= gap && arr[j-gap] > temp; j -= gap)
            {
                arr[j] = arr[j-gap];
            }
            arr[j] = temp;
        }
    }
}

int main(){
    vector<int> arr = {3, 4, 4, 7, 8, 10};
    sort(arr.begin(), arr.end());
    for(auto it: arr){
        cout<<it<<" ";
    }
    cout<<endl;
    int target = 8;
    auto it = lower_bound(arr.begin(), arr.end(), target);
    if(it != arr.end()){
        if(arr[it-arr.begin()]>target){
            cout<<"Floor: "<<arr[it-arr.begin()-1]<<endl;
        }
        else{
            cout<<"Floor: "<<arr[it-arr.begin()]<<endl;
        }
        cout<<"Ceil: "<<arr[it-arr.begin()]<<endl;
    }
}
