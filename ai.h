#ifndef AI_H
#define AI_H

#include <stdio.h>
#include <stdbool.h>

// In the makefile the external so lib has to be present with -L/path -llibname
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

struct ai_value {
    char* neural_network_file;
    bool Xor_in0;
    bool Xor_in1;
    float Xor_out0;
};

extern void train_ai_cpp(struct ai_setup ai);
extern struct ai_value run_ai_cpp(struct ai_value ai);


#endif // AI_H
