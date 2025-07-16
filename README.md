
# Library Management System

## Project Overview
This is a simple Library Management System implemented in C++ using Standard Template Library (STL) containers. The system allows administrators to manage books and students, and enables students to perform basic library operations such as viewing balance, depositing funds, issuing books, and returning books. Data persistence is handled via text files.

## Features
- **Admin Functions:**
  - Add, edit, delete, and view books
  - View all enrolled students (sorted by roll number)
  - View student balance
  - Search books by author
- **Student Functions:**
  - Create an account (with minimum deposit)
  - View balance
  - Deposit amount
  - Issue a book (if available and sufficient balance)
  - Return a book

## Data Structures Used
- `struct Book` — Represents a book with title, author, ISBN, and availability status
- `struct Student` — Represents a student with roll number, name, and balance
- `std::unordered_map<int, Book>` — Stores books, keyed by ISBN
- `std::unordered_map<int, Student>` — Stores students, keyed by roll number
- `std::vector` — Used for sorting and displaying lists

## File Management
- **books.txt** — Stores all book records (title, author, ISBN, availability)
- **students.txt** — Stores all student records (roll, name, balance)
- Data is loaded from these files at startup and saved back on exit

## Error Handling
- Input validation for all user entries
- File stream checks for reading/writing data
- Graceful handling of invalid operations (e.g., issuing unavailable books, insufficient balance, duplicate accounts)

## How to Run
1. Compile the code using a C++ compiler (e.g., g++, clang++)
   ```sh
   g++ -o main main.cpp
   ```
2. Run the executable:
   ```sh
   ./main
   ```
3. Follow the on-screen menu to log in as Admin or Student and perform operations.

## Suitable For
- Students and professionals who want to learn about efficient data structures (hash tables), persistent data management, and modular programming in C++.
- Demonstrating modern C++ and STL skills in a practical, real-world application.

---

**Note:**
- This project can be further enhanced by adding fine calculation, book reservation, a graphical user interface (GUI) using libraries like Qt or wxWidgets, and more advanced security features.
