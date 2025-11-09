#include "faculty.h"
#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;

Faculty::Faculty(int id_val, const string& name_val, const string& address_val, 
                 const string& phone_val, const string& department_val)
    : Person(id_val, name_val, address_val, phone_val), department(department_val) {}

void Faculty::display() const {
    cout << "--- Faculty Details ---" << endl;
    cout << "ID: " << id << endl;
    cout << "Name: " << name << endl;
    cout << "Department: " << department << endl;
    cout << "Courses Taught: " << course_load.size() << endl;
    cout << "Address: " << address << endl;
    cout << "Phone: " << phone << endl;
    
    if (!course_load.empty()) {
        cout << "Course IDs: ";
        for (int course_id : course_load) {
            cout << course_id << " ";
        }
        cout << endl;
    }
}

void Faculty::save_to_file() const {
    ofstream file("faculty.txt", ios::app);
    if (file.is_open()) {
        file << id << "," << name << "," << address << "," << phone << "," << department;
        
        file << ",";
        for (int course_id : course_load) {
            file << course_id << "|";
        }
        file << "\n";
        file.close();
    }
}

void Faculty::assign_course(int course_id) {
    if (find(course_load.begin(), course_load.end(), course_id) == course_load.end()) {
        course_load.push_back(course_id);
    }
}

const vector<int>& Faculty::get_course_load() const {
    return course_load;
}