#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX (1000)

char* replaceWord(const char* s, const char* oldW,
                  const char* newW){
    char* result;
    int i, cnt = 0;
    int newWlen = strlen(newW);
    int oldWlen = strlen(oldW);
  
    // Counting the number of times old word
    // occur in the string
    for (i = 0; s[i] != '\0'; i++) {
        if (strstr(&s[i], oldW) == &s[i]) {
            cnt++;
  
            // Jumping to index after the old word.
            i += oldWlen - 1;
        }
    }
  
    // Making new string of enough length
    result = (char*)malloc(i + cnt * (newWlen - oldWlen) + 1);
  
    i = 0;
    while (*s) {
        // compare the substring with the result
        if (strstr(s, oldW) == s) {
            strcpy(&result[i], newW);
            i += newWlen;
            s += oldWlen;
        }
        else
            result[i++] = *s++;
    }
  
    result[i] = '\0';
    return result;
}

int split (const char *txt, char delim, char ***tokens){
    int *tklen, *t, count = 1;
    char **arr, *p = (char *) txt;

    while (*p != '\0') if (*p++ == delim) count += 1;
    t = tklen = calloc (count, sizeof (int));
    for (p = (char *) txt; *p != '\0'; p++) *p == delim ? *t++ : (*t)++;
    *tokens = arr = malloc (count * sizeof (char *));
    t = tklen;
    p = *arr++ = calloc (*(t++) + 1, sizeof (char *));
    while (*txt != '\0')
    {
        if (*txt == delim)
        {
            p = *arr++ = calloc (*(t++) + 1, sizeof (char *));
            txt++;
        }
        else *p++ = *txt++;
    }
    free (tklen);
    return count;
}

int readInput(FILE* filePointer,int* input){
   int bufferLength = 4000;
   char buffer[bufferLength];
   char **numbers;
   int i=0;
   int sum=0;
   fgets(buffer, bufferLength, filePointer);
   int nPoints=split (buffer, ',', &numbers);
   for (int i=0; i<nPoints; i++){
	input[i]=atoi(numbers[i]);
	sum+=input[i];
   }
   
   return sum;
}

void merge(int arr[], int l, int m, int r){
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;
  
    /* create temp arrays */
    int L[n1], R[n2];
  
    /* Copy data to temp arrays L[] and R[] */
    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];
  
    /* Merge the temp arrays back into arr[l..r]*/
    i = 0; // Initial index of first subarray
    j = 0; // Initial index of second subarray
    k = l; // Initial index of merged subarray
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        }
        else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }
  
    /* Copy the remaining elements of L[], if there
    are any */
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }
  
    /* Copy the remaining elements of R[], if there
    are any */
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}
  

void mergeSort(int arr[], int l, int r){
    if (l < r) {
        // Same as (l+r)/2, but avoids overflow for
        // large l and h
        int m = l + (r - l) / 2;
  
        // Sort first and second halves
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);
  
        merge(arr, l, m, r);
    }
}

void printArray(int A[]){
    int i;
    for (i = 0; i < MAX; i++)
        printf("%d ", A[i]);
    printf("\n");
}


int fuelSpent(int* input, int median){
	int fuel=0;
	for(int i=0; i<MAX; i++)
		fuel+=abs(input[i]-median);
	
	return fuel;
}

int fuelSpent2(int* input, int media){
	int fuel=0;
	for(int i=0; i<MAX; i++){
		int val =abs(input[i]-media);
		fuel+=(val*(val+1))/2;
	}
	
	return fuel;
}

int main() {
   int input[MAX]={-1};
   FILE* filePointer;
   filePointer = fopen("input_day7", "r");
   int sum=readInput(filePointer,input);
   fclose(filePointer); 

   mergeSort(input, 0, MAX-1);
   int media=sum/MAX;
   int median=((MAX+1)/2) -1;

   int fuel = fuelSpent(input, input[median]);
   int fuel2 = fuelSpent2(input, media);
   //printInput(input);

   printf("prima stella: %d\n",fuel);
   
   printf("seconda stella: %d\n",fuel2);
   return 0;
}
