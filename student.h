#ifndef STUDENT_H
#define STUDENT_H

//inheriting from person class 

#include "person.h"
#include <vector>
#include <map>

using namespace std;

class Student : public Person {
private:
    string major;
    int year;
    map<int, string> grades;

public:
    Student(int id_val, const string& name_val, const string& address_val, 
            const string& phone_val, const string& major_val, int year_val);
            
    void display() const override;
    void save_to_file() const override;

    void enroll_course(int course_id);
    void set_grade(int course_id, const string& grade_val);
    
    void load_grade_data(int course_id, const string& grade_val);
    const map<int, string>& get_grades() const;
};

#endif // STUDENT_H