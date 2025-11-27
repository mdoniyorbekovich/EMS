#include "Developer.h"
#include <sstream>
#include <iostream>
using namespace std;

Developer::Developer() : Employee(), primaryLanguage("C++") { role = "Developer"; }
Developer::Developer(int id, const string &name, double salary, int perf, const string &lang)
    : Employee(id, name, "Developer", salary, perf), primaryLanguage(lang) {}
Developer::~Developer() {}

void Developer::setPrimaryLanguage(const string &l) { primaryLanguage = l; }
string Developer::getPrimaryLanguage() const { return primaryLanguage; }

string Developer::toCSV() const {
    ostringstream oss;
    oss << id << "," << name << "," << role << "," << salary
        << "," << performanceScore << "," << primaryLanguage << "," << username;
    return oss.str();
}

shared_ptr<Developer> Developer::fromCSVLine(const string &line) {
    istringstream iss(line);
    string token;
    vector<string> cols;

    while (getline(iss, token, ',')) cols.push_back(token);
    if (cols.size() < 6) return nullptr;

    int id = stoi(cols[0]);
    string name = cols[1];
    double salary = stod(cols[3]);
    int perf = stoi(cols[4]);
    string lang = cols[5];
    string username = (cols.size() > 6) ? cols[6] : "";

    auto dev = make_shared<Developer>(id, name, salary, perf, lang);
    dev->setUsername(username);
    return dev;
}

void Developer::printFull() const {
    Employee::printFull();
    cout << "Primary language: " << primaryLanguage << "\n";
}
