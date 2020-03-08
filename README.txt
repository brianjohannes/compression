A C program for run-length encoding compression of a pre-determined buffer.

Constraints:
- The buffer can only contain unsigned chars from 0 to 127
- This program does not support buffers longer that can be defined by single int

compression.c contains an example buffer which is compressed and then decompressed

The compression algorithm uses run-length encoding with the following rules
- Isolated values have 128 added to them to signify that they are not run lengths
- Runs of the same value are saved in two short ints
  1. First, run length
  2. Second, the value repeated during the run
- Runs of greater that 127 are written in the form of sequential runs
  (ex. 150 repeats of 0 would be [127 0 23 0] not [150 0])

The decompression algorithm reverses the run-length encoding
- Copy the compressed buffer to a new memory location to avoid overwriting
- Values > 127 are isolated values, so just subtract 128
- Values <= 127 are run lengths which will be followed directly by the run value,
  record the run value into each memory location for the length of the run
