# Edge Detection and Processing

Convolution based Edge Detection in C++ and other simple image processing algorithms.

The main feature is the edge detection algorithm, but this project also includes grayscale, blurring, flipping and various convolution uses like embossing.

## Screenshots

Initial Image

![input](https://github.com/A-Hoblit/Image-Processing/blob/main/input.jpg?raw=true)

First pass, grayscale + blur

![input](https://github.com/A-Hoblit/Image-Processing/blob/main/output/2%20-%20blur.png?raw=true)

Horizontal and Vertical edge detections

![input](https://github.com/A-Hoblit/Image-Processing/blob/main/output/3%20-%20Gx.png?raw=true)

![input](https://github.com/A-Hoblit/Image-Processing/blob/main/output/3%20-%20Gy.png?raw=true)

Merged final image

![input](https://github.com/A-Hoblit/Image-Processing/blob/main/output/4%20-%20G.png?raw=true)

## Using this code

1. Clone the repository

`git clone https://github.com/A-Hoblit/Image-Processing.git`

2. Compile main.cpp and image.cpp with your preferred C++ compiler, I used GCC

`g++ main.cpp image.cpp`

3. Place your input image "input.jpg" in the repository folder, replacing the default one, and run. All output images are deposited in the output folder.

Other simple image processing uses can be found in the test.cpp file.
 

