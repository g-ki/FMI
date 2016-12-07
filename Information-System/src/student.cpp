#include "student.h"
#include <iostream>

Student::Student(const char* _name, double _grade, tel_type _tel)
: grade(_grade), telephone(_tel) {
  strncpy(name, _name, name_lenght);
}

std::ostream& operator<<(std::ostream& os, const Student& s) {
  s.print(os);
  return os;
}

std::ostream& operator<<(std::ostream& os, const Student* s) {
  return os << *s;
}


std::istream& operator>>(std::istream& is, Student& s) {
  char name[32];
  is >> name >> s.grade >> s.telephone;
  strncpy(s.name, name, 32);
  return is;
}
