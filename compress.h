#ifndef COMPRESS_H
#define COMPRESS_H

#include <string>

bool compress_image(const std::string &input_filename, const std::string &output_filename, int quality);
bool convert_image(const std::string &input_filename, const std::string &output_filename);

#endif // COMPRESS_H
