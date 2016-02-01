// StringFormat.tcc

#include <iostream>
using std::fixed;
using std::scientific;
using std::defaultfloat;

#include <iomanip>
using std::setprecision;

namespace utilities
{
    //template<typename ... Args>
    //string StringFormat(const char* input, Args ...args)
    //{
    //    // allocate buffer of correct size
    //    auto size = snprintf(nullptr, 0, input, args ...);
    //    auto buf = new char[size + 1];      // leave room for trailing \0
    //    
    //    // format
    //    snprintf(buf, size + 1, input, args ...);
    //    
    //    // cast back to stl::string
    //    auto result = string(buf, buf + size);

    //    // cleanup and return
    //    delete[] buf;
    //    return result;
    //}

    //template<typename ... Args>
    //string StringFormat(const string& input, Args ...args)
    //{
    //    // get c-string
    //    const char* cstr = input.c_str();

    //    return StringFormat(cstr, args ...);
    //}

    template<typename ArgType, typename ... ArgTypes>
    void StringFormat(ostream& os, const char* cstr, ArgType arg, ArgTypes ...args)
    {
        int n=0;
        const char* ptr = cstr;
        while(*ptr != '%' && *ptr != '\0')
        {
            ++n;
            ++ptr;
        }

        os.write(cstr, n);

        // if reached end of string, exit
        if(*ptr == '\0')
        {
            return;
        }

        // if reached '%' character, print an arg
        char specifier = *(++ptr);
        auto prec = os.precision();

        switch(specifier)
        {
        case 'i':
            os << fixed << setprecision(0) << arg << setprecision(prec);
            break;

        case 'f':
            os << fixed << arg;
            break;

        case 'e':
            os << scientific << arg;
            break;

        case 's':
            os << defaultfloat << arg;
            break;

        case '%':
            os << '%';
            break;
        }

        // if end of string reached, exit
        ++ptr;
        if(*ptr == '\0')
        {
            return;
        }

        StringFormat(os, ptr, args...);
    }

    template<typename ... ArgTypes>
    void StringFormat(ostream& os, const char* cstr, ArgTypes ...args)
    {
        os << cstr;
    }


}