#include "EmployeeDatabase.h"
#include "Manager.h"
#include "Developer.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>
using namespace std;

EmployeeDatabase::EmployeeDatabase(const string &filename) : filename(filename), nextId(1) {}
EmployeeDatabase::~EmployeeDatabase() { save(); }

bool EmployeeDatabase::load() {
    employees.clear();
    ifstream ifs(filename);

    if (!ifs.is_open()) return true;

    string line;
    int highest = 0;

    while (getline(ifs, line)) {
        if (line.empty()) continue;

        istringstream iss(line);
        string token;
        vector<string> cols;
        while (getline(iss, token, ',')) cols.push_back(token);

        if (cols.size() < 5) continue;

        string role = cols[2];
        EmployeePtr ptr;

        if (role == "Manager") {
            ptr = Manager::fromCSVLine(line);
        } else if (role == "Developer") {
            ptr = Developer::fromCSVLine(line);
        } else {
            ptr = Employee::fromCSV(line);
        }

        if (ptr) {
            employees.push_back(ptr);
            highest = max(highest, ptr->getId());
        }
    }

    nextId = highest + 1;
    return true;
}

bool EmployeeDatabase::save() {
    ofstream ofs(filename, ios::out | ios::trunc);  // Explicitly truncate to overwrite
    if (!ofs.is_open()) {
        cerr << "Failed to open " << filename << " for writing.\n";
        return false;
    }

    for (auto &e : employees) {
        ofs << e->toCSV() << "\n";
    }
    ofs.close();  // Explicitly close the file
    return true;
}

vector<EmployeePtr> EmployeeDatabase::getAll() const { return employees; }

EmployeePtr EmployeeDatabase::findById(int id) const {
    for (auto &e : employees)
        if (e->getId() == id) return e;
    return nullptr;
}

vector<EmployeePtr> EmployeeDatabase::searchByName(const string &name) const {
    vector<EmployeePtr> res;
    for (auto &e : employees)
        if (e->getName().find(name) != string::npos)
            res.push_back(e);
    return res;
}

vector<EmployeePtr> EmployeeDatabase::searchByRole(const string &role) const {
    vector<EmployeePtr> res;
    for (auto &e : employees)
        if (e->getRole() == role)
            res.push_back(e);
    return res;
}

EmployeePtr EmployeeDatabase::addEmployee(const EmployeePtr &e) {
    // Check if employee with same ID already exists (shouldn't happen, but safety check)
    int id = getNextId();
    
    // Verify this ID doesn't already exist
    if (findById(id) != nullptr) {
        // Find the next available ID
        while (findById(id) != nullptr) {
            id++;
        }
        nextId = id;
    }
    
    EmployeePtr newE;
    string role = e->getRole();
    string username = e->getUsername();

    if (role == "Manager") {
        auto m = dynamic_pointer_cast<Manager>(e);
        newE = make_shared<Manager>(id, e->getName(), e->getSalary(), e->getPerformanceScore(),
                                    m ? m->getTeamSize() : 0);
    } else if (role == "Developer") {
        auto d = dynamic_pointer_cast<Developer>(e);
        newE = make_shared<Developer>(id, e->getName(), e->getSalary(), e->getPerformanceScore(),
                                      d ? d->getPrimaryLanguage() : "C++");
    } else {
        newE = make_shared<Employee>(id, e->getName(), e->getRole(),
                                     e->getSalary(), e->getPerformanceScore());
    }

    // Preserve username if set
    if (!username.empty()) {
        newE->setUsername(username);
    }

    employees.push_back(newE);
    nextId = id + 1;  // Set nextId to be one more than the current ID
    save();
    return newE;
}

bool EmployeeDatabase::removeById(int id) {
    auto it = remove_if(employees.begin(), employees.end(),
                        [id](const EmployeePtr &e){ return e->getId() == id; });

    if (it == employees.end()) return false;

    employees.erase(it, employees.end());
    save();
    return true;
}

bool EmployeeDatabase::updateEmployee(int id, const EmployeePtr &updated) {
    for (auto &e : employees) {
        if (e->getId() == id) {
            e->setName(updated->getName());
            e->setRole(updated->getRole());
            e->setSalary(updated->getSalary());
            e->setPerformanceScore(updated->getPerformanceScore());

            if (e->getRole() == "Manager") {
                auto em = dynamic_pointer_cast<Manager>(e);
                auto um = dynamic_pointer_cast<Manager>(updated);
                if (em && um) em->setTeamSize(um->getTeamSize());
            } else if (e->getRole() == "Developer") {
                auto ed = dynamic_pointer_cast<Developer>(e);
                auto ud = dynamic_pointer_cast<Developer>(updated);
                if (ed && ud) ed->setPrimaryLanguage(ud->getPrimaryLanguage());
            }

            save();
            return true;
        }
    }
    return false;
}

int EmployeeDatabase::getNextId() { return nextId; }

bool EmployeeDatabase::assignBonus(int id, double amount) {
    auto e = findById(id);
    if (!e) return false;
    e->setSalary(e->getSalary() + amount);
    save();
    return true;
}

bool EmployeeDatabase::setPerformance(int id, int newScore) {
    auto e = findById(id);
    if (!e) return false;
    e->setPerformanceScore(newScore);
    save();
    return true;
}
