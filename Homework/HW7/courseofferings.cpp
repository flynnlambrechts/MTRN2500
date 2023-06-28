#include <iostream>
#include <string>
#include <set>
#include <map>

class Person;

class Course;

class Student;

class CourseOffering;


class Person {
public:
    Person(std::string name) : mName{name} {}
    std::string getName() const {return mName;}
protected:
    std::string mName;
};

class Course {
public:
    Course(std::string code) : mCode(code) {}
    std::string getCode() const {return mCode;}
protected:
    std::string mCode;
};



// ______________________________________________________



class Student : public Person{
public:
    Student(std::string, std::string);
    std::string getZID() const;
    std::set<CourseOffering> getCourses() const;
    bool addCourseOffering(CourseOffering&);
    bool removeCourseOffering(CourseOffering&);

    friend bool operator<(Student const& lhs, Student const& rhs) {
        return lhs.getZID() < rhs.getZID();
    }

    friend bool operator==(Student const& lhs, Student const& rhs) {
        return lhs.getZID() == rhs.getZID();
    }

private:
    std::set<CourseOffering> mCourses;
    std::string mZID;
};

class CourseOffering : public Course{
public:
    CourseOffering(std::string, std::string);
    std::string getTerm() const;
    std::set<Student> getStudents() const;
    bool addStudent(Student&);
    bool removeStudent(Student&);

    friend bool operator<(CourseOffering const& lhs, CourseOffering const& rhs) {
        return lhs.getCode() == rhs.getCode() ? lhs.getTerm() < rhs.getTerm()
                                              : lhs.getCode() < rhs.getCode();
    }

    friend bool operator==(CourseOffering const& lhs, CourseOffering const& rhs) {
        return lhs.getCode() == rhs.getCode() && lhs.getTerm() == rhs.getTerm();
    }

private:
    std::set<Student> mStudents;
    std::string mTerm;
};

// IMPLEMENT THIS FUNCTION.
CourseOffering::CourseOffering(std::string code, std::string term) 
    : Course(code), mTerm{term} {}

// IMPLEMENT THIS FUNCTION.
std::string CourseOffering::getTerm() const {return mTerm;}

// IMPLEMENT THIS FUNCTION.
std::set<CourseOffering> Student::getCourses() const { return mCourses; }

// IMPLEMENT THIS FUNCTION.
std::set<Student> CourseOffering::getStudents() const { return mStudents; }

// IMPLEMENT THIS FUNCTION.
bool CourseOffering::addStudent(Student& student) {
    bool success = mStudents.insert(student).second;

    if (success) {
        student.addCourseOffering(*this);
        return true;
    } else {
        return false;
    }

}



// IMPLEMENT THIS FUNCTION.
bool CourseOffering::removeStudent(Student& student) {
    int success = mStudents.erase(student);
    if (success == 0) {
        return false;
    } else {
        student.removeCourseOffering(*this);
        return true;
    }
}



// IMPLEMENT THIS FUNCTION.
Student::Student(std::string name, std::string zID)
    : Person(name), mZID{zID} {}

// IMPLEMENT THIS FUNCTION.
std::string Student::getZID() const {return mZID;}

// IMPLEMENT THIS FUNCTION.
bool Student::addCourseOffering(CourseOffering& courseOffering) {
    bool success = mCourses.insert(courseOffering).second;

    if (success) {
        courseOffering.addStudent(*this);
        return true;
    } else {
        return false;
    }
}

// IMPLEMENT THIS FUNCTION.
bool Student::removeCourseOffering(CourseOffering& courseOffering) {
    int success = mCourses.erase(courseOffering);
    if (success == 0) {
        return false;
    } else {
        courseOffering.removeStudent(*this);
        return true;
    }
}

void print_students(std::set<Student> students) {
    std::cout << "\tThere are " << static_cast<int>(students.size()) << " students: ";
    for (std::set<Student>::iterator iter = students.begin(); iter != students.end(); iter++) {
        std::cout << iter->getName() << "  ";
    }
    std::cout << std::endl;
}

void print_courses(std::set<CourseOffering> courses) {
    std::cout << "\tThere are " << static_cast<int>(courses.size()) << " courses: ";
    for (std::set<CourseOffering>::iterator iter = courses.begin(); iter != courses.end(); iter++) {
        std::cout << iter->getCode() << "  ";
    }
    std::cout << std::endl;
}


void test_case_last() {
    // Adding multiple course offerings to student then removing.
    CourseOffering mtrn2500("MTRN2500", "22T3");
    CourseOffering mtrn3500("MTRN3500", "22T3");
    CourseOffering mtrn3100("MTRN3100", "22T3");
    Student jo("Jo", "z123");
    Student mike("Mike", "1");

    std::cout << (mtrn2500.addStudent(jo) == true);
    print_students(mtrn2500.getStudents());
    std::cout << (mtrn3500.addStudent(jo) == true);
    print_students(mtrn3500.getStudents());
    std::cout << (mtrn3100.addStudent(jo) == true);
    print_students(mtrn3100.getStudents());

    std::cout << (mtrn2500.getStudents() == std::set<Student>({jo}));
    std::cout << (mtrn3500.getStudents() == std::set<Student>({jo}));
    std::cout << (mtrn3100.getStudents() == std::set<Student>({jo}));
    std::cout << std::endl;

    std::cout << (jo.getCourses() == std::set<CourseOffering>({mtrn2500, mtrn3500, mtrn3100}));
    print_courses(jo.getCourses());


    std::cout << (jo.removeCourseOffering(mtrn2500) == true);
    std::cout << (mtrn2500.getStudents() == std::set<Student>());
    std::cout << (mtrn3500.getStudents() == std::set<Student>({jo}));
    std::cout << (mtrn3100.getStudents() == std::set<Student>({jo}));
    std::cout << (jo.getCourses() == std::set<CourseOffering>({mtrn3500, mtrn3100}));
    std::cout << (jo.removeCourseOffering(mtrn3100) == true);
    std::cout << (mtrn2500.getStudents() == std::set<Student>());
    std::cout << (mtrn3500.getStudents() == std::set<Student>({jo}));
    std::cout << (mtrn3100.getStudents() == std::set<Student>());
    std::cout << (jo.getCourses() == std::set<CourseOffering>({mtrn3500}));
    std::cout << (jo.removeCourseOffering(mtrn3500) == true);
    std::cout << (mtrn2500.getStudents() == std::set<Student>());
    std::cout << (mtrn3500.getStudents() == std::set<Student>());
    std::cout << (mtrn3100.getStudents() == std::set<Student>());
    std::cout << (jo.getCourses() == std::set<CourseOffering>());
}

int main() {
    test_case_last();
    std::cout << std::endl;
}