#ifndef EMPLOYEEDB_H
#define EMPLOYEEDB_H

#include "Employee.h"
#include <vector>
#include <string>
#include <memory>
using namespace std;

class EmployeeDatabase {
    vector<EmployeePtr> employees;
    string filename;
    int nextId;

public:
    EmployeeDatabase(const string &filename = "employees.csv");
    ~EmployeeDatabase();

    bool load();
    bool save();

    vector<EmployeePtr> getAll() const;
    EmployeePtr findById(int id) const;
    vector<EmployeePtr> searchByName(const string &name) const;
    vector<EmployeePtr> searchByRole(const string &role) const;

    EmployeePtr addEmployee(const EmployeePtr &e);
    bool removeById(int id);
    bool updateEmployee(int id, const EmployeePtr &updated);
    int getNextId();

    bool assignBonus(int id, double amount);
    bool setPerformance(int id, int newScore);
};

#endif
