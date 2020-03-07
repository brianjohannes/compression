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


  printf("print the example input buffer")
  for(i = 0; i < data_size; i++){
    printf(" %d ", buffer[i]);
  }

  printf("the data size is %d bytes \n", data_size);

  // create the pointer to our example buffer
  data_ptr = &buffer[0];
  new_size = byte_compress(data_ptr, data_size);

  printf("the new buffer size is %d bytes \n", new_size);
  return 0;
}

// The compression algorithm
int byte_compress(short int* data_ptr, int data_size){
  int new_buffer[];

  // for each
  for(i = 0; i < )
  new_buffer[0] = data_ptr;
  printf("the new buffer is %d \n", &new_buffer);

  for(i = 0, i < data_size, i++){
    printf(" %d ", new_buffer[i]);
  }

  int new_size = 1;
  return new_size;
}

// The decompression algorithm
