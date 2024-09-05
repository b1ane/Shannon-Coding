//Write your program here
#include <iostream>
#include <string>
#include <vector>
#include <pthread.h>


struct Data {
    char letter;
    int frequency;
    std::string line;
};


void* freq(void* void_ptr) {
    Data* ptr = (Data*) void_ptr;

    return ptr;
}

//main thread reads input
int main() {
    std::string line;
    std::vector<Data> lines;

    Data temp;

    std::cout << "Enter lines of text: " << std::endl;
    while(std::getline(std::cin, line)) {
        if(line.empty()) {
            break;
        }

        temp.line = line; //stores line in the Data structure 
        temp.letter = '\0'; //initializes letter 
        temp.frequency = 0; //initializes frequency 

        lines.push_back(temp); //adds struct instance to vector
    }

    int numLines = lines.size();
    pthread_t* tid = new pthread_t[numLines];

    for( int i= 0; i < numLines; i++) {
        if(pthread_create(&tid[i], nullptr, freq, (void*) &lines.at(i)) != 0) {
            std::cerr << "Error creating thread" << std::endl;
            return 1;
        }
    }

    for( int i = 0; i < numLines; i++) {
        pthread_join(tid[i],nullptr);
    }

    for( int i = 0; i < numLines; i++ ) {
        std::cout << "Message: " << lines[i].line << std::endl;
    }

    if(tid!=nullptr){
        delete[] tid;
    }





    return 0;
}