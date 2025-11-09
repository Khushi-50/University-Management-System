#ifndef MANAGER_H
#define MANAGER_H

#include "student.h"
#include "faculty.h"
#include "course.h"

#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>

using namespace std;

class ManagementSystem {
private:
    vector<Student> students;
    vector<Faculty> faculty;
    vector<Course> courses;

    void save_all_data() const;
    void load_all_data();
    vector<string> splitString(const string& s, char delimiter);
    
    Student* find_student(int id);
    Faculty* find_faculty(int id);
    Course* find_course(int id);

public:
    ManagementSystem();
    ~ManagementSystem();

    //menu functions 
    
    void add_new_student();
    void add_new_faculty();
    void add_new_course();
    void view_all_faculties() const;
    void view_all_students() const;
    void view_all_courses() const;
    void enroll_student_in_course();
    void set_student_grade();
    void run_menu();
};

#endif // MANAGER_H