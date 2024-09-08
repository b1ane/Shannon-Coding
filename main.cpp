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

    std::vector<char> orderedLetters; //stores each letter in message, ordered by frequency 
    std::vector<int> orderedFrequency; //stores frequency of each letter in message, ordered by frequency 
    std::vector<float> probabilities;
    std::vector<float> accumulation;
};


void inOrder(std::vector<char>& orderedL, std::vector<int>& orderedF) {
    for( int i = 0; i < orderedF.size(); i++) {
        for( int j = i + 1; j < orderedF.size(); j++) {
            if(orderedF[j] > orderedF[i]) {
                std::swap(orderedF[i], orderedF[j]);
                std::swap(orderedL[i], orderedL[j]);
            }
        }
    }
}


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


//places letters and its frequencies in the ordered vectors, ordered by frequeny 
    for( int i = 0; i < ptr->letters.size(); i++ ) {
        if(ptr->frequency[i] > 0) {
            ptr->orderedFrequency.push_back(ptr->frequency[i]);
            ptr->orderedLetters.push_back(ptr->letters[i]);
        }
    }

    inOrder(ptr->orderedLetters, ptr->orderedFrequency);

//find probabilities
    int sum = 0;
    for( int i = 0; i < ptr->orderedFrequency.size(); i++ ) {
        sum = sum + ptr->orderedFrequency[i];
    }

    ptr->probabilities.resize(ptr->orderedFrequency.size());

    for( int i = 0; i < ptr->orderedFrequency.size(); i++ ) {
        ptr->probabilities[i] = static_cast<float>(ptr->orderedFrequency[i]) / sum;
    }

//accumulation
    ptr->accumulation.resize(ptr->probabilities.size());

    ptr->accumulation[0] = 0.0; //first symbol is always 0
    for( int i = 1; i < ptr->probabilities.size(); i++) {
        ptr->accumulation[i] = ptr->accumulation[i-1] + ptr->probabilities[i-1]; 
    }



    return ptr;
}

//main thread reads input
int main() {
    std::string line;
    std::vector<Data> lines;

    Data temp;

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
        std::cout << std::endl;
        std::cout << "Alphabet: " << std::endl;
        for(int j = 0; j < lines[i].orderedLetters.size(); j++) {
            std::cout << "Symbol: " << lines[i].orderedLetters[j];
            std::cout << ", Frequency: " << lines[i].orderedFrequency[j] << std::endl;
        }
        std::cout<<std::endl;

    }

    if(tid!=nullptr){
        delete[] tid;
    }

    return 0;
}