#ifndef AI_CPP_H
#define AI_CPP_H

#include "ai_cpp_global.h"

// c module variables:
struct ai_setup {
    //! Machine model data:
    // Neural Network parameters
    unsigned int num_inputs;
    unsigned int num_outputs;
    unsigned int num_layers;
    unsigned int num_neurons_hidden;
    float desired_error;
    unsigned int max_epochs;
    unsigned int epochs_between_reports;
    char* train_on_file;
    char* neural_network_file;
};
ai_setup ai_setup;

struct ai_value {
    char* neural_network_file;
    bool Xor_in0;
    bool Xor_in1;
    float Xor_out0;
};
ai_value ai_value;

class AI_CPP_EXPORT Ai_cpp
{
public:
    Ai_cpp();
    void train(struct ai_setup ai);
    struct ai_value run(struct ai_value ai);

    // C module functions:
    void train_ai_cpp(struct ai_setup ai);
    struct ai_value run_ai_cpp(struct ai_value ai);
};

#endif // AI_CPP_H
