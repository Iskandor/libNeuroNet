//
// Created by user on 11. 6. 2016.
//

#include "NaturalGradientActor.h"

using namespace NeuroNet;

NaturalGradientActor::NaturalGradientActor(NeuralNetwork *p_network) : GradientDescent(p_network) {
    _error.resize(p_network->getOutput()->size());
}

void NaturalGradientActor::train(VectorXd *p_state0, double tdError) {
    _network->activate(p_state0);

    _error = tdError * *_network->getOutput();
    calcNatGradient(0.001, &_error);

    for(auto it = _network->getConnections()->begin(); it != _network->getConnections()->end(); it++) {
        updateWeights(it->second);
    }
}

void NaturalGradientActor::updateWeights(NeuroNet::Connection *p_connection) {
    int nCols = p_connection->getInGroup()->getDim();
    int nRows = p_connection->getOutGroup()->getDim();
    MatrixXd delta(nRows, nCols);

    delta = _alpha * _natGradient[p_connection->getId()];
    p_connection->getWeights()->operator+=(delta);
}

NaturalGradientActor::~NaturalGradientActor() {

}
