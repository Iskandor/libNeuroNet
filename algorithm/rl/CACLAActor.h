//
// Created by mpechac on 22. 3. 2017.
//

#ifndef NEURONET_CACLAACTOR_H
#define NEURONET_CACLAACTOR_H


#include "../LearningAlgorithm.h"
#include "../optimizer/Optimizer.h"

namespace NeuroNet {

class CACLAActor : public LearningAlgorithm {
public:
    CACLAActor(Optimizer* p_optimizer, NeuralNetwork* p_network);
    ~CACLAActor();

    double train(Vector* p_state0, Vector* p_action, double p_delta);

    void setAlpha(double p_alpha);
private:
    Optimizer*      _optimizer;
    NeuralNetwork*  _network;
};

}

#endif //NEURONET_CACLAACTOR_H
