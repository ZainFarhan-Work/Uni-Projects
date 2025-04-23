#include <iostream>

#include "Practice.cpp"

using namespace std;

void function()
{
    static int times = 0;

    if (times == 0)
    {
        cout << "First Time!!!" << endl;
    }

    else cout << "Not First Time :(" << endl;

    times++;
    
}


int main()
{
    // Movie your_name("Your Name", "Dont Know", "Romance?", 90);
    // your_name.playMovie();

    function();
    function();
    function();

    return 0;
}