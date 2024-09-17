#include "Interpolator.h"
/*
	Uses linear interpolation (1D).
*/


Interpolator::Interpolator(double step, double currentValue) {
	this->step = step;
	this->currentStep = step;

	this->startingValue = currentValue;
	this->lerping = false;
	this->targetValue = this->startingValue;
}

void Interpolator::initializeInterpolation(double startingValue, double targetValue) {
	this->startingValue = startingValue;
	this->targetValue = targetValue;
	this->lerping = true;
	this->currentStep = this->step;
}

double Interpolator::interpolate() {
	if (this->lerping) {
		double out = this->startingValue + (this->targetValue - this->startingValue) * this->currentStep;
		this->currentStep += this->step;
		if (this->currentStep > 1) {
			this->currentStep = 1;
			this->lerping = false;
		}
		return out;
	}
	else {
		return this->targetValue;
	}
}
