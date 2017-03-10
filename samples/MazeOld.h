#pragma once

#include "../algorithm/IEnvironment.h"

using namespace NeuroNet;

class MazeOld : public IEnvironment
{
public:
    MazeOld(int p_dim);
    ~MazeOld(void);

    bool evaluateAction(VectorXd* p_action, VectorXd* p_state) override;
    void updateState(VectorXd* p_action) override;
    double getStateValue();
    void reset() override;
    bool isFinished() const;
    bool isFailed() const;

    VectorXd* getPlayer();
    int getDim() const { return _dim;};

private:
    void decodeAction(VectorXd* p_action, VectorXd* p_command) const;
    bool isValidMove(double p_x, double p_y) const;

    int _dim;
    VectorXd _player;
    VectorXd _goal;
    bool _failed;
};
