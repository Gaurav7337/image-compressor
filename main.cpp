#include <iostream>
#include <string>
#include "image.h"
#include "compress.h"

int main(int argc, char *argv[]) {
    if (argc != 5) {
        std::cout << "Usage: " << argv[0] << " <compress|convert> <input file> <output file> <quality>\n";
        return 1;
    }

    std::string command = argv[1];
    std::string inputFile = argv[2];
    std::string outputFile = argv[3];
    int quality = std::stoi(argv[4]);

    if (command == "compress") {
        if (compress_image(inputFile, outputFile, quality)) {
            std::cout << "Compression successful.\n";
        } else {
            std::cout << "Compression failed.\n";
        }
    } else if (command == "convert") {
        if (convert_image(inputFile, outputFile)) {
            std::cout << "Conversion successful.\n";
        } else {
            std::cout << "Conversion failed.\n";
        }
    } else {
        std::cout << "Unknown command: " << command << '\n';
        return 1;
    }

    return 0;
}
