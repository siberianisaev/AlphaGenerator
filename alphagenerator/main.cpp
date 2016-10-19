//
//  main.cpp
//  alphagenerator
//
//  Created by Andrey Isaev on 18.10.16.
//  Copyright © 2016 JINR. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <random>
#include <math.h>

using namespace std;

float random_from_0_to_1() {
    float r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
    return r;
}

struct Point {
    double x;
    double y;
};

// Позиция вылета частицы на поверхности круглого источника
// http://www.anderswallin.net/2009/05/uniform-random-points-in-a-circle-using-polar-coordinates/
Point random_point(double radius) {
    double r = radius * sqrt(random_from_0_to_1());
    double a = 2 * M_PI * random_from_0_to_1();
    double x = r * cos(a);
    double y = r * sin(a);
    struct Point p;
    p.x = x;
    p.y = y;
    return p;
}

struct Angles {
    double theta;
    double phi;
};

// Углы вылета частицы из источника
// http://mathworld.wolfram.com/SpherePointPicking.html
Angles random_angles() {
    double theta = 2 * M_PI * random_from_0_to_1();
    double phi = 1 / cos(2 * random_from_0_to_1() - 1);
    struct Angles a;
    a.theta = theta;
    a.phi = phi;
    return a;
}

int main(int argc, const char * argv[]) {
    // число событий
    int n = 10000;
    std::cout << "Events Count: ";
    std::cin >> n;
    
    // радиус источника (мм)
    double radius = 30.0;
    std::cout << "Source Radius: ";
    std::cin >> radius;
    
    // энергия пика (кэВ)
    double mean = 8700.0;
    std::cout << "Alpha Energy: ";
    std::cin >> mean;
    
    // стандартное отклонение для энергии
    double stddev = 100.0;
    std::cout << "Standard Deviation: ";
    std::cin >> stddev;
    
    // заряд
    int charge_min = 1;
    std::cout << "Сharge Min: ";
    std::cin >> charge_min;
    int charge_max = 20;
    std::cout << "Сharge Max: ";
    std::cin >> charge_max;
    int c1 = min(charge_min, charge_max);
    int c2 = max(charge_min, charge_max);
    charge_min = c1;
    charge_max = c2;
    
    // Нормальное распределение в C++11 http://www.cplusplus.com/reference/random/normal_distribution/
    // Альтернатива из Boost библиотеки http://www.boost.org/doc/libs/1_42_0/libs/math/doc/sf_and_dist/html/math_toolkit/dist/dist_ref/dists/normal_dist.html
    std::default_random_engine generator;
    std::normal_distribution<double> distribution(mean, stddev);
    
    std::ofstream out("result.dat",ios::out);
    std::cout << "point.x  point.y  angles.theta  angles.phi  energy  charge" << std::endl;
    
    for (int i = 0; i < n; ++i) {
        Point point = random_point(radius);
        Angles angles = random_angles();
        double energy = distribution(generator);
        int charge = rand() % (charge_max - charge_min + 1) + charge_min;
        
        std::cout << point.x << "  " << point.y << "  " << angles.theta << "  " << angles.phi << "  " << energy << "  " << charge << std::endl;
        if (out.good()) {
            out << point.x << "  " << point.y << "  " << angles.theta << "  " << angles.phi << "  " << energy << "  " << charge << std::endl;
        }
    }
    
    out.close();
    
    return 0;
}
