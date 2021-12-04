#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int position = 0;

struct strMatrix {
	int matrix[5][5];
	int marked[5][5];
	int countrows[5];
	int countcols[5];
	int win;
};

void emptyMatrix(struct strMatrix* cartella){
	for(int i=0; i<5; i++)
		for(int j=0; j<5; j++){
	      (*cartella).matrix[i][j]=-1;
		  (*cartella).marked[i][j]=-1;
		}
	for (int i=0; i<5; i++){
		(*cartella).countrows[i]=-1;
		(*cartella).countcols[i]=-1;
	}
	
	(*cartella).win=++position;
}

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

void readMatrix(FILE* filePointer, struct strMatrix* cartella){
   int bufferLength = 255;
   char buffer[bufferLength];
   char **numbers;
   int count,i=0;
   
   while(fgets(buffer, bufferLength, filePointer)) {
	  if (strcmp(buffer, "\r\n")==0)
	  	break;
	
      char c[] = "  ";
      char d[] = " ";
	  char *out2=buffer;
	  if(buffer[0]==' ') out2=buffer+1;
	  char *out1=replaceWord(out2, c, d);
	  count = split (out1, ' ', &numbers);
	  for(int j=0; j<count; j++){
		  (*cartella).matrix[i][j]=atoi(numbers[j]);
		  (*cartella).marked[i][j]=0;
	  }
	  i++;
   }
   
   for (int i=0; i<5; i++){
      (*cartella).countrows[i] = 0;
      (*cartella).countcols[i] = 0;
   }
   (*cartella).win=-1;
}

void printMatrix(struct strMatrix* cartelle){
	for (int nc=0; nc<100; nc++)
	{
	  for (int i=0; i<5; i++){
		  for (int j=0; j<5; j++)
			  printf("%d ",cartelle[nc].matrix[i][j]);
		printf("\n");
	  }
	  printf("position: %d\n",cartelle[nc].win);
	}
}

void printOneMatrix(struct strMatrix cartelle){
	printf("matrice\n");
	  for (int i=0; i<5; i++){
		  for (int j=0; j<5; j++)
			  printf("%d ",cartelle.matrix[i][j]);
		printf("\n");
	  }
	printf("segnati\n");
	  for (int i=0; i<5; i++){
		  for (int j=0; j<5; j++)
			  printf("%d ",cartelle.marked[i][j]);
		printf("\n");
	  }
	printf("posizione%d\n",cartelle.win);
	printf("\n");
}

int checkBingo(int rand, struct strMatrix* cartelle){
	int output=0;
	for (int nc=0; nc<100; nc++){
	  int i=0,j=0, exit=0;
	  for (; i<5; i++){
		j=0, exit=0;
	    for (; j<5; j++)
		  if(cartelle[nc].matrix[i][j] == rand){
			  cartelle[nc].marked[i][j] = 1;
			  exit=1;
			  break;
		  }
		if (exit) break;
	  }
	  
	  int salta=0;
	  if(i<5){
	   if (++cartelle[nc].countrows[i]==5){
		  for(int i=0; i<5; i++)
		     for(int j=0; j<5; j++)
		       if(!cartelle[nc].marked[i][j]){
			      output+=cartelle[nc].matrix[i][j];
				  salta=1;
			   }
		  cartelle[nc].win=position++;
	   }
	  }
	  if(!salta){
		  if (j<5){
		   if (++cartelle[nc].countcols[j]==5){
			 for(int i=0; i<5; i++)
				 for(int j=0; j<5; j++)
				   if(!cartelle[nc].marked[i][j]) 
					  output+=cartelle[nc].matrix[i][j];
			 cartelle[nc].win=position++;
		   }
		  }
	  }
	}
	
	return output*rand;
}

int checkBingo2(int rand, struct strMatrix* cartelle){
	int output=0;
	for (int nc=0; nc<100; nc++){
	  if (cartelle[nc].win>0) continue;
	  int i=0,j=0, exit=0;
	  for (; i<5; i++){
		j=0, exit=0;
	    for (; j<5; j++)
		  if(cartelle[nc].matrix[i][j] == rand){
			  cartelle[nc].marked[i][j] = 1;
			  exit=1;
			  break;
		  }
		if (exit) break;
	  }
	  
	  int salta=0;
	  if(i<5){
	   if (++cartelle[nc].countrows[i]==5){
		  emptyMatrix(&cartelle[nc]);
		  salta=1;
	   }
	  }
	  if (!salta){ 
		  if (j<5){
		   if (++cartelle[nc].countcols[j]==5){
			 emptyMatrix(&cartelle[nc]);
		   }
		  }
	  }
	}
	
	return -1;
}

int checkLast(struct strMatrix* cartelle){
	int count=0;
	int index=-1;
	for (int nc=0; nc<100; nc++){
		//printf("cartella %d, posizione: %d\n",nc,cartelle[nc].win);
		if(cartelle[nc].win==-1){
			count++;
			index=nc;
		}
	}
	
	if (count==1){
		//printMatrix(cartelle);
		return index;
	}
	return -1;
}

int unMark(struct strMatrix cartella){
	int output=0;
	for(int i=0; i<5; i++)
		for(int j=0; j<5; j++)
			if(!cartella.marked[i][j]) 
				output+=cartella.matrix[i][j];
	
	return output;
}


int main() {
   struct strMatrix cartelle[100];   
   FILE* filePointer;
   filePointer = fopen("input_day4", "r");
   char sNumbers[300],empty[3];
   fgets(sNumbers, 300, filePointer);
   fgets(empty, 3, filePointer);
   
   for (int i=0; i<100; i++){
      readMatrix(filePointer,&cartelle[i]);
   }
   fclose(filePointer); 

   char **numbers;
   int count;
   count = split (sNumbers, ',', &numbers);
   int randomNum[100];
   int output=0;
   
   //first Star
   /*
   for(int i=0; i<100; i++){
      randomNum[i]=atoi(numbers[i]);
	  if (output=checkBingo(randomNum[i],cartelle))
	     break;
   }
   
   //printOneMatrix(cartelle[41]);
   
   printf("prima stella:  %d\n",output);
   */
   
   //second Star
   int i=0;
   for(; i<100; i++){
      randomNum[i]=atoi(numbers[i]);
	  checkBingo2(randomNum[i],cartelle);
	  int index=checkLast(cartelle);
	  if(index>0){
		  //printf("numero %d; indice %d\n",randomNum[i],index);
		  break;
	  }
	  /*if(output=){
		//printf("\ncorrente %d\n",output);
	    output=unMark(cartelle[output])*randomNum[i];
		//printOneMatrix(cartelle[output]);
	    break;
	  }*/
   }
   for (i++;i<100;i++){
	  randomNum[i]=atoi(numbers[i]);
	  if (output=checkBingo(randomNum[i],cartelle))
	     break;
   }
   //printMatrix(cartelle);
   //printf("cartella29\n");
   //printOneMatrix(cartelle[29]);
   
   printf("stella 2: %d\n",output);
   
   return 0;
}
