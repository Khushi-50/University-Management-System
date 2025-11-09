#include "manager.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <limits>

using namespace std;

vector<string> ManagementSystem::splitString(const string& s, char delimiter) {
    vector<string> tokens;
    string token;
    istringstream tokenStream(s);
    while (getline(tokenStream, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}

Student* ManagementSystem::find_student(int id) {
    for (auto& s : students) {
        if (s.get_id() == id) {
            return &s;
        }
    }
    return nullptr;
}

Faculty* ManagementSystem::find_faculty(int id) {
    for (auto& f : faculty) {
        if (f.get_id() == id) {
            return &f;
        }
    }
    return nullptr;
}

Course* ManagementSystem::find_course(int id) {
    for (auto& c : courses) {
        if (c.get_id() == id) {
            return &c;
        }
    }
    return nullptr;
}

void ManagementSystem::save_all_data() const {
    cout << "\nSaving all data to files..." << endl;
    
    ofstream s_file("students.txt", ios::trunc); 
    s_file.close();
    ofstream f_file("faculty.txt", ios::trunc); 
    f_file.close();
    ofstream c_file("courses.txt", ios::trunc);
     c_file.close();

    for (const auto& student : students) {
        student.save_to_file();
    }
    for (const auto& f : faculty) {
        f.save_to_file();
    }
    for (const auto& c : courses) {
        c.save_to_file();
    }
    
    cout << "All data saved successfully." << endl;
}

void ManagementSystem::load_all_data() {
    cout << "Loading previous data..." << endl;
    
    students.clear();
    faculty.clear();
    courses.clear();
    
    // Load Students
    ifstream student_file("students.txt");
    string line;
    while (getline(student_file, line)) {
        if (line.empty()) continue;
        vector<string> parts = splitString(line, ',');
        
        if (parts.size() >= 6) {
            int id = stoi(parts[0]);
            int year = stoi(parts[5]);
            
            Student s(id, parts[1], parts[2], parts[3], parts[4], year);

            if (parts.size() > 6 && !parts[6].empty()) {
                vector<string> grade_pairs = splitString(parts[6], '|');
                for (const string& pair : grade_pairs) {
                    if (pair.empty()) continue;
                    vector<string> item = splitString(pair, ':');
                    if (item.size() == 2) {
                        s.load_grade_data(stoi(item[0]), item[1]);
                    }
                }
            }
            students.push_back(s);
        }
    }
    student_file.close();

    ifstream faculty_file("faculty.txt");
    while (getline(faculty_file, line)) {
        if (line.empty()) continue;
        vector<string> parts = splitString(line, ',');
        
        if (parts.size() >= 5) {
            int id = stoi(parts[0]);
            Faculty f(id, parts[1], parts[2], parts[3], parts[4]);

            if (parts.size() > 5 && !parts[5].empty()) {
                vector<string> course_ids = splitString(parts[5], '|');
                for (const string& cid_str : course_ids) {
                    if (!cid_str.empty()) {
                        f.assign_course(stoi(cid_str)); 
                    }
                }
            }
            faculty.push_back(f);
        }
    }
    faculty_file.close();

    ifstream course_file("courses.txt");
    while (getline(course_file, line)) {
        if (line.empty()) continue;
        vector<string> parts = splitString(line, ',');

        if (parts.size() >= 4) {
            int course_id = stoi(parts[0]);
            int credits = stoi(parts[2]);
            int faculty_id = stoi(parts[3]);

            Course c(course_id, parts[1], credits, faculty_id);
            
            if (parts.size() > 4 && !parts[4].empty()) {
                vector<string> student_ids = splitString(parts[4], '|');
                for (const string& sid_str : student_ids) {
                    if (!sid_str.empty()) {
                        c.load_student_id(stoi(sid_str)); 
                    }
                }
            }
            courses.push_back(c);
        }
    }
    course_file.close();
    
    cout << "Data loading complete. " << students.size() << " students, " 
         << faculty.size() << " faculty, and " << courses.size() << " courses loaded." << endl;
}


ManagementSystem::ManagementSystem() {
    load_all_data();
}

ManagementSystem::~ManagementSystem() {
    save_all_data();
}

void ManagementSystem::add_new_student() {
    int id;
    string name, address, phone, major;
    int year;

    cout << "\n--- Add New Student ---" << endl;
    
    int next_id = 1000;
    if (!students.empty()) {
        next_id = students.back().get_id() + 1;
    }
    id = next_id;
    cout << "Generated Student ID: " << id << endl;

    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    
    cout << "Enter Student Name: ";
    getline(cin, name);
    
    cout << "Enter Student Address: ";
    getline(cin, address);
    
    cout << "Enter Student Phone: ";
    getline(cin, phone);
    
    cout << "Enter Student Major: ";
    getline(cin, major);
    
    cout << "Enter Student Year (1-5): ";
    while (!(cin >> year) || year < 1 || year > 5) {
        cout << "Invalid year. Enter a number between 1 and 5: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    
    Student new_student(id, name, address, phone, major, year);
    students.push_back(new_student);
    
    cout << "\nSUCCESS: Student " << name << " (ID: " << id << ") added." << endl;
}

void ManagementSystem::add_new_faculty() {
    int id;
    string name, address, phone, department;

    cout << "\n--- Add New Faculty ---" << endl;
    
    int next_id = 2000;
    if (!faculty.empty()) {
        next_id = faculty.back().get_id() + 1;
    }
    id = next_id;
    cout << "Generated Faculty ID: " << id << endl;

    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    
    cout << "Enter Faculty Name: ";
    getline(cin, name);
    
    cout << "Enter Faculty Address: ";
    getline(cin, address);
    
    cout << "Enter Faculty Phone: ";
    getline(cin, phone);
    
    cout << "Enter Faculty Department: ";
    getline(cin, department);
    
    Faculty new_faculty(id, name, address, phone, department);
    faculty.push_back(new_faculty);
    
    cout << "\nSUCCESS: Faculty member " << name << " (ID: " << id << ") added." << endl;
}

void ManagementSystem::add_new_course() {
    int course_id;
    string title;
    int credits;
    int faculty_id;
    
    cout << "\n--- Add New Course ---" << endl;

    int next_id = 5000;
    if (!courses.empty()) {
        next_id = courses.back().get_id() + 1;
    }
    course_id = next_id;
    cout << "Generated Course ID: " << course_id << endl;
    
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    
    cout << "Enter Course Title: ";
    getline(cin, title);
    
    cout << "Enter Course Credits (1-4): ";
    while (!(cin >> credits) || credits < 1 || credits > 4) {
        cout << "Invalid credit value. Enter a number between 1 and 4: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    Faculty* instructor = nullptr;
    do {
        cout << "Enter Faculty ID to assign as instructor: ";
        if (!(cin >> faculty_id)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
        instructor = find_faculty(faculty_id);

        if (!instructor) {
            cout << "Error: Faculty ID " << faculty_id << " not found. Please enter a valid ID." << endl;
        }
    } while (!instructor);

    Course new_course(course_id, title, credits, faculty_id);
    courses.push_back(new_course);
    
    instructor->assign_course(course_id);

    cout << "\nSUCCESS: Course '" << title << "' (ID: " << course_id << ") added and assigned to Faculty ID " << faculty_id << "." << endl;
}

void ManagementSystem::view_all_students() const {
    cout << "\n==========================================" << endl;
    cout << "            ALL STUDENT RECORDS" << endl;
    cout << "==========================================" << endl;

    if (students.empty()) {
        cout << "No student records found." << endl;
        return;
    }
    
    for (const auto& student : students) {
        student.display();
        cout << "------------------------------------------" << endl;
    }
}


void ManagementSystem::view_all_faculties() const {
    cout << "\n==========================================" << endl;
    cout << "            ALL FACULTY RECORDS" << endl;
    cout << "==========================================" << endl;

    if (faculty.empty()) {
        cout << "No faculty records found." << endl;
        return;
    }
    
    for (const auto& f : faculty) {
        f.display();
        cout << "------------------------------------------" << endl;
    }
}

void ManagementSystem::view_all_courses() const {
    cout << "\n==========================================" << endl;
    cout << "            ALL COURSE RECORDS" << endl;
    cout << "==========================================" << endl;

    if (courses.empty()) {
        cout << "No course records found." << endl;
        return;
    }
    
    // Iterate over the vector of Course objects and call display()
    for (const auto& c : courses) {
        c.display();
        cout << "------------------------------------------" << endl;
    }
}

void ManagementSystem::enroll_student_in_course() {
    int student_id, course_id;
    cout << "Enter Student ID to enroll: ";
    if (!(cin >> student_id)) return;
    cout << "Enter Course ID: ";
    if (!(cin >> course_id)) return;

    Student* student = find_student(student_id);
    Course* course = find_course(course_id);

    if (!student) {
        cout << "Error: Student with ID " << student_id << " not found." << endl;
        return;
    }
    if (!course) {
        cout << "Error: Course with ID " << course_id << " not found." << endl;
        return;
    }

    student->enroll_course(course_id);
    course->add_student(student_id);
    cout << "Enrollment successful." << endl;
}

void ManagementSystem::set_student_grade() {
    int student_id, course_id;
    string grade;
    cout << "Enter Student ID: ";
    if (!(cin >> student_id)) return;
    cout << "Enter Course ID: ";
    if (!(cin >> course_id)) return;

    Student* student = find_student(student_id);
    
    if (!student) {
        cout << "Error: Student with ID " << student_id << " not found." << endl;
        return;
    }
    
    cout << "Enter Grade (e.g., A, B+, F): ";
    cin >> grade;

    student->set_grade(course_id, grade);
    cout << "\nGrade set successfully for Student " << student_id << " in Course " << course_id << "." << endl;
}

void ManagementSystem::run_menu() {
    int choice;
    
    do {
        cout << "\n==========================================" << endl;
        cout << "  UNIVERSITY MANAGEMENT SYSTEM" << endl;
        cout << "==========================================" << endl;
        cout << "1. Add New Student" << endl;
        cout << "2. Add New Faculty" << endl;
        cout << "3. Add New Course" << endl;
        cout << "4. View All Students" << endl;
        cout << "5. View All Faculty" << endl;
        cout << "6. View All Courses" << endl;
        cout << "7. Enroll Student in Course" << endl;
        cout << "8. Set Student Grade" << endl;
        cout << "9. Exit System" << endl;
        cout << "Enter your choice: ";
        
        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            choice = 0;
            cout << "Invalid input. Please enter a number." << endl;
            continue;
        }

        switch (choice) {
            case 1: add_new_student(); break;
            case 2: add_new_faculty(); break;
            case 3: add_new_course(); break;
            case 4: view_all_students(); break;
            case 5: view_all_faculties(); break;
            case 6: view_all_courses(); break;
            case 7:enroll_student_in_course(); break;
            case 8: set_student_grade(); break;
            case 9:
                cout << "Exiting system. Data is being saved..." << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
                break;
        }
    } while (choice != 9);
}