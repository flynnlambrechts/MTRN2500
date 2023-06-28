// ADD YOUR INCLUDES HERE.
#include <iostream>

// WRITE YOUR SOLUTION IN THIS FUNCTION.
void catch_exceptions() {
    try {
        throw_alot_of_exceptions();
    } catch (std::runtime_error) {
        std::cout << "Caught std::runtime_error!\n";
    } catch (std:invalid_argument) {
        std::cout << "Caught std::invalid_argument!\n";
    } catch (std::out_of_range) {
        std::cout << "Caught std::out_of_range!\n";
    } catch (std::length_error) {
        std::cout << "Caught std::length_error!\n";
    } catch (std::logic_error) {
        std::cout << "Caught std::logic_error!\n";
    }
}