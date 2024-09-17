#ifndef INTERPOLATOR_H
#define INTERPOLATOR_H

class Interpolator
{
private:
	double step;
	double currentStep; // [0,1] <-> [start, target].
	bool lerping;
	double targetValue;
	double startingValue;
public:
	Interpolator(double step, double currentValue);
	Interpolator() = default;
	void initializeInterpolation(double startingValue, double targetValue);
	double interpolate();
};

#endif