#ifndef SUBJECT_H
#define SUBJECT_H

class Subject{
public:
  Subject(const int& subjectID, const int& conditions, const int& trials);
  std::string filename(const int& condition, const int& trial);

private:
  int subjectID;
  int conditions;
  int trials;

};

#endif
