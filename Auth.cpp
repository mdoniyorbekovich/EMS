#include "Auth.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
using namespace std;

Auth::Auth(const string &filename) : filename(filename) {
    // Add default users
    users["admin"] = User{"admin", "Manager", "admin123"};
    users["dev"]   = User{"dev", "Developer", "dev123"};
    // Load persisted users from file
    load();
}

void Auth::addUser(const User &u) {
    users[u.username] = u;
    save();
}

bool Auth::authenticate(const string &username, const string &password) const {
    auto it = users.find(username);
    if (it == users.end()) return false;
    return it->second.password == password;
}

string Auth::getRole(const string &username) const {
    auto it = users.find(username);
    if (it == users.end()) return "";
    return it->second.role;
}

bool Auth::load() {
    ifstream ifs(filename);
    if (!ifs.is_open()) {
        // File doesn't exist yet, that's okay - we have default users
        return true;
    }

    string line;
    while (getline(ifs, line)) {
        if (line.empty()) continue;

        istringstream iss(line);
        string token;
        vector<string> cols;
        while (getline(iss, token, ',')) cols.push_back(token);

        if (cols.size() < 3) continue;

        string username = cols[0];
        string role = cols[1];
        string password = cols[2];

        if (users.find(username) == users.end()) {
            users[username] = User{username, role, password};
        }
    }

    return true;
}

bool Auth::save() {
    ofstream ofs(filename);
    if (!ofs.is_open()) {
        cerr << "Failed to open " << filename << " for writing.\n";
        return false;
    }

    // Save all users to file
    for (const auto &pair : users) {
        ofs << pair.second.username << ","
            << pair.second.role << ","
            << pair.second.password << "\n";
    }

    return true;
}

bool Auth::userExists(const string &username) const {
    return users.find(username) != users.end();
}
