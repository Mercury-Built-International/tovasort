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

int main(int argc, char* argv[])
{
	int* numbers;
	int i; //iterator
	clock_t begin, end;
	double time_spent;

	printf("Number of elements: %d\n", SIZE);
	//printf("Vanilla Tova Sort:\n");
	printf("Tova Sort:\n");
	//printf("Vanilla Quick Sort:\n");
	numbers = malloc(sizeof(int)*SIZE);
	while (1)
	{
		for (i = 0; i < SIZE; i++)
		{
			numbers[i] = (rand() << 15) + rand();
			//numbers[i] = rand();
		}
		printf("****\n");

		begin = clock();
		//vanilla_tova_sort(numbers, 0, SIZE - 1);
		tova_sort(numbers, 0, SIZE - 1);
		//vanilla_QS(numbers, 0, SIZE - 1);
		end = clock();

		//tests that the array is in sorted order (smallest to largest)
		for (i = 0; i < SIZE - 1; i++)
		{
			if (numbers[i] > numbers[i + 1])
			{
				printf("BAM %d %d %d\n", i, numbers[i], numbers[i + 1]);
				getch();
			}
		}
		printf("Done\n");
		time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
		printf("Time Spent = %.3f seconds\n", time_spent);

		//printf("r_count = %d\n", r_count); r_count = 0;
		//printf("a_count = %d\n", a_count); a_count = 0;
		//printf("c_count = %d\n", c_count); c_count = 0;
	}
	return 0;
}
void vanilla_QS(int number[], int first, int last) {
	int i, j, pivot, temp, mid;

	if (first<last) {
		//Median of Three modification
		mid = (first + last) / 2;
		if (number[last] < number[first]) {
			temp = number[first];
			number[first] = number[last];
			number[last] = temp;
		}
		if (number[mid] < number[first]) {
			temp = number[first];
			number[first] = number[mid];
			number[mid] = temp;
		}
		if (number[last] < number[mid]) {
			temp = number[mid];
			number[mid] = number[last];
			number[last] = temp;
		}

		pivot = first;
		i = first; //left sweeping index
		j = last; //right sweeping index

		while (i<j) {
			while (number[i] <= number[pivot] && i < last) { i++; }
			while (number[j] > number[pivot]) { j--; }
			if (i<j) {
				temp = number[i];
				number[i] = number[j];
				number[j] = temp;
			}
		}
		temp = number[pivot];
		number[pivot] = number[j];
		number[j] = temp;
		vanilla_QS(number, first, j - 1);
		vanilla_QS(number, j + 1, last);
	}
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