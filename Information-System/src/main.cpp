#include <iostream>
#include <sstream>
#include "info_sys.h"
using namespace std;

bool scmp(const char* a,const char* b) {
  return strcmp(a, b) == 0;
}

int menu(InformationSystem& is, istream& in, bool flag = true) {
  char command[32];

  if(flag) cout << "~$ ";
  in >> command;

  if (scmp(command, "print")) {
    is.print(cout);
    return 1;
  }
  else if (scmp(command, "exit")) exit(0);

  char value[32];
  in >> value;

  if(scmp(command, "load")) is.load(value);
  else if (scmp(command, "save")) is.save(value);
  else if (scmp(command, "grade")) cout << is.average_grade(value) << endl;
  else if (scmp(command, "update_grade")) {
    double grade;
    in >> grade;
    is.average_grade(value, grade);
  }
  else if (scmp(command, "telephone")) cout << is.telephone(value) << endl;
  else if (scmp(command, "update_telephone")) {
    Student::tel_type tel;
    in >> tel;
    is.telephone(value, tel);
  }
  else if (scmp(command, "add")) {
    double grade;
    Student::tel_type tel;
    in >> grade >> tel;
    is.add_student(value, grade, tel);
  } else if (scmp(command, "remove"))
    is.remove_student(value);

  return 1;
}


int main(int argc, char const *argv[]) {
  InformationSystem data;

  if (argc >= 3 && strcmp(argv[1], "-i") == 0) {
    data.load(argv[2]);
    stringstream consoleIn;
    for (int i = 3; i < argc; ++i)
      consoleIn << " " << argv[i];

    while (consoleIn.good())
       menu(data, consoleIn, false);
  }


  while(menu(data, cin));

  return 0;
}
