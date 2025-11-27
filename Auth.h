#ifndef AUTH_H
#define AUTH_H

#include <string>
#include <unordered_map>
using namespace std;

struct User {
    string username;
    string role;
    string password;
};

class Auth {
    unordered_map<string, User> users;
    string filename;
public:
    Auth(const string &filename = "users.csv");
    void addUser(const User &u);
    bool authenticate(const string &username, const string &password) const;
    string getRole(const string &username) const;
    bool load();
    bool save();
    bool userExists(const string &username) const;
};

#endif
