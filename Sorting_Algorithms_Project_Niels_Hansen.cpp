#include<iostream>
#include<iomanip>
using namespace std;
int partition(int arr[], int start, int end);

int getMax(int arr[],int n){
    int max = arr[0];
    for(int i=1; i<n; i++){
        if(arr[i]>max){
            max = arr[i];
        }
    }
    return max;
}

//CountSort
void countSort(int arr[], int n, int ex){
    int output[n];
    int i, count[10] = {0}; //10 assumed value

    for(i=0; i<n; i++){
        count[(arr[i]/ex) % 10]++;
    }
    for(i=1; i<10; i++){
        count[i] += count[i-1];
    }
    for(i=n-1; i>=0; i--){
        output[count[(arr[i]/ex)%10]-1] = arr[i];
        count[(arr[i]/ex)%10]--;
    }
    for(i=0;i<n;i++){
        arr[i]=output[i];
    }
}

//Random Partition
int RandomPivotPartition(int arr[], int start, int end){
    int pivot, n, temp;
    n = rand();
    pivot = start + n%(end - start+1);
    swap(arr[end], arr[pivot]);

    int x = partition(arr,start,end);
    return x;
}

//Partition
int partition(int arr[], int start, int end){
    int pivot = arr[start];
    int count = 0;
    for(int i = start+1; i<= end;i++){
        if(arr[i]<=pivot){
            count++;
        }
    }
    int pivotIndex = start + count;
    swap(arr[pivotIndex],arr[start]);

    int i = start, j = end;
    while(i<pivotIndex && j>pivotIndex){
        while(arr[i]<=pivot){
            i++;
        }
        while(arr[j]>pivot){
            j--;
        }
        if(i<pivotIndex && j>pivotIndex){
            swap(arr[i++],arr[j--]);
        }
    }
    return pivotIndex;
}

//Heapify
void heapify(int arr[], int n, int i){
    int largest = i,
        l = 2*i+1,
        r = 2*i+2;

        if(l<n && arr[l]>arr[largest]){
            largest = l;}
        if(r<n && arr[r]>arr[largest]){
            largest = r; 
        }
        if(largest != i){
            swap(arr[i], arr[largest]);
            heapify(arr, n, largest);
        }
}

//Merge
void merge(int arr[], int left, int mid, int right){
    auto subArrOne = mid - left + 1;
    auto subArrTwo = right - mid;

    auto *leftArr = new int[subArrOne],
         *rightArr = new int[subArrTwo];

    for(auto i=0; i<subArrOne; i++){
        leftArr[i] = arr[left+1];
    }
    for(auto j=0; j<subArrTwo; j++){
        rightArr[j]=arr[mid+1+j];
    }

    auto indexOfSubArrOne = 0,
         indexOfSubArrTwo = 0;
    int indexOfMergedArr = left;

    while(indexOfSubArrOne<subArrOne && indexOfSubArrTwo<subArrTwo){
        if(leftArr[indexOfSubArrOne]<= rightArr[indexOfSubArrTwo]){
            arr[indexOfMergedArr] = leftArr[indexOfSubArrOne];
            indexOfSubArrOne++;
        }
    else{
        arr[indexOfMergedArr] = rightArr[indexOfSubArrTwo];
        indexOfSubArrTwo++;
            }
    indexOfMergedArr++;
    }
    while(indexOfSubArrOne<subArrOne){
        arr[indexOfMergedArr] = leftArr[indexOfSubArrOne];
        indexOfSubArrOne++;
        indexOfMergedArr++;
    }
    while(indexOfSubArrTwo<subArrTwo){
        arr[indexOfMergedArr] = rightArr[indexOfSubArrTwo];
        indexOfSubArrTwo++;
        indexOfMergedArr++;
    }
    delete[]leftArr;
    delete[]rightArr;
}

//Print
void printArray(int arr[], int n){
    for(int i=0; i<n; i++){
        cout << arr[i] << " ";
    }
    cout << endl;
}

//Insertion Sort
void insertionSort(int arr[], int n){
    for(int i=1; i<n; i++){
        int key = arr[i];
        int j = i-1;

        while(key < arr[j] && j>=0){
            arr[j+1] = arr[j];
            --j;
        }
        arr[j+1] = key;
    }
}

//Merge Sort
void mergeSort(int arr[], int const begin, int const end){
    
    if(begin >= end)
        return;
    
    auto mid = (begin + end)/2;
    mergeSort(arr, begin, mid);
    mergeSort(arr, mid+1, end);

    merge(arr,begin,mid,end);
}

//Heap Sort
void heapSort(int arr[], int n){
    for(int i = n/2 -1; i>=0; i--){
        heapify(arr,n,i);
    }
    for(int i=n-1; i>0; i--){
        swap(arr[0],arr[i]);
        heapify(arr,i,0);
    }
}

//QuickSort
void quickSort(int arr[], int start, int end){
    if(start>=end)
        return;
    
    int p = partition(arr,start,end);
    quickSort(arr, start, p-1);
    quickSort(arr,p+1,end);
}
//Random Quick Sort
void randomQuickSort(int arr[], int start, int end){
    if(start>=end)
        return;
    
    int p = RandomPivotPartition(arr,start,end);
    quickSort(arr, start, p-1);
    quickSort(arr,p+1,end);
}
//Redix Sort
void radixSort(int arr[], int n){
    int m=getMax(arr,n);

    for(int exp=1; m/exp>0; exp*=10){
        countSort(arr,n,exp);
    }
}

int main(){
    int a = 1000000; //Size of Array
    int arr[a];// , sortArr[p], unsortArr[p]; // Array Declarations
    srand(time(0));

    //random array
    for(int i=0; i<a; i++){
        arr[i]= rand()%10000;
    }
    //Sorted Array
   /* for(int j=0; j<a; j++){
        sortArr[j]=j+1;
       // cout << sortArr[j] << " ";
    }
    //unsorted Array
    int x=a;
    for(int i=0; i<a; i++){
        unsortArr[i]=x;
        x--;
    }*/
    /*This sorted and unsorted arrays are to try cases like Insertion Sort's time complexity when the input 
    is sorted and unsorted*/
    
    //printArray(arr,n); // To Print the unsorted Array
    //cout << "\n";
    //Start Time
    auto  start = chrono::steady_clock::now();
    

    //insertionSort(arr,a);
    //mergeSort(arr,0,a-1);
    //heapSort(arr,a);
    quickSort(arr, 0, a-1);
    //randomQuickSort(arr,0,a-1);
    //radixSort(arr,a);

    
    //End Time
    auto  end = chrono::steady_clock::now();
    
    //Running Time
    double runningTime = double(chrono::duration_cast<chrono::nanoseconds> (end - start).count());

    //printArray(arr,n);
    cout << "\n";
    cout << "Running Time: " << fixed << runningTime/1e9 << " sec\n";
    return 0;
}