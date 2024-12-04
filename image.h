#ifndef IMAGE_H
#define IMAGE_H

#include <string>

class Image {
private:
    unsigned char *data;
    int width;
    int height;
    int channels;

public:
    Image(const std::string &filename);
    ~Image();
    bool write(const std::string &filename, int quality) const;

private:
    void freeImage(); // Declare freeImage as private member function
};

#endif // IMAGE_H

