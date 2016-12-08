#include "Gamrnd.h"

Gamrnd* Gamrnd::_global_instance = NULL;

Gamrnd::Gamrnd()
{
}

Gamrnd::~Gamrnd()
{
}

double Gamrnd::_get(double alpha, double beta)
{
	param._Alpha = alpha;
	param._Beta = beta;
	gd.param(param);
	return gd(generator);
}

double Gamrnd::get(double alpha, double beta)
{
	if (!_global_instance) {
		_global_instance = new Gamrnd();
	}
	return _global_instance->_get(alpha, beta);
}
