#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

const int NUM_SUBJECTS = 5;

class students; 

class faculty {
    int id;
    string name;

public:
    void enterinfo();
    void getinfo();
    void getaveragemarks(const vector<students*>& cl, int studentId);
};

class students {
    static int count;
    int id;
    string name;
    float marks[NUM_SUBJECTS];

public:
    friend void faculty::getaveragemarks(const vector<students*>& cl, int studentId);

    students() {
        id = count;
        count++;

        cout << "Enter name: ";
        cin >> name;

        for (int i = 0; i < NUM_SUBJECTS; i++) {
            cout << "Enter marks in subject " << i + 1 << ": ";
            cin >> marks[i];
        }
    }

    int getid() const {
        return id;
    }

    string getname() const {
        return name;
    }

    float getaverage() const {
        float sum = 0;
        for (int i = 0; i < NUM_SUBJECTS; i++) {
            sum += marks[i];
        }
        return sum / NUM_SUBJECTS;
    }

    void getinfo() const {
        cout << "ID: " << id << endl;
        cout << "Name: " << name << endl;
        for (int i = 0; i < NUM_SUBJECTS; i++) {
            cout << "Marks in subject " << i + 1 << " : " << marks[i] << endl;
        }
    }

    void updatename(const string& newName) {
        name = newName;
    }

    void updatemark(int subjectIndex, float newMark) {
        marks[subjectIndex] = newMark;
    }

    static void getcount() {
        cout << "Total students: " << count << endl;
    }
};

int students::count = 0;

void faculty::enterinfo() {
    cout << "ID: ";
    cin >> id;
    cout << "Name: ";
    cin >> name;
}

void faculty::getinfo() {
    cout << "ID: " << id << endl;
    cout << "Name: " << name << endl;
}

void faculty::getaveragemarks(const vector<students*>& cl, int studentId) {
    for (size_t i = 0; i < cl.size(); i++) {
        if (cl[i]->id == studentId) {
            float sum = 0;
            for (int j = 0; j < NUM_SUBJECTS; j++) {
                sum += cl[i]->marks[j];
            }
            cout << "Average marks of student " << studentId << " is " << sum / NUM_SUBJECTS << endl;
            return;
        }
    }
    cout << "No student found with ID " << studentId << "\n";
}

void printMenu() {
    cout << "\n1. Enter student\n";
    cout << "2. Get info\n";
    cout << "3. Get average\n";
    cout << "4. Get count\n";
    cout << "5. Average marks of class\n";
    cout << "6. Update student info\n";
    cout << "7. Delete student\n";
    cout << "8. Search student\n";
    cout << "9. Exit\n";
}

int findIndexById(const vector<students*>& cl, int id) {
    for (size_t i = 0; i < cl.size(); i++) {
        if (cl[i]->getid() == id) {
            return static_cast<int>(i);
        }
    }
    return -1;
}

void handleUpdate(vector<students*>& cl) {
    if (cl.empty()) {
        cout << "No students enrolled yet\n";
        return;
    }

    int id;
    cout << "Enter student ID to update: ";
    cin >> id;

    int idx = findIndexById(cl, id);
    if (idx == -1) {
        cout << "No student found with ID " << id << "\n";
        return;
    }

    cout << "1. Update name\n";
    cout << "2. Update a subject's marks\n";
    cout << "Choice: ";
    int choice;
    cin >> choice;

    if (choice == 1) {
        string newName;
        cout << "Enter new name: ";
        cin >> newName;
        cl[idx]->updatename(newName);
        cout << "Name updated.\n";
    }
    else if (choice == 2) {
        int subj;
        cout << "Enter subject number (1-" << NUM_SUBJECTS << "): ";
        cin >> subj;
        if (subj < 1 || subj > NUM_SUBJECTS) {
            cout << "Invalid subject number\n";
            return;
        }
        float mark;
        cout << "Enter new marks: ";
        cin >> mark;
        cl[idx]->updatemark(subj - 1, mark);
        cout << "Marks updated.\n";
    }
    else {
        cout << "Invalid choice\n";
    }
}

void handleDelete(vector<students*>& cl) {
    if (cl.empty()) {
        cout << "No students enrolled yet\n";
        return;
    }

    int id;
    cout << "Enter student ID to delete: ";
    cin >> id;

    int idx = findIndexById(cl, id);
    if (idx == -1) {
        cout << "No student found with ID " << id << "\n";
        return;
    }

    delete cl[idx];                
    cl.erase(cl.begin() + idx);   

    cout << "Student with ID " << id << " deleted.\n";
}

void handleSearch(const vector<students*>& cl) {
    if (cl.empty()) {
        cout << "No students enrolled yet\n";
        return;
    }

    cout << "1. Search by ID\n";
    cout << "2. Search by name\n";
    cout << "Choice: ";
    int choice;
    cin >> choice;

    if (choice == 1) {
        int id;
        cout << "Enter ID: ";
        cin >> id;
        int idx = findIndexById(cl, id);
        if (idx == -1) {
            cout << "No student found with ID " << id << "\n";
        } else {
            cl[idx]->getinfo();
        }
    }
    else if (choice == 2) {
        string query;
        cout << "Enter name (or part of it): ";
        cin >> query;

        bool found = false;
        for (size_t i = 0; i < cl.size(); i++) {
            if (cl[i]->getname().find(query) != string::npos) {
                cl[i]->getinfo();
                cout << "---\n";
                found = true;
            }
        }
        if (!found) {
            cout << "No student found matching \"" << query << "\"\n";
        }
    }
    else {
        cout << "Invalid choice\n";
    }
}

int main() {
    vector<students*> cl; 
    int a;

    while (true) {
        printMenu();
        cout << "Enter choice: ";
        cin >> a;

        if (a == 1) {
            cl.push_back(new students());
        }
        else if (a == 2) {
            int id;
            cout << "Enter student ID: ";
            cin >> id;
            int idx = findIndexById(cl, id);
            if (idx == -1) cout << "No student found with ID " << id << "\n";
            else cl[idx]->getinfo();
        }
        else if (a == 3) {
            int id;
            cout << "Enter student ID: ";
            cin >> id;
            int idx = findIndexById(cl, id);
            if (idx == -1) cout << "No student found with ID " << id << "\n";
            else cout << "Average marks: " << cl[idx]->getaverage() << endl;
        }
        else if (a == 4) {
            students::getcount();
        }
        else if (a == 5) {
            if (cl.empty()) {
                cout << "No students enrolled yet\n";
            } else {
                float av = 0;
                for (size_t i = 0; i < cl.size(); i++) {
                    av += cl[i]->getaverage();
                }
                cout << "Average marks of the class is " << av / cl.size() << endl;
            }
        }
        else if (a == 6) {
            handleUpdate(cl);
        }
        else if (a == 7) {
            handleDelete(cl);
        }
        else if (a == 8) {
            handleSearch(cl);
        }
        else if (a == 9) {
            break;
        }
        else {
            cout << "Invalid choice\n";
        }
    }

    if (!cl.empty()) {
        faculty f;
        f.enterinfo();
        f.getinfo();

        int o;
        cout << "Enter the ID of the student you want the average marks of: ";
        cin >> o;
        f.getaveragemarks(cl, o);
    }

    for (size_t i = 0; i < cl.size(); i++) {
        delete cl[i];
    }

    return 0;
}
