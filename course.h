#ifndef COURSE_H
#define COURSE_H

#include <string>
#include <vector>

using namespace std;

class Course {
private:
    //instance variables for course details
    //private so that inaccessible to user 
    //encapsulation implementation
    int course_id;
    string title;
    int credits;
    int faculty_id;
    vector<int> student_ids;

public:
    Course(int id_val, const string& title_val, int credits_val, int faculty_id_val);

    int get_id() const;
    int get_faculty_id() const;
    const vector<int>& get_students() const;

    void assign_faculty(int new_faculty_id);
    void add_student(int student_id);
    void load_student_id(int student_id);
    
    void display() const;
    void save_to_file() const;
};

#endif // COURSE_H