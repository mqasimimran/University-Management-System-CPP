#include <iostream>
#include <string>
#include <vector>

using namespace std;

// BASE CLASS: Person 
class Person {
protected:
    string name;
public:
    Person(const string& name) : name(name) {}
    virtual ~Person() {} // Virtual destructor for safe inheritance
    virtual void display() const {
        cout << "Name: " << name << endl;
    }
};

// INHERITANCE: Student 
class Student : public Person {
private:
    vector<int> courseIds;
public:
    Student(const string& name) : Person(name) {}
    void addCourse(int courseId) { courseIds.push_back(courseId); }
    
    // POLYMORPHISM: Method Overriding 
    void display() const override {
        Person::display();
        cout << "   Enrolled Course IDs: ";
        if(courseIds.empty()) cout << "None";
        for (int id : courseIds) {
            cout << id << " ";
        }
        cout << endl;
    }
};

class Faculty : public Person {
public:
    Faculty(const string& name) : Person(name) {}
};

// AGGREGATION: Department 
class Department {
private:
    string name;
    vector<Faculty> facultyMembers;
public:
    Department(const string& name) : name(name) {}
    // Efficiency: Pass by const reference
    void addFacultyMember(const Faculty& faculty) { facultyMembers.push_back(faculty); }
    void display() const {
        cout << "Department: " << name << "\n Faculty Members:\n";
        for (const auto& f : facultyMembers) {
            f.display();
        }
    }
};

class Course {
private:
    string title;
    vector<Student> students;
public:
    Course(const string& title) : title(title) {}
    void addStudent(const Student& student) { students.push_back(student); }
    void display() const {
        cout << "Course: " << title << "\n Enrolled Students:\n";
        for (const auto& s : students) {
            s.display();
        }
    }
};

class University {
private:
    string universityName;
    vector<Department> departments;
public:
    University(const string& universityName) : universityName(universityName) {}
    void addDepartment(const Department& dept) { departments.push_back(dept); }
    void display() const {
        cout << "\n--- " << universityName << " Records ---\n";
        for (const auto& d : departments) {
            d.display();
        }
    }
};

// COMPOSITION Examples 
class Building {
    string name;
public:
    Building(const string& n) : name(n) {}
    void display() const { cout << "Building: " << name << endl; }
};

class Classroom {
    int id;
    Building building; // Composition 
public:
    Classroom(int id, const Building& b) : id(id), building(b) {}
    void display() const {
        cout << "Classroom ID: " << id << " | ";
        building.display();
    }
};

// MAIN SYSTEM: Menu Driven 
int main() {
    string uniName;
    cout << "Welcome to UMS Setup\n";
    cout << "Enter University Name: ";
    getline(cin, uniName);
    University myUni(uniName);

    int choice;
    do {
        cout << "\n--- University Management Menu ---\n";
        cout << "1. Create Department & Add Faculty\n";
        cout << "2. Display University Info\n";
        cout << "0. Exit System\n";
        cout << "Selection: ";
        cin >> choice;
        cin.ignore();

        if (choice == 1) {
            string dName, fName;
            cout << "Enter Dept Name: ";
            getline(cin, dName);
            Department newDept(dName);
            
            cout << "Enter Head Faculty Name: ";
            getline(cin, fName);
            newDept.addFacultyMember(Faculty(fName));
            
            myUni.addDepartment(newDept);
            cout << "Department added successfully!\n";
        } 
        else if (choice == 2) {
            myUni.display();
        }

    } while (choice != 0);

    cout << "Exiting system. All records saved in memory.\n";
    return 0;
}
