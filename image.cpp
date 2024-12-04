#include "image.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"
#include <iostream>
#include <cstring> // Include <cstring> for strrchr and strcmp
#include <stdexcept>

Image::Image(const std::string &filename) : data(nullptr), width(0), height(0), channels(0) {
    data = stbi_load(filename.c_str(), &width, &height, &channels, 0);
    if (!data) {
        std::cerr << "Error loading image: " << filename << '\n';
        std::cerr << "Reason: " << stbi_failure_reason() << '\n';
        throw std::runtime_error("Error loading image");
    }
}

Image::~Image() {
    freeImage(); // Call freeImage in the destructor
}

bool Image::write(const std::string &filename, int quality) const {
    const char *ext = strrchr(filename.c_str(), '.');
    if (!ext) {
        std::cerr << "No file extension found.\n";
        return false;
    }

    if (strcmp(ext, ".jpg") == 0 || strcmp(ext, ".jpeg") == 0) {
        if (!stbi_write_jpg(filename.c_str(), width, height, channels, data, quality)) {
            std::cerr << "Error writing JPEG image: " << filename << '\n';
            return false;
        }
    } else if (strcmp(ext, ".png") == 0) {
        if (!stbi_write_png(filename.c_str(), width, height, channels, data, width * channels)) {
            std::cerr << "Error writing PNG image: " << filename << '\n';
            return false;
        }
    } else if (strcmp(ext, ".bmp") == 0) {
        if (!stbi_write_bmp(filename.c_str(), width, height, channels, data)) {
            std::cerr << "Error writing BMP image: " << filename << '\n';
            return false;
        }
    } else {
        std::cerr << "Unsupported file format: " << filename << '\n';
        return false;
    }

    return true;
}

void Image::freeImage() {
    if (data) {
        stbi_image_free(data);
        data = nullptr;
    }
}

