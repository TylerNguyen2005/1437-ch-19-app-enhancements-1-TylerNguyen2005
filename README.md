# Grade Calculator (OOP Edition)

A C++ console application that tracks graded items (homework, quizzes, exams),
calculates points-based and weighted final grades, and persists data between sessions.
Built around an inheritance hierarchy with a menu-driven interface.

## Author
Tyler Nguyen - COSC 1437, 2026

## Description
This program calculate grades from homework, quizzes, and exams. To calculate grades, it provides various options such as setting up a grading scheme, adding or removing a graded item, and many others. This program is designed for students who want to know what grade they have.

## Features
- Menu-driven interface (add / view / remove / calculate / exit)
- Three graded-item categories: Homework, Quiz, Exam
- Custom grading scheme: category weights + letter-grade cutoffs
- Two grade modes: points-based and weighted
- Save and load grades to/from a text file
- Ensuring that user inputs are valid
- Searches for an existing item
- Edit an existing item
- Display items through a filter
- Displaying letter grades in different colors

## Files
| File         | Purpose                                          |
|--------------|--------------------------------------------------|
| main.cpp     | Driver program: menu loop and orchestration     |
| GradedItem.h | Base class for all graded items                 |
| Homework.h   | Derived class - homework items                  |
| Quiz.h       | Derived class - quiz items                      |
| Exam.h       | Derived class - exam items                      |
| USER_GUIDE.md| End-user instructions                           |

## How to Build
Using g++ (Linux / macOS / WSL / MinGW):

    g++ -std=c++17 *.cpp -o GradeCalculator

## How to Run
    ./GradeCalculator        # macOS / Linux
    GradeCalculator.exe      # Windows

## Requirements
- C++17 or newer compiler (g++, clang, or MSVC)

## Course Concepts Demonstrated
Chapters 11-18 of [Textbook Title] plus four UX enhancement sprints (Labs 19-22).
