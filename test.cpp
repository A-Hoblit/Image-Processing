#include "Image.h"

void testIO(Image test) {
    test.write("output/new.png");
    Image copy = test;
    for(int i=0; i<copy.w*copy.channels; ++i) {
        copy.data[i] = 255;
    }
    copy.write("output/copy.png");

    Image blank(100, 100, 3);
    blank.write("output/blank.jpg");  
}

void testGrayscale(Image test){
    Image gray_avg = test;
    gray_avg.grayscale_avg();
    gray_avg.write("output/gray_avg.png");

    Image gray_lum = test;
    gray_lum.grayscale_lum();
    gray_lum.write("output/gray_lum.png");
}
void testColorMask(Image test){
    Image bluegreen = test;
    bluegreen.colorMask(0, 1, 1);
    bluegreen.write("output/bluegreen.png");

    Image redblue = test;
    redblue.colorMask(1, 0, 1);
    redblue.write("output/redblue.png");

    Image redgreen = test;
    redgreen.colorMask(1, 1, 0);
    redgreen.write("output/redgreen.png");
}
void testFlipping(Image test) {
    Image flippedX = test;
    flippedX.flipX();
    flippedX.write("output/flippedX.png");

    Image flippedY = test;
    flippedY.flipY();
    flippedY.write("output/flippedY.png");
}

void testConvolutionBlur(Image test) {
    Image blurred = test;
    double blur_kernel[9] = { 
        1/9.0, 1/9.0, 1/9.0,
        1/9.0, 1/9.0, 1/9.0,
        1/9.0, 1/9.0, 1/9.0 
    };

    blurred.std_convolve_clamp_to_0(0, 3, 3, blur_kernel, 1, 1);
    blurred.std_convolve_clamp_to_0(1, 3, 3, blur_kernel, 1, 1);
    blurred.std_convolve_clamp_to_0(2, 3, 3, blur_kernel, 1, 1);
    blurred.write("output/blurred.png");
}

void testConvolutionEmboss(Image test){
    Image sharpened = test;
	double emboss_kernel[9] = {
		-2/9.0,-1/9.0, 0,
		-1/9.0, 1/9.0, 1/9.0,
		 0,     1/9.0, 2/9.0
	};

    sharpened.std_convolve_clamp_to_0(0, 3, 3, emboss_kernel, 1, 1);
    sharpened.std_convolve_clamp_to_0(1, 3, 3, emboss_kernel, 1, 1);
    sharpened.std_convolve_clamp_to_0(2, 3, 3, emboss_kernel, 1, 1);
    sharpened.write("output/embossAll.png");
}

int main(int argc, char** argv) {
    Image test("test.jpg");
    Image test2("test2.jpg");

    //testIO(test);
    //testGrayscale(test);
    //testColorMask(test);
    //testFlipping(test);
    testConvolutionBlur(test);
    testConvolutionEmboss(test2);

    return 0;
}