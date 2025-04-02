//ronamsalem4@gmail.com
#ifndef GRAPH_ERROR_HPP
#define GRAPH_ERROR_HPP
/**
A simple exception class for signaling errors in graph operations.
This class provides basic error handling by storing a message string
library to report issues such as invalid input, logic errors, or unsupported operations.
 */
class GraphError {
private:
    const char* message;
public:
    GraphError(const char* msg) : message(msg) {}
    const char* what() const { return message; }
};

#endif 
