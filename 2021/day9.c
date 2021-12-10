#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX (100)
#define RES (600)

struct strPoint {
	int row;
	int col;
};

int maxPoints=0;

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
	  for(int j=0; j<MAX; j++){
		input[i][j]=buffer[j]-48;
	  }
	  
	  i++;
	  if (i==MAX) break;
   }
}

int searchLow(int input[MAX][MAX],struct strPoint* points){
	int sum=0;
	
	for(int i=0; i<MAX; i++)
		for (int j=0; j<MAX; j++){
			if (i==0 && j==0){
				if( input[i][j]<input[i+1][j] &&
					input[i][j]<input[i][j+1]){
						sum+=(input[i][j]+1);
						points[maxPoints].row=i;
						points[maxPoints].col=j;
						maxPoints++;
					}
				continue;
			}
			if (i==MAX-1 && j==MAX-1){
				if( input[i][j]<input[i-1][j] &&
					input[i][j]<input[i][j-1]){
						sum+=(input[i][j]+1);
						points[maxPoints].row=i;
						points[maxPoints].col=j;
						maxPoints++;
					}
				continue;
			}
			
			if (i==0 && j==MAX-1){
				if( input[i][j]<input[i+1][j] &&
					input[i][j]<input[i][j-1]){
						sum+=(input[i][j]+1);
						points[maxPoints].row=i;
						points[maxPoints].col=j;
						maxPoints++;
					}
				continue;
			}
			if (i==MAX-1 && j==0){
				if( input[i][j]<input[i-1][j] &&
					input[i][j]<input[i][j+1]){
						sum+=(input[i][j]+1);
						points[maxPoints].row=i;
						points[maxPoints].col=j;
						maxPoints++;
					}
				continue;
			}
			
			
			if (i==0){
				if( input[i][j]<input[i+1][j] &&
					input[i][j]<input[i][j-1] &&
					input[i][j]<input[i][j+1]){
						sum+=(input[i][j]+1);
						points[maxPoints].row=i;
						points[maxPoints].col=j;
						maxPoints++;
					}
				continue;
			}
			if (i==MAX-1){
				if( input[i][j]<input[i-1][j] &&
					input[i][j]<input[i][j-1] &&
					input[i][j]<input[i][j+1]){
						sum+=(input[i][j]+1);
						points[maxPoints].row=i;
						points[maxPoints].col=j;
						maxPoints++;
					}
				continue;
			}
			
			if (j==0){
				if( input[i][j]<input[i-1][j] &&
					input[i][j]<input[i+1][j] &&
					input[i][j]<input[i][j+1]){
						sum+=(input[i][j]+1);
						points[maxPoints].row=i;
						points[maxPoints].col=j;
						maxPoints++;
					}
				continue;
			}
			if (j==MAX-1){
				if( input[i][j]<input[i-1][j] &&
					input[i][j]<input[i+1][j] &&
					input[i][j]<input[i][j-1]){
						sum+=(input[i][j]+1);
						points[maxPoints].row=i;
						points[maxPoints].col=j;
						maxPoints++;
					}
				continue;
			}
			
			if( input[i][j]<input[i-1][j] &&
				input[i][j]<input[i+1][j] &&
				input[i][j]<input[i][j-1] &&
				input[i][j]<input[i][j+1]){
					sum+=(input[i][j]+1);
					points[maxPoints].row=i;
					points[maxPoints].col=j;
					maxPoints++;
				}
			    
		}
	
	return sum;
}

int total=0;

void count(int input[MAX][MAX],struct strPoint point, int* basis,int index,int done[MAX][MAX] ){
	int value = input[point.row][point.col];
	if (value==9 || done[point.row][point.col]>-1) return;
	//printf("\npoint x:%d y:%d has %d \t\t\n",point.row,point.col,basis[index]);
	//printf("value: %d\n",done[point.row][point.col]);
	if (point.row==0 && point.col==0){
		int next1=input[point.row+1][point.col];
		int next2=input[point.row][point.col+1];
		//printf("C1 n1:%d n2:%d",next1,next2);
		if( next1 !=9){
			struct strPoint nextPoint;
			nextPoint.row=point.row+1;
			nextPoint.col=point.col;
			if(done[point.row][point.col]==-1){
				done[point.row][point.col]=next1;
				basis[index]++;
			}
			count(input,nextPoint,basis,index,done);
		}
		if( next2 !=9){
			struct strPoint nextPoint;
			nextPoint.row=point.row;
			nextPoint.col=point.col+1;
			if(done[point.row][point.col]==-1){
				done[point.row][point.col]=next2;
				basis[index]++;
			}
			count(input,nextPoint,basis,index,done);
		}
		
		return;
	}
	if (point.row==MAX-1 && point.col==MAX-1){
		int next1=input[point.row-1][point.col];
		int next2=input[point.row][point.col-1];
		//printf("C2 n1:%d n2:%d",next1,next2);
		if( next1 !=9){
			struct strPoint nextPoint;
			nextPoint.row=point.row-1;
			nextPoint.col=point.col;
			if(done[point.row][point.col]==-1){
				done[point.row][point.col]=next1;
				basis[index]++;
			}
			count(input,nextPoint,basis,index,done);
		}
		if( next2 !=9){
			struct strPoint nextPoint;
			nextPoint.row=point.row;
			nextPoint.col=point.col-1;
			if(done[point.row][point.col]==-1){
				done[point.row][point.col]=next2;
				basis[index]++;
			}
			count(input,nextPoint,basis,index,done);
		}
		
		return;
	}
	
	if (point.row==0 && point.col==MAX-1){
		int next1=input[point.row+1][point.col];
		int next2=input[point.row][point.col-1];
		//printf("C3 n1:%d n2:%d",next1,next2);
		if(next1 !=9){
			struct strPoint nextPoint;
			nextPoint.row=point.row+1;
			nextPoint.col=point.col;
			if(done[point.row][point.col]==-1){
				done[point.row][point.col]=next1;
				basis[index]++;
			}
			count(input,nextPoint,basis,index,done);
		}
		if( next2 !=9){
			struct strPoint nextPoint;
			nextPoint.row=point.row;
			nextPoint.col=point.col-1;
			if(done[point.row][point.col]==-1){
				done[point.row][point.col]=next2;
				basis[index]++;
			}
			count(input,nextPoint,basis,index,done);
		}
		
		return;		
	}
	if (point.row==MAX-1 && point.col==0){
		int next1=input[point.row-1][point.col];
		int next2=input[point.row][point.col+1];
		//printf("C4 n1:%d n2:%d",next1,next2);
		if( next1 !=9){
			struct strPoint nextPoint;
			nextPoint.row=point.row-1;
			nextPoint.col=point.col;
			if(done[point.row][point.col]==-1){
				done[point.row][point.col]=next1;
				basis[index]++;
			}
			count(input,nextPoint,basis,index,done);
		}
		if(next2 !=9){
			struct strPoint nextPoint;
			nextPoint.row=point.row;
			nextPoint.col=point.col+1;
			if(done[point.row][point.col]==-1){
				done[point.row][point.col]=next2;
				basis[index]++;
			}
			count(input,nextPoint,basis,index,done);
		}
		
		return;
	}
	
	if (point.row==0){
		int next1=input[point.row+1][point.col];
		int next2=input[point.row][point.col-1];
		int next3=input[point.row][point.col+1];
		//printf("C5 n1:%d n2:%d n3:%d",next1,next2,next3);
		if( next1 !=9){
			struct strPoint nextPoint;
			nextPoint.row=point.row+1;
			nextPoint.col=point.col;
			if(done[point.row][point.col]==-1){
				done[point.row][point.col]=next1;
				basis[index]++;
			}
			count(input,nextPoint,basis,index,done);
		}
		if( next2 !=9){
			struct strPoint nextPoint;
			nextPoint.row=point.row;
			nextPoint.col=point.col-1;
			if(done[point.row][point.col]==-1){
				done[point.row][point.col]=next2;
				basis[index]++;
			}
			count(input,nextPoint,basis,index,done);
		}
		if(next3 !=9){
			struct strPoint nextPoint;
			nextPoint.row=point.row;
			nextPoint.col=point.col+1;
			if(done[point.row][point.col]==-1){
				done[point.row][point.col]=next3;
				basis[index]++;
			}
			count(input,nextPoint,basis,index,done);
		}
		
		return;
	}
	if (point.row==MAX-1){
		int next1=input[point.row-1][point.col];
		int next2=input[point.row][point.col-1];
		int next3=input[point.row][point.col+1];
		//printf("C6 n1:%d n2:%d n3:%d",next1,next2,next3);
		if( next1 !=9){
			struct strPoint nextPoint;
			nextPoint.row=point.row-1;
			nextPoint.col=point.col;
			if(done[point.row][point.col]==-1){
				done[point.row][point.col]=next1;
				basis[index]++;
			}
			count(input,nextPoint,basis,index,done);
		}
		if( next2 !=9){
			struct strPoint nextPoint;
			nextPoint.row=point.row;
			nextPoint.col=point.col-1;
			if(done[point.row][point.col]==-1){
				done[point.row][point.col]=next2;
				basis[index]++;
			}
			count(input,nextPoint,basis,index,done);
		}
		if( next3 !=9){
			struct strPoint nextPoint;
			nextPoint.row=point.row;
			nextPoint.col=point.col+1;
			if(done[point.row][point.col]==-1){
				done[point.row][point.col]=next3;
				basis[index]++;
			}
			count(input,nextPoint,basis,index,done);
		}
		
		return;
		
	}
	
	if (point.col==0){
		int next1=input[point.row-1][point.col];
		int next2=input[point.row+1][point.col];
		int next3=input[point.row][point.col+1];
		//printf("C7 n1:%d n2:%d n3:%d",next1,next2,next3);
		if( next1 !=9){
			struct strPoint nextPoint;
			nextPoint.row=point.row-1;
			nextPoint.col=point.col;
			if(done[point.row][point.col]==-1){
				done[point.row][point.col]=next1;
				basis[index]++;
			}
			count(input,nextPoint,basis,index,done);
		}
		if( next2 !=9){
			struct strPoint nextPoint;
			nextPoint.row=point.row+1;
			nextPoint.col=point.col;
			if(done[point.row][point.col]==-1){
				done[point.row][point.col]=next2;
				basis[index]++;
			}
			count(input,nextPoint,basis,index,done);
		}
		if(next3 !=9){
			struct strPoint nextPoint;
			nextPoint.row=point.row;
			nextPoint.col=point.col+1;
			if(done[point.row][point.col]==-1){
				done[point.row][point.col]=next3;
				basis[index]++;
			}
			count(input,nextPoint,basis,index,done);
		}
		
		return;
	}
	
	if (point.col==MAX-1){
		int next1=input[point.row-1][point.col];
		int next2=input[point.row+1][point.col];
		int next3=input[point.row][point.col-1];
		//printf("C8 n1:%d n2:%d n3:%d",next1,next2,next3);
		if( next1 !=9){
			struct strPoint nextPoint;
			nextPoint.row=point.row-1;
			nextPoint.col=point.col;
			if(done[point.row][point.col]==-1){
				done[point.row][point.col]=next1;
				basis[index]++;
			}
			count(input,nextPoint,basis,index,done);
		}
		if( next2 !=9){
			struct strPoint nextPoint;
			nextPoint.row=point.row+1;
			nextPoint.col=point.col;
			if(done[point.row][point.col]==-1){
				done[point.row][point.col]=next2;
				basis[index]++;
			}
			count(input,nextPoint,basis,index,done);
		}
		if( next3 !=9){
			struct strPoint nextPoint;
			nextPoint.row=point.row;
			nextPoint.col=point.col-1;
			if(done[point.row][point.col]==-1){
				done[point.row][point.col]=next3;
				basis[index]++;
			}
			count(input,nextPoint,basis,index,done);
		}
		
		return;
	}   
	
	int next1=input[point.row-1][point.col];
	int next2=input[point.row+1][point.col];
	int next3=input[point.row][point.col+1];
	int next4=input[point.row][point.col-1];
	//printf("C9 n1:%d n2:%d n3:%d n4:%d",next1,next2,next3,next4);
	if( next1 !=9){
		struct strPoint nextPoint;
		nextPoint.row=point.row-1;
		nextPoint.col=point.col;
		if(done[point.row][point.col]==-1){
				done[point.row][point.col]=next1;
				basis[index]++;
			}
		count(input,nextPoint,basis,index,done);
	}
	if( next2 !=9){
		struct strPoint nextPoint;
		nextPoint.row=point.row+1;
		nextPoint.col=point.col;
		if(done[point.row][point.col]==-1){
				done[point.row][point.col]=next2;
				basis[index]++;
			}
		count(input,nextPoint,basis,index,done);
	}
	if(next3 !=9){
		struct strPoint nextPoint;
		nextPoint.row=point.row;
		nextPoint.col=point.col+1;
		if(done[point.row][point.col]==-1){
				done[point.row][point.col]=next3;
				basis[index]++;
			}
		count(input,nextPoint,basis,index,done);
	}
	if( next4 !=9){
		struct strPoint nextPoint;
		nextPoint.row=point.row;
		nextPoint.col=point.col-1;
		if(done[point.row][point.col]==-1){
			done[point.row][point.col]=next4;
			basis[index]++;
		}
		count(input,nextPoint,basis,index,done);
	}
	
	return;
	
}

void searchBasis(int input[MAX][MAX],struct strPoint* points, int* basis,int done[MAX][MAX]){
	for(int p=0; p<maxPoints; p++){
		//printf("value: %d\n",done[points[p].row][points[p].col]);
		count(input,points[p],basis,p,done);
		//printf("Bacino x:%d y:%d val=%d\n",points[p].row,points[p].col,basis[p]);
	}
}

void resetMatrix(int done[MAX][MAX]){
	for (int i=0; i<MAX; i++)
		for (int j=0; j<MAX; j++)
			done[i][j]=-1;
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

int main() {
   int input[MAX][MAX];
   int done[MAX][MAX];
   resetMatrix(done);
   struct strPoint points[RES];
   int basis[RES]={0};
   FILE* filePointer;
   filePointer = fopen("input_day9", "r");
   readInputCByC(filePointer,input);
   fclose(filePointer); 
   int sum=searchLow(input,points);
   printf("prima stella: %d\n",sum);
   
   searchBasis(input,points,basis,done);
   
   mergeSort(basis, 0, maxPoints-1);
   /*for (int i=0; i<maxPoints; i++)
	   printf("dato %d\n",basis[i]);*/
   
   int basisV=basis[maxPoints-1]*basis[maxPoints-2]*basis[maxPoints-3];
   printf("seconda stella: %d\n",basisV);
   return 0;
}
