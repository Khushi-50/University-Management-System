#include "course.h"
#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;

Course::Course(int id_val, const string& title_val, int credits_val, int faculty_id_val)
    : course_id(id_val), title(title_val), credits(credits_val), faculty_id(faculty_id_val) {}

int Course::get_id() const {
    return course_id;
}

int Course::get_faculty_id() const {
    return faculty_id;
}

const vector<int>& Course::get_students() const {
    return student_ids;
}

void Course::assign_faculty(int new_faculty_id) {
    faculty_id = new_faculty_id;
}

void Course::add_student(int student_id) {
    if (find(student_ids.begin(), student_ids.end(), student_id) == student_ids.end()) {
        student_ids.push_back(student_id);
    }
}
void Course::load_student_id(int student_id) {
    student_ids.push_back(student_id);
}

//overriden dusplay function definition
void Course::display() const {
    cout << "--- Course Details ---" << endl;
    cout << "Code: " << course_id << endl;
    cout << "Title: " << title << endl;
    cout << "Credits: " << credits << endl;
    cout << "Instructor ID: " << faculty_id << endl;
    cout << "Total Enrolled: " << student_ids.size() << endl;
}

void Course::save_to_file() const {
    ofstream file("courses.txt", ios::app);
    if (file.is_open()) {
        file << course_id << "," << title << "," << credits << "," << faculty_id;
        
        // Saving  enrolled students
        file << ",";
        for (int student_id : student_ids) {
            file << student_id << "|";
        }
        file << "\n";
        file.close();
    }
}