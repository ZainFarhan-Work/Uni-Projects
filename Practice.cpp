#include <iostream>

using namespace std;

class Car
{
    private:

    int speed;

    public:

    Car(int s);

    int getSpeed();
    
};

Car::Car(int s)
{
    speed = s;
}


int Car::getSpeed()
{
    return speed;
}


int main()
{
    Car alto(50);

    cout << "Return: " << alto.getSpeed() << endl;
}


