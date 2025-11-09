#ifndef PERSON_H
#define PERSON_H

#include <string>
#include <iostream>
using namespace std;

//person abstract class not to be instantiated 
//no member function definitions in header file only declarations
class Person {
protected:
    int id;
    string name;
    string address;
    string phone;

public:
    Person(int id_val, const string& name_val, const string& address_val, const string& phone_val);
    virtual ~Person() = default;

    int get_id() const;
    string get_name() const;
    void update_address(const string& new_address);

    virtual void display() const = 0;
    virtual void save_to_file() const = 0;
};

#endif 