#include <iostream>
#include <fstream> // for file handling
#include <string> // this is for the read file purpose, clean the data
#include <vector> // for processing the exam score data

using namespace std; // we use this just to simplify the writing

struct Student {
    string id;
    float marks;
    // here we use struct for better managing the input data, seperate out the id and the marks
};

// partition used to swap the position, then find out the pivot for the partition
int partition(vector<Student>& arr, int low, int high){
    float pivot = arr[high].marks; // the last position will become the pivot
    int i =(low-1); // position of the i we set it before the j

    for(int j = low; j < high; j++){
        // partitioning based on floating point comparison, smaller than pivot go to left, larger go to right
        if(arr[j].marks < pivot){ //if the mark of the j smaller than pivot mark
            i++; // move the i point to the next position (i point to the sorted arr)
            // swap the position using temp
            Student temp = arr[i];
            arr[i] = arr[j];
            arr[j]= temp;
        }
    } // for loop end when the j point to the last position

    Student temp = arr[i + 1]; // swap the position of the pivot to the current i position + 1
    arr[i + 1] = arr[high];
    arr[high] = temp;

    return (i + 1); // return the position of this time run
}


// standard function on processing quicksort
void quicksort(vector<Student>& arr, int low, int high){ //pass the vector reference 
    if(low < high){ // if the first position not yet pass the last position
        int pivot_index = partition(arr, low, high);
        quicksort(arr, low, pivot_index -1);
        quicksort(arr, pivot_index + 1, high);
    }
}

void insertionSort(vector<Student>& arr) {
    int n = arr.size();
    for (int i = 1; i < n; i++) {
        Student key = arr[i];
        int j = i - 1;

        while (j >= 0 && arr[j].marks > key.marks) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}




int main(){
    cout << "This is the Insertion Sort & Quick Sort Application on Student Exam Scores\n";

    vector<Student> studentlist; // declare a vector, it help us to process the data more conveniently
    ifstream StudentScore ("ExamScore.txt");

    //Read the file
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
        }
        StudentScore.close(); // close the file after reads all the data.
    }else{ // this is the exception case
        cout << "Error: Could not find the exam file" << endl;
        return 1;
    }
    
    // Now we proceed to process studentlist after we added all the list
    if (!studentlist.empty()){
        int choice;
        cout << "Please choose your preferred sort method: "<< endl;
        cout << "1. Quick Sort\n";
        cout << "2. Insertion Sort\n";
        cout << "Enter choice (1 or 2): ";
        cin >> choice;

        if (choice == 1) {
            // pass the vector struct to the quicksort function
            // three thing to pass, one is array, one is the begining position, one is last position
            quicksort(studentlist, 0, studentlist.size() - 1);
            cout << "Successfully sorted using Quick Sort!" << endl;
        } else if (choice == 2) {
            insertionSort(studentlist);
            cout << "Successfully sorted using Insertion Sort!" << endl;
        } else {
            cout << "Invalid choice. Sorting skipped." << endl;
        }
    }
        
    cout << "\nSorted Results (ID, Marks): \n";
        
    // we use auto& to save memory in running since it is using reference
    for (const auto& s : studentlist){
        cout << s.id << "," << s.marks << endl;
    }

    ofstream outputStudentScore("Sorted_ExamScore.txt");
    if (outputStudentScore.is_open()) {
        // similar meethod on cout
        for (const auto& s : studentlist) {
            // Writing format: ID,Marks
            outputStudentScore << s.id << ", " << s.marks << endl;
        }
        outputStudentScore.close();
        cout << "Sorted data has been saved to 'Sorted_ExamScore.txt'.\n";
    } else {
        cout << "Error: Could not create output file." << endl;
    }



   
    return 0;
}