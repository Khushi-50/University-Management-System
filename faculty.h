#ifndef FACULTY_H
#define FACULTY_H

#include "person.h"
#include <vector>

using namespace std;

class Faculty : public Person {
private:
    string department;
    vector<int> course_load;

public:
    Faculty(int id_val, const string& name_val, const string& address_val, 
            const string& phone_val, const string& department_val);

    void display() const override;
    void save_to_file() const override;

    void assign_course(int course_id);
    const vector<int>& get_course_load() const;
};

#endif 