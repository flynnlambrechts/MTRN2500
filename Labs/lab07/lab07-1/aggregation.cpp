#include <iostream>
#include <string>
#include <vector>

class Passenger {
public:
    Passenger(std::string const& name) : mName{name} {}

    friend bool operator==(Passenger const& p1, Passenger const& p2) {
        if (p1.mName != p2.mName) {
            return false;
        } else {
            return true;
        }
    }

    friend std::ostream& operator<<(std::ostream& os, Passenger const& p) {
        os << p.mName;
        return os;
    }
private:
    std::string mName {};
};

class Train {
public:
    Train() {}
    Train(std::vector<Passenger> const& passengers) : mPassengers{passengers} {}
    
    void embark(std::vector<Passenger> const& passengers) {
        for (auto &p : passengers) {
            mPassengers.push_back(p);
        }
    }

    void disembark(std::vector<Passenger> const& passengers) {
        for (auto &p : passengers) {
            std::remove(mPassengers.begin(), mPassengers.end(), p);
        }
    }

    friend std::ostream& operator<<(std::ostream& os, Train const& t) {
        for (auto &passenger : t.mPassengers) {
            os << passenger << ", ";
        }
        return os;
    }
private:
    std::vector<Passenger> mPassengers;
};

int main() {
    Passenger p1("Peter");
    Passenger p2("Peter");
    std::cout << (p1 == p2) << std::endl; // True.

    Passenger p("Peter");
    std::cout << p;

    Train t1;

    Passenger p3("Abe");
    Passenger p4("Mel");
    Train t2({p3, p4});
    std::cout << "T2:\n" << t2 << std::endl;

    Passenger p5("Mik");
    std::cout << "Embarking Mik\n";
    t1.embark({p5});

    Passenger p6("Lin");
    std::cout << "Embarking Lin\n";
    t1.embark({p6});
    t1.disembark({p6});\

    std::cout << t1 << std::endl;
    std::cout << t2 << std::endl;

    return 0;
}