#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INTAL_LENGTH 1000

// function to initialize an INTAL
char* initializeINTAL() {
    char *_intal = (char *)malloc((INTAL_LENGTH + 1) * sizeof(char));
    for (int i = 0; i < INTAL_LENGTH; i++) { _intal[i] = '0'; }
    _intal[INTAL_LENGTH] = '\0';
    return _intal;
}

//1. function to compare two INTALs
int compareINTAL(char* intal_a, char* intal_b) {
  if(strlen(intal_a) > strlen(intal_b))
    return 1;
  if(strlen(intal_a) < strlen(intal_b))
    return -1;
  int len = 0;
  while(len < strlen(intal_a)) {
    if(intal_a[len] > intal_b[len])
      return 1;
    else if(intal_a[len] < intal_b[len])
      return -1;
    len++;
  }
  return 0;
}

// function to set the larger and the smaller INTALs into intal_a and intal_b respectively
void setINTALs(char **_intal_a, char **_intal_b) {
  if(compareINTAL(*_intal_a, *_intal_b) != -1) return;
  char *temp_INTAL = *_intal_a;
  *_intal_a = *_intal_b;
  *_intal_b = temp_INTAL;
}

// function to trim the resultant INTAL
char* trimINTAL(char* _intal) {
  if(strlen(_intal) == 1) return _intal;
  while(*_intal == '0') { _intal++; }
  return _intal;
}

// utility function to add two INTALs
void addINTALs(char* intal_a, char* intal_b, char* result, int res_len) {
  int i = strlen(intal_a) - 1;        // index of the INTAL_A
  int j = strlen(intal_b) - 1;        // index of the INTAL_B
  int digit, carry = 0;

  // adding the two given INTALs
  for (int k = res_len-1; k > 0; k--) {
    // sum of each digit
    if(j < 0) digit = intal_a[i--] + '0' + carry - 96;
    else digit = intal_a[i--] + intal_b[j--] + carry - 96;

    // resultant digit and the carry
    result[k] = 48 + (digit % 10);
    carry = digit / 10;
  }

  result[0] = (carry == 1) ? '1' : '0'; // 48 + 1(carry)
}

//2. function to calculate the sum of two INTALs
char* INTALadder(char* intal_a, char* intal_b) {
  // setting the INTALs
  setINTALs(&intal_a, &intal_b);

  // setting the length of the resultant array and other necessary parameters
  int res_len = strlen(intal_a) + 1;  //length of the resultant array

  // allocating and initializing the resulant array
  char *result = (char *)malloc((res_len + 1) * sizeof(char));
  for (int i = 0; i < res_len; i++) { result[i] = '0'; }
  result[res_len] = '\0';

  addINTALs(intal_a, intal_b, result, res_len); // utility function

  return trimINTAL(result);
}

// utility function to subtract INTALs
void subtractINTALs(char* intal_a, char* intal_b, char* result, int res_len) {
  int digit, carry = 0;
  int i = strlen(intal_a) - 1;       // index of the minuend
  int j = strlen(intal_b) - 1;       // index of the subtrahend
  
  // calculating the difference between the given INTALs
  for (int k = res_len-1; k >= 0; k--) {
    // subtracting the subtrahend from the minuend
    if(j < 0) digit = intal_a[i--] - '0' - carry + 10;
    else digit = intal_a[i--] - intal_b[j--] - carry + 10;

    // resultant digit and the carry
    result[k] = 48 + (digit % 10);
    carry = (digit < 10) ? 1 : 0;
  }
}

//3. function to calculate the difference between two INTALs
char* INTALsubtractor(char* intal_a, char* intal_b) {
  // setting the minuend and the subtrahend
  setINTALs(&intal_a, &intal_b);

  // Equivalent INTALs
  if(compareINTAL(intal_a, intal_b) == 0) return "0";

  int res_len = strlen(intal_a);     // length of the resultant array

  // allocating and initializing the resultant array
  char *result = (char *)malloc((res_len + 1) * sizeof(char));
  for (int i = 0; i < res_len; i++) { result[i] = '0';}
  result[res_len] = '\0';

  subtractINTALs(intal_a, intal_b, result, res_len);  // utility function

  return trimINTAL(result);
}

// utility function to multiply two INTALS
void multiplyINTALs(char* intal_a, char* intal_b, char* result) {
  int digit, carry, ptr2, ptr1 = 1;
  int i = strlen(intal_b) - 1;  // index of intal_b
  int j;

  // multiplying the two INTALs
  while(i >= 0) {
    digit = 0, carry = 0;
    ptr2 = strlen(intal_a) + strlen(intal_b) - ptr1;  // index of the resultant array

    // multiplication of each digit
    j = strlen(intal_a) - 1;
    while (j >= 0) {
      digit = (intal_a[j--] - '0') * (intal_b[i] - '0') + (result[ptr2] - '0') + carry;
      result[ptr2--] = 48 + (digit % 10); // resultant digit
      carry = digit / 10;                 // resultant carry
    }

    if(carry) result[ptr2] = carry + '0'; // if carry exists, insert it into the resultant array
    i--;
    ptr1++;
  }
}

//3. function to calculate the multiplication of two INTALs
char* INTALmultiplicator(char* intal_a, char* intal_b) {
  int len_intal_a = strlen(intal_a);
  int len_intal_b = strlen(intal_b);

  // checking the length of  the INTALs
  if((len_intal_a + len_intal_b) > INTAL_LENGTH) {
    printf("Length of resultant INTAL out of range of maximum length...");
    return NULL;
  }

  if(len_intal_a == 1) {
    if(*intal_a == '0') return intal_a;
    if(*intal_a == '1') return intal_b;
  } else {
    if(len_intal_b == 1) {
      if(*intal_b == '0') return intal_b;
      if(*intal_b == '1') return intal_a;
    }
  }

  // setting the length of the resultant array and other necessary parameters
  int res_len = len_intal_a + len_intal_b;  // length of the resultant array                   

  // allocating and initializing the resulant array
  char *result = (char *)malloc((res_len + 1) * sizeof(char));
  for (int i = 0; i < res_len; i++) { result[i] = '0'; }
  result[res_len] = '\0';

  multiplyINTALs(intal_a, intal_b, result); // utility function

  return trimINTAL(result);;
}

//4. function to calculate the nth fibonacci INTAL
char* INTALfibonacci(unsigned int n) {
  // initializing basic parameters
  char *intal_a = initializeINTAL(), *intal_b = initializeINTAL();
  char *_init_0_ = "0", *_init_1_ = "1";

  intal_a = _init_0_;
  intal_b = _init_1_;

  if(n == 1) return intal_a;
  if(n == 2) return intal_b;

  char *temp_INTAL;
  while(n-- > 2) {
    temp_INTAL = intal_b;
    intal_b = INTALadder(intal_a, intal_b);
    free(intal_a);
    intal_a = temp_INTAL;
  }

  temp_INTAL = intal_b;
  free(intal_a);
  free(intal_b);

  return temp_INTAL;
}

//5. function to calculate the factorial of a number in INTAL
char* INTALfactorial(unsigned int m) {
  char *intal_fact = initializeINTAL();
  char *intal_it = initializeINTAL();
  char *_init_ = "1";

  intal_fact = intal_it = _init_;

  if(m == 0 || m == 1) return intal_fact;

  char *temp;
  for (unsigned int i = 2; i <= m; i++) {
    temp = INTALadder(intal_it, "1");
    intal_it = temp;
    temp = INTALmultiplicator(intal_it, intal_fact);
    free(intal_fact);
    intal_fact = temp;
  }

  free(intal_it);

  return intal_fact;
}