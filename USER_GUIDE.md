# Grade Calculator (OOP Edition)

## Introduction
This program provides various ways to calculate and manage grades for homeworks, quizzes, and exams from a menu-driven interface. Many of these features include points-based and weighted grade calculations, along with a customizable grading scheme.

## Getting Started
To launch the program, refer to the README.md file. This program requires a C++17 or any newer compiler, built in g++ -std=c++17 *.cpp -o GradeCalculator, and runs ./GradeCalculator in macOS/Linux or GradeCalculator.exe in Windows.

## Menu Walkthrough
Within the main menu, there are 10 different options; each having a unique property:

- **0**: If the user chooses 0, the program will exit the grade calculator. This option does not require anything or uses any data types or format.
- **1**: If the user chooses 1, the program sets up a grading scheme. The program will ask for the weight of homework, quizzes, and exams; each using a data type homeworkWeight, quizWeight, examWeight. For weights, it only accepts numeric values that are greater than or equal to zero. The program will only continue if the total weight of all three equals 100. This option also requires the minimum percentage for an A, B, C, and D. For each grade, they use the data type cutoffA, cutoffB, cutoffC, and cutoffD. Just like weights, it only accepts numeric values that are greater than or equal to zero.
- **2**: If the user chooses 2, the program adds a graded item. To add a graded item, the program will ask for a category, name, the amount of points possible, and the amount of points earned. The input format used includes the integer variable category, string variable name, and floating point-variable possible and earned. For choice, points possible, and points earned, it only accepts numeric values that are greater than or equal to zero. As for name, it allows any input.
- **3**: If the user chooses 3, the program displays every graded item. Since the program only displays, it does not ask for anything or uses any data types or format. If there are no items, the display will not appear and only prints a message stating that there are no items entered yet.
- **4**: If the user chooses 4, the program will remove an item. To remove an item, the program provides every graded item and asks the user to enter the item number to remove. The input format used is the integer variable index. In removing item, it only accepts numeric values that are shown to be available. If 0 is chosen, remove item is cancelled. If there is no item, the program prints a message stating that there are no items to remove.
- **5**: If the user chooses 5, the program will calculate the grade through points-based. Since the program only displays, it does not ask for anything. The data type used includes floating-point variable totalEarned, totalPossible, and percentage. Another data type used is character grade. If there is no item, the program prints a message stating that there are no items to calculate.
- **6**: If the user chooses 6, the program will calculate the grade through weighted. Since the program only displays, it does not ask for anything. The data type used includes floating-point variable hwTotal, hwCount, quizTotal, quizCount, examTotal, examCount, hwAvg, quizAvg, examAvg, and finalGrade. If there are no items, the program prints a message stating that there are no items to calculate.
- **7**: If the user chooses 7, the program will search for the item. To search for the item, the program will ask for the name of the item. The input format used is the string variable searchName. For search item to work properly, the name must match the name of an existing item. If the name does not match, the program prints a message stating that the item is not found.
- **8**: If the user chooses 8, the program will edit the item. To edit an item, the program will ask for the name of the item. If the name is found, the program will ask for the new points earned and the new points possible. The input format used is the floating-point variable newEarned and newPossible. If the name does not match, the program prints a message stating that the item is not found. As for the points, it only accepts numeric values that are greater than or equal to zero.
- **9**: If the user chooses 9, the program will display filtered items. To display filtered items, the program will ask for the category to filter by. The input format used is a constant string variable filterCategory. If the category does not match, the program prints a message stating that no items were found in the category.

## Sample Session
    ==================================================
    GRADE CALCULATOR - MAIN MENU
    ==================================================
    0. Exit
    1. Set Grading Scheme
    2. Add Graded Item
    3. View All Items
    4. Remove Item
    5. Calculate Grade (Points-Based)
    6. Calculate Grade (Weighted)
    7. Search Item
    8. Edit Item
    9. Display Filtered Items
    --------------------------------------------------
    Enter choice: 1

    ==================================================
    SET GRADING SCHEME
    ==================================================
    -- Category Weights --
    Enter weight for Homework (%): 20
    Enter weight for Quizzes (%): 30
    Enter weight for Exams (%): 50
    Weights saved!

    -- Letter Grade Cutoffs --
    Enter minimum % for A: 90
    Enter minimum % for B: 80
    Enter minimum % for C: 70
    Enter minimum % for D: 60
    Cutoffs saved!

    ==================================================
    GRADE CALCULATOR - MAIN MENU
    ==================================================
    0. Exit
    1. Set Grading Scheme
    2. Add Graded Item
    3. View All Items
    4. Remove Item
    5. Calculate Grade (Points-Based)
    6. Calculate Grade (Weighted)
    7. Search Item
    8. Edit Item
    9. Display Filtered Items
    --------------------------------------------------
    Enter choice: 2

    ==================================================
    ADD GRADED ITEM
    ==================================================
    Select category:
    1. Homework
    2. Quiz
    3. Exam
    Choice: 1
    Name: H
    Points possible: 100
    Points earned: 90
    Item added!

    ==================================================
    GRADE CALCULATOR - MAIN MENU
    ==================================================
    0. Exit
    1. Set Grading Scheme
    2. Add Graded Item
    3. View All Items
    4. Remove Item
    5. Calculate Grade (Points-Based)
    6. Calculate Grade (Weighted)
    7. Search Item
    8. Edit Item
    9. Display Filtered Items
    --------------------------------------------------
    Enter choice: 2

    ==================================================
    ADD GRADED ITEM
    ==================================================
    Select category:
    1. Homework
    2. Quiz
    3. Exam
    Choice: 2
    Name: Quiz
    Points possible: 100
    Points earned: 80
    Item added!

    ==================================================
    GRADE CALCULATOR - MAIN MENU
    ==================================================
    0. Exit
    1. Set Grading Scheme
    2. Add Graded Item
    3. View All Items
    4. Remove Item
    5. Calculate Grade (Points-Based)
    6. Calculate Grade (Weighted)
    7. Search Item
    8. Edit Item
    9. Display Filtered Items
    --------------------------------------------------
    Enter choice: 2

    ==================================================
    ADD GRADED ITEM
    ==================================================
    Select category:
    1. Homework
    2. Quiz
    3. Exam
    Choice: 3
    Name: Exam 1
    Points possible: 50 
    Points earned: 40
    Item added!

    ==================================================
    GRADE CALCULATOR - MAIN MENU
    ==================================================
    0. Exit
    1. Set Grading Scheme
    2. Add Graded Item
    3. View All Items
    4. Remove Item
    5. Calculate Grade (Points-Based)
    6. Calculate Grade (Weighted)
    7. Search Item
    8. Edit Item
    9. Display Filtered Items
    --------------------------------------------------
    Enter choice: 3

    ==================================================
    ALL GRADED ITEMS
    ==================================================
    #    Name                Category        Earned  Possible   Percent
    --------------------------------------------------
    1    H                   Homework          90.0     100.0     90.0%
    2    Quiz                Quiz              80.0     100.0     80.0%
    3    Exam 1              Exam              40.0      50.0     80.0%

    ==================================================
    GRADE CALCULATOR - MAIN MENU
    ==================================================
    0. Exit
    1. Set Grading Scheme
    2. Add Graded Item
    3. View All Items
    4. Remove Item
    5. Calculate Grade (Points-Based)
    6. Calculate Grade (Weighted)
    7. Search Item
    8. Edit Item
    9. Display Filtered Items
    --------------------------------------------------
    Enter choice: 5

    ==================================================
    POINTS-BASED GRADE
    ==================================================
    Total Earned: 210.0 / 250.0
    Overall: 84.0%
    Letter Grade: B

    ==================================================
    GRADE CALCULATOR - MAIN MENU
    ==================================================
    0. Exit
    1. Set Grading Scheme
    2. Add Graded Item
    3. View All Items
    4. Remove Item
    5. Calculate Grade (Points-Based)
    6. Calculate Grade (Weighted)
    7. Search Item
    8. Edit Item
    9. Display Filtered Items
    --------------------------------------------------
    Enter choice: 6

    ==================================================
    WEIGHTED GRADE CALCULATION
    ==================================================
    Homework Average:  90.0% (20.0% weight)
    Quiz Average:      80.0% (30.0% weight)
    Exam Average:      80.0% (50.0% weight)

    Final Weighted Grade: 82.0%
    Letter Grade: B

    ==================================================
    GRADE CALCULATOR - MAIN MENU
    ==================================================
    0. Exit
    1. Set Grading Scheme
    2. Add Graded Item
    3. View All Items
    4. Remove Item
    5. Calculate Grade (Points-Based)
    6. Calculate Grade (Weighted)
    7. Search Item
    8. Edit Item
    9. Display Filtered Items
    --------------------------------------------------
    Enter choice: 0

    ==================================================
    GOODBYE
    ==================================================
    Thank you for using Grade Calculator!

## Sprint Features
**Lab 19**: This sprint rejects any non-numeric input by using the function template, getValidatedInput. To be invoked, the code must declare getValidatedInput along, with the variable type declared within angle brackets and the text that accompany the input within parentheses. If the input is a valid numerical value, the program will return the input. But if the input is not a numeric value or any value that is not stated, the program will print an error message and ask to be inputted again.

**Lab 20**: This sprint searches or edits an existing item and displays items through a filter.
- **Search Item**: When searching an item is invoked, the user must choose option 7 with the code declaring the function, searchItem, with items being declared within parentheses. How searchItem works is that the code goes through each item to see if the name from the user matches the name of an existing item. If not found, the program prints a message saying that the item is not found. If found, the program will print the name of the item, along with the category.
- **Edit Item**: Editing an item is similarly invoked to searching for an item, but the user must choose option 8 with the code declaring the function, editItem. Just like searchItem, editItem goes through each item to see if the name from the user matches the name of an existing item. If not found, the program prints a message saying that the item is not found. Unlike searchItem the code will ask for the new points earned, along with the new points possible, and replace the original points when found.
- **Display Filtered Items**: It is invoked by having the user choose option 9 and the code declaring the function, displayFilteredItems with item and category declared within parentheses. How this works is that the program will ask for a category that it will filter by. Within displayFilteredItems, if the category from the user matches an existing category, the program will display every item from that category. If the category cannot be found, the program prints out a message stating that no items were found.

**Lab 21**: This sprint prints the letter grade with a corresponding color: A is green, B is blue, C is yellow, D is magenta, and F is red. For this sprint to be invoked, the code must declare gradeColors with the grade declared within square brackets. How this works is that each grade is assigned to a color, and the grade declare within the square brackets must find the matching grade.

**Lab 22**: This sprint has nothing to provide since the goal for this sprint is to refine the code.

## Understanding Your Results
Points-based calculation calculates the grade as a simple percentage of total points earned out of total points possible across all items. It is used if you want a straightforward representation of performance without considering varying importance among different categories. As for weighted calculations, it takes into account the different weights assigned to categories like homework, quizzes, and exams. It is used if you want to emphasize the significance of certain categories over others, like giving exams more weight in the overall grade calculation.

## Known Limitations
While this program works as intended, there is some minor inconsistencies:

**1**. When inputting a non-numeric value or a negative number in the main menu, the program will print out an error message. But if a numeric value bigger than 9 is entered, the program will print out an error message and reprint the main menu.

**2**. When choosing a category in Display Filtered Items, it is important to note that the input is case-sensitive; meaning that the category with the same name, yet having different capitalizations are considered separate category. The categories that are acceptable are Homework, Quiz, and Exam.

## Troubleshooting
**1**. If the program crashes or displays incorrect behavior, use the getValidatedInput template function to ensure that input is a valid numeric value.

**2**. Categories such as "Homework", "Quiz", and "Exam" are case-sensitive. To improve this, use std::transform to convert the input to a specific case (all lowercase or all uppercase) before comparison.
