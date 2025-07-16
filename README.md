# Library Management System in C++

## Project Overview
The Library Management System is a console-based application developed in C++ that allows both admins and students to manage library resources efficiently. The system supports dynamic book and student management using linked lists, providing a scalable and organized solution for library operations.

## Key Features

### User Authentication
- Login options for both Admin and Student roles, protected by a password.

### Admin Functions
1. **Add a Book:** Add new books to the library by entering the title, author, and ISBN.
2. **Edit Book Details:** Edit the title and author of a book using its ISBN number.
3. **View Book Status:** View the complete list of books and their availability in the library.
4. **View Enrolled Students:** View the list of all registered students, sorted by their roll numbers.
5. **View Student Balance:** Check the account balance of any student by roll number.
6. **Delete a Book:** Remove a book from the library using its ISBN number.
7. **Search Book by Author:** Find all books by a specific author and view their details and availability.

### Student Functions
1. **Create an Account:** Register as a new student by providing roll number, name, and an initial deposit.
2. **View Balance:** Check your current account balance.
3. **Deposit Amount:** Add money to your account balance.
4. **Issue a Book:** Issue a book from the list of available books (each issue costs $2).
5. **Return a Book:** Return a previously issued book to the library.

### Account and Book Management
- Each student pays $20 for account opening and $30 as a security deposit.
- Students can issue any book for $2 for a 10-day period.
- The system can be easily extended to support fines for late returns.

- All book and student data is managed using modern C++ STL hash tables (`std::unordered_map`) for fast and efficient storage and lookup.

### Data Storage & Persistence
- Uses `std::unordered_map` (hash tables) to store details of students and books, providing O(1) average time for add, search, edit, and delete operations.
- All data is persisted to files (`books.txt` and `students.txt`) and automatically loaded/saved on program start/exit.
- Each student account contains roll number, name, and balance.

## Implementation Details
- Implemented in modern C++ using structures, STL containers (`std::unordered_map`, `std::vector`), and modular functions.
- Robust error handling for all user input and file operations.
- The main menu allows users to select their role and perform multiple actions until they choose to log out or exit.
- Clear success and error messages are displayed after every operation for better user experience.

## How to Run
1. Compile the `main.cpp` file using a C++ compiler (e.g., `g++ main.cpp -o main.exe`).
2. Run the executable (`main.exe` on Windows or `./main` on Linux/Mac).
3. Follow the on-screen instructions to log in as Admin or Student and use the system features.

## Suitable For
- Students and professionals who want to learn about efficient data structures (hash tables), persistent data management, and modular programming in C++.
- Demonstrating modern C++ and STL skills in a practical, real-world application.

---

**Note:**
- This project can be further enhanced by adding fine calculation, book reservation, a graphical user interface (GUI) using libraries like Qt or wxWidgets, and more advanced security features.
