#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX (1000000)
#define DAYS (80)

int nArray=0;

char* replaceWord(const char* s, const char* oldW,
                  const char* newW)
{
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

int split (const char *txt, char delim, char ***tokens)
{
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

unsigned long readInput(FILE* filePointer,short input[MAX][MAX]){
   int bufferLength = 1000;
   char buffer[bufferLength];
   char **numbers;
   int i=0;
   
   fgets(buffer, bufferLength, filePointer);
   unsigned long nFisches=split (buffer, ',', &numbers);
   for (int i=0; i<nFisches; i++){
	input[nArray][i]=atoi(numbers[i]);
   }
   
   return nFisches;
}

void printInput(short input[MAX][MAX], unsigned long nFisches){
	for (int i=0; i<nFisches; i++){
		printf("pesce: %d\t",input[nArray][i]);
	}
}

void countFishes(short input[MAX][MAX],unsigned long* nFisches){
	int currentFishes=(*nFisches);
	for (int i=0; i<currentFishes; i++) {
		if(input[nArray][i]==-1) break;
		if(input[nArray][i]==0){
			input[nArray][i]=6;
			input[nArray][(*nFisches)++]=8;
		}
		else input[nArray][i]--;
	}
}


int main() {
   short input[MAX][MAX]={-1};
   printf("1");
   FILE* filePointer;
   filePointer = fopen("input_day6", "r");
   unsigned long nFisches=readInput(filePointer,input);
   fclose(filePointer); 
   
   //printInput(input);
   for (int d=0; d<DAYS; d++)
   {
	   printf("%d iter: %lu\n",d,nFisches);
	   countFishes(input,&nFisches);
   }
   printf("prima stella: %lu\n",nFisches);
   
   //printf("seconda stella: %d\n",output);
   return 0;
}
