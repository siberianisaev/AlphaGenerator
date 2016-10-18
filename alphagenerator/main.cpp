//
//  main.cpp
//  alphagenerator
//
//  Created by Andrey Isaev on 18.10.16.
//  Copyright © 2016 JINR. All rights reserved.
//

#include <iostream>
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
    const int n = 10000;  // число событий
    double radius = 30.0; // радиус источника (мм)
    double mean = 8700.0; // энергия пика (кэВ)
    double stddev = 100.0; // стандартное отклонение для энергии
    
    // Нормальное распределение в C++11 http://www.cplusplus.com/reference/random/normal_distribution/
    // Альтернатива из Boost библиотеки http://www.boost.org/doc/libs/1_42_0/libs/math/doc/sf_and_dist/html/math_toolkit/dist/dist_ref/dists/normal_dist.html
    std::default_random_engine generator;
    std::normal_distribution<double> distribution(mean, stddev);
    
    for (int i = 0; i < n; ++i) {
        Point point = random_point(radius);
        Angles angles = random_angles();
        double number = distribution(generator);
        std::cout << point.x << "\t" << point.y << "\t" << angles.theta << "\t" << angles.phi << "\t" << number << std::endl;
    }
    
    return 0;
}
