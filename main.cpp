//Write your program here
#include <iostream>
#include <string>
#include <vector>

int main() {
    std::string line;
    std::vector<std::string> lines;

    std::cout << "Enter lines of text: " << std::endl;

    while(std::getline(std::cin, line)) {
        if(line.empty()) {
            break;
        }
        lines.push_back(line);
    }

    for(int i = 0; i < lines.size(); i++) {
        std::cout << lines.at(i) << std::endl;
    }

    return 0;
}