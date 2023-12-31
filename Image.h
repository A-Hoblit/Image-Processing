#include <stdint.h>
#include <cstdio>
#include <complex>

enum ImageType {
	PNG, JPG, BMP, TGA
};

struct Image {
    uint8_t* data = NULL;
    size_t size = 0;
    int w;
    int h;
    int channels;

    Image(const char* filename);
    Image(int w, int h, int channels);
    Image(const Image& img);
    ~Image();

    bool read(const char* filename);
    bool write(const char* filename);

    ImageType getFileType(const char* filename);

    Image& grayscale_avg();
    Image& grayscale_lum();

    Image& colorMask(float r, float g, float b);

    Image& flipX();
    Image& flipY();
    
    Image& std_convolve_clamp_to_0(uint8_t channel, uint32_t ker_w, uint32_t ker_h, double ker[], uint32_t cr, uint32_t cc);

    Image& convolve_linear(uint8_t channel, uint32_t ker_w, uint32_t ker_h, double ker[], uint32_t cr, uint32_t cc);

/* Stegonography (hide messages in images)
    Image& encodeMessage(const char* message);
    Image& decodeMEssage(char* buffer, size_t* messageLength);
*/

};

