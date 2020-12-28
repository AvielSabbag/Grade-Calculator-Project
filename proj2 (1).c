#include <stdio.h>
#include <stdlib.h>

void firstHeap(double** ptr);
void mallocHeap(double** ptr);
void printAvg(double** ptr);
void calcAvg(unsigned int*,double*,double*,double*);
void printEnd();

double num = 0;
double total = 0;
double avg = 0;
unsigned int capacity = 0;
unsigned int totalCapacity = 0;
unsigned int amount = 0;
double *heap;
double *original;

unsigned int allocs = 0;
unsigned int frees = 0;

int main() {
  printf("Enter a list of grades below where each grade is separated by a "
	 "newline character.\n"
	 "After the last grade is entered, enter a negative value to end the list.\n");
  while (num >= 0) {    
    scanf("%lf",&num);
    if (num >= 0) {
      amount++;
      calcAvg(&amount,&total,&avg,&num);
      if (amount == 1) {
	      firstHeap(&heap);
	      printf("Allocated %d bytes to the heap at %p. \n",capacity,(void*)heap);
      }      
      *(heap+(amount-1)) = num;
      printf("Stored %lf in the heap at %p. \n",num,(void*)(heap+(amount-1)));      
      if (amount%5 == 0) {
	printf("Stored %d grades (%d bytes) to the heap at %p. \n",amount,capacity,(void*)heap);
	printf("Heap at %p is full. \n",(void*)heap);
	mallocHeap(&heap);
      }
    }
    else {	
      printAvg(&heap);
    } 
  } 
  return 0;
}

void firstHeap(double** ptr) {
    capacity += 40;
    totalCapacity += capacity;
    *ptr = (double*) malloc(capacity);
    allocs++;
}

void mallocHeap(double** ptr) {
  double *copyHeap = *ptr; 
  capacity += 40;
  totalCapacity += capacity;
  original = *ptr;

  *ptr = (double*) malloc(capacity);
  allocs++;
  
  for (int j = 0; j<amount; j++) {
    *(*ptr+j) = *(copyHeap+j);
  }
  printf("Allocated %d bytes to the heap at %p. \n",capacity,(void*)*ptr);
  printf("Copied %d grades from %p to %p. \n",amount,(void*)original,(void*)*ptr);
  printf("Freed %d bytes from the heap at %p. \n",capacity-40,(void*)original);
	
  free(copyHeap);
  frees++;
}

void printAvg(double** ptr) {
  printf("The average of %d grades is %f. \n",amount,avg);
  for (int i = 0; i<amount; i++) {
    if (*(*ptr+i) < avg) 
      printf("%d. The grade of %lf is < the average. \n",i+1,*(*ptr+i));
    else if (*(*ptr+i) >= avg)
      printf("%d. The grade of %lf is >= the average. \n",i+1,*(*ptr+i));    
  }
  
  if (amount > 0) {
    free(*ptr);
    frees++;
    printf("Freed %d bytes from the heap at %p. \n",capacity,(void*)*ptr);
  }
  printf("total heap usage: %d allocs, %d frees, %d bytes allocated \n", allocs,
         frees,totalCapacity);
}


void calcAvg(unsigned int*amount,double*total,double*avg,double*num) {
  *total += *num;
  *avg = *total/(*amount);
}

