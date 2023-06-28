int main() { 
    const int a{42}; 
    const int b{a}; 
    double c{21.2}; 
    
    for (int i{0}; i < 10; i++) { 
        const double d{a * b};         
        c *= d;     
    } 
    return 0; 
}