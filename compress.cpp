#include "compress.h"
#include "image.h"
#include <iostream>

bool compress_image(const std::string &input_filename, const std::string &output_filename, int quality) {
    try {
        Image image(input_filename);
        if (!image.write(output_filename, quality)) {
            return false;
        }
    } catch (const std::exception &e) {
        std::cerr << e.what() << '\n';
        return false;
    }
    return true;
}

bool convert_image(const std::string &input_filename, const std::string &output_filename) {
    try {
        Image image(input_filename);
        if (!image.write(output_filename, 100)) {
            return false;
        }
    } catch (const std::exception &e) {
        std::cerr << e.what() << '\n';
        return false;
    }
    return true;
}
