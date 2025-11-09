#include "person.h"
//funtion definitons corresponding to person header file 
Person::Person(int id_val, const string& name_val, const string& address_val, const string& phone_val)
    : id(id_val), name(name_val), address(address_val), phone(phone_val) {}

int Person::get_id() const {
    return id;
}

string Person::get_name() const {
    return name;
}

void Person::update_address(const string& new_address) {
    address = new_address;
}