#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION

#include "stb_image/stb_image.h"
#include "stb_image/stb_image_write.h"

#include "Image.h"

#define STEG_HEADER_SIZE sizeof(uint32_t) * 8;


Image::Image(const char* filename){
    if(read(filename)) {
        printf("Read %s\n", filename);
        size = w*h*channels;
    }
    else {
        printf("Failed to read %s\n", filename);
    }
}
Image::Image(int w, int h, int channels) : w(w), h(h), channels(channels){
    size = w*h*channels;
    data = new uint8_t[size];
}
Image::Image(const Image& img) : Image(img.w, img.h, img.channels){
    memcpy(data, img.data, img.size);

}
Image::~Image(){
    stbi_image_free(data);
}

bool Image::read(const char* filename){
    data = stbi_load(filename, &w, &h, &channels, 0);
    return data != NULL;
}
bool Image::write(const char* filename) {
    ImageType type = getFileType(filename);
    int success;
    switch (type) {
        case PNG:
        success = stbi_write_png(filename, w, h, channels, data, w*channels);
        break;
        case BMP:
        success = stbi_write_bmp(filename, w, h, channels, data);
        break;
        case JPG:
        success = stbi_write_jpg(filename, w, h, channels, data, 100);
        break;
        case TGA:
        success = stbi_write_tga(filename, w, h, channels, data);
        break;
    }

    if(success != 0) {
        printf("\e[32mWrote \e[36m%s\e[0m, %d, %d, %d, %zu\n", filename, w, h, channels, size);
        return true;
    }
    else {
        printf("\e[31;1m Failed to write \e[36m%s\e[0m, %d, %d, %d, %zu\n", filename, w, h, channels, size);
        return false;
    }


}

ImageType Image::getFileType(const char* filename) {
    const char* ext = strrchr(filename, '.');
    if(ext != nullptr) {
        if(strcmp(ext, ".png") == 0) {
            return PNG;
        }
        else if(strcmp(ext, ".jpg") == 0) {
            return JPG;
        }
        else if(strcmp(ext, ".bmp") == 0) {
            return BMP;
        }
        else if(strcmp(ext, ".tga") == 0) {
            return TGA;
        }
    }
    return PNG;
}

Image& Image::grayscale_avg(){
    // r+g+b/3
    if(channels < 3) {
        printf("Image %p has less than 3 channels, it is assumed to be already grayscale", this);
    }
    else {
        for (int i=0; i < size; i += channels) {
            int gray = (data[i] + data[i+1] + data[i+2]) / 3;
            memset(data+i, gray, 3);
        }
    }
    return *this;
}

Image& Image::grayscale_lum(){
    //Gamma expansion, normalized for the human eye
    if(channels < 3) {
        printf("Image %p has less than 3 channels, it is assumed to be already grayscale", this);
    }
    else {
        for (int i=0; i < size; i += channels) {
            int gray = 0.2126*data[i] + 0.7152*data[i+1] + 0.0722*data[i+2];
            memset(data+i, gray, 3);
        }
    }
    return *this;
}

Image& Image::colorMask(float r, float g, float b) {
    if (channels < 3) {
        printf("\e[31m[Error] Color mask requires at least 3 channels]");
    }
    else{
        for (int i=0; i < size; i += channels) {
            data[i] *= r;
            data[i+1] *= g;
            data[i+2] *= b;
        }
    }
    return *this;
}

Image& Image::flipX() {
    uint8_t tmp[4];
    uint8_t* px1;
    uint8_t* px2;
    for(int y=0;y < h;++y) {
        for(int x=0;x < w/2;++x) {
            px1 = &data[(x + y * w) * channels];
            px2 = &data[((w - 1 - x) + y * w) * channels];
            
            memcpy(tmp, px1, channels);
            memcpy(px1, px2, channels);
            memcpy(px2, tmp, channels);
        }
    }
    return *this;
}

Image& Image::flipY() {
    uint8_t tmp[4];
    uint8_t* px1;
    uint8_t* px2;
    for(int x=0;x < w;++x) {
        for(int y=0;y < h/2;++y) {
            px1 = &data[(x + y * w) * channels];
            px2 = &data[(x + (h - 1 - y) * w) * channels];

            memcpy(tmp, px1, channels);
            memcpy(px1, px2, channels);
            memcpy(px2, tmp, channels);
        }
    }
    return *this;
}

/* Stegonography (hide messages in images)
Image& Image::encodeMessage(const char* message){
    uint32_t len = strlen(message) * sizeof(char);
    for(uint8_t i=0; i < STEG_HEADER_SIZE; ++i){
        data[i] |= (len >> (STEG_HEADER_SIZE - 1 - i)) & 1UL;
    }

    return *this
}
Image& Image::decodeMEssage(char* buffer, size_t* messageLength){

}
*/
