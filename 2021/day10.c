#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#define MAX (110)

int incMax=0;
int corMax=0;

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

char* checkString(char* string){
	int redo=0;
	if (strstr(string,"()")!=NULL){
		string=replaceWord(string,"()","");
		redo=1;
	}
	if (strstr(string,"[]")!=NULL){
		string=replaceWord(string,"[]","");
		redo=1;
	}
	if (strstr(string,"{}")!=NULL){
		string=replaceWord(string,"{}","");
		redo=1;
	}
	if (strstr(string,"<>")!=NULL){
		string=replaceWord(string,"<>","");
		redo=1;
	}
	if(redo) return checkString(string);
	return string;
}


void readInput(FILE* filePointer, char* incomplete[MAX],char* corrupted[MAX]){
   int bufferLength = 256;
   char buffer[bufferLength];
   int i=0;
   int len=0;
   
   while(fgets(buffer, bufferLength, filePointer)) {
	   
	  char* s=checkString(buffer);
	  if (	(strstr(s,")")!=NULL)||
			(strstr(s,"]")!=NULL)||
			(strstr(s,"}")!=NULL)||
			(strstr(s,">")!=NULL)){
			corrupted[corMax++]=s;
			}
	  else {
		incomplete[incMax++]=s;
	  }
	  
	  i++;
	  if (i==MAX) break;
   }
}


void merge(unsigned long arr[], int l, int m, int r){
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;
  
    /* create temp arrays */
    unsigned long L[n1], R[n2];
  
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
  
void mergeSort(unsigned long arr[], int l, int r){
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

void printMatrix(char* matrix[MAX], int max){
	for (int i=0; i<max; i++)
		printf("%s\n",matrix[i]);
	
}

int sumCorrupted(char* matrix[MAX], int max){
	int sum=0;
	for (int i=0; i<max; i++)
	{
		for (int j=0; j<(int)strlen(matrix[i]); j++){
			if(matrix[i][j]==')'){
				sum+=3;
				break;
			}
			if(matrix[i][j]==']'){
				sum+=57;
				break;
			}
			if(matrix[i][j]=='}'){
				sum+=1197;
				break;
			}
			if(matrix[i][j]=='>'){
				sum+=25137;
				break;
			}
		}
	}
	
	return sum;
}

void sumIncomplete(char* matrix[MAX], int max,unsigned long *result){
	for (int i=0; i<max; i++)
	{
		unsigned long sum=0;
		int len=(int)strlen(matrix[i]);
		char complete[len];
		//if (i==0) printf("%s\t%d\n",matrix[i],len);
		for (int j=len-1; j>=0; j--)
		{
			if(	(matrix[i][j]!='(') &&
				(matrix[i][j]!='[') &&	
				(matrix[i][j]!='{') &&	
				(matrix[i][j]!='<') ) continue;
			
			//if (i==0) printf("char di %d:%c\n",j,matrix[i][j]);
			sum*=5;
			if(matrix[i][j]=='(') sum+=1;
			if(matrix[i][j]=='[') sum+=2;
			if(matrix[i][j]=='{') sum+=3;
			if(matrix[i][j]=='<') sum+=4;
			//if (i==0) printf("sum2 %lu",sum);
		}
	
		result[i]=sum;
		//printf("%lu\n",sum);
	}
}

int main() {
   char* incomplete[MAX];
   char* corrupted[MAX];
   FILE* filePointer;
   filePointer = fopen("input_day10", "r");
   readInput(filePointer,incomplete,corrupted);
   fclose(filePointer); 
   //printf("corr:%d\tinc:%d\n",corMax,incMax);
   int s1=sumCorrupted(corrupted,corMax);
   printf("prima stella: %d\n",s1);
   
   unsigned long s2[incMax];
   sumIncomplete(incomplete,incMax,s2);
   mergeSort(s2,0,incMax);
   int middle=(incMax/2)+1;
   printf("seconda stella: %lu\n",s2[middle]);
   return 0;
}
