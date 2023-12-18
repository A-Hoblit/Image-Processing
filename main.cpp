#include "Image.h"

int main(int argc, char** argv) {
    Image test("test.jpg");

    // Test color masking
    test.colorMask(0, 1, 1);
    test.write("blue.png");

    // Test grayscale
    /*
    Image gray_avg = test;
    gray_avg.grayscale_avg();
    gray_avg.write("gray_avg.png");

    Image gray_lum = test;
    gray_lum.grayscale_lum();
    gray_lum.write("gray_lum.png");
    */

    // Test reading, writing and creating
    /*
    test.write("new.png");
    Image copy = test;
    for(int i=0; i<copy.w*copy.channels; ++i) {
        copy.data[i] = 255;
    }
    copy.write("copy.png");

    Image blank(100, 100, 3);
    blank.write("blank.jpg");
    */
    return 0;
}