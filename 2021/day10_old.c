#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX (110)


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

void readInputCByC(FILE* filePointer, int input[MAX][MAX]){
   int bufferLength = 256;
   char buffer[bufferLength];
   int i=0;
   int len=0;
   
   while(fgets(buffer, bufferLength, filePointer)) {
	   printf("%s\n",buffer);
	  //if(strlen(buffer)!=MAX+1)  continue;
	  for(int j=0; j<MAX; j++){
		  if (buffer[j]=='\r' || buffer[j]=='\n') break;
		  switch( buffer[j] ){
			case '(':
				input[i][j]=1;
				break;
			case ')':
				input[i][j]=2;
				break;
			case '[':
				input[i][j]=3;
				break;
			case ']':
				input[i][j]=4;
				break;
			case '{':
				input[i][j]=5;
				break;
			case '}':
				input[i][j]=6;
				break;
			case '<':
				input[i][j]=7;
				break;
			case '>':
				input[i][j]=8;
				break;
			default:
				input[i][j]=-1;
				break;
		  }
	  }
	  
	  i++;
	  if (i==MAX) break;
   }
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

void printMatrix(int done[MAX][MAX]){
	for (int i=0; i<MAX; i++){
		printf("row %d\t",i);
		for (int j=0; j<MAX; j++)
			printf("%d ",done[i][j]);
		printf("\n");
	}
}

void resetMatrix(int done[MAX][MAX]){
	for (int i=0; i<MAX; i++)
		for (int j=0; j<MAX; j++)
			done[i][j]=-1;
}

int checkRow(int row[MAX]){
	for(int i=0; i<MAX; i++)
	{
		if (row[i] <= 0) return 0;
		if (row[i] == 2) return 3;
		if (row[i] == 4) return 57;
		if (row[i] == 6) return 1197;
		if (row[i] == 8) return 25137;
	}
	return 0;
}

int rowsAreEquals(int row[MAX],int newRow[MAX]){
	for (int i=0; i<MAX; i++){
		//printf("first:%d\tsec:%d\n",row[i],newRow[i]);
		if (row[i]!=newRow[i]){
			//printf("qui\n");
			return 0;
		}
	}
	//printf("fuori\n");
	return 1;
}

int analizeRow(int row[MAX]){
	//if (checkRow(row)==0) return 0;
	/*printf("riga:\t");
	for(int i=0; i<MAX && row[i]>0; i++)
		printf("%d",row[i]);
	printf("\n");*/
	int newRow[MAX]={0}, newIndex=0;
	for (int i=0; i<MAX-1; i++){
		if(row[i]<=0) break;
		/*printf("index1:%d val1:%d\t\t",i,row[i]);
		printf("index2:%d val2:%d\n",i+1,row[i+1]);*/
		int before=row[i], after=row[i+1];
		if ((before==1 && after==2) ||
			(before==3 && after==4) ||
			(before==5 && after==6) ||
			(before==7 && after==8) ) i++;
		else{
			newRow[newIndex]=row[i];
			//printf("newIndex:%d val:%d\n",newIndex,newRow[newIndex]);
			newIndex++;
		}
	}
	/*printf("riga new:\t");
	for(int i=0; i<MAX && newRow[i]>0; i++)
		printf("%d ",newRow[i]);
	printf("\n");*/
	
	if(!rowsAreEquals(row,newRow))
	{	
		int out=analizeRow(newRow);
		return(out);
	}
	else{
		int out=checkRow(row);
		return (out);
	}
}

int count(int input[MAX][MAX]){
	int sum=0;
	int tmp=0;
	for (int i=0; i<MAX && input[i][0]>0; i++){
		int row[MAX];
		for(int j=0;j<MAX; j++){ 
			if(input[i][j]==-1) break;
		    row[j]=input[i][j];
		}
		tmp=analizeRow(row);
		printf("row %d\tval %d\n",i+1,tmp);
		sum+=tmp;
	}
	
	return sum;
}


int main() {
   int input[MAX][MAX];
   resetMatrix(input);
   FILE* filePointer;
   filePointer = fopen("input_day10", "r");
   readInputCByC(filePointer,input);
   fclose(filePointer); 
   //printMatrix(input);
   int sum=count(input);
   printf("prima stella: %d\n",sum);
   
   
   printf("seconda stella: %d\n",sum);
   return 0;
}
