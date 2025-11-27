#ifndef MANAGER_H
#define MANAGER_H

#include "Employee.h"
using namespace std;

class Manager : public Employee {
    int teamSize;
public:
    Manager();
    Manager(int id, const string &name, double salary, int perf, int teamSize = 0);
    ~Manager() override;

    void setTeamSize(int s);
    int getTeamSize() const;

    string toCSV() const override;
    static shared_ptr<Manager> fromCSVLine(const string &line);

    void printFull() const override;
};

#endif
