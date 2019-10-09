#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TRUE 1
#define FALSE 0
#define MIN_SIZE 3
#define MAX_SIZE 1000
#define MIN_VALUE_ELEMENT 1
#define MAX_VALUE_ELEMENT 1000000000
#define MAX_VALUE_SUM 3000000000
typedef unsigned int uint;

void randomArray(uint *array, const uint size_of_array);
void printArray(int *array, const uint size_of_array);
int binarySearch(const int *array, int leftIndex, int rightIndex, const int value);
void quickSort(int *array, int leftIndex, int rightIndex);
int loveStory(uint *array, const uint size_of_array, const uint value, const uint count);
int main()
{
	int size_of_array = MAX_SIZE;
	int value = 20;
	const int countElementsInSum = 3;
	uint *array = (uint*)calloc(size_of_array, sizeof(uint));
	randomArray(array, size_of_array);
	int result = loveStory(array, size_of_array, value, countElementsInSum);
	result == TRUE ? printf("\nYES\n") : printf("\nNO\n");
	free(array);
	array = NULL;
	system("pause");
	return 0;
}

void printArray(int *array, const uint size_of_array)
{
	for (int i = size_of_array - 1; i >= 0; ++i) {
		printf("%d\t", array[i]);
	}
	printf("\n");
}

void randomArray(uint *array, const uint size_of_array)
{
	srand(time(NULL));
	for (int i = 0; i < size_of_array; ++i) {
		array[i] = rand()%100 + 1;
		
	}
}

int binarySearch(const int *array, int leftIndex, int rightIndex, const int value)
{
	int middleIndex = (leftIndex + rightIndex) >> 1;
	if (rightIndex < leftIndex)
		return middleIndex;
	if (array[middleIndex] > value)
		return binarySearch(array, leftIndex, middleIndex - 1, value);
	else if (array[middleIndex] < value)
		return binarySearch(array, middleIndex + 1, rightIndex, value);
	else
		return middleIndex;
}

void quickSort(int *array, int leftIndex, int rightIndex)
{
	if (leftIndex > rightIndex)
		return;
	int  i = leftIndex;
	int  j = rightIndex;
	int baseElement = array[leftIndex];
	do {
		while (array[i] < baseElement)
			++i;
		while (array[j] > baseElement)
			--j;
		if (i <= j) {
			if (i < j) {
				int temp = array[i];
				array[i] = array[j];
				array[j] = temp;
			}
			++i;
			--j;
		}
	} while (i <= j);
	quickSort(array, i, rightIndex);
	quickSort(array, leftIndex, j);
	return;
}

struct Pair {
	int value;
	int index;
};

int loveStory(uint *array, const uint size_of_array, const uint sum, const uint countElements)
{
	quickSort(array, 0, size_of_array - 1);
	int indexFirst = binarySearch(array, 0, size_of_array - 1, sum - 1);
	if (indexFirst == -1)//всі елементи більші за value
		return FALSE;
	struct Pair *elements = (struct Pair*)calloc(countElements, sizeof(struct Pair));
	elements->index = indexFirst;
	while (elements->index >= MIN_SIZE - 1) {
		elements->value = array[elements->index];
		for (int i = 1; i < countElements; ++i){
			elements[i].value = sum;
			for (int k = 0; k < i; ++k)
				elements[i].value -= elements[k].value;
			if (i < countElements - 1)
				--elements[i].value;
			elements[i].index = binarySearch(array, 0, elements[i - 1].index - 1, elements[i].value);
			if (elements[i].index == -1)
				break;
			if ((i == countElements - 1) && elements[i].value == array[elements[i].index]) {
				free(elements);
				return TRUE;
			}
			elements[i].value = array[elements[i].index];
		}
		--(elements->index);
	}
	free(elements);
	return FALSE;
}

