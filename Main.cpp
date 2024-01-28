#include <iostream>
#include <fstream>
#include <string>

bool isValidHTML(const std::string& filePath) {
    std::ifstream file(filePath);
    if (!file.is_open()) {
        std::cerr << "Unable to open file: " << filePath << std::endl;
        return false;
    }

    int openTagCount = 0;
    int closeTagCount = 0;

    std::string line;
    while (std::getline(file, line)) {
        size_t pos = 0;
        while ((pos = line.find('<', pos)) != std::string::npos) {
            size_t endPos = line.find('>', pos);
            if (endPos == std::string::npos) {
                std::cerr << "Error: Unclosed tag found." << std::endl;
                return false;
            }

            std::string tag = line.substr(pos, endPos - pos + 1);
            if (tag[1] == '/') {
                closeTagCount++;
            }
            else {
                openTagCount++;
            }

            pos = endPos + 1;
        }
    }
    file.close();

    if (openTagCount != closeTagCount) {
        std::cerr << "Error: Number of opening tags does not match number of closing tags." << std::endl;
        return false;
    }

    return true;
}

int main() {
    std::string filePath;
    std::cout << "Enter the path to the HTML file: ";
    std::getline(std::cin, filePath);

    if (isValidHTML(filePath)) {
        std::cout << "The HTML file is valid." << std::endl;
    }
    else {
        std::cout << "The HTML file is not valid." << std::endl;
    }

    return 0;
}
