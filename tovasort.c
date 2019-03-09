/*
	Author: Elena Izotova
	Start Date: 11 April 2018
	Purpose: To show the differences between TovaSort and QuickSort
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void vanilla_tova_sort(int list[], int start, int end);
void tova_sort(int list[], int start, int end);
void vanilla_QS(int list[], int start, int end);
void print_array(int* arr, int size);

#define SIZE 10000000
int a_count = 0; //assignment count
int c_count = 0; //comparison count
int r_count = 0; //recursive call count

double run_test(void(*sorting_algorithm)(int*,int,int), int thickness) ;

int main(int argc, char* argv[])
{
	double tovasort_duration, qsort_duration, delta ;
	unsigned test_thickness_value = 10 ;

	printf("Unequivocal and objective demonstration of the efficiency of tovasort over qsort() from <stdlib.h> on ten random integer sets\n") ;

	printf("qsort():\n") ;
	qsort_duration = run_test(vanilla_QS,test_thickness_value) ;
	printf("tovasort:\n") ;
	tovasort_duration = run_test(tova_sort,test_thickness_value) ;

	delta = qsort_duration - tovasort_duration ;

	printf("tovasort beats quicksort by %lf seconds\n", delta) ;
	return 0 ;
}

double run_test(void(*sorting_algorithm)(int*,int,int), int thickness){

	int* numbers;
	int i; //iterator
	clock_t begin, end;
	double time_spent;
	numbers = malloc(sizeof(int)*SIZE);
	double slice_total = 0 ;

	for(unsigned slice = 0; slice < thickness; ++slice)
	{
		for (i = 0; i < SIZE; i++)
		{
			numbers[i] = (rand() << 15) + rand();
			//numbers[i] = rand();
		}
		printf("****\n");

		begin = clock();
		sorting_algorithm(numbers, 0, SIZE - 1);
		end = clock();

		//tests that the array is in sorted order (smallest to largest)
		for (i = 0; i < SIZE - 1; i++)
		{
			if (numbers[i] > numbers[i + 1])
			{
				printf("BAM %d %d %d\n", i, numbers[i], numbers[i + 1]);
				getchar();
			}
		}
		//printf("Done\n");
		slice_total += time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
		//printf("Time Spent = %.3f seconds\n", time_spent);


	}
	printf("Average sorting time of %d random sets of integers: %lf\n",
		thickness, slice_total/thickness) ;

	return slice_total/thickness ;
}


int int_compare(const void * p1, const void * p2) {
	return *(int*)p1 > *(int*)p2 ;
}

void vanilla_QS(int number[], int first, int last) {
	qsort(number,last + 1,sizeof(int),int_compare);
}

//similar to vanilla TS but modified to make less swaps with duplicate values
void tova_sort(int list[], int start, int end) {
	if ((end - start) < 1)return;
	int temp;
	int reference_value = list[start + (end - start) / 2];
	int left = start;
	int right = end;

	while (left <= right) {
		while (list[left] < reference_value) { left++; }
		while (list[right] > reference_value) { right--; }
		if (left < right) {
			temp = list[left];
			list[left] = list[right];
			list[right] = temp;
			left++;
			right--;
		}
		else if (left == right) {
			left++;
			right--;
		}
	}
	if (start < right) { tova_sort(list, start, right); }
	if (end > left) { tova_sort(list, left, end); }
}

void vanilla_tova_sort(int list[], int start, int end) {
	if ((end - start) < 1)return;

	int reference_value = list[start + (end - start) / 2];
	int left = start;
	int right = end;
	int temp;

	while (left <= right) {
		while (list[left] < reference_value) { left++; }
		while (list[right] > reference_value) { right--; }
		if (left <= right) {
			temp = list[left];
			list[left] = list[right];
			list[right] = temp;
			left++;
			right--;
		}
	}
	if (start < right) { vanilla_tova_sort(list, start, right); }
	if (end > left) { vanilla_tova_sort(list, left, end); }
}

void print_array(int* arr, int size) {
	int i;
	for (i = 0; i < size; i++) {
		printf("%d ", arr[i]);
	}
	printf("\n");
}//used to visualize swaps with smaller arrays
