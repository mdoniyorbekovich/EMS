#include <iostream>
#include <memory>
#include <limits>
#include "EmployeeDatabase.h"
#include "Employee.h"
#include "Developer.h"
#include "Manager.h"
#include "Auth.h"
using namespace std;

void pause() {
    cout << "Press Enter to continue...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

int main() {
    Auth auth;
    EmployeeDatabase db("employees.csv");
    db.load();

    cout << "=== Employee Management System ===\n";
    string username, password;

    cout << "Login\nUsername: ";
    getline(cin, username);
    cout << "Password: ";
    getline(cin, password);

    if (!auth.authenticate(username, password)) {
        cout << "Authentication failed. Exiting.\n";
        return 0;
    }

    string role = auth.getRole(username);
    cout << "Welcome, " << username << " (" << role << ")\n";

    if (role == "Manager") {
        while (true) {
            cout << "\nManager Menu:\n"
                 << "1. View all employees\n"
                 << "2. Search employee by ID\n"
                 << "3. Search by name\n"
                 << "4. Assign bonus\n"
                 << "5. Set performance score\n"
                 << "6. Remove employee\n"
                 << "7. Exit\n"
                 << "Choose: ";

            int ch;
            if (!(cin >> ch)) break;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            if (ch == 1) {
                for (auto &e : db.getAll()) e->printShort();
                pause();
            }
            else if (ch == 2) {
                int id;
                cout << "Enter ID: ";
                cin >> id;
                cin.ignore();
                auto e = db.findById(id);
                if (e) e->printFull(); else cout << "Not found\n";
                pause();
            }
            else if (ch == 3) {
                cout << "Name substring: ";
                string q; getline(cin, q);
                for (auto &e : db.searchByName(q)) e->printShort();
                pause();
            }
            else if (ch == 4) {
                int id; double amt;
                cout << "Enter ID and bonus amount: ";
                cin >> id >> amt; cin.ignore();
                if (db.assignBonus(id, amt)) cout << "Bonus assigned.\n";
                else cout << "Failed.\n";
                pause();
            }
            else if (ch == 5) {
                int id, score;
                cout << "Enter ID and score: ";
                cin >> id >> score; cin.ignore();
                if (db.setPerformance(id, score)) cout << "Updated.\n";
                else cout << "Failed.\n";
                pause();
            }
            else if (ch == 6) {
                int id;
                cout << "Enter ID to remove: ";
                cin >> id; cin.ignore();
                if (db.removeById(id)) cout << "Removed.\n";
                else cout << "Not found.\n";
                pause();
            }
            else if (ch == 7) break;
        }
    }

    else if (role == "Developer") {
        while (true) {
            cout << "\nDeveloper Menu:\n"
                 << "1. View all employees\n"
                 << "2. Add employee\n"
                 << "3. Update employee\n"
                 << "4. Delete employee\n"
                 << "5. Search by name\n"
                 << "6. Exit\n"
                 << "Choose: ";

            int ch;
            if (!(cin >> ch)) break;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            if (ch == 1) {
                for (auto &e : db.getAll()) e->printShort();
                pause();
            }

            else if (ch == 2) {
                cout << "Role? (1=Manager, 2=Developer, 3=Employee): ";
                int r; cin >> r; cin.ignore();

                string name; double salary; int perf;
                cout << "Name: "; getline(cin, name);
                cout << "Salary: "; cin >> salary;
                cout << "Performance: "; cin >> perf; cin.ignore();

                if (r == 1) {
                    int ts; cout << "Team size: "; cin >> ts; cin.ignore();
                    auto e = make_shared<Manager>(0, name, salary, perf, ts);
                    
                    // Prompt for login credentials for Manager
                    string username, password;
                    cout << "Username for login (required): "; getline(cin, username);
                    if (username.empty()) {
                        cout << "Username cannot be empty for Manager. Operation cancelled.\n";
                        pause();
                        continue;
                    }
                    if (auth.userExists(username)) {
                        cout << "Username already exists. Operation cancelled.\n";
                        pause();
                        continue;
                    }
                    cout << "Password: "; getline(cin, password);
                    
                    e->setUsername(username);
                    auto added = db.addEmployee(e);
                    
                    // Create auth user account
                    User newUser{username, "Manager", password};
                    auth.addUser(newUser);
                    
                    cout << "Added Manager with ID " << added->getId() << " and login account '" << username << "'\n";
                }
                else if (r == 2) {
                    string lang;
                    cout << "Primary language: "; cin.ignore(); getline(cin, lang);
                    auto e = make_shared<Developer>(0, name, salary, perf, lang);
                    
                    // Prompt for login credentials for Developer
                    string username, password;
                    cout << "Username for login (required): "; getline(cin, username);
                    if (username.empty()) {
                        cout << "Username cannot be empty for Developer. Operation cancelled.\n";
                        pause();
                        continue;
                    }
                    if (auth.userExists(username)) {
                        cout << "Username already exists. Operation cancelled.\n";
                        pause();
                        continue;
                    }
                    cout << "Password: "; getline(cin, password);
                    
                    e->setUsername(username);
                    auto added = db.addEmployee(e);
                    
                    // Create auth user account
                    User newUser{username, "Developer", password};
                    auth.addUser(newUser);
                    
                    cout << "Added Developer with ID " << added->getId() << " and login account '" << username << "'\n";
                }
                else {
                    auto e = make_shared<Employee>(0, name, "Employee", salary, perf);
                    auto added = db.addEmployee(e);
                    cout << "Added Employee with ID " << added->getId() << "\n";
                }
                pause();
            }

            else if (ch == 3) {
                cout << "ID: ";
                int id; cin >> id; cin.ignore();
                auto e = db.findById(id);
                if (!e) { cout << "Not found\n"; pause(); continue; }

                string name;
                double salary;
                int perf;

                cout << "New name (leave blank to keep): ";
                getline(cin, name);

                cout << "New salary (-1 to keep): ";
                cin >> salary;

                cout << "New perf (-1 to keep): ";
                cin >> perf; cin.ignore();

                auto updated = e;

                if (!name.empty()) updated->setName(name);
                if (salary >= 0) updated->setSalary(salary);
                if (perf >= 0) updated->setPerformanceScore(perf);

                if (updated->getRole() == "Manager") {
                    int ts;
                    cout << "New team size (-1 to keep): ";
                    cin >> ts; cin.ignore();
                    if (ts >= 0) dynamic_pointer_cast<Manager>(updated)->setTeamSize(ts);
                }
                else if (updated->getRole() == "Developer") {
                    string lang;
                    cout << "New lang (empty = keep): ";
                    getline(cin, lang);
                    if (!lang.empty()) dynamic_pointer_cast<Developer>(updated)->setPrimaryLanguage(lang);
                }

                db.updateEmployee(id, updated);
                cout << "Updated.\n";
                pause();
            }

            else if (ch == 4) {
                cout << "ID: ";
                int id; cin >> id; cin.ignore();
                if (db.removeById(id)) cout << "Deleted.\n";
                else cout << "Not found.\n";
                pause();
            }

            else if (ch == 5) {
                string q;
                cout << "Name substring: ";
                getline(cin, q);
                for (auto &e : db.searchByName(q)) e->printShort();
                pause();
            }

            else if (ch == 6) break;
        }
    }

    return 0;
}
