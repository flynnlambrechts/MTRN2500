
class Student : public Person {
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

    void addCourseWithoutRecip(CourseOffering &course) {
        mCourses.insert(course);
    }

    void removeCourseWithoutRecip(CourseOffering &course) {
        mCourses.erase(course);
    }

private:
    std::string mZID;
    std::set<CourseOffering> mCourses;
};

class CourseOffering : public Course {
public:
    CourseOffering(std::string, std::string);
    std::string getTerm() const;
    std::set<Student> getStudents() const;
    bool addStudent(Student&);
    bool removeStudent(Student&);

    friend bool operator<(CourseOffering const& lhs, CourseOffering const& rhs) {
        return lhs.getCode() == rhs.getCode() ? lhs.getCode() < rhs.getCode()
                                              : lhs.getTerm() < rhs.getTerm();
    }

    friend bool operator==(CourseOffering const& lhs, CourseOffering const& rhs) {
        return lhs.getCode() == rhs.getCode() && lhs.getTerm() == rhs.getTerm();
    }

    void addStudentWithoutRecip(Student &student) {
        mStudents.insert(student);
    }

    void removeStudentWithoutRecip(Student &student) {
        mStudents.erase(student);
    }

private:
    std::string mTerm;
    std::set<Student> mStudents;
};

// IMPLEMENT THIS FUNCTION.
CourseOffering::CourseOffering(std::string code, std::string term)
    : Course(code), mTerm{term} {}

// IMPLEMENT THIS FUNCTION.
std::string CourseOffering::getTerm() const {return mTerm;}

// IMPLEMENT THIS FUNCTION.
std::set<Student> CourseOffering::getStudents() const {return mStudents;}

// IMPLEMENT THIS FUNCTION.
bool CourseOffering::addStudent(Student& student) {
    if (mStudents.insert(student).second) {
        student.addCourseWithoutRecip(*this);
        return true;
    }
    return false;
}

// IMPLEMENT THIS FUNCTION.
bool Student::addCourseOffering(CourseOffering& courseOffering) {
    if (mCourses.insert(courseOffering).second) {
        courseOffering.addStudentWithoutRecip(*this);
        return true;
    }
    return false;
}

// IMPLEMENT THIS FUNCTION.
bool CourseOffering::removeStudent(Student& student) {
    if (mStudents.erase(student) != 0) {
        student.removeCourseWithoutRecip(*this);
        return true;
    }
    return false;
}

// IMPLEMENT THIS FUNCTION.
bool Student::removeCourseOffering(CourseOffering& courseOffering) {
    if (mCourses.erase(courseOffering) != 0) {
        courseOffering.removeStudentWithoutRecip(*this);
        return true;
    }
    return false;
}


// IMPLEMENT THIS FUNCTION.
Student::Student(std::string name, std::string zID) 
    : Person(name), mZID{zID} {}

// IMPLEMENT THIS FUNCTION.
std::string Student::getZID() const {return mZID;}

// IMPLEMENT THIS FUNCTION.
std::set<CourseOffering> Student::getCourses() const { return mCourses; }



//

void print_courses(Student &student) {
    std::set<CourseOffering> courses = student.getCourses();

    std::cout << static_cast<int>(courses.size()) << "\t";


    for (auto &elem : courses) {
        std::cout << elem.getCode() << " ";
    }
    std::cout << std::endl;
}


void print_students(CourseOffering &course) {
    std::set<Student> students = course.getStudents();

    std::cout << "\t" <<  static_cast<int>(students.size()) << "\t";

    for (auto &elem : students) {
        std::cout << elem.getName() << " ";
    }
    std::cout << std::endl;
}

void test_case_second_last() {	
    // Adding multiple students to course offering then removing.
    CourseOffering mtrn2500("MTRN2500", "22T3");
    Student jo("Jo", "z123");
    Student to("To", "z456");
    Student mo("Mo", "z678");
    std::cout << (mtrn2500.addStudent(jo) == true);
    print_courses(jo);
    std::cout << (mtrn2500.addStudent(to) == true);
    print_courses(jo);
    std::cout << (mtrn2500.addStudent(mo) == true);
    std::cout << (mtrn2500.getStudents() == std::set<Student>({jo, to, mo}));
    print_courses(jo);
    std::cout << (jo.getCourses() == std::set<CourseOffering>({mtrn2500}));
    std::cout << (to.getCourses() == std::set<CourseOffering>({mtrn2500}));
    std::cout << (mo.getCourses() == std::set<CourseOffering>({mtrn2500}));
    std::cout << (mtrn2500.removeStudent(to) == true);
    std::cout << (mtrn2500.getStudents() == std::set<Student>({jo, mo}));
    std::cout << (jo.getCourses() == std::set<CourseOffering>({mtrn2500}));
    std::cout << (to.getCourses() == std::set<CourseOffering>());
    std::cout << (mo.getCourses() == std::set<CourseOffering>({mtrn2500}));
    std::cout << (mtrn2500.removeStudent(mo) == true);
    std::cout << (mtrn2500.getStudents() == std::set<Student>({jo}));
    std::cout << (jo.getCourses() == std::set<CourseOffering>({mtrn2500}));
    std::cout << (to.getCourses() == std::set<CourseOffering>());
    std::cout << (mo.getCourses() == std::set<CourseOffering>());
    std::cout << (mtrn2500.removeStudent(jo) == true);
    std::cout << (mtrn2500.getStudents() == std::set<Student>());
    std::cout << (jo.getCourses() == std::set<CourseOffering>());
    std::cout << (to.getCourses() == std::set<CourseOffering>());
    std::cout << (mo.getCourses() == std::set<CourseOffering>());
}


void test_case_last() {
    // Adding multiple course offerings to student then removing.
    CourseOffering mtrn2500("MTRN2500", "22T3");
    CourseOffering mtrn3500("MTRN3500", "22T3");
    CourseOffering mtrn3100("MTRN3100", "22T3");
    Student jo("Jo", "z123");

    std::cout << (mtrn2500.addStudent(jo) == true);
    std::cout << (mtrn3500.addStudent(jo) == true);
    std::cout << (mtrn3100.addStudent(jo) == true);
    std::cout << (mtrn2500.getStudents() == std::set<Student>({jo}));
    std::cout << (mtrn3500.getStudents() == std::set<Student>({jo}));
    std::cout << (mtrn3100.getStudents() == std::set<Student>({jo}));
    std::cout << (jo.getCourses() == std::set<CourseOffering>({mtrn2500, mtrn3500, mtrn3100}));
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
    // test_case_second_last();
    // std::cout << std::endl;
    test_case_last();
    std::cout << std::endl;
    
    // CourseOffering mtrn2500("MTRN2500", "22T3");
    // CourseOffering mtrn3500("MTRN3500", "22T3");
    // CourseOffering mtrn3100("MTRN3100", "22T3");
    // Student jo("Jo", "z123");
    // Student mama("Mama", "z69");

    // mtrn2500.addStudent(mama);
    // mtrn2500.addStudent(jo);
    // print_students(mtrn2500);
    // print_courses(jo);
    // print_courses(mama);

    // mtrn3500.addStudent(jo);
    // print_students(mtrn3500);
    // mtrn3500.addStudent(mama);
    // print_students(mtrn3500);
    // print_courses(jo);
    // print_courses(mama);
    // jo.removeCourseOffering(mtrn2500);
    // print_courses(jo);
    // print_students(mtrn2500);
}