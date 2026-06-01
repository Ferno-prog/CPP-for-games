#include <iostream>

int main()
{
    double d = 42.99;
    float f = static_cast<float>(d);
    int i = static_cast<int>(f);
    char c = static_cast<char>(i);
    bool b = static_cast<bool>(c);

    std::cout << d << '\n'
        << f << '\n'
        << i << '\n'
        << c << '\n'
        << b << '\n';

    return 0;
}