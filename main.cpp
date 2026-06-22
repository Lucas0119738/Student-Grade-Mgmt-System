#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include <iomanip>

using namespace std;

template <typename T>            /*Template*/
T getMax(T a, T b) {
    return (a > b) ? a : b;
}

template <typename T>
T getMin(T a, T b) {
    return (a < b) ? a : b;
}

struct Student {                 /*Student Structure*/
    string id;
    string name;
    int score;
};

void addStudent(map<string, Student>& s_map) {            /*Function1:add student info*/
    string id, name;
    int score;
    
    cout <<"\n"<< "Add Student->" << endl;
    cout << "Enter ID: ";
    cin >> id;
    
    if (s_map.find(id) != s_map.end()) {                                      /*Check if exist */
        cout << "Error: ID " << id << " already exists."<< endl;
        return;
    }
    
    cout << "Enter Name: ";
    cin >> name;
    cout << "Enter Score: ";
    while (!(cin >> score) || score < 0 || score > 100) {                             /*Check if 1-100*/
        cout << "Invalid score. Please enter an integer between 0 and 100: ";
        cin.clear();
        cin.ignore(1000, '\n');
    }
    
    s_map[id] = {id, name, score};
    cout << "Successfully added student: " << name << endl;
}

void listStudents(const map<string, Student>& s_map) {                              /*Function2:list student*/
    cout <<"\n"<< "All Students->" << endl;
    if (s_map.empty()) {
        cout << "No student data available."<< endl;
        return;
    }

    cout << left << setw(12) << "ID" << setw(15) << "Name" << "Score" << endl;      /*<iomanip>排版*/
    cout << "---------------------------------------" << endl;
    for (const auto& pair : s_map) {
        const Student& s = pair.second;
        cout << left << setw(12) << s.id << setw(15) << s.name << s.score << endl;
    }
}

void sortByScore(const map<string, Student>& s_map) {                       /*Function3:sort by score*/
    cout << "\n" << "Sorted by Score (High to Low)->" << endl;
    if (s_map.empty()) {
        cout << "No student data available." << endl;
        return;
    }

    vector<Student> temp_vec;                                /*vector to sort*/
    for (const auto& pair : s_map) {
        temp_vec.push_back(pair.second);
    }
    
    sort(temp_vec.begin(), temp_vec.end(), [](const Student& a, const Student& b) {             /*<algorithm>*/
        return a.score > b.score;
    });
    
    cout << left << setw(6) << "Rank" << setw(12) << "ID" << setw(15) << "Name" << "Score" << endl;  /*<iomanip>*/
    cout << "-----------------------------------------------" << endl;
    int rank = 1;
    for (const auto& s : temp_vec) {
        cout << left << setw(6) << rank++ << setw(12) << s.id << setw(15) << s.name << s.score << endl;
    }
}

void searchById(const map<string, Student>& s_map) {                            /*Function4:search student*/
    cout << "Search Student->" << endl;
    if (s_map.empty()) {
        cout << "No student data available." << endl;
        return;
    }
    
    string id;
    cout << "Enter ID to search: ";
    cin >> id;
    
    auto it = s_map.find(id);
    if (it != s_map.end()) {
        const Student& s = it->second;
        cout << "Data found:" << endl;
        cout << "ID: " << s.id << "\nName: " << s.name << "\nScore: " << s.score << endl;
    } else {
        cout << "Cannot find student with ID " << id << ".\n";
    }
}

void showStatistics(const map<string, Student>& s_map) {                /*Fuction5:all stastic(with template)*/
    cout << "Class Statistics->" << endl;
    if (s_map.empty()) {
        cout << "No student data ." << endl;;
        return;
    }
    
    int total_students = s_map.size();
    double sum = 0;
    int max_score = -1;
    int min_score = 101;
    int pass_count = 0;
    int fail_count = 0;
    
    string max_student, min_student;
    
    for (const auto& pair : s_map) {
        const Student& s = pair.second;
        sum += s.score;
        

        int updated_max = getMax(max_score, s.score);                     /*template Max*/
        if (updated_max != max_score) {
            max_score = updated_max;
            max_student = s.name;
        }
        
        int updated_min = getMin(min_score, s.score);                     /*template Min*/
        if (updated_min != min_score) {
            min_score = updated_min;
            min_student = s.name;
        }

        if (s.score >= 60) {                                        /*Fail student*/
            pass_count++;
        } else {
            fail_count++;
        }
    }
    
    cout << "Class Average: " << fixed << setprecision(2) << (sum / total_students) << endl;
    cout << "Highest Score: " << max_score << " (" << max_student << ")" << endl;
    cout << "Lowest Score:  " << min_score << " (" << min_student << ")" << endl;
    cout << "Pass Count:    " << pass_count << endl;
    cout << "Fail Count:    " << fail_count << endl;
}

int main() {
    map<string, Student> students_map;
    int choice;
    
    do {
        cout << " Student Grade Mgmt System--->" << endl;               /*Menu 0-6*/
        cout << "1. Add student" << endl;
        cout << "2. List all students" << endl;
        cout << "3. Sort by score" << endl;
        cout << "4. Search by id" << endl;
        cout << "5. Show statistics" << endl;
        cout << "0. Exit" << endl;
        cout << "Enter your choice (0-5): ";

        if (!(cin >> choice)) {                                         /*if enter letter*/
            cout << "Please enter a valid numerical choice.";
            cin.clear();
            cin.ignore(1000, '\n');
            continue;
        }
        
        switch (choice) {
            case 1: addStudent(students_map); break;
            case 2: listStudents(students_map); break;
            case 3: sortByScore(students_map); break;
            case 4: searchById(students_map); break;
            case 5: showStatistics(students_map); break;
            case 0: cout << "\nThank you for using the system. Goodbye!\n"; break;
            default: cout << "Invalid choice, please try again.\n"; break;
        }
    } while (choice != 0);
    
    return 0;
}