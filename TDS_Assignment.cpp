#include <iostream>
#include <fstream> // for file handling
#include <string> // this is for the read file purpose, clean the data
#include <vector> // for processing the exam score data

using namespace std; // we use this just to simplify the writing

struct Student {
    string id;
    float marks;
    // here we use struct for better managing the input data, seperate out the id and the marks
}

int partition()
void quicksort()


int main(){
    cout << "This is the Insertion Sort & Quick Sort Application on Student Exam Scores\n";

    vector<Student> studentlist; // declare a vector, it help us to process the data more conveniently
    fstream StudentScore;
    
    StudentScore.open("ExamScore.txt", ios::in); // this is the read file
    if (StudentScore.is_open()){
        string line;
        // using while loop to read the file, end when no more line to read
        while (getline(StudentScore, line)){
            // if the current is empty, process to next line
            if (line.empty()) continue;
            
            // using the unsigned integer method to store the position
            size_t comma_position = line.find(',');
            // In here, we use string::npos to check if comma exist ('no position'), so the program proceed if the comma position found
            if (comma_position != string::npos){
                // declare a string to store the ID
                string ID_part = line.substr(0,comma_position);
                // declare another string to store the marks
                string Score_part = line.substr(comma_position + 1);

                // here we declare a lcoal object to store the ID and score, then later we push it to our struct vector 
                Student s;
                s.id = ID_part;
                // for the student's score, we use try and catch for better error handling since there might possible the file contain invalid data
                try{
                    // convert the score format from string to float
                    s.marks = stof(Score_part);
                    // push the object s to the studentlist vector
                    studentlist.push_back(s);
                }catch(...){
                    // it catch all types error
                    continue;
                }
            }
            StudentScore.close(); // close the file after reads all the data.

        }
    }






}