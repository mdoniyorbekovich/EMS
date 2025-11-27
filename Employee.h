#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include <string>
#include <memory>
#include <vector>
using namespace std;

class Employee {
protected:
    int id;
    string name;
    string role;
    double salary;
    int performanceScore;
    string username;  // For login accounts (optional)

public:
    Employee();
    Employee(int id, const string &name, const string &role, double salary, int perf);
    virtual ~Employee();

    int getId() const;
    string getName() const;
    string getRole() const;
    double getSalary() const;
    int getPerformanceScore() const;
    string getUsername() const;

    void setName(const string &n);
    void setRole(const string &r);
    void setSalary(double s);
    void setPerformanceScore(int p);
    void setUsername(const string &u);

    virtual string toCSV() const;
    static shared_ptr<Employee> fromCSV(const string &csvLine);

    virtual void printShort() const;
    virtual void printFull() const;
};

using EmployeePtr = shared_ptr<Employee>;

#endif
