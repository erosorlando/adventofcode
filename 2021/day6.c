#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX (9)
#define DAYS (256)

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

unsigned long readInput(FILE* filePointer,unsigned long input[2][MAX]){
   int bufferLength = 1000;
   char buffer[bufferLength];
   char **numbers;
   int i=0;
   
   fgets(buffer, bufferLength, filePointer);
   unsigned long nFisches=split (buffer, ',', &numbers);
   for (int i=0; i<nFisches; i++){
	  int index=atoi(numbers[i]); 
	  input[0][index]++;
	  input[1][index]++;
   }
   
   return nFisches;
}

void printInput(unsigned long input[2][MAX]){
	for (int i=0; i<MAX; i++){
		printf("pesce: %lu\t",input[0][i]);
	}
	printf("\n");
}

void countFishes(unsigned long input[2][MAX],unsigned long* nFisches){
	for (int i=MAX-1;i>=0; i--){
		if(i==0){
			input[1][6]+=input[0][i];
			input[1][MAX-1]=input[0][i];
			(*nFisches)+=input[0][i];
		}
		else input[1][i-1]=input[0][i];
	}
	for (int i=0; i<MAX; i++){
		input[0][i]=input[1][i];
	}
}


int main() {
   unsigned long input[2][MAX]={0};
   printf("1");
   FILE* filePointer;
   filePointer = fopen("input_day6", "r");
   unsigned long nFisches=readInput(filePointer,input);
   fclose(filePointer); 
   
   
   for (int d=0; d<DAYS; d++){
	   countFishes(input,&nFisches);
	   //printInput(input);
   }
   printf("prima stella: %lu\n",nFisches);
   
   //printf("seconda stella: %d\n",output);
   return 0;
}
