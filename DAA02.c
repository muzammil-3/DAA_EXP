#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<limits.h>

unsigned long long noOfComparison1,noOfComparison2;


void quickSort(int arr[], int left, int right,int *qs_compares) {  
  if (left < right) {
    int pivot = arr[right];
    int i = left - 1;
    for (int j = left; j < right; j++) {
      (*qs_compares)++;  
      if (arr[j] < pivot) {
        i++;
        int temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
      }
    }
    int temp = arr[i + 1];
    arr[i + 1] = arr[right];
    arr[right] = temp;

    int p = i + 1; // p is the pivot element

    quickSort(arr, left, p - 1,qs_compares);
    quickSort(arr, p + 1, right,qs_compares);
  }
}

void merge(int arr[], int l, int m, int r)
{
	int i, j, k;
	int n1 = m - l + 1;
	int n2 = r - m;
 
	// Create temp arrays
	int L[n1], R[n2];
 
	// Copy data to temp arrays
	// L[] and R[]
	for (i = 0; i < n1; i++)
    	L[i] = arr[l + i];
	for (j = 0; j < n2; j++)
    	R[j] = arr[m + 1 + j];
 
	// Merge the temp arrays back
	// into arr[l..r]
	// Initial index of first subarray
	i = 0;
 
	// Initial index of second subarray
	j = 0;
 
	// Initial index of merged subarray
	k = l;
	while (i < n1 && j < n2)
	{
		noOfComparison2++;
    	if (L[i] <= R[j])
    	{
        	arr[k] = L[i];
        	i++;
    	}
    	else
    	{
        	arr[k] = R[j];
        	j++;
    	}
    	k++;
	}
 
	// Copy the remaining elements
	// of L[], if there are any
	while (i < n1) {
    	arr[k] = L[i];
    	i++;
    	k++;
	}
 
	// Copy the remaining elements of
	// R[], if there are any
	while (j < n2)
	{
    	arr[k] = R[j];
    	j++;
    	k++;
	}
}

void mergeSort(int arr[], int l, int r)
{
	noOfComparison2=0;
	if (l < r)
	{
    	// Same as (l+r)/2, but avoids
    	// overflow for large l and h
    	int m = l + (r - l) / 2;
 
    	// Sort first and second halves
    	mergeSort(arr, l, m);
    	mergeSort(arr, m + 1, r);
 
    	merge(arr, l, m, r);
	}
}


void main() {

unsigned long long noOfComparison_quickSort,noOfCompariosn_mergeSort;

	FILE *fp;
	fp  = fopen ("EXP2.txt", "w");
	srand((unsigned int) time(NULL));
	for(int block=0;block<1000;block++) {
    	for(int i=0;i<100;i++) {
        	int number = (int)(((float) rand() / (float)(RAND_MAX))*100000);
        	fprintf(fp,"%d ",number);
    	}
    	fputs("\n",fp);
	}
	fclose (fp);
   fp = fopen("EXP2.txt", "r");
   printf("Block\tQUICK SORT\tMERGE SORT \t No of Comparison in QuickSort \t No of Comparison in MergeSort \n");
   for(int block=0;block<1000;block++) {
       
	clock_t t1,t2;
	int arr[(block+1)*100];
	int arr1[(block+1)*100];
	int qs_compares = 0;
	for(int i=0;i<(block+1)*100;i++){
    	fscanf(fp, "%d", &arr[i]);
    	arr1[i] = arr[i];
	}
	fseek(fp, 0, SEEK_SET);
    
	//CALLING QUICKSORT
	t1 = clock();   
	int size = sizeof(arr) / sizeof(arr[0]);
	quickSort(arr, 0, size - 1, &qs_compares);
	//noOfComparison_quickSort = noOfComparison1;
	t1 = clock() - t1;
	double quick_sort_time = ((double)t1)/CLOCKS_PER_SEC;
	
    
    
	t2 = clock();
	size = sizeof(arr1) / sizeof(arr1[0]);
	mergeSort(arr1, 0, size - 1);
	noOfCompariosn_mergeSort = noOfComparison2;
	t2 = clock() - t2;
	double merge_sort_time = ((double)t2)/CLOCKS_PER_SEC;
	

	printf("%d \t %f \t %f%26d%26llu\n",(block+1),quick_sort_time,merge_sort_time,qs_compares,noOfCompariosn_mergeSort);
   }
	fclose(fp);
}
