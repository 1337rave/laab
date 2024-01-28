#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>

void searchAndReplace(std::string& source, const std::string& search, const std::string& replace, int& replacements) {
    size_t pos = 0;
    replacements = 0;
    while ((pos = source.find(search, pos)) != std::string::npos) {
        source.replace(pos, search.length(), replace);
        pos += replace.length();
        replacements++;
    }
}

void displayFileContents(const std::string& filePath) {
    std::ifstream file(filePath);
    if (!file.is_open()) {
        std::cerr << "Unable to open file: " << filePath << std::endl;
        return;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::cout << line << std::endl;
    }
    file.close();
}

void reverseFileContents(const std::string& filePath) {
    std::ifstream file(filePath);
    if (!file.is_open()) {
        std::cerr << "Unable to open file: " << filePath << std::endl;
        return;
    }

    std::string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    std::reverse(content.begin(), content.end());
    std::cout << content << std::endl;

    file.close();
}

int main() {
    std::string filePath;
    std::cout << "Enter the path to the file: ";
    std::getline(std::cin, filePath);

    std::ifstream file(filePath);
    if (!file.is_open()) {
        std::cerr << "Unable to open file: " << filePath << std::endl;
        return 1;
    }
    file.close();

    std::string input;
    while (true) {
        std::cout << "\nMenu:\n1. Search and replace\n2. Display file contents\n3. Reverse file contents\n4. Exit\n";
        std::cout << "Choose an option: ";
        std::getline(std::cin, input);

        if (input == "1") {
            std::string search, replace;
            std::cout << "Enter the string to search: ";
            std::getline(std::cin, search);
            std::cout << "Enter the replacement string: ";
            std::getline(std::cin, replace);

            std::ifstream infile(filePath);
            std::string content((std::istreambuf_iterator<char>(infile)), std::istreambuf_iterator<char>());
            infile.close();

            int replacements = 0;
            searchAndReplace(content, search, replace, replacements);
            std::ofstream outfile(filePath);
            outfile << content;
            outfile.close();

            std::cout << "Replacements: " << replacements << std::endl;
        }
        else if (input == "2") {
            displayFileContents(filePath);
        }
        else if (input == "3") {
            reverseFileContents(filePath);
        }
        else if (input == "4") {
            break;
        }
        else {
            std::cout << "Invalid input. Please try again." << std::endl;
        }
    }

    return 0;
}
