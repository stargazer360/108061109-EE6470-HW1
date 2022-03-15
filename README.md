# Homework 1
A 3x3 approximated Gaussian blur filter for 256x256 bmp images implemented in SytemC.
There are two implementation reside in the sub-directorys, blur-fifo and blur0fifo-row-based with different data transfer method.
- blur-fifo transfer all required pixels of convolution for each pixel corresponding to the output image.
- blur-fifo-row-based transfer pixels with row buffers to reuse pixels between calculation of convolutions.
## Compile & Run
1. Enter either blur-fifo or blur-fifo-row-based directory and make a directory for generated binary files
    - `$ cd blur-fifo` or `cd blur-fifo-row-based`
    - `$ mkdir build`
    - `$ cd build`
2. Generate Makefiles
    - `$ cmake ..`
3. Compile the source code and run the program
    - `$ make`
    - `$ make run`
4. An output image named out.bmp will generate, which is the filtered result of image input.bmp in blur-fifo or blur-fifo-row-based.
You can replace input.bmp with a 256x256 bmp images with the same name to get corresponding output.
