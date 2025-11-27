#include "Employee.h"
#include <sstream>
#include <iostream>
using namespace std;

Employee::Employee() : id(0), name(""), role("Employee"), salary(0.0), performanceScore(0), username("") {}
Employee::Employee(int id, const string &name, const string &role, double salary, int perf)
    : id(id), name(name), role(role), salary(salary), performanceScore(perf), username("") {}
Employee::~Employee() {}

int Employee::getId() const { return id; }
string Employee::getName() const { return name; }
string Employee::getRole() const { return role; }
double Employee::getSalary() const { return salary; }
int Employee::getPerformanceScore() const { return performanceScore; }
string Employee::getUsername() const { return username; }

void Employee::setName(const string &n) { name = n; }
void Employee::setRole(const string &r) { role = r; }
void Employee::setSalary(double s) { salary = s; }
void Employee::setPerformanceScore(int p) { performanceScore = p; }
void Employee::setUsername(const string &u) { username = u; }

string Employee::toCSV() const {
    ostringstream oss;
    oss << id << "," << name << "," << role << "," << salary << "," << performanceScore << "," << username;
    return oss.str();
}

shared_ptr<Employee> Employee::fromCSV(const string &csvLine) {
    istringstream iss(csvLine);
    string token;
    vector<string> cols;

    while (getline(iss, token, ',')) cols.push_back(token);

    if (cols.size() < 5) return nullptr;

    int id = stoi(cols[0]);
    string name = cols[1];
    string role = cols[2];
    double salary = stod(cols[3]);
    int perf = stoi(cols[4]);
    string username = (cols.size() > 5) ? cols[5] : "";

    auto emp = make_shared<Employee>(id, name, role, salary, perf);
    emp->setUsername(username);
    return emp;
}

void Employee::printShort() const {
    cout << "[" << id << "] " << name << " (" << role << ") Salary: "
         << salary << " Perf: " << performanceScore << "\n";
}

void Employee::printFull() const {
    cout << "ID: " << id << "\nName: " << name
         << "\nRole: " << role << "\nSalary: " << salary
         << "\nPerformance: " << performanceScore << "\n";
}