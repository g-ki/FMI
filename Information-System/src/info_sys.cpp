#include "info_sys.h"
#include <fstream>

using namespace std;

void InformationSystem::load(const char* filename) {
  ifstream input(filename);
  Student tmp("",0,0);

  while (input >> tmp)
    DB.insert(tmp);

  input.close();

}

void InformationSystem::save(const char* filename) {
  ofstream output(filename);
  print(output);
  output.close();
}

void InformationSystem::add_student(const Student&& s) {
  DB.insert(s);
}

void InformationSystem::add_student(const char* name, double grade, Student::tel_type tel) {
  add_student(Student(name, grade, tel));
}

void InformationSystem::remove_student(const char* student_name) {
  DB.remove(student_name);
}

double InformationSystem::average_grade(const char* student_name) const {
  const Student* s = DB.search(student_name);

  if(s != NULL)
    return s->get_grade();

  return -1;
}
Student::tel_type InformationSystem::telephone(const char* student_name) const {
  const Student* s = DB.search(student_name);

  if(s != NULL)
    return s->get_tel();

  return -1;
}

void InformationSystem::average_grade(const char* student_name, double grade) {
  DB.update(student_name,
    [grade](Student s) -> Student {
      s.set_grade(grade);
      return s;
    });
}

void InformationSystem::telephone(const char* student_name, Student::tel_type _telephone) {
  DB.update(student_name,
    [_telephone](Student s) -> Student {
      s.set_tel(_telephone);
      return s;
    });
}

void InformationSystem::print(ostream& os) const {
  DB.dump(os);
}
