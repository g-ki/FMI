#ifndef STUDENT_H
#define STUDENT_H

#include <cstring>
#include <string>
#include <iostream>

class Student {
public:
  typedef unsigned long tel_type;

  Student (const char* _name, double _grade, tel_type _tel);

  const char* get_name() const { return name;}
  //void set_name(const char* _name) { strncpy(name, _name, 31);}

  void set_grade(double _grade) {
    grade = _grade;
  }

  double get_grade() const { return grade; }

  void set_tel(tel_type _tel) {
    telephone = _tel;
  }

  tel_type get_tel() const { return telephone; }

  void print(std::ostream& os) const {
    os << get_name() << " " << get_grade() << " " << get_tel();
  }

  friend std::istream& operator>>(std::istream& is, Student& s);

private:
  static const int name_lenght = 31;
  char name[name_lenght + 1];
  double grade;
  tel_type telephone;
};

std::ostream& operator<<(std::ostream& os, const Student& s);
std::ostream& operator<<(std::ostream& os, const Student* s);

std::istream& operator>>(std::istream& is, Student& s);

struct StudentIndex {
  typedef std::string index_type;

  index_type operator() (const Student& s) const {
    return s.get_name();
  }
};

#endif
