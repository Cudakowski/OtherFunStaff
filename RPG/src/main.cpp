#include <iostream>

using namespace std::string_literals;

int main([[maybe_unused]] int argc,[[maybe_unused]] char const *argv[])
{
    //testing build versions
    #ifdef DEBUG_BUILD
    std::cout << "This is the debug version.\n";//if this is grayed out then see README file
    #else
    std::cout << "This is the release version.\n";
    #endif

    std::cout<<"kek\n";
    return 0;

}

