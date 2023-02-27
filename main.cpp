// List Matching problem
// In this code, the cpommon elements in two given list are found
// Firts, both listed are sorted based on the merge sort.
// Then the binary search is used to compare and find the common elements
// wihtin two lists

// @ Reza Roofegari nejad

#include <iostream>
#include <vector>

using namespace std;

/*---------------------------------------------------------------
Declare functions
----------------------------------------------------------------*/
void print_array(int arr[], int arr_size);

/*---------------------------------------------------------------
Helper function to print an array
----------------------------------------------------------------*/
void print_array(int arr[], int arr_size)
{
    for (int i = 0; i < arr_size; i++)
    {
        cout << arr[i] << " ";
    }
}

/*---------------------------------------------------------------
Helper function to print a vector
----------------------------------------------------------------*/
void print_vector(vector<int> vec)
{
    for (int i = 0; i < vec.size(); i++)
    {
        cout << vec[i] << " ";
    }
}


/*---------------------------------------------------------------
merge function
----------------------------------------------------------------*/
void merge(int arr[],
int const left,
int const mid,
int const right)
{
    // size of sub arrays
    // Note: not add 1 to the size of the sub array 2
    // since the mid is on the side of the sub array one.
    int size_sub_array_left = mid - left + 1;
    int size_sub_array_right = right - mid;
    
    // Create temp sub arrays
    int *sub_array_left = new int[size_sub_array_left];
    int *sub_array_right = new int[size_sub_array_right];
    
    // copy data to temp array left
    for (int i = 0; i < size_sub_array_left; i++)
    {
        sub_array_left[i] = arr[left + i];
    }
    
    // copy data to temp array right
    for (int i = 0; i < size_sub_array_right; i++)
    {
        sub_array_right[i] = arr[mid + 1 + i];
    }
    
    // temp indeces for both sub arrays
    int ind1 = 0;
    int ind2 = 0;
    int ind_merge = left;
    
    
    while (ind1 < size_sub_array_left && ind2 < size_sub_array_right)
    {
        if (sub_array_left[ind1] <= sub_array_right[ind2])
        {
            arr[ind_merge] = sub_array_left[ind1];
            ind1++;
        }
        else
        {
            arr[ind_merge] = sub_array_right[ind2];
            ind2++;
        }
        
        ind_merge++;
    }
    
    // copy remaining of the sub array left to the original array if anything left
    while (ind1 < size_sub_array_left)
    {
        arr[ind_merge] = sub_array_left[ind1];
        ind1++;
        ind_merge++;
    }
    
    // copy remaining of the sub array right to the original array if anything left
    while (ind2 < size_sub_array_right)
    {
        arr[ind_merge] = sub_array_right[ind2];
        ind2++;
        ind_merge++;
    }
    
    
    // delete sub arrays from the heap memory to prevent memory leak
    delete[] sub_array_left;
    delete[] sub_array_right;
}

/*---------------------------------------------------------------
helper merge sort function
----------------------------------------------------------------*/
void merge_sort_sort(int arr[], int start, int end)
{
    // recurrsive check
    if (start >= end)
    {
        return;
    }
    
    int mid = start + (end-start)/2;
    
    // first half recurrsive call
    merge_sort_sort(arr, start, mid);
    
    // second half recurrsive call
    merge_sort_sort(arr, mid+1, end);
    
    // merge function
    merge(arr, start, mid, end);
    
}


/*---------------------------------------------------------------
Merge sort function
----------------------------------------------------------------*/
void merge_sort(int arr[], int arr_size)
{
    int start = 0;
    int end = arr_size - 1;
    
    merge_sort_sort(arr, start, end);
}

/*---------------------------------------------------------------
Binary search recurrsive search function
 
 @ arr      array to search
 @ left     left of the subsection array to search
 @ left     right of the subsection array to search
 @ x        element to find in the array
----------------------------------------------------------------*/
int binary_search_search(int arr[],
                         int left,
                         int right,
                         int x)
{
    // base case that cannot find the element
    if (right < left)
    {
        return -1;
    }
    
    int result;
    int mid = (left+right) / 2;
    
    // check element in the array mid point
    if (x == arr[mid])
    {
        return mid;
    }
    
    if (x < arr[mid])
    {
        // recurrsive call on the left side
        result = binary_search_search(arr, left, mid - 1, x);
    }
    else
    {
        // recurrsive call on the right side
        result = binary_search_search(arr, mid + 1, right, x);
    }
    
    return result;

}
/*---------------------------------------------------------------
Binary search main function
 
 @ arr      array to search
 @ size     size of the array
 @ x        element to find in the array
----------------------------------------------------------------*/
int binary_search(int arr[], int size, int x)
{
    int index = -1;
    
    // recurrsive binary search
    index = binary_search_search(arr, 0, size, x);
    
    return index;
}

/*---------------------------------------------------------------
Binary search main function
 
 @ arr      array to search
 @ size     size of the array
 @ x        element to find in the array
----------------------------------------------------------------*/
void list_matching(vector<int> *common_arr,
int arr1[],
int arr2[],
int arr1_size,
int arr2_size)
{
    int result = -1;

    for (int ind = 0; ind < arr1_size; ind++)
    {
        result = binary_search(arr2, arr2_size, arr1[ind]);
        
        if (result > 0)
        {
            (*common_arr).push_back(arr1[ind]);
        }
    }
    
}

/*---------------------------------------------------------------
main function
----------------------------------------------------------------*/
int main()
{
    vector<int> arr_common;
    
    // array 1
    int arr1[] = {12, 11, 8, 13, 5, 6, 7, 1, 10, 60, 100, 200, 256, 4};
    int arr1_size = sizeof(arr1) / sizeof(arr1[0]);
    
    // array 2
    int arr2[] = {10, 5, 7, 8, 100, 40, 41, 58, 1};
    int arr2_size = sizeof(arr2) / sizeof(arr2[0]);
    
    // sort both arrays
    // array 1
    merge_sort(arr1, arr1_size);
    merge_sort(arr2, arr2_size);
    
    list_matching(&arr_common, arr1, arr2, arr1_size, arr2_size);
    
    cout << " common element in the given arrays are: \n";
    print_vector(arr_common);
    cout << endl;
    
    return 0;
}



