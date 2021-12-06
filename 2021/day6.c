#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX (990)
#define MAXLINE (500)

int max=0;

struct line{
	int x1;
	int y1;
	int x2;
	int y2;
};

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

void readMatrix(FILE* filePointer,struct line* input){
   int bufferLength = 255;
   char buffer[bufferLength];
   char **numbers;
   int i=0;
   
   while(fgets(buffer, bufferLength, filePointer)) {

      char from[] = " -> ";
      char to[] = ",";
	  char *out1=replaceWord(buffer, from, to);
	  split (out1, ',', &numbers);
	  input[i].x1=atoi(numbers[1]);
	  input[i].y1=atoi(numbers[0]);
	  input[i].x2=atoi(numbers[3]);
	  input[i].y2=atoi(numbers[2]);
	  i++;
   }
}

void printInput(struct line* input){
	for(int i=0; i<MAXLINE; i++)
	   printf("line %d: x1=%d,y1=%d x2=%d,y2=%d\n",i,input[i].x1,
				input[i].y1,input[i].x2,input[i].y2);
}

void printMatrix(int cartesian[MAX][MAX]){
	for(int i=0; i<MAX; i++){
		for (int j=0; j<MAX; j++)
			printf("%d ",cartesian[i][j]);
		printf("\n\n");
	}
}

void printMatrixRox(int cartesian[MAX][MAX], int row){
	printf("Row %d\n",row);
	for (int j=0; j<MAX; j++)
		printf("%d ",cartesian[row][j]);
	
	printf("\n");
}

void fillMatrixHV(struct line* input, int cartesian[MAX][MAX]){
	for(int i=0; i<MAXLINE; i++){
		if(input[i].x1!=input[i].x2 && 
			input[i].y1!=input[i].y2) continue;
		
		if(input[i].x1==input[i].x2 && 
			input[i].y1==input[i].y2){
				cartesian[input[i].x1][input[i].y1]++;
				continue;
		}
			
		if (input[i].x1==input[i].x2)
		{
			if(input[i].y1<input[i].y2)
				for(int j=input[i].y1;j<=input[i].y2; j++){
					cartesian[input[i].x1][j]++;
					if (max<cartesian[input[i].x1][j])
						max = cartesian[input[i].x1][j];
				}
			else
				for(int j=input[i].y2;j<=input[i].y1; j++){
					cartesian[input[i].x1][j]++;
					if (max<cartesian[input[i].x1][j])
						max = cartesian[input[i].x1][j];
				}
		}
		if (input[i].y1==input[i].y2)
		{
			if(input[i].x1<input[i].x2)
				for(int j=input[i].x1;j<=input[i].x2; j++){
					cartesian[j][input[i].y1]++;
					if (max<cartesian[j][input[i].y1])
						max = cartesian[j][input[i].y1];
				}
			else
				for(int j=input[i].x2;j<=input[i].x1; j++){
					cartesian[j][input[i].y1]++;
					if (max<cartesian[j][input[i].y1])
						max = cartesian[j][input[i].y1];
				}
		}
	}
}

void fillMatrixD(struct line* input, int cartesian[MAX][MAX]){
	for(int i=0; i<MAXLINE; i++){
		if(input[i].x1==input[i].x2 || 
			input[i].y1==input[i].y2) continue;
		
		int x = abs(input[i].x1-input[i].x2);
		int y = abs(input[i].y1-input[i].y2);
		if (x==y){
			//1,1 --> 3,3
			if(input[i].x1<input[i].x2 && input[i].y1<input[i].y2){
				for (int inc=0; inc<=x; inc++)
					cartesian[input[i].x1+inc][input[i].y1+inc]++;
				continue;
			}
			
			//3,3 --> 1,1
			if(input[i].x2<input[i].x1 && input[i].y2<input[i].y1){
				for (int inc=0; inc<=x; inc++)
					cartesian[input[i].x2+inc][input[i].y2+inc]++;
				continue;
			}
			
			//7,9 --> 9,7
			if(input[i].x1<input[i].x2 && input[i].y2<input[i].y1){
				for (int inc=0; inc<=x; inc++)
					cartesian[input[i].x1+inc][input[i].y1-inc]++;
				continue;
			}
			
			//9,7 --> 7,9
			if(input[i].x2<input[i].x1 && input[i].y1<input[i].y2){
				for (int inc=0; inc<=x; inc++)
					cartesian[input[i].x1-inc][input[i].y1+inc]++;
				continue;
			}
		}
	}
}

int countMax(int cartesian[MAX][MAX]){
	int count=0;
	for(int i=0; i<MAX; i++)
		for (int j=0; j<MAX; j++)
			if(cartesian[i][j]>=2) count++;
		
	return count;
}

int main() {
   int cartesian[MAX][MAX]={0};
   struct line input[MAXLINE];
   FILE* filePointer;
   filePointer = fopen("input_day5", "r");
   readMatrix(filePointer,input);
   fclose(filePointer); 

   fillMatrixHV(input,cartesian);
   int output = countMax(cartesian);
   printf("prima stella: %d\n",output);
   
   fillMatrixD(input,cartesian);
   output = countMax(cartesian);
   //printMatrix(cartesian);
   printf("seconda stella: %d\n",output);
   return 0;
}
