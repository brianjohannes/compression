#include<stdio.h>

int byte_compress(short int* data_ptr, int data_size);

int main(){
  // example buffer and data_size
  int data_size = 24;
  int new_size;
  short int buffer[] = {0x03, 0x74, 0x04, 0x04, 0x04, 0x35, 0x35, 0x64,
    0x64, 0x64, 0x64, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x56, 0x45, 0x56, 0x56, 0x56, 0x09, 0x09, 0x09};
  short int* data_ptr;
  int i;


  printf("\nprint the example input buffer \n");
  for(i = 0; i < data_size; i++){
    printf(" %d ", buffer[i]);
  }

  printf("\nthe data size is %d bytes \n", data_size);

  // create the pointer to our example buffer
  data_ptr = &buffer[0];
  new_size = byte_compress(data_ptr, data_size);

  printf("the new buffer size is %d bytes \n", new_size);
  printf("print the example new buffer\n");
  for(i = 0; i < new_size; i++){
    printf(" %d ", buffer[i]);
  }
  printf("\n");
  return 0;
}

// The compression algorithm
int byte_compress(short int* data_ptr, int data_size){
  int i;
  short int single_add = 128;
  short int* next_ptr;
  short int same = 1;

  // short int* temp_ptr;

  // compress each value
  int new_size = 0;
  for(i = 0; i < data_size; i++){
    // if different add 128
    next_ptr = data_ptr + 1;
    if(*data_ptr != *next_ptr){
      *data_ptr += single_add;
      new_size++;
      data_ptr = next_ptr;
      same = 0;
    }

    // if same find the length
    else{
      new_size++;
      data_ptr = next_ptr;
      same = 1;
      /*
      *temp_ptr = *data_ptr;
      while(*temp_ptr == *(temp_ptr++)){


        temp_ptr++
      }
      */

    }
    printf("i = %d,  same?: %d, address: %d \n",i,same,data_ptr);
  }
  return new_size;
}

// The decompression algorithm
