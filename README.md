# Employee Management System  
**C++ Final Project – Autumn 2025**  
**Group Members:**  
- Muhammadsodiq Doniyorbekov  
- Behruz Siddiqjonov  
- To’raxonov Akmalxon  

A secure and role-based Employee Management System built with modern C++, OOP, polymorphism, smart pointers, and file handling.

## Features
- Role-based login (Manager vs Developer)  
- Full CRUD operations (Add, View, Search, Update, Delete)  
- Automatic saving to `employees.csv` and `users.csv`  
- Inheritance + polymorphism (Employee → Developer → Manager)  
- Zero memory leaks (100% `shared_ptr`)  
- Manager-only actions: assign bonus, change performance  
- Search by ID, name, or role  

## Default Login Credentials
| Username | Password   | Role      |
|----------|------------|-----------|
| admin    | admin123   | Manager   |
| dev      | dev123     | Developer |

## Project Structure

├── Auth.h / Auth.cpp
├── Employee.h / Employee.cpp
├── Developer.h / Developer.cpp
├── Manager.h / Manager.cpp
├── EmployeeDatabase.h / EmployeeDatabase.cpp
├── main.cpp
├── CMakeLists.txt
├── employees.csv          (auto-created on first run)
├── users.csv              (auto-created on first run)
└── screenshots/           (optional)


## How to Compile and Run

### Using CMake (Recommended)
```bash
mkdir build && cd build
cmake ..
cmake --build .
./EmployeeManagementSystem          # Linux/macOS
# or
./EmployeeManagementSystem.exe      # Windows
