#include <iostream>
#include <vector>
#include <iomanip>
#include <memory>
#include <string>
#include "GradedItem.h"
#include "Homework.h"
#include "Quiz.h"
#include "Exam.h"
#include <limits> //Allows the code to use numeric_limits
#include <algorithm> // Uses various algorithms provided by the C++ Standard Library
#include <map> //Allows the code to use std::map
#include <fstream>

/*
 * Grade Calculator (OOP Edition) — Final Project
 * Author: Tyler Nguyen
 * Course: COSC 1437, 2026
 *
 * Concepts Demonstrated (Chapters 11-18 + Sprints 19-22)
 * ------------------------------------------------------
 * Ch 11 - Foundation from COSC 1436: std::vector, control flow, modular code
 * Ch 12 - <algorithm>: find_if
 * Ch 13 - <fstream> file I/O: saveGrades() / loadGrades() to "grades.txt"
 * Ch 14 - User-defined class: GradedItem with private fields + getters
 * Ch 15 - Object refinement: parameterized constructor, getPercentage(), encapsulation
 * Ch 16 - Menu-driven UI: switch statement, <iomanip> formatting, helper functions
 * Ch 17 - Inheritance + polymorphism: Homework / Quiz / Exam derive from GradedItem
 * Ch 18 - Smart pointers: std::vector<std::unique_ptr<GradedItem>>; GradingScheme struct
 *
 * Sprint 19 - Reject non-numeric input: getValidatedInput
 * Sprint 20 - Edit existing item: editItem
 * Sprint 21 - ANSI color for letter grades: gradeColors
 * Sprint 22 - GPA scale conversion
 */

using namespace std;

struct GradingScheme {
    float homeworkWeight = 0.20f;
    float quizWeight = 0.30f;
    float examWeight = 0.50f;
    float cutoffA = 90.0f;
    float cutoffB = 80.0f;
    float cutoffC = 70.0f;
    float cutoffD = 60.0f;
};

//Changes the grade color based on the grade.
map<char, string> gradeColors = {
        {'A', "\033[32m"}, // Green
        {'B', "\033[34m"}, // Blue
        {'C', "\033[33m"}, // Yellow
        {'D', "\033[35m"}, // Magenta
        {'F', "\033[31m"}  // Red
    };

void displayHeader(const string& title) {
    cout << "\n";
    cout << string(50, '=') << '\n';
    cout << "  " << title << '\n';
    cout << string(50, '=') << '\n';
}

void displaySeparator() {
    cout << string(50, '-') << '\n';
}

//Creates a summary of the graded items by counting how many items exist in each category
void displayDashboard(const vector<unique_ptr<GradedItem>>& items) {
    map<string, int> categoryCount;
    for (const auto& item : items) {
        categoryCount[item->getCategory()]++;
    }

    // Display summary
    displayHeader("DASHBOARD SUMMARY");
    for (const auto& category : categoryCount) {
        cout << category.first << ": " << category.second << " items\n";
    }
    displaySeparator();
}

void saveGrades(const vector<unique_ptr<GradedItem>>& items) {
    std::ofstream outFile("grades.txt");
    if (!outFile) {
        cout << "Error opening file for writing.\n";
        return;
    }
    for (const auto& item : items) {
        outFile << item->getCategory() << ","
                << item->getName() << ","
                << item->getPointsEarned() << ","
                << item->getPointsPossible() << "\n";
    }
}

void loadGrades(vector<unique_ptr<GradedItem>>& items) {
    std::ifstream inFile("grades.txt");
    if (!inFile) {
        cout << "Error opening file for reading.\n";
        return;
    }
    string category, name;
    float earned, possible;
    while (inFile >> category >> name >> earned >> possible) {
        if (category == "Homework") {
            items.push_back(make_unique<Homework>(name, earned, possible));
        } else if (category == "Quiz") {
            items.push_back(make_unique<Quiz>(name, earned, possible));
        } else if (category == "Exam") {
            items.push_back(make_unique<Exam>(name, earned, possible));
        }
    }
}

void displayMenu() {
    displayHeader("GRADE CALCULATOR - MAIN MENU");

    //Uses std::map to simplfy the code for the menu
    map<int, string> menuOptions = {
            {1, "Set Grading Scheme"},
            {2, "Add Graded Item"},
            {3, "View All Items"},
            {4, "Remove Item"},
            {5, "Calculate Grade (Points-Based)"},
            {6, "Calculate Grade (Weighted)"},
            {7, "Search Item"},
            {8, "Edit Item"},
            {9, "Display Filtered Items"},
            {0, "Exit"},
        };

    for (const auto& option : menuOptions) {
        cout << option.first << ". " << option.second << '\n';
    }
    displaySeparator();
}

//Organizes and displays graded items based on their category
void displayItemsByCategory(const vector<unique_ptr<GradedItem>>& items) {
    map<string, vector<const GradedItem*>> categorizedItems; // Store pointers

    for (const auto& item : items) {
        categorizedItems[item->getCategory()].push_back(item.get());
    }

    for (const auto& category : categorizedItems) {
        displayHeader("CATEGORY: " + category.first);
        for (const auto& item : category.second) {
            cout << item->getName() << ", " << item->getPercentage() << "%\n";
        }
        displaySeparator();
    }
}

char getLetterGrade(float percentage, const GradingScheme& scheme) {
    if (percentage >= scheme.cutoffA) return 'A';
    if (percentage >= scheme.cutoffB) return 'B';
    if (percentage >= scheme.cutoffC) return 'C';
    if (percentage >= scheme.cutoffD) return 'D';
    return 'F';
}

//This template function ensures that the input from the user is true. If false, the code will print out an error message and uses a while loop to ask for the input again. This will prevent the code from creating an infinite loop.
template<typename T>
T getValidatedInput(const string& prompt) {
    T input;
    while (true) {
        cout << prompt;

        //Declares a string variable,  reads a full line of input into a string, and attempts to parse the string into a specified data type for validation.
        string line;
        getline(cin, line);
        istringstream iss(line);
        iss >> input;

        //If the input is not a valid numeric value, it displays an error message. If not, input is returned.
        if (iss.fail() || !iss.eof() || input < 0) {
            cout << "Invalid input. Please enter a valid numeric value.\n";
        } else {
            return input;
        }
    }
}

void setGradingScheme(GradingScheme& scheme) {
    displayHeader("SET GRADING SCHEME");
    cout << "-- Category Weights --\n";

    //The try block is used to execute code that might throw an exception
    try {
        //Allows floating-point values hw, qz, and ex to access getValidatedInput
        float hw = getValidatedInput<float>("Enter weight for Homework (%): ");
        float qz = getValidatedInput<float>("Enter weight for Quizzes (%): ");
        float ex = getValidatedInput<float>("Enter weight for Exams (%): ");
        
        float total = hw + qz + ex;
        if (total != 100.0f) {
            //Uses a throw to displays an error message if total does not equal to 100.0f
            throw std::invalid_argument("Weights must sum to 100%. Press enter to return to the main menu.");
        }

        scheme.homeworkWeight = hw / 100.0f;
        scheme.quizWeight = qz / 100.0f;
        scheme.examWeight = ex / 100.0f;
        cout << "Weights saved!\n";

        cout << "\n-- Letter Grade Cutoffs --\n";
        scheme.cutoffA = getValidatedInput<float>("Enter minimum % for A: ");
        scheme.cutoffB = getValidatedInput<float>("Enter minimum % for B: ");
        scheme.cutoffC = getValidatedInput<float>("Enter minimum % for C: ");
        scheme.cutoffD = getValidatedInput<float>("Enter minimum % for D: ");

        cout << "Cutoffs saved!\n";
    } catch (const std::invalid_argument& e) {
        cout << e.what() << " Try again.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    } //Display an error message by using the catch block
}

void addGradedItem(vector<unique_ptr<GradedItem>>& items) {
    displayHeader("ADD GRADED ITEM");
    cout << "Select category:\n";
    cout << "1. Homework\n";
    cout << "2. Quiz\n";
    cout << "3. Exam\n";

    //Allows integer variable category to access getValidatedInput.
    int category = getValidatedInput<int>("Choice: ");
    cout << "Name: ";
    string name;
    getline(cin, name);

    //Allows floating-point values possible, and earned to access getValidatedInput.
    float possible = getValidatedInput<float>("Points possible: ");
    float earned = getValidatedInput<float>("Points earned: ");

    switch (category) {
        case 1:
            items.push_back(make_unique<Homework>(name, earned, possible));
            break;
        case 2:
            items.push_back(make_unique<Quiz>(name, earned, possible));
            break;
        case 3:
            items.push_back(make_unique<Exam>(name, earned, possible));
            break;
        default:
            cout << "Invalid category.\n";
            return;
    }
    cout << "Item added!\n";
}

void viewItems(const vector<unique_ptr<GradedItem>>& items) {
    displayHeader("ALL GRADED ITEMS");
    if (items.empty()) {
        cout << "No items entered yet.\n";
        return;
    }
    cout << left << setw(5) << "#"
         << setw(20) << "Name"
         << setw(12) << "Category"
         << right << setw(10) << "Earned"
         << setw(10) << "Possible"
         << setw(10) << "Percent" << '\n';
    displaySeparator();
    cout << fixed << setprecision(1);
    for (size_t i = 0; i < items.size(); ++i) {
        cout << left << setw(5) << (i + 1)
             << setw(20) << items[i]->getName()
             << setw(12) << items[i]->getCategory()
             << right << setw(10) << items[i]->getPointsEarned()
             << setw(10) << items[i]->getPointsPossible()
             << setw(9) << items[i]->getPercentage() << "%\n";
    }
}

void removeItem(vector<unique_ptr<GradedItem>>& items) {
    displayHeader("REMOVE ITEM");
    if (items.empty()) {
        cout << "No items to remove.\n";
        return;
    }

    int index = -1;
    while (true) {
        for (size_t i = 0; i < items.size(); ++i) {
            cout << (i + 1) << ". " << items[i]->getCategory()
                 << " - " << items[i]->getName() << '\n';
        }
        cout << "Enter item number to remove (0 to cancel): ";

        //Allows integer variable index to access getValidatedInput.
        index = getValidatedInput<int>("");

        //If index is less than zero or bigger than the size of the item, the code will display an error message. If index is zero, remove item is cancelled. If index is none of these, it removes an item.
        if (index < 0 || index > static_cast<int>(items.size())) {
            cout << "Invalid input. Please enter a valid numeric value.\n";
        } else if (index == 0) {
            cout << "Cancelled.\n";
            return;
        } else {
            break;
        }
    }

    cout << "Removed: " << items[index - 1]->getName() << '\n';
    items.erase(items.begin() + (index - 1));
}

void calculatePointsBased(const vector<unique_ptr<GradedItem>>& items, const GradingScheme& scheme) {
    displayHeader("POINTS-BASED GRADE");
    if (items.empty()) {
        cout << "No items to calculate.\n";
        return;
    }

    float totalEarned = 0, totalPossible = 0;
    for (const auto& item : items) {
        totalEarned += item->getPointsEarned();
        totalPossible += item->getPointsPossible();
    }

    float percentage = (totalPossible > 0) ? (totalEarned / totalPossible) * 100 : 0;
    char grade = getLetterGrade(percentage, scheme); //Created a new character to reduce the length of work when used in gradeColor

    cout << fixed << setprecision(1);
    cout << "Total Earned: " << totalEarned << " / " << totalPossible << '\n';
    cout << "Overall: " << percentage << "%\n";
    cout << gradeColors[grade] << "Letter Grade: " << grade << "\033[0m\n"; // Apply color
}

void calculateWeighted(const vector<unique_ptr<GradedItem>>& items,
                        const GradingScheme& scheme) {
    displayHeader("WEIGHTED GRADE CALCULATION");
    if (items.empty()) {
        cout << "No items to calculate.\n";
        return;
    }

    float hwTotal = 0, hwCount = 0;
    float quizTotal = 0, quizCount = 0;
    float examTotal = 0, examCount = 0;

    for (const auto& item : items) {
        if (item->getCategory() == "Homework") {
            hwTotal += item->getPercentage();
            hwCount++;
        } else if (item->getCategory() == "Quiz") {
            quizTotal += item->getPercentage();
            quizCount++;
        } else if (item->getCategory() == "Exam") {
            examTotal += item->getPercentage();
            examCount++;
        }
    }

    float hwAvg = hwCount > 0 ? hwTotal / hwCount : 0;
    float quizAvg = quizCount > 0 ? quizTotal / quizCount : 0;
    float examAvg = examCount > 0 ? examTotal / examCount : 0;

    float finalGrade = (hwAvg * scheme.homeworkWeight)
                     + (quizAvg * scheme.quizWeight)
                     + (examAvg * scheme.examWeight);
    
    char grade = getLetterGrade(finalGrade, scheme); //Created a new character to reduce the length of work when used in gradeColor

    cout << fixed << setprecision(1);
    cout << "Homework Average:  " << hwAvg << "% ("
         << (scheme.homeworkWeight * 100) << "% weight)\n";
    cout << "Quiz Average:      " << quizAvg << "% ("
         << (scheme.quizWeight * 100) << "% weight)\n";
    cout << "Exam Average:      " << examAvg << "% ("
         << (scheme.examWeight * 100) << "% weight)\n";
    cout << "\nFinal Weighted Grade: " << finalGrade << "%\n";
    cout << gradeColors[grade] << "Letter Grade: " << grade << "\033[0m\n"; // Apply color
}

//This function allows the user to search for an item by finding its name. If found, the program will print the name and the category of the item. If not found, the program prints a message.
void searchItem(const vector<unique_ptr<GradedItem>>& items) {
    string searchName;
    cout << "Enter the name of the item you want to search for: ";
    getline(cin, searchName);

    auto it = find_if(items.begin(), items.end(), [&searchName](const unique_ptr<GradedItem>& item) {
        return item->getName() == searchName;
    });

    if (it != items.end()) {
        cout << "Item found: " << (*it)->getName() << ", Category: " << (*it)->getCategory() << '\n';
    } else {
        cout << "Item not found.\n";
    }
}

//This function allows the user to edit an item by finding its name. If found, the program will print the name, along with the new points earned. If not found, the program prints a message.
void editItem(vector<unique_ptr<GradedItem>>& items) {
    string itemName;
    cout << "Enter the name of the item to edit: ";
    getline(cin, itemName);

    auto it = find_if(items.begin(), items.end(), [&itemName](const unique_ptr<GradedItem>& item) {
        return item->getName() == itemName;
    });

    if (it != items.end()) {
        cout << "Item found: " << (*it)->getName() << '\n';

        float newEarned = getValidatedInput<float>("New points earned: ");
        float newPossible = getValidatedInput<float>("New points possible: ");
        // Assuming setter methods exist or similar accessible method
        (*it)->setPointsEarned(newEarned);
        (*it)->setPointsPossible(newPossible);
        cout << "Item updated.\n";
    } else {
        cout << "Item not found.\n";
    }
}

//This function allows the user to display the filtered item from category.
void displayFilteredItems(const vector<unique_ptr<GradedItem>>& items, const string& filterCategory) {
    displayHeader("FILTERED ITEMS");

    bool found = false;
    for (const auto& item : items) {
        if (item->getCategory() == filterCategory) {
            cout << item->getName() << ", " << item->getPointsEarned() << " / "
                 << item->getPointsPossible() << ", " << item->getPercentage() << "%\n";
            found = true;
        }
    }

    if (!found) {
        cout << "No items found in the category: " << filterCategory << '\n';
    }

    displaySeparator();
}

int main() {
    GradingScheme scheme;
    vector<unique_ptr<GradedItem>> items;

    int choice = 0;
    do {
        displayMenu();
        cout << "Enter choice: ";
        choice = getValidatedInput<int>("");

        switch (choice) {
            case 1: setGradingScheme(scheme); break;
            case 2: addGradedItem(items); break;
            case 3: viewItems(items); break;
            case 4: removeItem(items); break;
            case 5: calculatePointsBased(items, scheme); break;
            case 6: calculateWeighted(items, scheme); break;
            case 7: searchItem(items); break;  // New search feature
            case 8: editItem(items); break;    // New edit feature
            case 9: {
                string category;
                cout << "Enter category to filter by (Homework/Quiz/Exam): ";
                cin >> category;
                
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear input buffer
                displayFilteredItems(items, category);
                break; // New display feature
            }
            case 10: saveGrades(items); break;
            case 11: loadGrades(items); break;
            case 0:
                displayHeader("GOODBYE");
                cout << "Thank you for using Grade Calculator!\n";
                break;
            default:
                cout << "Invalid input. Please enter a valid numeric value.\n";
        }
    } while (choice != 0);

    return 0;
}