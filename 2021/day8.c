#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

int readInputAndCount(FILE* filePointer){
   int bufferLength = 4000;
   char buffer[bufferLength];
   char **output;
   char **segments;
   int sum=0;
   
   while(fgets(buffer, bufferLength, filePointer)) {
	  
	  if (strcmp(buffer, "\r\n")==0)
	  	break;
	  split (buffer, '|', &output);
	  //printf("qui %s\n",output[1]);
	  int seg = split(output[1],' ',&segments);
	  
	  for (int i=0; i<seg; i++){
		  int len=strlen(segments[i]);
		  if (len==2){
			char **segmentsIn;
			int segIn= split(output[0],' ',&segmentsIn);  
			if(strchr(output[0],segments[i][0]) &&
				strchr(output[0],segments[i][1])){
					sum++;
					continue;
				}
				
		  }
		  if (len==3){
			char **segmentsIn;
			int segIn= split(output[0],' ',&segmentsIn);  
			if(strchr(output[0],segments[i][0]) &&
				strchr(output[0],segments[i][1]) &&
				strchr(output[0],segments[i][2])){
					sum++;
					continue;
				}
				
		  }
		  if (len==4){
			char **segmentsIn;
			int segIn= split(output[0],' ',&segmentsIn);  
			if(strchr(output[0],segments[i][0]) &&
				strchr(output[0],segments[i][1]) &&
				strchr(output[0],segments[i][2]) &&
				strchr(output[0],segments[i][3])){
					sum++;
					continue;
				}
				
		  } 	  
		  if (len==8){
			char **segmentsIn;
			int segIn= split(output[0],' ',&segmentsIn);  
			if(strchr(output[0],segments[i][0]) &&
				strchr(output[0],segments[i][1]) &&
				strchr(output[0],segments[i][2]) &&
				strchr(output[0],segments[i][3]) &&
				strchr(output[0],segments[i][4]) &&
				strchr(output[0],segments[i][5]) &&
				strchr(output[0],segments[i][6]) &&
				strchr(output[0],segments[i][7])){
					sum++;
					continue;
				}
		  } 
	  }
   }
   
   return sum;
}

int main() {
   FILE* filePointer;
   filePointer = fopen("input_day8", "r");
   int sum=readInputAndCount(filePointer);
   fclose(filePointer); 

   printf("prima stella: %d\n",sum);
   
   //printf("seconda stella: %d\n",fuel2);
   return 0;
}
