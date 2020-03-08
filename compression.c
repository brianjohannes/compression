// Compression Example
// Written by: Brian Irvine
// Created: 03.06.2020
// Last edit: 03.08.2020

#include<stdio.h>
#include<string.h>

int byte_compress(unsigned char* data_ptr, int data_size);
int byte_decompress(unsigned char* data_ptr, int comp_size);

int main(){
  // example buffer and data_size
  int data_size = 24;
  int new_size;
  int original_size;
  unsigned char buffer[] = {0x03, 0x74, 0x04, 0x04, 0x04, 0x35, 0x35, 0x64,
    0x64, 0x64, 0x64, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x56, 0x45, 0x56, 0x56, 0x56, 0x09, 0x09, 0x09};
  unsigned char* data_ptr;
  int i;

  // Print the original buffer
  printf("\nPrint the example input buffer \n");
  for(i = 0; i < data_size; i++){
    printf(" %d ", buffer[i]);
  }
  printf("\nThe data size is %d bytes \n\n", data_size);

  // create the pointer to our example buffer
  data_ptr = &buffer[0];

  // Compress the buffer
  new_size = byte_compress(data_ptr, data_size);

  // Print the compressed buffer
  printf("Print the example buffer after compression\n");
  for(i = 0; i < new_size; i++){
    printf(" %d ", buffer[i]);
  }
  printf("\nThe compressed buffer size is %d bytes \n\n", new_size);

  // Decompress the buffer
  original_size = byte_decompress(data_ptr, new_size);

  // Print the decompressed buffer
  printf("Print the example buffer after decompression\n");
  for(i = 0; i < original_size; i++){
    printf(" %d ", buffer[i]);
  }
  printf("\nThe decompressed buffer size is %d bytes \n\n", original_size);

  return 0;
}

// Run-Length Compression
int byte_compress(unsigned char* data_ptr, int data_size){
  int new_size = 0;
  unsigned char run_length;         // the number of times repeated
  unsigned char run_value;          // the repeated value
  unsigned char* write_ptr;         // Write location
  unsigned char same = 1;           // debug

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

      // Skip over all the repeated values
      i += (run_length - 1);
    }
  }
  return new_size;
}

// Run length decompression
int byte_decompress(unsigned char* data_ptr, int compressed_size){
  unsigned char* write_ptr;
  unsigned char run;
  unsigned char run_length;
  unsigned char run_value;
  unsigned char bigbuffer[compressed_size];
  int original_size = 0;

  write_ptr = data_ptr;         // Set the write pointer to the begining of the buffer
  data_ptr = &bigbuffer[0];     // Put the

  // Copy the buffer to a new memory location to avoid overwriting
  memcpy(data_ptr, write_ptr, compressed_size*4);

  original_size = 0;
  for(int i = 0; i < compressed_size; i++){
    // if value > 127 it is a single value
    if(*data_ptr >= 128){
      *write_ptr = (*data_ptr) - 128;

      data_ptr++;
      write_ptr++;
      original_size++;
    }
    // if value < 127 it is a run
    else{
      run_length = *data_ptr;
      run_value = *(data_ptr + 1);
      run = 1;

      // For the length of the run write the value to the write pointer
      while(run <= run_length){
        *write_ptr = run_value;
        write_ptr++;
        original_size++;
        run++;
      }
      
      data_ptr += 2;      // skip the next value in the data buffer
      i++;                // skip the next iteration of the loop
    }
  }
  return original_size;
}

// The decompression algorithm
