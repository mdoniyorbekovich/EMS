#include "Manager.h"
#include <sstream>
#include <iostream>
using namespace std;

Manager::Manager() : Employee(), teamSize(0) { role = "Manager"; }
Manager::Manager(int id, const string &name, double salary, int perf, int teamSize)
    : Employee(id, name, "Manager", salary, perf), teamSize(teamSize) {}
Manager::~Manager() {}

void Manager::setTeamSize(int s) { teamSize = s; }
int Manager::getTeamSize() const { return teamSize; }

string Manager::toCSV() const {
    ostringstream oss;
    oss << id << "," << name << "," << role << "," << salary
        << "," << performanceScore << "," << teamSize << "," << username;
    return oss.str();
}

shared_ptr<Manager> Manager::fromCSVLine(const string &line) {
    istringstream iss(line);
    string token;
    vector<string> cols;

    while (getline(iss, token, ',')) cols.push_back(token);
    if (cols.size() < 6) return nullptr;

    int id = stoi(cols[0]);
    string name = cols[1];
    double salary = stod(cols[3]);
    int perf = stoi(cols[4]);
    int ts = stoi(cols[5]);
    string username = (cols.size() > 6) ? cols[6] : "";

    auto mgr = make_shared<Manager>(id, name, salary, perf, ts);
    mgr->setUsername(username);
    return mgr;
}

void Manager::printFull() const {
    Employee::printFull();
    cout << "Team size: " << teamSize << "\n";
}
