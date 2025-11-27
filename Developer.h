#ifndef DEVELOPER_H
#define DEVELOPER_H

#include "Employee.h"
using namespace std;

class Developer : public Employee {
    string primaryLanguage;
public:
    Developer();
    Developer(int id, const string &name, double salary, int perf, const string &lang = "C++");
    ~Developer() override;

    void setPrimaryLanguage(const string &l);
    string getPrimaryLanguage() const;

    string toCSV() const override;
    static shared_ptr<Developer> fromCSVLine(const string &line);

    void printFull() const override;
};

#endif
