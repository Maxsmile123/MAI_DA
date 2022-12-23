#ifndef UTILS_HPP
#define UTILS_HPP
#include <string>

class KPException: public std::exception
{
    std::string error_msg;
public:
    enum errors_type
    {
        DIMENSION_ERROR
    };
    explicit KPException(errors_type error)
    {
        switch (error) {
            case DIMENSION_ERROR:error_msg = "Dimension of two point aren't equal!";
                break;
            default:error_msg = "An exception has happened.";
        }
    }
    [[nodiscard]] const char *what() const noexcept override
    {
        return error_msg.c_str();
    }

};

#endif //UTILS_HPP
