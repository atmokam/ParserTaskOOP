#ifndef EXITSIGNALEXCEPTION_HPP
#define EXITSIGNALEXCEPTION_HPP

#include <exception>

class ExitSignalException : public std::exception {
public:
    ExitSignalException() {}
    ~ExitSignalException() = default;

    const char* what() const throw() {
        return "Exited successfully.";
    }
};

#endif