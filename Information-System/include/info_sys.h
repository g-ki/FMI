#ifndef INFO_SYS_H
#define INFO_SYS_H

#include "database.h"
#include "student.h"

class InformationSystem {
private:
  Database<Student, StudentIndex> DB;

public:
  void load(const char* filename);
  void save(const char* filename);

  void add_student(const Student&& s);
  void add_student(const char* name, double grade, Student::tel_type tel);

  void remove_student(const char* student_name);

  double average_grade(const char* student_name) const ;
  Student::tel_type telephone(const char* student_name) const;

  void average_grade(const char* student_name, double grade);
  void telephone(const char* student_name, Student::tel_type _telephone);

  void print(ostream& os) const;
};

#endif
