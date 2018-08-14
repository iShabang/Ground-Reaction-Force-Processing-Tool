#include "newSub.h"

Subject::Subject(const int& subjectID, const int& conditions, const int& trials){
  this->subjectID = subjectID;
  this->conditions = conditions;
  this->trials = trials;
}

std::string Subject::filename(const int& condition, const int& trial){
  std::string s = std::to_string(subjectID);
  std::string c = std::to_string(condition);
  std::string t = std::to_string(trial);
  string name = "S" + S + "C" + C + "T" + T;
  return name;
}
