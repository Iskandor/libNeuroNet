#pragma once

#include <vector>
#include "NeuralGroup.cuh"
#include "Connection.h"

using namespace std;

class NeuralNetwork
{
public:
    enum GROUP_TYPE {
        HIDDEN = 0,
        INPUT = 1,
        OUTPUT = 2
    };

	NeuralNetwork(void);
	~NeuralNetwork(void);

    void init();
    void onLoop();
    NeuralGroup* addLayer(int p_dim, int p_activationFunction, GROUP_TYPE p_type);
    Connection* addConnection(NeuralGroup* p_inGroup, NeuralGroup* p_outGroup, double p_density = 1, double p_inhibition = 0.5);

    bool running() const { return _running; };
    double* getOutput() const { return _output; };
    double getScalarOutput() const { return _output[0]; };
    vector<NeuralGroup*>* getGroups() { return &_groups; };
    NeuralGroup* getOutputGroup() const { return _outputGroup; };
    NeuralGroup* getInputGroup() const { return _inputGroup; };
    vector<Connection*>* getConnections() { return &_connections; };

    void setInput(double* p_input) { _input = p_input; };

private:
    void activate(NeuralGroup* p_node);

    int _groupId;
    int _connectionId;

    NeuralGroup* _inputGroup;
    NeuralGroup* _outputGroup;

    vector<NeuralGroup*> _groups;
    vector<Connection*> _connections;

    double* _inputWeights;
    double* _input;
    double* _output;

    bool _running;
};

