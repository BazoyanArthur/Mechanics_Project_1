#include <iostream>
#include "car.h"
#include "intersection.h"
#include <iomanip>
#include <fstream>

int main()
{
	double time = 0.0;
	std::ofstream myFile;
	myFile.open("Data.txt");

	car car_1(40, 60, 50, 1, 1, 100);
	car car_2(60, 80, 80, 3, 3, 20);
	intersection crossroad_1(4, 10);

	std::cout << "Initial Speed: " << car_1.get_init_speed() << std::endl;
	std::cout << "Max Speed: " << car_1.get_max_speed() << std::endl;
	std::cout << "Distance till Intersection: " << car_1.get_curr_dist_intersect() << std::endl;
	std::cout << "Positive Acceleration: " << car_1.get_pos_accel() << std::endl;
	std::cout << "Negative Acceleration: " << car_1.get_neg_accel() << std::endl;
	std::cout << "Current Speed: " << car_1.get_curr_speed() << std::endl;

	std::cout << "Yellow light timer: " << crossroad_1.get_y_dur() << std::endl;
	std::cout << "Intersection Width: " << crossroad_1.get_width() << std::endl;

	std::cout << "Suggestion is: " << car_1.get_suggestion(car_1.get_curr_dist_intersect() + crossroad_1.get_width(), crossroad_1.get_y_dur() - time) << std::endl;


	while (time <= crossroad_1.get_y_dur() && car_1.get_curr_dist_intersect() + crossroad_1.get_width() - car_1.get_passed_dist() > 0 && car_1.get_curr_speed() > 0 /*&& car_2.get_dist_to_car() > 0*/)
	{
		car_1.accelerate(time);
		car_2.get_suggestion(car_2.get_curr_dist_intersect() + crossroad_1.get_width(), crossroad_1.get_y_dur() - time, car_1);
		car_2.accelerate(time, car_2);
		std::cout << "Distance car1: " << car_1.get_curr_dist_intersect() + crossroad_1.get_width() - car_1.get_passed_dist() << "\t" << "Speed car1: " << car_1.get_curr_speed() << "\t" << "Time: " << time << std::endl;
		std::cout << "Distance car2: " << car_2.get_curr_dist_intersect() + crossroad_1.get_width() - car_2.get_passed_dist() << "\t" << "Speed car2: " << car_2.get_curr_speed() << "\t" << "Time: " << time << std::endl;
		//std::cout << "Distance between cars: " << car_2.get_dist_to_car() << std::endl;
		myFile << car_1.get_passed_dist()<< std::setprecision(4) << "\t\t"  << time << "\t\t" << car_1.get_curr_speed() << "\t\t" << std::endl;
		time = time + 0.001;
	}

	// couldn't figure out the 2nd part. The idea was to keep track of the distance between two cars and depending on the decisions of the car in front choose to hit brakes or keep going. Maybe eventually crash

	

	return 0;
};