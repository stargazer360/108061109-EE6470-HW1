# Hw1 Report by 108061109
In this homework, a 3x3 approximated gaussian blur filter for 256x256 image is implemented in SystemC, based on the sobel-fifo source code in lab2.
## Implementation
Two modules, blur_filter and testbench, are constructed and connected with fifo for pixel transaction.
- The blur_filter calculated the convolution based on the given pixels with approximation 3x3 kernel.
- The testbench deal with IO of the image file and manage how pixel is transferred.

Pixels with color channel 0x0x0 are set and sent to filter for the calculation of pixels on the boundary

There are two different method for pixel transaction in this homework.
### Pixel-Based
For each pixel in the output, the testbench will send all of required pixels to filters, which is a 3x3 block of pixels centered at the corresponding pixel in the input.
### Row-Based
The testbench would first sent two rows of pixels to the filter. Then, for the successive transaction, The filter will calculated the convolution for each pixel in the corresponding output row once each required pixels has arrived. 
Once a row of calculation is finished, the rows in row buffers shift to new row to compute new output row pixels. There are three row buffers kept in the thread locally in the implementation.

Counters are added corresponding to each write or read call involving pixel transfer in the testbench for following part. 
## Experimental result
| Method | To filter | to testbench | total  |
|-----------------|-----------|--------------|--------|
| Pixel-Based     | 589824    | 65536        | 655360 |
| Row-Based       | 66564     | 65536        | 132100 |

The table shows the number of pixels transfer with the direction.  
The number of pixels transfer to the filter with row-based method reduce to about 1/9 of the number with pixel-based method. This is reasonable as the pixel-based method transfer 9 pixels for each pixels in the output, and the row-based method, on the other hand, transfer each pixels of the input only once.  
For the number of the pixel transferring to the testbench, , since the output of the filter is corresponding to the output image size, the results are  identical in the two methods.  
The row-based method reduce the number of pixel transfer to about 1/5 of the number with pixel-based method.
## Conclusion
The row-based method gives out a better performance on the number of pixel transfer against the pixel-based method, with a trade-off of more storage space needed.
