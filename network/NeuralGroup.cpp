#include <memory>
#include <cmath>
#include "NeuralGroup.h"
#include "Define.h"
#include "NetworkUtils.h"

using namespace std;

NeuralGroup::NeuralGroup(string p_id, int p_dim, int p_activationFunction)
{
  _id = p_id;
  _dim = p_dim;
  _activationFunction = p_activationFunction;
  _outConnection = -1;

  _output = VectorXd::Zero(_dim);
  _derivs = MatrixXd::Zero(_dim, _dim);
  _actionPotential = VectorXd::Zero(_dim);

  if (_activationFunction == BIAS) {
    for(int i = 0; i < p_dim; i++) {
      _output[i] = 1;
    }
  }

  _valid = false;
}


NeuralGroup::~NeuralGroup(void)
{
}

/* calculate output of group */
void NeuralGroup::fire() {
    _valid = true;
    activate();
}

void NeuralGroup::addInConnection(int p_index) {
    _inConnections.push_back(p_index);
}

void NeuralGroup::addOutConnection(int p_index) {
    _outConnection = p_index;
}

void NeuralGroup::integrate(VectorXd* p_input, MatrixXd* p_weights) {
  _actionPotential += (*p_weights) * (*p_input);
}

/* function which should calculate the output of neuron (activation function output) according to action potential */
void NeuralGroup::activate() {

  double sumExp = 0;
  for(int i = 0; i < _dim; i++) {
    sumExp += exp(_actionPotential[i]);
  }

  for(auto index = 0; index < _dim; index++) {    
    switch (_activationFunction) {
      case IDENTITY:
        _output[index] = _actionPotential(index);
        _actionPotential[index] = 0;
      break;
      case BIAS:
        _output[index] = -1;
        _actionPotential[index] = 0;
      break;
      case BINARY:
        if (_actionPotential[index] > 0) {
            _output[index] = 1;
            _actionPotential[index] = 0;
        }
        else {
            _output[index] = 0;
        }
      break;
      case SIGMOID:
        _output[index] = 1 / (1 + exp(-_actionPotential[index]));
        _actionPotential[index] = 0;
      break;
      case TANH:
        _output[index] = tanh(_actionPotential[index]);
        _actionPotential[index] = 0;
      case SOFTMAX:
        _output[index] = exp(_actionPotential[index]) / sumExp;
      break;
    }
  }
}

void NeuralGroup::calcDerivs() {
    switch (_activationFunction) {
        case IDENTITY:
            _derivs = MatrixXd::Identity(_dim, _dim);
        break;
        case BIAS:
            _derivs = MatrixXd::Zero(_dim, _dim);
        break;
        case BINARY:
            _derivs = MatrixXd::Zero(_dim, _dim);
        break;
        case SIGMOID:
            for(int i = 0; i < _dim; i++) {
                _derivs(i,i) = _output[i] * (1 - _output[i]);
            }
        break;
        case TANH:
            for(int i = 0; i < _dim; i++) {
                _derivs(i,i) = (1 - pow(_output[i], 2));
            }
        case SOFTMAX:
            for(int i = 0; i < _dim; i++) {
                for(int j = 0; j < _dim; j++) {
                    _derivs(i,j) = _output[i] * (NetworkUtils::kroneckerDelta(i,j) - _output[j]);
                }
            }
        break;
    }
}
