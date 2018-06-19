#include <vector>
#include <string>

class Subject
{
    public:
        Subject();
        Subject(std::string, int);
        int getTrials() const;
        std::string getName() const;


    private:
        std::string name;            // Name of the subject
        int trials;
        std::vector<std::pair<double, double> > *backTucks;      // Array of vectors dynamically allocated.
        std::vector<std::pair<double, double> > *vertJumps;      // Array of vectors dynamically allocated.

        //input name, movement type, number of trials

};
