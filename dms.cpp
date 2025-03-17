#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
#include <windows.h> // For setting colors in Windows
using namespace std;

// Function to set console color
void setColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}
   
// Student Structure
struct Student {
    int id;
    string name;
    int age;
    float marks[4][5]; // 4 Semesters, 5 subjects each
    float cgpa[4];

    // Constructor to initialize student data
    Student(int sid, string sname, int sage, float smarks[4][5]) {
        id = sid;
        name = sname;
        age = sage;
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 5; j++) {
                marks[i][j] = smarks[i][j];
            }
            cgpa[i] = calculateCGPA(marks[i]);
        }
    }

    // Function to calculate CGPA for each semester
    float calculateCGPA(float marks[]) {
        float sum = 0;
        for (int i = 0; i < 5; i++) {
            sum += marks[i];
        }
        return sum / 50; // Assuming each subject is out of 10
    }
};

// Vector to store students
vector<Student> students;

// Function to save student records to a file
void saveToFile() {
    ofstream file("students.txt", ios::trunc);
    for (auto& s : students) {
        file << s.id << " " << s.name << " " << s.age << " ";
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 5; j++) {
                file << s.marks[i][j] << " ";
            }
            file << s.cgpa[i] << " ";
        }
        file << endl;
    }
    file.close();
}

// Function to load student records from a file
void loadFromFile() {
    ifstream file("students.txt");
    if (!file) return;
    int id, age;
    string name;
    float marks[4][5], cgpa[4];

    while (file >> id >> name >> age) {
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 5; j++) {
                file >> marks[i][j];
            }
            file >> cgpa[i];
        }
        students.push_back(Student(id, name, age, marks));
    }
    file.close();
}

// Function to add a new student
void addStudent() {
    int id, age;
    string name;
    float marks[4][5];

    setColor(10); // Green Color
    cout << "\nEnter Student ID: "; cin >> id;
    cout << "Enter Name: "; cin >> name;
    cout << "Enter Age: "; cin >> age;

    for (int i = 0; i < 4; i++) {
        cout << "\nEnter marks for Semester " << (i + 1) << " (5 subjects out of 10): ";
        for (int j = 0; j < 5; j++) {
            cin >> marks[i][j];
        }
    }

    students.push_back(Student(id, name, age, marks));
    saveToFile();

    setColor(14); // Yellow Color
    cout << "\nStudent Record Added Successfully!\n";
}

// Function to display all student records
void displayStudents() {

    setColor(11); // Cyan Color
    cout << "\n================ Student Records ================\n";

    if (students.empty()) {
        cout << "No students found!\n";
        return;
    }

    for (auto& s : students) {
        cout << "ID: " << s.id << " | Name: " << s.name << " | Age: " << s.age << endl;
        for (int i = 0; i < 4; i++) {
            cout << "Semester " << (i + 1) << " CGPA: " << fixed << setprecision(2) << s.cgpa[i] << endl;
        }
        cout << "-----------------------------------------------\n";
    }
}

// Function to initialize 10 students
void initializeStudents() {
    float marks[4][5] = {
        {8, 7, 6, 9, 8},
        {7, 6, 9, 8, 7},
        {9, 8, 7, 9, 10},
        {6, 7, 8, 7, 6}
    };

    students.push_back(Student(1, "Ali", 18, marks));
    students.push_back(Student(2, "Ahmed", 19, marks));
    students.push_back(Student(3, "Fatima", 20, marks));
    students.push_back(Student(4, "Zain", 18, marks));
    students.push_back(Student(5, "Noor", 21, marks));
    students.push_back(Student(6, "Hassan", 22, marks));
    students.push_back(Student(7, "Ayesha", 20, marks));
    students.push_back(Student(8, "Bilal", 18, marks));
    students.push_back(Student(9, "Maryam", 19, marks));
    students.push_back(Student(10, "Saad", 21, marks));

    saveToFile();
}

// Main Function
int main() {
    loadFromFile();

    // If file is empty, initialize with 10 students
    if (students.empty()) {
        initializeStudents();
    }

    int choice;
    while (true) {
        setColor(13); // Magenta Color
        cout << "\n1. Add Student Record";
        cout << "\n2. Display All Students";
        cout << "\n3. Exit";
        cout << "\nEnter Choice: ";
        cin >> choice;

        switch (choice) {
        case 1: addStudent(); break;
        case 2: displayStudents(); break;
        case 3: exit(0);
        default: cout << "\nInvalid Choice!";
        }
    }
    return 0;
}
