#include <iostream>
#include <random>
#include <fstream>
#include "Timer.h"
#include "Gamrnd.h"
#include "Mvnrnd.h"

#include <Eigen/Cholesky>
#include <Eigen/Dense>

using Eigen::MatrixXd;
using Eigen::VectorXd;

using namespace std;

int main() {
	Timer timer1;
	default_random_engine generator;

	// Time gamrnd
	{
		// generation from different generator		
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
		normal_distribution<double> nd(0,1);
		MatrixXd covMat(2,2);
		covMat << 1, 0, 0, 1;
		cout << covMat << endl;
		VectorXd mu(2);
		mu << 1, 3;
		VectorXd x(2);
		for (int d = 0; d < x.size(); d++) {
			x[d] = nd(generator);
		}
		MatrixXd L = covMat.llt().matrixL(); // From Cholesky decomposition
		cout << "L is :" << endl;
		cout << L << endl;
		x = mu + L*x;
		cout << "Sample is:" << endl;
		cout << x << endl;
	}

	//Time it
	{
		normal_distribution<double> nd_base(0, 1);
		MatrixXd covMat(3, 3);
		covMat << 1, 0.3, 0.2, 0.3, 1, 0.3, 0.2, 0.3, 1;
		VectorXd mu(3);
		mu << 1, 3, 0.8;
		int iter = 10000;

		timer1.start();
		for (int i = 0; i < iter; i++) {
			VectorXd x(3);
			for (int d = 0; d < x.size(); d++) {
				x[d] = nd_base(generator);
			}
			MatrixXd L = covMat.llt().matrixL(); // From Cholesky decomposition
			x = mu + L*x;
		}
		timer1.stop(iter);
	}

	//Time it
	{
		normal_distribution<double> nd_base(0, 1);
		MatrixXd covMat(3, 3);
		covMat << 1, 0.3, 0.2, 0.3, 1, 0.3, 0.2, 0.3, 1;
		VectorXd mu(3);
		mu << 1, 3, 0.8;
		int iter = 100;

		timer1.start();
		for (int i = 0; i < iter; i++) {
			Mvnrnd::get(mu, covMat);
		}
		timer1.stop(iter);
	}
}