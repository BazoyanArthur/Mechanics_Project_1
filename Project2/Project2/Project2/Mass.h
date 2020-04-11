#pragma once

class Mass
{
public:
	Mass(double x, double y, double m) : mass(m), velocity(0), accel(0)
	{
		if (!(m > 0 && m <= 10))
			throw("Mass is out of bounds! at Mass::Mass()");

		x_cor = x;
		y_cor = y;
	}

	// Copy constructor
	Mass( const Mass &m )
	{
		x_cor = m.get_x_cor();
		y_cor = m.get_y_cor();
		mass = m.get_mass();
		velocity = m.get_vel();
		accel = m.get_accel();
	}

	// set functions start

	void set_x_cor(double x)
	{
		x_cor = x;
	}

	void set_y_cor(double y)
	{
		y_cor = y;
	}

	void set_accel(double a)
	{
		accel = a;
	}

	void set_vel(double v)
	{
		velocity = v;
	}

	// set functions end

	// get functions start

	double get_x_cor() const
	{
		return x_cor;
	}

	double get_y_cor() const
	{
		return y_cor;
	}

	double get_mass() const
	{
		return mass;
	}

	double get_accel() const
	{
		return accel;
	}

	double get_vel() const
	{
		return velocity;
	}

	// get functions end
	

private:
	double x_cor;
	double y_cor;
	double mass;
	double accel;
	double velocity;
};

