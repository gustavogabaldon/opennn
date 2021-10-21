//   OpenNN: Open Neural Networks Library
//   www.opennn.net
//
//   B L A N K   A P P L I C A T I O N
//
//   Artificial Intelligence Techniques SL
//   artelnics@artelnics.com

// System includes

#include <cstring>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstring>
#include <time.h>
#include <stdio.h>

// OpenNN includes

#include "../../opennn/opennn/opennn.h"

using namespace OpenNN;
using namespace std;
using namespace Eigen;

int main()
{
    try{
        cout << "Hello, OpenNN!" << endl;

        cout << "OpenNN. Rosenbrock Example." << endl;

        // Data Set

        const Index samples_number = 10000;
        const Index inputs_number = 10;
        const Index outputs_number = 1;
        const Index hidden_neurons_number = inputs_number;

        DataSet data_set;// ("C:/rosenbrock.csv", ',', true);

        data_set.generate_Rosenbrock_data(samples_number, inputs_number + outputs_number);

        data_set.set_training();

        // Neural network

        NeuralNetwork neural_network(NeuralNetwork::ProjectType::Approximation, {inputs_number, hidden_neurons_number, outputs_number});

        // Training strategy

        TrainingStrategy training_strategy(&neural_network, &data_set);

        training_strategy.set_loss_method(TrainingStrategy::LossMethod::MINKOWSKI_ERROR);
        training_strategy.get_loss_index_pointer()->set_regularization_method(LossIndex::RegularizationMethod::NoRegularization);
        training_strategy.set_optimization_method(TrainingStrategy::OptimizationMethod::STOCHASTIC_GRADIENT_DESCENT);

        training_strategy.get_gradient_descent_pointer()->set_display_period(100);
        training_strategy.get_gradient_descent_pointer()->set_maximum_epochs_number(1000);

        TrainingResults training_results = training_strategy.perform_training();

        cout << "Good bye!" << endl;

        return 0;
    }
    catch(exception& e)
    {
        cerr << e.what() << endl;

        return 1;
    }
}


// OpenNN: Open Neural Networks Library.
// Copyright (C) Artificial Intelligence Techniques SL.
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2.1 of the License, or any later version.
//
// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// Lesser General Public License for more details.
// You should have received a copy of the GNU Lesser General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
