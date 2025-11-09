# 🏛️ University Management System (UMS)

## Project Overview

The University Management System (UMS) is a console-based application built in C++ to model and manage the core administrative processes of an educational institution. This project serves as a comprehensive demonstration of **Object-Oriented Programming (OOP)** principles, robust **File I/O**, and modular software design.

### Key Objectives Achieved

  * **Inheritance:** Modeling human entities (`Student`, `Faculty`) from a common base class (`Person`).
  * **Polymorphism:** Using virtual functions (`display()`, `save_to_file()`) to handle different object types uniformly.
  * **Encapsulation:** Protecting data integrity by enforcing access controls (`private` members) and dedicated methods (`set_grade()`).
  * **Data Persistence:** Implementing custom serialization logic to save and load all records to text files (`*.txt`).

-----

## 🛠️ Project Structure

The application follows best practices by separating declarations (`.h` files) from implementations (`.cpp` files).

| File/Module | Role | Key Functionality |
| :--- | :--- | :--- |
| **`manager.cpp`** | **Core Logic/Controller** | Handles application flow, menu, user input validation, complex file I/O (`load_all_data`, `save_all_data`), and object linking. |
| **`person.h/cpp`** | **Abstract Base Class** | Provides the foundation for all human entities (`id`, `name`). |
| **`student.h/cpp`** | **Entity Class** | Manages `major`, `year`, and grades (`std::map`). Implements enrollment logic. |
| **`faculty.h/cpp`** | **Entity Class** | Manages `department` and assigned courses (`course_load`). |
| **`course.h/cpp`** | **Entity Class** | Manages `title`, `credits`, and the enrollment roster (`student_ids`). |
| **`main.cpp`** | **Entry Point** | Instantiates the `ManagementSystem` and calls the `run_menu()` loop. |

-----

## 🚀 Getting Started

### Prerequisites

You need a C++ compiler installed on your system. We recommend **g++** or **Clang** (default on macOS).

### Compilation

Since the project uses C++17 features (specifically, structured bindings like `[key, value]`), you must explicitly tell the compiler to use the C++17 standard.

1.  Open your terminal or command prompt.
2.  Navigate to the project directory where all the `.cpp` files are located.
3.  Execute the following command, ensuring you list **all six source files**:

<!-- end list -->

```bash
g++ -std=c++17 main.cpp manager.cpp person.cpp student.cpp faculty.cpp course.cpp -o ums_system
```

### Execution

After successful compilation, run the generated executable:

```bash
./ums_system
```

*(On Windows, you may need to type `ums_system.exe`)*

The system will start by loading data from `students.txt`, `faculty.txt`, and `courses.txt`.

-----

## 💡 How Data Persistence Works

The UMS ensures all data is saved between sessions using file handling:

1.  **Loading:** The `ManagementSystem` constructor automatically reads and parses data from the `.txt` files into in-memory `std::vector` containers.
2.  **Saving:** When the user selects the "Exit System" option, the `ManagementSystem` **destructor** is called. This destructor automatically triggers the `save_all_data()` function, which overwrites the `.txt` files with the current state of the in-memory objects.

-----

## ⚙️ Key Features

The system supports the following core operations:

  * **Add Records:** Create new `Student`, `Faculty`, and `Course` entities.
  * **View Records:** Display detailed records for all students, faculty, and courses.
  * **Enrollment:** Link a `Student` ID to a `Course` ID, performing a **two-way update** on both objects.
  * **Grading:** Set grades for students in specific courses.
  * **Robust Input:** Uses advanced input validation (`cin.clear()`, `cin.ignore()`) to prevent crashes from invalid user input.
