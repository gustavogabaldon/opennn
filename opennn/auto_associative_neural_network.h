//   OpenNN: Open Neural Networks Library
//   www.opennn.net
//
//   A U T O   A S S O C I A T I V E   N E U R A L   N E T W O R K   C L A S S   H E A D E R
//
//   Artificial Intelligence Techniques SL
//   artelnics@artelnics.com

#ifndef AUTOASSOCIATIVENEURALNETWORK_H
#define AUTOASSOCIATIVENEURALNETWORK_H

// System includes

#include <cmath>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <errno.h>

// OpenNN includes

#include "neural_network.h"

namespace opennn
{


class AutoAssociativeNeuralNetwork : public NeuralNetwork
{

public:

   // Constructors

   explicit AutoAssociativeNeuralNetwork();

    BoxPlot get_auto_associative_distances_box_plot() const;
    Descriptives get_distances_descriptives() const;

    type get_box_plot_minimum() const;
    type get_box_plot_first_quartile() const;
    type get_box_plot_median() const;
    type get_box_plot_third_quartile() const;
    type get_box_plot_maximum() const;

    Tensor<BoxPlot, 1> get_multivariate_distances_box_plot() const;
    Tensor<type, 1> get_multivariate_distances_box_plot_minimums() const;
    Tensor<type, 1> get_multivariate_distances_box_plot_first_quartile() const;
    Tensor<type, 1> get_multivariate_distances_box_plot_median() const;
    Tensor<type, 1> get_multivariate_distances_box_plot_third_quartile() const;
    Tensor<type, 1> get_multivariate_distances_box_plot_maximums() const;

    void set_box_plot_minimum(const type&);
    void set_box_plot_first_quartile(const type&);
    void set_box_plot_median(const type&);
    void set_box_plot_third_quartile(const type&);
    void set_box_plot_maximum(const type&);

    void set_distances_box_plot(BoxPlot&);
    void set_multivariate_distances_box_plot(Tensor<BoxPlot, 1>&);
    void set_variables_distances_names(const Tensor<string, 1>&);
    void set_distances_descriptives(Descriptives&);

    void box_plot_from_XML(const tinyxml2::XMLDocument&);
    void distances_descriptives_from_XML(const tinyxml2::XMLDocument&);
    void multivariate_box_plot_from_XML(const tinyxml2::XMLDocument&);

    void write_XML(tinyxml2::XMLPrinter&) const;
    void from_XML(const tinyxml2::XMLDocument&);

    string write_expression_autoassociation_distances(string&, string&) const;
    string write_expression_autoassociation_variables_distances(string&, string&) const;

    Tensor<type, 2> calculate_multivariate_distances(type* &, Tensor<Index,1>&, type* &, Tensor<Index,1>&);
    Tensor<type, 1> calculate_samples_distances(type* &, Tensor<Index,1>&, type* &, Tensor<Index,1>&);

    void save_autoassociation_outputs(const Tensor<type, 1>&,const Tensor<string, 1>&, const string&) const;

private:

    /// AANN distances box plot

    BoxPlot auto_associative_distances_box_plot = BoxPlot();

    Tensor<BoxPlot, 1> multivariate_distances_box_plot;

    Descriptives distances_descriptives = Descriptives();

    Tensor<string, 1> variables_distances_names = Tensor<string, 1>();

};
};
#endif

// OpenNN: Open Neural Networks Library.
// Copyright(C) 2005-2024 Artificial Intelligence Techniques, SL.
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