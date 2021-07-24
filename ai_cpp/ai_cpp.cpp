#include "ai_cpp.h"

// https://www.codeproject.com/Articles/5292985/Artificial-Neural-Network-Cplusplus-class#Background
// https://genbattle.bitbucket.io/blog/2016/03/19/Simple-Artificial-Neural-Networks-with-FANN-and-C/

#include <stdio.h>
#include <iostream>
#include <cstdlib>
#include <array>
#include <fann.h>
#include <fann_cpp.h>
using uint = unsigned int;

Ai_cpp::Ai_cpp()
{
}

void Ai_cpp::train(struct ai_setup ai)
{
    // Create the network
    const std::array<uint, 4> layers = {ai.num_inputs, ai.num_neurons_hidden, ai.num_outputs};
    FANN::neural_net net(FANN::LAYER, ai.num_layers, layers.data());
    net.set_activation_function_hidden(FANN::SIGMOID_STEPWISE);
    net.set_activation_function_output(FANN::SIGMOID_STEPWISE);

    net.train_on_file(ai.train_on_file, ai.max_epochs, ai.epochs_between_reports, ai.desired_error);
    net.save(ai.neural_network_file);
}

struct ai_value Ai_cpp::run(struct ai_value ai)
{
    std::array<fann_type, 2> input{float(ai.Xor_in0), float(ai.Xor_in1)};

    // Run the input against the neural network
    FANN::neural_net net(ai.neural_network_file);

    fann_type* output = net.run(input.data());
    if (output != nullptr)
        std::cout << "output: " << *output << std::endl;
    else
        std::cout << "error, no output." << std::endl;

    ai.Xor_out0=*output;
    return ai;
}

// C module function wrappers:
extern "C" void train_ai_cpp(struct ai_setup ai){ // C to cpp wrapper function
    Ai_cpp().train(ai);
}

extern "C" struct ai_value run_ai_cpp(struct ai_value ai){ // C to cpp wrapper function
    ai=Ai_cpp().run(ai);
    return ai;
}

















