#include "student.h"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

Student::Student(int id_val, const string& name_val, const string& address_val, 
                 const string& phone_val, const string& major_val, int year_val)
    : Person(id_val, name_val, address_val, phone_val), major(major_val), year(year_val) {}

void Student::display() const {
    cout << "--- Student Details ---" << endl;
    cout << "ID: " << id << endl;
    cout << "Name: " << name << endl;
    cout << "Major: " << major << endl;
    cout << "Year: " << year << endl;
    cout << "Address: " << address << endl;
    cout << "Phone: " << phone << endl;
    
    if (!grades.empty()) {
        cout << "--- Grades ---" << endl;
        for (auto const& [course_id, grade] : grades) {
            cout << "Course " << course_id << ": " << grade << endl;
        }
    }
}
//saving stud data in text file 
void Student::save_to_file() const {
    ofstream file("students.txt", ios::app);
    if (file.is_open()) {
        // Format: ID,Name,Address,Phone,Major,Year,Grades...
        file << id << "," << name << "," << address << "," << phone << "," << major << "," << year;
        
        // Save grades: CourseID1:Grade1|CourseID2:Grade2...
        file << ",";
        for (auto const& [course_id, grade] : grades) {
            file << course_id << ":" << grade << "|";
        }
        file << "\n";
        file.close();
    }
}

// Student specific methods

void Student::enroll_course(int course_id) {
    if (grades.find(course_id) == grades.end()) {
        grades[course_id] = "N/A";
    }
}

void Student::set_grade(int course_id, const string& grade_val) {
    if (grades.count(course_id)) {
        grades[course_id] = grade_val;
    } else {
        cout << "Error: Student not enrolled in course ID " << course_id << endl;
    }
}


void Student::load_grade_data(int course_id, const string& grade_val) {
    grades[course_id] = grade_val;
}

const map<int, string>& Student::get_grades() const {
    return grades;
}