#include <iostream>
#include <vector>
using namespace std;


class Person {
protected:
    string name, id, address, phoneNumber, email;

public:
    Person(string n, string i, string addr, string phone, string mail)
        : name(n), id(i), address(addr), phoneNumber(phone), email(mail) {}

    virtual void displayInfo() {
        cout << "\n--- Person Info ---\n";
        cout << "Name: " << name << endl;
        cout << "ID: " << id << endl;
        cout << "Address: " << address << endl;
        cout << "Phone: " << phoneNumber << endl;
        cout << "Email: " << email << endl;
    }

    void updateInfo(string addr, string phone, string mail) {
        address = addr;
        phoneNumber = phone;
        email = mail;
    }

    string getName() { return name; }

    virtual ~Person() {}
};

// Student Class
class Student : public Person {
private:
    vector<string> coursesEnrolled;
    double GPA;
    int enrollmentYear;

public:
    Student(string n, string i, string addr, string phone, string mail,
            int year, double gpa)
        : Person(n, i, addr, phone, mail), enrollmentYear(year), GPA(gpa) {}

    void enrollCourse(string course) {
        coursesEnrolled.push_back(course);
    }

    void displayInfo() override {
        Person::displayInfo();
        cout << "Enrollment Year: " << enrollmentYear << endl;
        cout << "GPA: " << GPA << endl;
        cout << "Courses Enrolled: ";
        for (auto &c : coursesEnrolled)
            cout << c << " ";
        cout << endl;
    }
};

// Professor Class
class Professor : public Person {
private:
    string department;
    vector<string> coursesTaught;
    double salary;

public:
    Professor(string n, string i, string addr, string phone, string mail,
              string dept, double sal)
        : Person(n, i, addr, phone, mail), department(dept), salary(sal) {}

    void addCourse(string course) {
        coursesTaught.push_back(course);
    }

    void displayInfo() override {
        Person::displayInfo();
        cout << "Department: " << department << endl;
        cout << "Salary: " << salary << endl;
        cout << "Courses Taught: ";
        for (auto &c : coursesTaught)
            cout << c << " ";
        cout << endl;
    }

    string getName() { return name; }
};

// Staff Class
class Staff : public Person {
private:
    string department;
    string position;
    double salary;

public:
    Staff(string n, string i, string addr, string phone, string mail,
          string dept, string pos, double sal)
        : Person(n, i, addr, phone, mail),
          department(dept), position(pos), salary(sal) {}

    void displayInfo() override {
        Person::displayInfo();
        cout << "Department: " << department << endl;
        cout << "Position: " << position << endl;
        cout << "Salary: " << salary << endl;
    }
};

// Course Class
class Course {
private:
    string courseId, courseName, schedule;
    int credits;
    Professor* instructor;
    vector<Student*> students;

public:
    Course(string id, string name, int cred, string sched, Professor* prof)
        : courseId(id), courseName(name), credits(cred),
          schedule(sched), instructor(prof) {}

    void registerStudent(Student* s) {
        students.push_back(s);
        s->enrollCourse(courseName);
    }

    void calculateGrades() {
        cout << "\nGrades calculated for course: " << courseName << endl;
        for (auto s : students) {
            cout << s->getName() << " -> Grade: A (Sample)\n";
        }
    }

    void displayCourse() {
        cout << "\n--- Course Info ---\n";
        cout << "Course ID: " << courseId << endl;
        cout << "Course Name: " << courseName << endl;
        cout << "Credits: " << credits << endl;
        cout << "Schedule: " << schedule << endl;
        cout << "Instructor: " << instructor->getName() << endl;

        cout << "Enrolled Students: ";
        for (auto s : students)
            cout << s->getName() << " ";
        cout << endl;
    }
};

int main() {
    // Create Professor
    Professor prof("Dr. Ahmed", "P101", "Karachi", "123456789", "ahmed@uni.edu",
                   "Computer Science", 120000);
    prof.addCourse("OOP");

    // Create Students
    Student s1("Ali", "S001", "Karachi", "987654321", "ali@uni.edu", 2023, 3.5);
    Student s2("Sara", "S002", "Lahore", "111222333", "sara@uni.edu", 2022, 3.8);

    // Create Staff
    Staff staff("John", "ST01", "Islamabad", "555666777", "john@uni.edu",
                "Admin", "Clerk", 50000);

    // Create Course
    Course oop("CS101", "OOP", 3, "Mon-Wed 10AM", &prof);

    // Register Students
    oop.registerStudent(&s1);
    oop.registerStudent(&s2);

    // Display Info
    prof.displayInfo();
    s1.displayInfo();
    s2.displayInfo();
    staff.displayInfo();

    oop.displayCourse();
    oop.calculateGrades();

    return 0;
}
