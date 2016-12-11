#include <iostream>
#include <random>
#include <fstream>
#include "Timer.h"
#include "Gamrnd.h"
#include "Mvnrnd.h"
#include "Betarnd.h"

#include <Eigen/Cholesky>
#include <Eigen/Dense>

using Eigen::MatrixXd;
using Eigen::VectorXd;

using namespace std;

int main() {
	Timer timer1;
	default_random_engine generator;
	int mainIter = 4;
	for (int t = 0; t < mainIter; t++)
	{
		cout << endl << "RUN " << t << endl;
		// Time Gamrnd class
		{
			cout << "Gamma random variable generation:" << endl;
			//ofstream gamma_ostream("outputs/gam.csv");
			double v;
			int iter = 10000;
			v = Gamrnd::get(10, 3);
			timer1.start();
			for (int i = 0; i < iter; i++)
			{
				v = Gamrnd::get(10, 3);
				//gamma_ostream << v << endl;
			}
			timer1.stop(iter);
			//gamma_ostream.close();
		}



		//Time it
		{
			cout << "Multivariate normal random variable generation:" << endl;
			//ofstream norm_ostream("outputs/mvnrnd.csv");
			MatrixXd covMat(3, 3);
			covMat << 1, 0.3, 0.2, 0.3, 1, 0.3, 0.2, 0.3, 1;
			VectorXd mu(3);
			mu << 1, 3, 0.8;
			int iter = 10000;

			VectorXd x;
			Mvnrnd::get(mu, covMat);
			timer1.start();
			for (int i = 0; i < iter; i++) {
				x = Mvnrnd::get(mu, covMat);
				//norm_ostream << x[0] << "," << x[1] << "," << x[2] << endl;
			}
			timer1.stop(iter);
			//norm_ostream.close();
		}

		//Time it
		{
			//ofstream beta_ostream("outputs/betarnd.csv");
			cout << "Beta random variable generation:" << endl;
			double v;
			int iter = 10000;
			v = Betarnd::get(400, 1);
			timer1.start();
			for (int i = 0; i < iter; i++)
			{
				v = Betarnd::get(1, 100);
				//beta_ostream << v << endl;
			}
			timer1.stop(iter);
			//beta_ostream.close();
		}
	}
	
}