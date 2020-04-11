#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <algorithm>

using namespace std;

int recursiveFind(int* array, int left, int right, int element);
int nonrecursiveFind(int* array, unsigned size, int element);
void generateArray(int* array, unsigned size);
void printArray(int* array, unsigned size);

int main()
{
    const unsigned kSize = 20;
    int array[kSize];
    generateArray(array, kSize);
    std::sort(array, array + kSize);

    printf("Generated array:\n");
    printArray(array, kSize);

    int elementToFind;
    printf("Specify element to find: ");
    scanf("%d", &elementToFind);

    int rec_result = recursiveFind(array, 0, kSize - 1, elementToFind);
    int nrec_result= nonrecursiveFind(array, kSize, elementToFind);

    printf("Recursive result:     %d\n", rec_result);
    printf("Non-recursive result: %d\n", nrec_result);

    return 0;
}

int recursiveFind(int* array, int left, int right, int element)
{
    if (left == right)
    {
        if (array[left] == element)
            return left;
        else
            return -1;
    }

    int mid = (left + right) / 2;
    if (element > array[mid])
        return recursiveFind(array, mid + 1, right, element);
    else
        return recursiveFind(array, left, mid, element);
}

int nonrecursiveFind(int* array, unsigned size, int element)
{
    int left = 0, right = size - 1;
    while (left < right)
    {
        int mid = (left + right) / 2;
        if (element > array[mid])
            left = mid + 1;
        else
            right = mid;
    }
    if (array[left] == element) return left;
    return -1;
}

void generateArray(int* array, unsigned size)
{
    srand(time(nullptr));
    for (unsigned i = 0; i < size; ++i)
        array[i] = rand() % 50 - 20;
}

void printArray(int* array, unsigned size)
{
    for (unsigned i = 0; i < size; ++i)
        printf("%4d", array[i]);
    printf("\n");
}
