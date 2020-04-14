#pragma once
#include "Mass.h"
#include "cstdlib"

class System
{
	enum DIRECTION
	{
		unknown = -2,
		left = -1,
		none = 0,
		right = 1
	};

public:

	System(Mass m1, Mass m2, Mass m3, double my1, double my2, double my3, double f ) :
	M1(m1), M2(m2), M3(m3),
	myu1(my1), myu2(my2), myu3(my3),
	force(f), direction(unknown),
	g(10)
	{
		if (!((myu1 > 0 && myu1 <= 0.5) && (myu2 > 0 && myu2 <= 0.5) && (myu3 > 0 && myu3 <= 0.5)))
			throw("Myu is out of bounds! - at System::System()");

		if (!(force >= -300 && force <= 300))
			throw("Force is out of bounds! - at System::System()");

		if (force > 0)
			direction = right;
		else if (force == 0)
			direction = none;
		else if (force < 0)
			direction = left;
	}

	double get_m1_accel()
	{
		// if no force is pushin M1 then it has no acceleration
		if (direction == 0)
			return 0;

		// if the direction is to the right then 
		double M1_friction_ground = ((M1.get_mass() * g) + (M2.get_mass() * g)) * myu1;
		double M1_friction_M2 = (M2.get_mass() * g * myu2);
		double abs_force = force;
		//getting the absolute value of force
		if (force < 0)
			abs_force = (-1 * force);
		// if the force isn't enough to move M1 due to its friction
		if (abs_force < M1_friction_ground + M1_friction_M2)
			return 0;

		
		double accel_m1 = (abs_force - M1_friction_ground - M1_friction_M2) / M1.get_mass();
		
		if(direction == left)
			return -accel_m1;
		
		return accel_m1;
	}

	double get_m23_accel()
	{
		double f_friction = M2.get_mass() * g * myu2;

		// the force pushing M2 in the direction of F applied
		double f_pushing_m2 = f_friction;

		if (direction == 0)
			f_pushing_m2 = 0;
		
		//if the direction of movement is to the right then f_pushing is positive else it is negative
		if (direction == left)
			f_pushing_m2 = (-1 * f_pushing_m2);
		
		double N3 = M1.get_accel() * M3.get_mass();
		 
		double accel_m2 = ((M3.get_mass() * g) - (N3 * myu3) - f_pushing_m2 + f_friction) / (M2.get_mass() + M3.get_mass());

		if (accel_m2 <= 0)
			return 0;

		return accel_m2;
	}

	void PUSH( )
	{
		// case where f is const
		M1.set_accel(get_m1_accel());
		M2.set_accel(get_m23_accel());
		M3.set_accel(get_m23_accel());

		double t = 0.0;
		double delta_t = 0.1;

		while (t < 10)
		{
			// changing the velocity and finding the distance passed during delta_t

			double dx_m1 = ((M1.get_vel() * delta_t) + M1.get_accel() * ((delta_t * delta_t) / 2));
			double dv_m1 = M1.get_accel() * delta_t;
			M1.set_vel(M1.get_vel() + dv_m1);


			double dx_m2 = ((M2.get_vel() * delta_t) + M2.get_accel() * ((delta_t * delta_t) / 2));
			double dv_m2 = M2.get_accel() * delta_t;
			M2.set_vel(M2.get_vel() + dv_m2);

			double dy_m3 = dx_m2;
			double dv_m3 = dv_m2;
			M3.set_vel(M3.get_vel() + dv_m3);

			// applying the changes

			M1.set_x_cor(M1.get_x_cor() + dx_m1);	//changing x-coordinate of M1
			M3.set_x_cor(M1.get_x_cor());			//M3 has the same x-coordinate as M1

			// if M2 is moving right it means M3 is falling down
			if (M2.get_accel() > 0)
				dy_m3 = -dy_m3;

			// updating M2 and M3 coordinates when they didn't hit the pulley yet
			if (M2.get_x_cor() + dx_m2 + dx_m1 < M1.get_x_cor() && M3.get_y_cor() + dy_m3 < M1.get_y_cor())
			{
				M2.set_x_cor(M2.get_x_cor() + dx_m2 + dx_m1);
				M3.set_y_cor(M3.get_y_cor() + dy_m3);
			}
			else
			{
				M2.set_x_cor(M1.get_x_cor());
			}

			M3.set_x_cor(M1.get_x_cor());

			std::cout << "M1_x: " << M1.get_x_cor() << "\t" << "M1_y: " << M1.get_y_cor() << "\t" << "M2_x: " << M2.get_x_cor() << "\t" << "M2_y: " << M2.get_y_cor() << "\t" << "M3_x: " << M3.get_x_cor() << "\t" << "M3_y: " << M3.get_y_cor() << std::endl;

			t += delta_t;
		}
	}


private:
	Mass M1, M2, M3;
	double myu1, myu2, myu3;
	double force;
	int g;
	DIRECTION direction;
};
