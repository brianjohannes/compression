// Compression Example
// Written by: Brian Irvine
// Created: 03.06.2020
// Last edit: 03.07.2020

#include<stdio.h>
#include<string.h>

int byte_compress(short int* data_ptr, int data_size);
int byte_decompress(short int* data_ptr, int comp_size);

int main(){
  // example buffer and data_size
  int data_size = 180;
  int new_size;
  int original_size;
  short int buffer[] = {0x03, 0x74, 0x04, 0x04, 0x04, 0x35, 0x35, 0x64,
    0x64, 0x64, 0x64, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x56, 0x45, 0x56, 0x56, 0x56, 0x09, 0x09, 0x09,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
    ,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
    ,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
    ,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
    ,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
    ,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
    ,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
    ,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
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

  original_size = byte_decompress(data_ptr, new_size);

  printf("the original buffer size is %d bytes \n", original_size);
  printf("print the example new buffer\n");
  for(i = 0; i < original_size; i++){
    printf(" %d ", buffer[i]);
  }
  printf("\n");

  return 0;
}

// Run-Length Compression
int byte_compress(short int* data_ptr, int data_size){
  int new_size = 0;
  short int run_length;         // the number of times repeated
  short int run_value;          // the repeated value
  short int* write_ptr;         // Write location
  short int same = 1;           // debug

  // Initialize the writing pointer to the data_pointer
  write_ptr = data_ptr;

  // compress each value
  for(int i = 0; i < data_size; i++){
    // if values are different
    if(*data_ptr != *(data_ptr + 1)){
      *write_ptr = *data_ptr + 128;

      // Advance
      data_ptr++;
      write_ptr++;
      new_size++;
      same = 0; //debug ***
    }

    // if values are the same
    else{
      // Initialize run length to 1 and loop until the end
      run_length = 1;
      run_value = *data_ptr;
      while(*data_ptr == *(data_ptr + run_length) & run_length < 127){
        run_length++;
      }

      // Save the run length
      *write_ptr = run_length;

      // Increment and save the repeated value
      write_ptr++;
      *write_ptr = run_value;

      // Advance
      data_ptr += run_length;
      write_ptr++;
      new_size += 2;
      same = 1;

      // Skip over all the repeated values
      i += (run_length - 1);
    }
    printf("i = %d,  same?: %d, address: %d, new_size: %d\n",i,same,data_ptr,new_size);
  }
  return new_size;
}

int byte_decompress(short int* data_ptr, int compressed_size){
  short int* write_ptr;
  short int run;
  short int run_length;
  short int run_value;
  short int bigbuffer[compressed_size];
  int original_size = 0;

  write_ptr = data_ptr;         // Overwrite the old buffer
  data_ptr = &bigbuffer[0];     // Put the

  // Copy the buffer
  memcpy(data_ptr, write_ptr, compressed_size*4);

  for(int i = 0; i < compressed_size; i++){
    // if value > 127
    if(*data_ptr >= 128){
      *write_ptr = (*data_ptr) - 128;

      data_ptr++;
      write_ptr++;
      original_size++;
    }
    else{
      run_length = *data_ptr;
      run_value = *(data_ptr + 1);
      run = 1;

      while(run <= run_length){
        *write_ptr = run_value;
        write_ptr++;
        original_size++;
        run++;
      }
      data_ptr += 2;
      i++;
    }
    //printf("i = %d,  same?: %d, address: %d, new_size: %d\n",i,same,data_ptr,new_size);
  }
  return original_size;
}

// The decompression algorithm
