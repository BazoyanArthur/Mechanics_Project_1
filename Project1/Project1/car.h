#pragma once

class car
{


public:

	car(double speed, double max_speed, double dist, double p_accel, double n_accel, double car_dist)
	{
		max_dist_to_car = 100;
		min_dist_to_car = 10;

		max_init_speed_limit = 80;
		min_init_speed_limit = 20;

		max_speed_limit = 100;
		min_speed_limit = 50;

		max_dist_limit = 150;
		min_dist_limit = 10;

		max_p_accel_limit = 3;
		min_p_accel_limit = 1;

		max_n_accel_limit = 3;
		min_n_accel_limit = 1;


		set_max_speed(max_speed);
		set_init_speed(speed);
		set_curr_speed(speed);
		set_curr_dist_intersect(dist);
		set_pos_accel(p_accel);
		set_neg_accel(n_accel);
		set_dist_car(car_dist);

		suggestion = false;
		passed_dist = 0;
		acceleration = false;

	};

	// get the initial speed
	double get_init_speed() const
	{
		return init_speed;
	};

	//get the initial distance to the intersection
	double get_curr_dist_intersect() const
	{
		return curr_dist_intersect;
	};

	//get the positive acceleration
	double get_pos_accel() const
	{
		return pos_accel;
	};

	// get the negative acceleration
	double get_neg_accel() const
	{
		return neg_accel;
	};

	double get_curr_speed() const
	{
		return curr_speed * 3600 / 1000;
	};

	double get_max_speed() const
	{
		return max_speed;
	};

	double get_passed_dist() const
	{
		return passed_dist;
	}

	double get_dist_to_car() const
	{
		return dist_to_fcar;
	}

	//////////////////////////////////////
	// set the initial speed, converts km/h to m/s
	void set_init_speed(double speed)
	{
		if (speed > max_init_speed_limit || speed < min_init_speed_limit)
			throw("Speed outside limits! Error at: car::set_init_speed");
		init_speed = speed * 1000 / 3600;
	};

	//set the initial distance to the intersection
	void set_curr_dist_intersect(double dist)
	{
		if (dist > max_dist_limit || dist < min_dist_limit)
			throw("Distance to Intersection outside the limits! Error at: car::set_curr_dist_intersect");
		curr_dist_intersect = dist;
	};


	// converts km/h to m/s
	void set_curr_speed(double speed)
	{
		curr_speed = speed * 1000 / 3600;
	};

	void accelerate( double time)
	{
		double accel = 0.0;
		if (suggestion == true)
		{
			acceleration = true;
			accel = pos_accel;
		}
		else
		{
			acceleration = false;
			accel = -neg_accel;
		}

		double d_vel = curr_speed + accel * time;

		if (d_vel > max_speed)
		{
			passed_dist = passed_dist + (max_speed * time) + ((pos_accel * (time * time)) / 2);
			return;
		}
		if (d_vel <= 0)
		{
			curr_speed = 0;
			return;
		}

		curr_speed = d_vel;
		passed_dist = passed_dist + (curr_speed * time) + ((pos_accel * (time * time)) / 2);
	};

	void accelerate(double time, car front_car)
	{
		double accel = 0.0;
		if (suggestion == true)
		{
			acceleration = true;
			accel = pos_accel;
		}
		else
		{
			acceleration = false;
			accel = -neg_accel;
		}

		double d_vel = curr_speed + accel * time;

		if (d_vel > max_speed)
		{
			passed_dist = passed_dist + (max_speed * time) + ((pos_accel * (time * time)) / 2);
			return;
		}
		if (d_vel <= 0)
		{
			curr_speed = 0;
			return;
		}

		curr_speed = d_vel;
		passed_dist = passed_dist + (curr_speed * time) + ((pos_accel * (time * time)) / 2);

		double front_car_accel = 0.0;

		if (front_car.get_accel_status())
			front_car_accel = front_car.get_pos_accel();
		else
			front_car_accel = -front_car.get_neg_accel();

		double possible_dist_fcar = (front_car.get_curr_speed() * time) + ((front_car_accel * (time * time)) / 2);
		double possible_dist = (curr_speed * time) + ((pos_accel * (time * time)) / 2);

		if (possible_dist > possible_dist_fcar)
			dist_to_fcar = possible_dist - possible_dist_fcar;
		else
			dist_to_fcar = possible_dist_fcar - possible_dist;

	};

	bool get_suggestion(double distance, double time_left, car front_car)
	{
		double possible_dist = (curr_speed * time_left) + ((pos_accel * (time_left * time_left)) / 2);

		double front_car_accel = 0.0;

		if (front_car.get_accel_status())
			front_car_accel = front_car.get_pos_accel();
		else
			front_car_accel = -front_car.get_neg_accel();

		double possible_dist_fcar = (front_car.get_curr_speed() * time_left) + ((front_car_accel * (time_left * time_left)) / 2);

		if (possible_dist > possible_dist_fcar)
		{
			if (possible_dist - possible_dist_fcar < dist_to_fcar)
			{
				suggestion = false;
				return false;
			}
		}
		else
		{
			if (possible_dist_fcar - possible_dist < dist_to_fcar)
			{
				suggestion = false;
				return false;
			}
		}

		if (possible_dist < distance - passed_dist)
		{
			suggestion = false;
			return false;
		}

		suggestion = true;
		return true;
	};

	bool get_suggestion(double distance, double time_left )
	{
		double possible_dist = (curr_speed * time_left) + ((pos_accel * (time_left * time_left)) / 2);
		if (possible_dist < distance - passed_dist)
		{
			suggestion = false;
			return false;
		}
		
		suggestion = true;
		return true;
	}

	void set_dist_car(double dist)
	{
		if (dist > max_dist_to_car || dist < min_dist_to_car)
			throw("Distance to a car is out of limits! Error at: car::set_dist_car");
		dist_to_fcar = dist;
	}

	bool get_accel_status()
	{
		return acceleration;
	}


private:

	//converts km/h to m/s
	void set_max_speed(double speed)
	{
		if (speed > max_speed_limit || speed < min_speed_limit)
			throw("Speed outside of limits! Error at: car::set_max_speed");
		max_speed = speed * 1000 / 3600;
	};

	//set the positive acceleration
	void set_pos_accel(double p_accel)
	{
		if (p_accel > max_p_accel_limit || p_accel < min_p_accel_limit)
			throw("Positive acceleration is outside the limits! Error at: car::set_pos_accel");
		pos_accel = p_accel;
	};

	// set the negative acceleration
	void set_neg_accel(double n_accel)
	{
		if (n_accel > max_n_accel_limit || n_accel < min_n_accel_limit)
			throw("Negative acceleration is outside the limits! Error at: car::set_neg_accel");
		neg_accel = n_accel;
	};

	double curr_speed;				// current speed of the car
	double passed_dist;				// passed distance

	double max_speed;
	double max_speed_limit;
	double min_speed_limit;


	double init_speed;				// initial speed
	double max_init_speed_limit;
	double min_init_speed_limit;

	double curr_dist_intersect;	// current distance to the intersection
	double max_dist_limit;
	double min_dist_limit;

	double pos_accel;				// positive acceleration
	double max_p_accel_limit;
	double min_p_accel_limit;

	double neg_accel;				// negative acceleration
	double max_n_accel_limit;
	double min_n_accel_limit;

	double dist_to_fcar;	// distance to the car in front
	double max_dist_to_car;
	double min_dist_to_car;

	bool suggestion;	// false if cannot make it to the other side
	bool acceleration;	// shows if the car is accelerating or braking
};

