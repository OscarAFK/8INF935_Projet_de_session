#include <stdio.h>
#include <iostream>
#include "Particle.h"

int main()
{
    float deltaTime = 0.01f;

    std::string input;
    Particle p1 = Particle();
    Particle p2 = Particle(0, Vector3D(1,2,3), Vector3D(1, 2, 3), Vector3D(1, 2, 3));

    std::cout << p1.to_string() << std::endl;
    std::cout << p2.to_string() << std::endl;
    
    bool run = true;
    while (run)
    {
        p2.integrate(deltaTime);
        std::cout << p2.to_string() << std::endl;
        //printf(position.to_string().c_str());*

    }
}



