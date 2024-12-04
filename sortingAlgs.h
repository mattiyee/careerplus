#include <iostream>
#include <vector>
#include <string>
#include <chrono>

using namespace std;

void merge(vector<string>& courses, int left, int mid, int right){
    //sizes of two subarrarys to be merged;

    int leftSideLength = mid - left + 1;
    int rightSideLength = right - mid;

    //temp vectors
    vector<string> leftArray(leftSideLength);
    vector<string> rightArray(rightSideLength);

    //copy data to temporary vectors
    for(int i = 0; i < leftSideLength; i++){
        leftArray[i] = courses[left + i];
    }
    for(int j = 0; j < rightSideLength; j++){
        rightArray[j] = courses[mid + 1 + j];
    }

    //merge the temp arrays back into courses (the og vector)
    int i = 0;
    int j = 0;
    int k = left;

    while(i < leftSideLength and j < rightSideLength){
        if(leftArray[i] <= rightArray[j]){
            courses[k] = leftArray[i];
            i++;
        }
        else{
            courses[k] = rightArray[j];
            j++;
        }
        k++;
    }

    //copy remaining elements of the left array if there's any left
    while(i < leftSideLength){
        courses[k] = leftArray[i];
        i++;
        k++;
    }

    //copy remaining elements of the right array if there's any left
    while(j < rightSideLength){
        courses[k] = rightArray[j];
        j++;
        k++;
    }
}

//call mergeSort(vector to be sorted, 0, size of vector - 1)
void mergeSort(vector<string>& courseCodes, int left, int right){
    if (left < right){
        //find the middle point
        int mid = left + (right - left) / 2;

        //sort first and second halves
        mergeSort(courseCodes, left, mid);
        mergeSort(courseCodes, mid + 1, right);

        //merge the sorted halves
        merge(courseCodes, left, mid, right);
    }
}

int partition(vector<string>& courseCodes, int low, int high){
    //pivot element
    string pivot = courseCodes[high];

    //index of smaller element, indicates the right position of pivot found so far
    int smallIndex = low - 1;

    //traverse array and move all smaller elements to the left.
    // elements from low to the smaller index should get smaller after every iteration
    for(int j = low; j < high; j++){
        //if current element is smaller than or equal to the pivot
        if(courseCodes[j] <= pivot){
            smallIndex++;
            swap(courseCodes[smallIndex], courseCodes[j]);
        }
    }

    //swap the pivot element with the element at i+1 and then return its partition
    swap(courseCodes[smallIndex + 1], courseCodes[high]);

    return smallIndex + 1;
}

//call quickSort(vector to be sorted, 0, size of vector - 1)
void quickSort(vector<string>& courseCodes, int low, int high){
    if(low < high){
        //partition the array and get the partition index
        int partitionIndex = partition(courseCodes, low, high);

        //recursively sort the subarrays
        quickSort(courseCodes, low, partitionIndex - 1);
        quickSort(courseCodes, partitionIndex + 1, high);
    }
}

void printCodes(vector<string>& courseCodes){
    for(const auto& code: courseCodes){
        cout << code << endl;
    }
}

void measureAndSort(vector<string>& courseCodes){

    //clone the original vector for testing both algorithms
    auto coursesMergeSort = courseCodes;
    auto coursesQuickSort = courseCodes;

    //Measure time for merge sort
    auto startMergeSort = chrono::high_resolution_clock::now();
    mergeSort(coursesMergeSort, 0, coursesMergeSort.size() - 1);
    auto endMergeSort = chrono::high_resolution_clock::now();

    //calculate the elapsed time for merge sort
    auto mergeSortDuration = chrono::duration_cast<chrono::microseconds>(endMergeSort - startMergeSort);

    //measure time for quick sort
    auto startQuickSort = chrono::high_resolution_clock::now();
    mergeSort(coursesQuickSort, 0, coursesQuickSort.size() - 1);
    auto endQuickSort = chrono::high_resolution_clock::now();

    //calculate the elapsed time for merge sort
    auto quickSortDuration = chrono::duration_cast<chrono::microseconds>(endQuickSort - startQuickSort);
    string fasterSortingAlg;

    if(quickSortDuration > mergeSortDuration){
        printCodes(coursesQuickSort);
        fasterSortingAlg = "Quick Sort";
        cout << endl << "Sorted in " << quickSortDuration.count() << " ms using " << fasterSortingAlg << endl;
    }
    else if(quickSortDuration > mergeSortDuration){
        printCodes(coursesMergeSort);
        fasterSortingAlg = "Merge Sort";
        cout << endl << "Sorted in " << mergeSortDuration.count() << " ms using " << fasterSortingAlg << endl;
    }

}




