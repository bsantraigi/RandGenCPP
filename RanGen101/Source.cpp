#include <iostream>
#include <random>
#include "Timer.h"
#include "Gamrnd.h"

#include <Eigen/Cholesky>
#include <Eigen/Dense>

using Eigen::MatrixXd;
using Eigen::VectorXd;

using namespace std;

int main() {
	Timer timer1;
	
	// Time gamrnd
	{
		// generation from different generator
		default_random_engine generator;
		gamma_distribution<double> gd(10, 3);
		gamma_distribution<double>::param_type param;
		double v;
		int iter = 10000;
		timer1.start();
		for (int i = 0; i < iter; i++)
		{			
			param._Alpha = 10;
			param._Beta = 3;
			gd.param(param);
			v = gd(generator);
		}
		timer1.stop(iter);
	}
	// Time Gamrnd class
	{
		double v;
		int iter = 10000;
		timer1.start();
		for (int i = 0; i < iter; i++)
		{
			v = Gamrnd::get(10, 3);
		}
		timer1.stop(iter);

	}

	// Mvnrnd base code
	{
		MatrixXd covMat;
		VectorXd mu;
		VectorXd x;

		MatrixXd L; // From Cholesky decomposition

	}
}