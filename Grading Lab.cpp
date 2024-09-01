#include <iostream>
#include <string>
#include <vector>

std::vector<int> grades;
void enterGrade();
void removeGrade();
void showGrades();
void showFinalGrade();
void showFinalGradeDL();

int main()
{
    while (1) {
        std::cout << "1. Enter Grade" << std::endl;
        std::cout << "2. Remove Grades" << std::endl;
        std::cout << "3. Show Grades" << std::endl;
        std::cout << "4. Show Final Grade" << std::endl;
        std::cout << "5. Show Final Grade (With the lowest grade removed)." << std::endl;
        std::cout << "6. Quit" << std::endl;
    
        int input;
        std::cin >> input;

        if (input == 0) {
            return 0;
        }
        else if (input == 1) {
            enterGrade();
        }
        else if (input == 2) {
            removeGrade();
        }
        else if (input == 3) {
            showGrades();
        }
        else if (input == 4) {
            showFinalGrade();
        }
        else if (input == 5) {
            showFinalGradeDL();
        }
    }
}

void enterGrade() {
        int newGrade;
        std::cout << "Enter the grade: ";
        while (1) {
            std::cin >> newGrade;
            if (!(newGrade > 100 || newGrade <= -1)) {
                grades.push_back(newGrade);
                std::cout << "Grade has been added!\n___________" << std::endl;
                return;
            }else{
                std::cout << "Invalid Grade, Try Again" << std::endl;
        }
    }
}

void removeGrade() {
    std::cout << "Here is a list of the current grades:" << std::endl;
    for (unsigned int i = 0; i < grades.size(); i++) {
        std::cout << i << ". " << grades.at(i) << std::endl;
    }
    std::cout << "Which grade would you like to remove (Please enter the list number)" << std::endl;
    while (1) {
        unsigned int input;
        std::cin >> input;
        if (input <= grades.size() && input >= 0) {
            std::cout << "The Grade " << grades.at(input) << " has been Removed!\n___________" << std::endl;
            grades.erase(std::find(grades.begin(), grades.end(), grades.at(input)));
            return;
        }
        else {
            std::cout << "You entered an invalid number, please try again!" << std::endl;
        }
    }
}

void showGrades() {

    if (grades.size() == 0) {
        std::cout << "Sorry, there are no grades yet!\n___________" << std::endl;
        return;
    }
    for (unsigned int i = 0; i < grades.size(); i++) {
        std::cout << i << ". " << grades.at(i) << std::endl;
    }
    std::cout << "___________" << std::endl;
}

void showFinalGrade() {
    if (grades.size() == 0) {
        std::cout << "Sorry, there are no grades yet!\n___________" << std::endl;
        return;
    }
    double totalNumber = 0.0;
    for (int g:grades) {
        totalNumber += g;
    }
    totalNumber = totalNumber / grades.size();
    std::cout << "The average grade is: " << totalNumber << "!\n___________" << std::endl;

}

void showFinalGradeDL() {
    if (grades.size() == 0) {
        std::cout << "Sorry, there are no grades yet!\n___________" << std::endl;
        return;
    }
    int lowest = 100;
    for (int l : grades) {
        if (l < lowest) {
            lowest = l;
        }
    }

    grades.erase(std::find(grades.begin(), grades.end(), lowest));
    double totalNumber = 0.0;
    for (int g : grades) {
        totalNumber += g;
    }
    totalNumber = totalNumber / grades.size();
    grades.push_back(lowest);
    std::cout << "Your final grade, with " << lowest << " being removed, is " << totalNumber << "!\n___________" << std::endl;

}