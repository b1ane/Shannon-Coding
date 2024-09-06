//Write your program here
#include <iostream>
#include <string>
#include <vector>
#include <pthread.h>


struct Data {
    std::vector<char> letters; //stores each letter in message
    std::vector<int> frequency; //stores frequency of each letter in message
    std::vector<int> shannon; //stores shannon code for each letter in message
    std::string line; //message
    std::string encoded;
};


void* freq(void* void_ptr) {
    Data* ptr = (Data*) void_ptr;

    //stores each letter in string into its own vector 
    for(int i = 0; i < ptr->line.size(); i++) {
        ptr->letters.push_back(ptr->line[i]);
    }

    ptr->frequency.resize(ptr->letters.size(),0);

    //count frequency of each letter in the string
    for( int i = 0; i < ptr->letters.size(); i++) {
        char current = ptr->letters[i];
        bool isDupe = false;

        for(int j = 0; j < i; j++) {
            if(ptr->letters[j] == current) {
                isDupe=true;
                break;
            }
        }


        if(!isDupe) {
            int count = 0; 
            for(int j = 0; j < ptr->letters.size(); j++) {
                if(ptr->letters[j] == current) {
                    count++;
                }
            }
            ptr->frequency[i] = count;
        }
    }

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

        lines.push_back(temp); //adds struct instance to vector
    }

    //Create n POSIX threads (where n is the number of input strings)
    int numLines = lines.size();
    pthread_t* tid = new pthread_t[numLines];

//Call pthread_create
    for( int i= 0; i < numLines; i++) {
        if(pthread_create(&tid[i], nullptr, freq, (void*) &lines.at(i)) != 0) {
            std::cerr << "Error creating thread" << std::endl;
            return 1;
        }
    }

//Call pthread_join
    for( int i = 0; i < numLines; i++) {
        pthread_join(tid[i],nullptr);
    }

//Prints the information from the child threads into STDOUT
    for( int i = 0; i < numLines; i++ ) {
        std::cout << "Message: " << lines[i].line << std::endl;
        std::cout << "Alphabet: " << std::endl;
        for( int j = 0; j < lines[i].letters.size(); j++) {
            if(lines[i].frequency[j] > 0) {
                std::cout << "Symbol: " << lines[i].letters[j];
                std::cout << ", Frequency: " << lines[i].frequency[j] << std::endl;
            }
        }
        std::cout<<std::endl;

    }

    if(tid!=nullptr){
        delete[] tid;
    }





    return 0;
}