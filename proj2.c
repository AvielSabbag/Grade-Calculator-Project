#include <stdio.h>
#include <stdlib.h>
/*
  Creates first allocation of 40 bytes of memory when first grade is inputted
  Accepts a pointer to a pointer to a double
 */
void firstHeap(double** ptr);
/*
  Creates larger allocation of memory with an additional 40 bytes when 
  previous one becomes full
  Accepts a pointer to a pointer to a double
 */
void mallocHeap(double** ptr);
/*
  prints Average of grades along with whether or not each grade is 
  >= or < than the average
  Accepts a pointer to a pointer to a double
 */
void printAvg(double** ptr);
/*
  Calulates the average of all grades entered so far
  Accepts a pointer to an int and 3 pointers to doubles
*/
void calcAvg(unsigned int*,double*,double*,double*);

double num = 0;//the grade being currently entered
double total = 0;//total of all grades veing entered
double avg = 0;//the average of all grades
unsigned int capacity = 0;//capacity of current block of memory
unsigned int totalCapacity = 0;//total capacity of all memory used
unsigned int amount = 0;//the number of grades entered
double *heap;
double *original;

unsigned int allocs = 0;//the number of allocations
unsigned int frees = 0;//the number of frees

int main() {
  printf("Enter a list of grades below where each grade is separated by a "
	 "newline character.\n"
	 "After the last grade is entered, enter a negative value to end the list.\n");
  while (num >= 0) {    
    scanf("%lf",&num);
    if (num >= 0) {
      amount++;
      calcAvg(&amount,&total,&avg,&num);
      //allocates first block of memory when first grade is entered
      if (amount == 1) {
	      firstHeap(&heap);
	      printf("Allocated %d bytes to the heap at %p. \n",capacity,(void*)heap);
      }//if      
      *(heap+(amount-1)) = num;
      printf("Stored %lf in the heap at %p. \n",num,(void*)(heap+(amount-1)));
      //allocates new larger block for every 5 grades entered
      if (amount%5 == 0) {
	printf("Stored %d grades (%d bytes) to the heap at %p. \n",amount,capacity,(void*)heap);
	printf("Heap at %p is full. \n",(void*)heap);
	mallocHeap(&heap);
      }//if
    }//if
    else {	
      printAvg(&heap);
    }//else 
  }//while 
  return 0;
}//main()

void firstHeap(double** ptr) {
    capacity += 40;
    totalCapacity += capacity;
    *ptr = (double*) malloc(capacity);
    allocs++;
}//firstHeap()

void mallocHeap(double** ptr) {
  double *copyHeap = *ptr; 
  capacity += 40;
  totalCapacity += capacity;
  original = *ptr;

  *ptr = (double*) malloc(capacity);
  allocs++;
  //copying of old values into new allocation
  for (int j = 0; j<amount; j++) {
    *(*ptr+j) = *(copyHeap+j);
  }//for
  printf("Allocated %d bytes to the heap at %p. \n",capacity,(void*)*ptr);
  printf("Copied %d grades from %p to %p. \n",amount,(void*)original,(void*)*ptr);
  printf("Freed %d bytes from the heap at %p. \n",capacity-40,(void*)original);
	
  free(copyHeap);
  frees++;
}//mallocHeap()

void printAvg(double** ptr) {
  printf("The average of %d grades is %f. \n",amount,avg);
  for (int i = 0; i<amount; i++) {
    if (*(*ptr+i) < avg) 
      printf("%d. The grade of %lf is < the average. \n",i+1,*(*ptr+i));
    else if (*(*ptr+i) >= avg)
      printf("%d. The grade of %lf is >= the average. \n",i+1,*(*ptr+i));    
  }//for
  
  if (amount > 0) {
    free(*ptr);
    frees++;
    printf("Freed %d bytes from the heap at %p. \n",capacity,(void*)*ptr);
  }//if
  printf("total heap usage: %d allocs, %d frees, %d bytes allocated \n", allocs,
         frees,totalCapacity);
}//printAvg()


void calcAvg(unsigned int*amount,double*total,double*avg,double*num) {
  *total += *num;
  *avg = *total/(*amount);
}//calcAvg

