#pragma once


class intersection
{
public:
	intersection(int y_dur, int wid)
	{
		max_wid = 20;
		min_wid = 5;

		max_y_dur = 5;
		min_y_dur = 2;

		set_y_dur(y_dur);
		set_width(wid);
	};
	
	///////////////
	int get_y_dur()
	{
		return yellow_duration;
	}

	int get_width()
	{
		return width;
	}

	////////////////

	void set_y_dur(int y_dur)
	{
		if (y_dur > max_y_dur || y_dur < min_y_dur)
			throw("Yellow Light duration out of limits! Error at: intersection::set_y_dur");
		yellow_duration = y_dur;
	}

	void set_width(int wid)
	{
		if (wid > max_wid || wid < min_wid)
			throw("Width of Intersection out of limits! Error at: intesection::set_width");
		width = wid;
	}

private:
	int yellow_duration;
	int max_y_dur;
	int min_y_dur;

	int width;
	int min_wid;
	int max_wid;
};