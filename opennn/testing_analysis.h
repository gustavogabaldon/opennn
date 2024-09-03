//   OpenNN: Open Neural Networks Library
//   www.opennn.net
//
//   T E S T I N G   A N A L Y S I S   C L A S S   H E A D E R             
//
//   Artificial Intelligence Techniques SL
//   artelnics@artelnics.com

#ifndef TESTINGANALYSIS_H
#define TESTINGANALYSIS_H

// System includes

#include <iostream>
#include <string>

//#include <numeric>

// OpenNN includes

#include "config.h"
#include "data_set.h"
#include "neural_network.h"

//Eigen includes

namespace opennn
{

class TestingAnalysis
{

public: 

   // Constructors

   explicit TestingAnalysis();

   explicit TestingAnalysis(NeuralNetwork*, DataSet*);

    // Destructor

   virtual ~TestingAnalysis();

    struct GoodnessOfFitAnalysis
    {
       type determination = type(0);

       Tensor<type, 1> targets;
       Tensor<type, 1> outputs;

       void save(const string& file_name) const;

       void print() const
       {
           cout << "Goodness-of-fit analysis" << endl;
           cout << "Determination: " << determination << endl;
       }
    };


    struct RocAnalysis
    {
        Tensor<type, 2> roc_curve;

        type area_under_curve;

        type confidence_limit;

        type optimal_threshold;
    };


    struct KolmogorovSmirnovResults
    {
        Tensor<type, 2> positive_cumulative_gain;

        Tensor<type, 2> negative_cumulative_gain;

        Tensor<type, 1> maximum_gain;
    };


    struct BinaryClassificationRates
    {
        Tensor<Index, 1> true_positives_indices;

        Tensor<Index, 1> false_positives_indices;

        Tensor<Index, 1> false_negatives_indices;

        Tensor<Index, 1> true_negatives_indices;
    };

   // Get

   NeuralNetwork* get_neural_network() const;
   DataSet* get_data_set() const;

   const bool& get_display() const;

   // Set

   void set_neural_network(NeuralNetwork*);
   void set_data_set(DataSet*);

   void set_display(const bool&);

   void set_default();

   void set_threads_number(const int&);

   // Checking

   void check() const;

   // Error data

   Tensor<type, 3> calculate_error_data() const;
   Tensor<type, 2> calculate_percentage_error_data() const;

   Tensor<Descriptives, 1> calculate_absolute_errors_descriptives() const;
   Tensor<Descriptives, 1> calculate_absolute_errors_descriptives(const Tensor<type, 2>&, const Tensor<type, 2>&) const;

   Tensor<Descriptives, 1> calculate_percentage_errors_descriptives() const;
   Tensor<Descriptives, 1> calculate_percentage_errors_descriptives(const Tensor<type, 2>&, const Tensor<type, 2>&) const;

   Tensor<Tensor<Descriptives, 1>, 1> calculate_error_data_descriptives() const;
   void print_error_data_descriptives() const;

   Tensor<Histogram, 1> calculate_error_data_histograms(const Index& = 10) const;

   Tensor<Tensor<Index, 1>, 1> calculate_maximal_errors(const Index& = 10) const;

   Tensor<type, 2> calculate_errors() const;
   Tensor<type, 2> calculate_binary_classification_errors() const;
   Tensor<type, 2> calculate_multiple_classification_errors() const;

   Tensor<type, 1> calculate_training_errors() const;
   Tensor<type, 1> calculate_binary_classification_training_errors() const;
   Tensor<type, 1> calculate_multiple_classification_training_errors() const;

   Tensor<type, 1> calculate_selection_errors() const;
   Tensor<type, 1> calculate_binary_classification_selection_errors() const;
   Tensor<type, 1> calculate_multiple_classification_selection_errors() const;

   Tensor<Tensor<type, 1>, 1> calculate_testing_errors() const;
   Tensor<type, 1> calculate_binary_classification_testing_errors() const;
   Tensor<type, 1> calculate_multiple_classification_testing_errors() const;

   type calculate_normalized_squared_error(const Tensor<type, 2>&, const Tensor<type, 2>&) const;
   type calculate_cross_entropy_error(const Tensor<type, 2>&, const Tensor<type, 2>&) const;
   type calculate_cross_entropy_error_3d(const Tensor<type, 3>&, const Tensor<type, 2>&) const;
   type calculate_weighted_squared_error(const Tensor<type, 2>&, const Tensor<type, 2>&, const Tensor<type, 1>& = Tensor<type, 1>()) const;
   type calculate_Minkowski_error(const Tensor<type, 2>&, const Tensor<type, 2>&, const type = type(1.5)) const;

   type calculate_masked_accuracy(const Tensor<type, 3>&, const Tensor<type, 2>&) const;

   type calculate_determination_coefficient(const Tensor<type, 1>&, const Tensor<type, 1>&) const;

   // Goodness-of-fit analysis

   Tensor<Correlation, 1> linear_correlation() const;
   Tensor<Correlation, 1> linear_correlation(const Tensor<type, 2>&, const Tensor<type, 2>&) const;

   void print_linear_correlations() const;

   Tensor<GoodnessOfFitAnalysis, 1> perform_goodness_of_fit_analysis() const;
   void print_goodness_of_fit_analysis() const;

   // Binary classifcation

   Tensor<type, 1> calculate_binary_classification_tests() const;

   void print_binary_classification_tests() const;

   type calculate_logloss() const;

   // Confusion

   Tensor<Index, 2> calculate_confusion_binary_classification(const Tensor<type, 2>&, const Tensor<type, 2>&, const type&) const;
   Tensor<Index, 2> calculate_confusion_multiple_classification(const Tensor<type, 2>&, const Tensor<type, 2>&) const;
   Tensor<Index, 2> calculate_confusion(const Tensor<type, 2>&, const Tensor<type, 2>&, const Index&) const;

   Tensor<Index, 1> calculate_positives_negatives_rate(const Tensor<type, 2>&, const Tensor<type, 2>&) const;

   Tensor<Index, 2> calculate_confusion(const Tensor<type, 2>&, const Tensor<type, 2>&) const;
   Tensor<Index, 2> calculate_confusion() const;

   // ROC curve

   RocAnalysis perform_roc_analysis() const;

   Tensor<type, 2> calculate_roc_curve(const Tensor<type, 2>&, const Tensor<type, 2>&) const;

//   type calculate_area_under_curve(const Tensor<type, 2>&, const Tensor<type, 2>&) const;

   type calculate_area_under_curve(const Tensor<type, 2>&) const;
   type calculate_area_under_curve_confidence_limit(const Tensor<type, 2>&, const Tensor<type, 2>&) const;
//   type calculate_area_under_curve_confidence_limit(const Tensor<type, 2>&, const Tensor<type, 2>&, const type&) const;
//   type calculate_optimal_threshold(const Tensor<type, 2>&, const Tensor<type, 2>&) const;
   type calculate_optimal_threshold(const Tensor<type, 2>&) const;

   // Lift Chart

   Tensor<type, 2> perform_cumulative_gain_analysis() const;
   Tensor<type, 2> calculate_cumulative_gain(const Tensor<type, 2>&, const Tensor<type, 2>&) const;
   Tensor<type, 2> calculate_negative_cumulative_gain(const Tensor<type, 2>&, const Tensor<type, 2>&)const;

   Tensor<type, 2> perform_lift_chart_analysis() const;
   Tensor<type, 2> calculate_lift_chart(const Tensor<type, 2>&) const;

   Tensor<type, 1> calculate_maximum_gain(const Tensor<type, 2>&, const Tensor<type, 2>&) const;

   // Calibration plot

   Tensor<type, 2> perform_calibration_plot_analysis() const;

   Tensor<type, 2> calculate_calibration_plot(const Tensor<type, 2>&, const Tensor<type, 2>&) const;

   // Output histogram

   Tensor<Histogram, 1> calculate_output_histogram(const Tensor<type, 2>&, const Index& = 10) const;

   // Binary classification rates

   BinaryClassificationRates calculate_binary_classification_rates() const;

   Tensor<Index, 1> calculate_true_positive_samples(const Tensor<type, 2>&, const Tensor<type, 2>&, const Tensor<Index, 1>&, const type&) const;
   Tensor<Index, 1> calculate_false_positive_samples(const Tensor<type, 2>&, const Tensor<type, 2>&, const Tensor<Index, 1>&, const type&) const;
   Tensor<Index, 1> calculate_false_negative_samples(const Tensor<type, 2>&, const Tensor<type, 2>&, const Tensor<Index, 1>&, const type&) const;
   Tensor<Index, 1> calculate_true_negative_samples(const Tensor<type, 2>&, const Tensor<type, 2>&, const Tensor<Index, 1>&, const type&) const;

   // Multiple classification tests

   Tensor<type, 1> calculate_multiple_classification_precision() const;
   Tensor<type, 2> calculate_multiple_classification_tests() const;

   // Multiple classification rates

   Tensor<Tensor<Index,1>, 2> calculate_multiple_classification_rates() const;

   Tensor<Tensor<Index,1>, 2> calculate_multiple_classification_rates(const Tensor<type, 2>&, const Tensor<type, 2>&, const Tensor<Index, 1>&) const;

   Tensor<string, 2> calculate_well_classified_samples(const Tensor<type, 2>&, const Tensor<type, 2>&, const Tensor<string, 1>&) const;

   Tensor<string, 2> calculate_misclassified_samples(const Tensor<type, 2>&, const Tensor<type, 2>&, const Tensor<string, 1>&) const;

   // Save

   void save_confusion(const string&) const;

   void save_multiple_classification_tests(const string&) const;

   void save_well_classified_samples(const Tensor<type, 2>&, const Tensor<type, 2>&, const Tensor<string, 1>&, const string&) const;

   void save_misclassified_samples(const Tensor<type, 2>&, const Tensor<type, 2>&, const Tensor<string, 1>&, const string&) const;

   void save_well_classified_samples_statistics(const Tensor<type, 2>&, const Tensor<type, 2>&, const Tensor<string, 1>&, const string&) const;

   void save_misclassified_samples_statistics(const Tensor<type, 2>&, const Tensor<type, 2>&, const Tensor<string, 1>&, const string&) const;

   void save_well_classified_samples_probability_histogram(const Tensor<type, 2>&, const Tensor<type, 2>&, const Tensor<string, 1>&, const string&) const;

   void save_well_classified_samples_probability_histogram(const Tensor<string, 2>&, const string&) const;

   void save_misclassified_samples_probability_histogram(const Tensor<type, 2>&, const Tensor<type, 2>&, const Tensor<string, 1>&, const string&) const;

   void save_misclassified_samples_probability_histogram(const Tensor<string, 2>&, const string&) const;

   // Forecasting

   Tensor<Tensor<type, 1>, 1> calculate_error_autocorrelation(const Index& = 10) const;

   Tensor<Tensor<type, 1>, 1> calculate_inputs_errors_cross_correlation(const Index& = 10) const;

   // Transformer

   pair<type, type> test_transformer() const;

   // Serialization

   virtual void from_XML(const tinyxml2::XMLDocument&);

   virtual void to_XML(tinyxml2::XMLPrinter&) const;

   void save(const string&) const;
   void load(const string&);


private: 

   ThreadPool* thread_pool = nullptr;
   ThreadPoolDevice* thread_pool_device = nullptr;

   NeuralNetwork* neural_network = nullptr;

   DataSet* data_set = nullptr;

   bool display = true;

   const Eigen::array<IndexPair<Index>, 2> SSE = {IndexPair<Index>(0, 0), IndexPair<Index>(1, 1)};
};

}

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
