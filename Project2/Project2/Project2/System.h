#pragma once
#include "Mass.h"

class System
{
public:

	System(Mass m1, Mass m2, Mass m3, double my1, double my2, double my3, double f ) :
	M1(m1), M2(m2), M3(m3),
	myu1(my1), myu2(my2), myu3(my3),
	force(f),
	g(10)
	{
		if (!((myu1 > 0 && myu1 <= 0.5) && (myu2 > 0 && myu2 <= 0.5) && (myu3 > 0 && myu3 <= 0.5)))
			throw("Myu is out of bounds! - at System::System()");

		if (!(force >= -300 && force <= 300))
			throw("Force is out of bounds! - at System::System()");

		if (force > 0)
			direction = true;
		else
			direction = false;
	}

	double get_m1_accel()
	{
		double accel_m1 = (force - ((M1.get_mass() * g) + (M2.get_mass() * g)) * myu1 - (M2.get_mass() * g * myu2)) / M1.get_mass();
		if (accel_m1 < 0)
			return 0;
		return accel_m1;
	}

	double get_m23_accel()
	{
		double f_pushing_m2 = M2.get_mass() * g * myu2;

		double f_friction = f_pushing_m2;

		if (direction == true)
		{
			f_friction = -f_friction;
		}
		
		double N3 = M1.get_accel() * M3.get_mass();
		 
		double accel_m2 = ((M3.get_mass() * g) - (N3 * myu3) - f_pushing_m2 + f_friction) / (M2.get_mass() + M3.get_mass());

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
			double dx_m1 = ((M1.get_vel() * delta_t) + M1.get_accel() * ((delta_t * delta_t) / 2));
			double dv_m1 = M1.get_accel() * delta_t;
			M1.set_vel(M1.get_vel() + dv_m1);


			double dx_m2 = ((M2.get_vel() * delta_t) + M2.get_accel() * ((delta_t * delta_t) / 2));
			double dv_m2 = M2.get_accel() * delta_t;
			M2.set_vel(M2.get_vel() + dv_m2);

			double dy_m3 = dx_m2;
			double dv_m3 = dv_m2;
			M3.set_vel(M3.get_vel() + dv_m3);

			M1.set_x_cor(M1.get_x_cor() + dx_m1);
			M3.set_x_cor(M1.get_x_cor());

			M2.set_x_cor(M2.get_x_cor() + dx_m2);
			if (M2.get_x_cor() < M1.get_x_cor() - 10)
				M2.set_x_cor(M1.get_x_cor() - 10);	// canot fall
			else if (M2.get_x_cor() > M1.get_x_cor())
				M2.set_x_cor(M1.get_x_cor());	// cannot go through pulley

			M3.set_y_cor(M3.get_y_cor() + dy_m3);
			if (M3.get_y_cor() < 3)
				M3.set_y_cor(3);	// hit M1
			else if (M3.get_y_cor() > 10)
				M3.set_y_cor(10);	// cannot go through pulley


			std::cout << "M1_x: " << M1.get_x_cor() << "\t" << "M1_y: " << M1.get_y_cor() << "\t" << "M2_x: " << M2.get_x_cor() << "\t" << "M2_y: " << M2.get_y_cor() << "\t" << "M3_x: " << M3.get_x_cor() << "\t" << "M3_y: " << M3.get_y_cor() << std::endl;

			t += delta_t;
		}

	}


private:
	Mass M1, M2, M3;
	double myu1, myu2, myu3;
	double force;
	int g;
	bool direction; // false = left, true = right
};
