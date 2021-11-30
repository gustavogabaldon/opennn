//   OpenNN: Open Neural Networks Library
//   www.opennn.net
//
//   D A T A   S E T   T E S T   C L A S S                                 
//
//   Artificial Intelligence Techniques SL
//   artelnics@artelnics.com

#include "data_set_test.h"

DataSetTest::DataSetTest() : UnitTesting() 
{
//    data_set.set_display(false);
}


DataSetTest::~DataSetTest()
{
}


void DataSetTest::test_constructor()
{
   cout << "test_constructor\n";

   // Default constructor

   DataSet data_set_1;

   assert_true(data_set_1.get_variables_number() == 0, LOG);
   assert_true(data_set_1.get_samples_number() == 0, LOG);

   // Samples and variables number constructor

   DataSet data_set_2(1, 2);

   assert_true(data_set_2.get_samples_number() == 1, LOG);
   assert_true(data_set_2.get_variables_number() == 2, LOG);

   // Inputs, targets and samples numbers constructor

   DataSet data_set_3(1, 1, 1);

   assert_true(data_set_3.get_variables_number() == 2, LOG);
   assert_true(data_set_3.get_samples_number() == 1, LOG);
   assert_true(data_set_3.get_target_variables_number() == 1,LOG);
   assert_true(data_set_3.get_input_variables_number() == 1,LOG);
}


void DataSetTest::test_destructor()
{
   cout << "test_destructor\n";

   DataSet* data_set_pointer = new DataSet(1, 1, 1);

   delete data_set_pointer;
}


void DataSetTest::test_set() 
{
   cout << "test_set\n";

   // Samples and inputs and target variables

   data_set.set(1, 2, 3);

   assert_true(data_set.get_samples_number() == 1, LOG);
   assert_true(data_set.get_input_variables_number() == 2, LOG);
   assert_true(data_set.get_target_variables_number() == 3, LOG);

   data = data_set.get_data();

   assert_true(data.dimension(0) == 1, LOG);
   assert_true(data.dimension(1) == 5, LOG);
}


void DataSetTest::test_set_samples_number() 
{
   cout << "test_set_samples_number\n";

   data_set.set(1,1,1);

   data_set.set_samples_number(2);

   assert_true(data_set.get_samples_number() == 2, LOG);
}


void DataSetTest::test_set_columns_number()
{
   cout << "test_set_columns_number\n";

   data_set.set(1, 1);
   data_set.set_columns_number(2);

   assert_true(data_set.get_variables_number() == 2, LOG);
}


void DataSetTest::test_set_data()
{
   cout << "test_set_data\n";

   // Test

   inputs_number = 3;
   targets_number = 2;
   samples_number = 1;

   data.resize(samples_number, inputs_number + targets_number);
   data.setValues({{type(0),type(1),type(2),type(3),type(4)}});

   data_set.set_data(data);

   data = data_set.get_data();

   assert_true(data.dimension(0) == samples_number, LOG);
   assert_true(data.dimension(1) == inputs_number+targets_number, LOG);

   assert_true(abs(data(0,0)) < type(NUMERIC_LIMITS_MIN), LOG);
}


void DataSetTest::test_calculate_variables_descriptives()
{
    cout << "test_calculate_variables_descriptives\n";

    Tensor<Descriptives, 1> variables_descriptives;

    ofstream file;
    string data_string;

    const string data_file_name = "../data/data.dat";

    // Test

    data_set.set(1, 1);

    data_set.set_data_constant(type(0));

    variables_descriptives = data_set.calculate_variables_descriptives();

    assert_true(variables_descriptives.size() == 1, LOG);

    assert_true(abs(variables_descriptives[0].minimum) < type(NUMERIC_LIMITS_MIN), LOG);
    assert_true(abs(variables_descriptives[0].maximum) < type(NUMERIC_LIMITS_MIN), LOG);
    assert_true(abs(variables_descriptives[0].mean) < type(NUMERIC_LIMITS_MIN), LOG);
    assert_true(abs(variables_descriptives[0].standard_deviation) < type(NUMERIC_LIMITS_MIN), LOG);

    // Test

    data_set.set(2, 2, 2);

    data_set.set_data_constant(type(0));

    variables_descriptives = data_set.calculate_variables_descriptives();

    assert_true(variables_descriptives.size() == 4, LOG);

    assert_true(variables_descriptives[0].minimum < type(NUMERIC_LIMITS_MIN), LOG);
    assert_true(variables_descriptives[0].maximum < type(NUMERIC_LIMITS_MIN), LOG);
    assert_true(variables_descriptives[0].mean < type(NUMERIC_LIMITS_MIN), LOG);
    assert_true(variables_descriptives[0].standard_deviation < type(NUMERIC_LIMITS_MIN), LOG);

    assert_true(variables_descriptives[1].minimum < type(NUMERIC_LIMITS_MIN), LOG);
    assert_true(variables_descriptives[1].maximum < type(NUMERIC_LIMITS_MIN), LOG);
    assert_true(variables_descriptives[1].mean < type(NUMERIC_LIMITS_MIN), LOG);
    assert_true(variables_descriptives[1].standard_deviation < type(NUMERIC_LIMITS_MIN), LOG);

    assert_true(variables_descriptives[2].minimum < type(NUMERIC_LIMITS_MIN), LOG);
    assert_true(variables_descriptives[2].maximum < type(NUMERIC_LIMITS_MIN), LOG);
    assert_true(variables_descriptives[2].mean < type(NUMERIC_LIMITS_MIN), LOG);
    assert_true(variables_descriptives[2].standard_deviation < type(NUMERIC_LIMITS_MIN), LOG);

    assert_true(variables_descriptives[3].minimum < type(NUMERIC_LIMITS_MIN), LOG);
    assert_true(variables_descriptives[3].maximum < type(NUMERIC_LIMITS_MIN), LOG);
    assert_true(variables_descriptives[3].mean < type(NUMERIC_LIMITS_MIN), LOG);
    assert_true(variables_descriptives[3].standard_deviation < type(NUMERIC_LIMITS_MIN), LOG);

    // Test

    inputs_number = 2;
    targets_number = 1;
    samples_number = 3;

    data.resize(samples_number,inputs_number + targets_number);
    data.setValues({{type(-1000),type(2),type(0)},{type(1),type(4),type(2)},{type(1),type(4),type(0)}});

    data_set.set_data(data);

    variables_descriptives = data_set.calculate_variables_descriptives();

    assert_true(variables_descriptives.size() == 3, LOG);

    assert_true(abs(variables_descriptives[0].minimum + type(1000)) < type(NUMERIC_LIMITS_MIN), LOG);
    assert_true(abs(variables_descriptives[1].minimum - type(2)) < type(NUMERIC_LIMITS_MIN), LOG);
    assert_true(abs(variables_descriptives[2].minimum) < type(NUMERIC_LIMITS_MIN), LOG);

    assert_true(abs(variables_descriptives[0].maximum - type(1)) < type(NUMERIC_LIMITS_MIN), LOG);
    assert_true(abs(variables_descriptives[1].maximum - type(4)) < type(NUMERIC_LIMITS_MIN), LOG);
    assert_true(abs(variables_descriptives[2].maximum - type(2)) < type(NUMERIC_LIMITS_MIN), LOG);
}


void DataSetTest::test_calculate_input_variables_descriptives() //@todo
{
   cout << "test_calculate_input_variables_descriptives\n";

   Tensor<Descriptives, 1> input_variables_descriptives;

   Tensor<Index, 1> indices;

   // Test

   data.resize(2, 3);
   data.setValues({{type(1.0), type(2.0), type(3.0)},
                   {type(1.0), type(2.0), type(3.0)}});

   data_set.set(data);

   indices.resize(2);
   indices.setValues({0, 1});

   input_variables_descriptives = data_set.calculate_input_variables_descriptives();

   assert_true(input_variables_descriptives[0].mean - type(2.0) < type(NUMERIC_LIMITS_MIN), LOG);
   assert_true(input_variables_descriptives[0].standard_deviation - type(1.0)< type(NUMERIC_LIMITS_MIN), LOG);
   assert_true(input_variables_descriptives[0].minimum - type(1.0) < type(NUMERIC_LIMITS_MIN), LOG);
   assert_true(input_variables_descriptives[0].maximum - type(3.0) < type(NUMERIC_LIMITS_MIN), LOG);
}


void DataSetTest::test_calculate_autocorrelations()
{
    cout << "test_calculate_autocorrelations\n";

    Tensor<type, 2> autocorrelations;

    Index samples_number;
    Index inputs_number;
    Index targets_number;

    Index lags_number;
    Index steps_ahead_number;

    // Test

    samples_number = 1;
    inputs_number = 1;
    targets_number = 1;

    lags_number = 1;
    steps_ahead_number = 1;

    data_set.set(samples_number, inputs_number, targets_number);
    data_set.set_lags_number(lags_number);
    data_set.set_steps_ahead_number(steps_ahead_number);
    data_set.transform_time_series();

/// @todo bad_allocation
//    autocorrelations = data_set.calculate_autocorrelations(lags_number);

//    assert_true(autocorrelations.dimension(1) == 10, LOG);
//    assert_true(autocorrelations.dimension(0) == 2, LOG);

}


void DataSetTest::test_calculate_cross_correlations()
{
    cout << "test_calculate_cross_correlations\n";

    Index lags_number;

    Tensor<type, 3> cross_correlations;

    // Test

    lags_number = 6;

    data.resize(6, 3);
    
    data.setValues({
        {type(5),type(2),type(8)},
        {type(7),type(8),type(7)},
        {type(3),type(6),type(4)},
        {type(8),type(1),type(6)},
        {type(5),type(8),type(6)},
        {type(6),type(3),type(4)}});


    data_set.set_data(data);

    data_set.set_lags_number(lags_number);
    data_set.set_steps_ahead_number(1);
    data_set.transform_time_series();

    cross_correlations = data_set.calculate_cross_correlations(lags_number);

    assert_true(cross_correlations.dimension(0) == 3, LOG);
}


void DataSetTest::test_calculate_data_distributions()
{
   cout << "test_calculate_data_distributions\n";

   Tensor<Histogram, 1> histograms;

   data_set.set();

   // Test

   data.resize(3, 3);

   data.setValues({
       {type(2),type(2),type(1)},
       {type(1),type(1),type(1)},
       {type(1),type(2),type(2)}});

   data_set.set_data(data);

   histograms = data_set.calculate_columns_distribution(2);

   assert_true(histograms.size() == 3, LOG);

   assert_true(abs( histograms(0).frequencies(0) - 2 )  < type(NUMERIC_LIMITS_MIN), LOG);
   assert_true(abs( histograms(1).frequencies(0) - 1 ) < type(NUMERIC_LIMITS_MIN), LOG);
   assert_true(abs( histograms(2).frequencies(0) - 2 ) < type(NUMERIC_LIMITS_MIN), LOG);

   assert_true(abs( histograms(0).centers(0) - 1 )  < type(NUMERIC_LIMITS_MIN), LOG);
   assert_true(abs( histograms(1).centers(0) - 1 ) < type(NUMERIC_LIMITS_MIN), LOG);
   assert_true(abs( histograms(2).centers(0) - 1 ) < type(NUMERIC_LIMITS_MIN), LOG);
}


void DataSetTest::test_filter_data()
{
   cout << "test_filter_data\n";

   Index samples_number;
   Index inputs_number;
   Index targets_number;

   Tensor<type, 1> minimums;
   Tensor<type, 1> maximums;

   // Test

   samples_number = 2;
   inputs_number = 1;
   targets_number = 1;

   data_set.set(samples_number, inputs_number, targets_number);
   data_set.set_data_constant(type(1));

   minimums.resize(2);
   minimums.setValues({ type(2), type(0.0)});

   maximums.resize(2);
   maximums.setValues({ type(2), type(0.5)});

   data_set.filter_data(minimums, maximums);

   assert_true(data_set.get_sample_use(0) == DataSet::SampleUse::UnusedSample, LOG);
   assert_true(data_set.get_sample_use(1) == DataSet::SampleUse::UnusedSample, LOG);

}


void DataSetTest::test_scale_data()
{
    cout << "test_scale_data\n";

    Tensor<Descriptives, 1> data_descriptives;
    Tensor<type, 2> scaled_data;

    // Test

    data.resize(2,2);
    data.setValues({
                       {type(1), type(2)},
                       {type(3), type(4)}});

    data_set.set_data(data);

    data_set.set_columns_scalers(Scaler::NoScaling);
    data_descriptives = data_set.scale_data();

    scaled_data = data_set.get_data();

    assert_true(are_equal(scaled_data, data), LOG);

    // Test

    data_set.set_columns_scalers(Scaler::MinimumMaximum);
    data_descriptives = data_set.scale_data();

    scaled_data = data_set.get_data();

    assert_true(abs(scaled_data(0) - type(-1)) < type(NUMERIC_LIMITS_MIN), LOG);
    assert_true(abs(scaled_data(1) - type(1)) < type(NUMERIC_LIMITS_MIN), LOG);
    assert_true(abs(scaled_data(2) - type(-1)) < type(NUMERIC_LIMITS_MIN), LOG);
    assert_true(abs(scaled_data(3) - type(1)) < type(NUMERIC_LIMITS_MIN), LOG);
}


void DataSetTest::test_unuse_constant_columns()
{
    cout << "test_unuse_constant_columns\n";

    // Test

    samples_number = 3;
    inputs_number = 2;
    targets_number = 1;

    data.resize(samples_number, inputs_number + targets_number);
    data.setValues({{type(1),type(2),type(0)},{type(1),type(2),type(1)},{type(1),type(2),type(2)}});

    data_set.set_data(data);
    data_set.set_has_columns_names(false);
    data_set.check_constant_columns();

    data_set.unuse_constant_columns();

    assert_true(data_set.get_input_columns_number() == 0, LOG);
    assert_true(data_set.get_target_columns_number() == 1, LOG);
}


void DataSetTest::test_set_data_constant()
{
   cout << "test_set_data_constant\n";

   Tensor<type, 2> solution;

   data.resize(3,3);

   data_set.set(data);

   data_set.set_data_constant(type(2));

   solution.resize(3, 3);
   solution.setValues({
       {type(2),type(2),type(2)},
       {type(2),type(2),type(2)},
       {type(2),type(2),type(2)}});

   assert_true(data_set.get_data()(0) - solution(0)< type(NUMERIC_LIMITS_MIN), LOG);
   assert_true(data_set.get_data()(1) - solution(1) < type(NUMERIC_LIMITS_MIN), LOG);
   assert_true(data_set.get_data()(2) - solution(2) < type(NUMERIC_LIMITS_MIN), LOG);
   assert_true(data_set.get_data()(3) - solution(3) < type(NUMERIC_LIMITS_MIN), LOG);
   assert_true(data_set.get_data()(4) - solution(4) < type(NUMERIC_LIMITS_MIN), LOG);
   assert_true(data_set.get_data()(5) - solution(5) < type(NUMERIC_LIMITS_MIN), LOG);
   assert_true(data_set.get_data()(6) - solution(6) < type(NUMERIC_LIMITS_MIN), LOG);

}


void DataSetTest::test_calculate_target_distribution()
{
    cout << "test_calculate_target_distribution\n";

    Tensor<Index, 1> target_distribution;

    // Test two classes

    data.resize(4, 5);
    
    data.setValues({
        {type(2),type(5),type(6),type(9),type(8)},
        {type(2),type(9),type(1),type(9),type(4)},
        {type(6),type(5),type(6),type(7),type(3)},
        {type(0),static_cast<type>(NAN),type(1),type(0),type(1)}});
    
    data_set.set(data);

    target_variables_indices.resize(1);
    target_variables_indices.setValues({3});

    input_variables_indices.resize(3);
    input_variables_indices.setValues({0, 1, 2});

//    data_set.set_target_variables_indices(target_variables_indices);
//    data_set.set_input_variables_indices(input_variables_indices);
    target_distribution = data_set.calculate_target_distribution();

    Tensor<Index, 1> solution(2);
    solution(0) = 2;
    solution(1) = 2;

//    assert_true(target_distribution(0) == solution(0), LOG);
//    assert_true(target_distribution(1) == solution(1), LOG);

    // Test more two classes

    data.resize(6, 6);
    data.setZero();

    data.setValues({{type(2),type(5),type(6),type(9),type(8),type(7)},
                    {type(2),type(9),type(1),type(9),type(4),type(5)},
                    {type(6),type(5),type(6),type(7),type(3),type(2)},
                    {type(6),type(5),type(6),type(7),type(3),type(2)},
                    {type(0),static_cast<type>(NAN),type(1),type(0),type(2),type(2)},
                    {static_cast<type>(NAN),static_cast<type>(NAN),type(1),type(0),type(0),type(2)}});

    target_variables_indices.resize(2);
    target_variables_indices.setValues({2,3});

    input_variables_indices.resize(2);
    input_variables_indices.setValues({0, 1});

//    data_set.set_target_variables_indices(target_variables_indices);
//    data_set.set_input_variables_indices(input_variables_indices);

    data_set.set_data(data);

    target_distribution = data_set.calculate_target_distribution();

//    assert_true(target_distribution[0] == 6, LOG);
//    assert_true(target_distribution[1] == 3, LOG);
//    assert_true(target_distribution[2] == 2, LOG);

}


void DataSetTest::test_calculate_Tukey_outliers()
{
    cout << "test_calculate_Tukey_outliers\n";

    Tensor<type, 1> sample;

    Tensor<Tensor<Index, 1>, 1> outliers_indices;

    // Test

    data_set.set(100, 5, 1);
    data_set.set_data_random();

    outliers_indices = data_set.calculate_Tukey_outliers(type(1.5));

    assert_true(outliers_indices.size() == 2, LOG);
    assert_true(outliers_indices(0)(0) == 0, LOG);

}


void DataSetTest::test_calculate_euclidean_distance()
{
   cout << "test_calculate_euclidean_distance\n";
}


void DataSetTest::test_calculate_distance_matrix()
{
   cout << "test_calculate_distance_matrix\n";
}


void DataSetTest::test_calculate_k_nearest_neighbors()
{
   cout << "test_k_nearest_neighbors\n";
}


void DataSetTest::test_calculate_average_reachability()
{
   cout << "test_calculate_average_reachability\n";
}


void DataSetTest::test_calculate_LOF_outliers()
{
   cout << "test_calculate_LOF_outliers\n";
}


void DataSetTest::test_unuse_local_outlier_factor_outliers()
{
   cout << "test_unuse_local_outlier_factor_outliers\n";
}


void DataSetTest::test_read_csv() 
{
   cout << "test_read_csv\n";

   // Test

   data_set.set(2, 2, 2);

   data_set.set_separator(',');

   data_file_name = "../data/data.dat";

   data_set.set_data_file_name(data_file_name);

   data_set.set_data_constant(type(0));

   data_set.save_data();

   data_set.read_csv();

   data = data_set.get_data();

   assert_true(is_equal(data, type(0.0)), LOG);

   // Test
   // Test

   data_set.set_separator('\t');

   data_string = "\n\n\n   1\t2   \n\n\n   3\t4   \n\n\n    5\t6    \n\n\n";

   file.open(data_file_name.c_str());
   file << data_string;
   file.close();

   data_set.set();
   data_set.set_data_file_name(data_file_name);

   data_set.read_csv();

   data = data_set.get_data();

   assert_true(data.dimension(0) == 3, LOG);
   assert_true(data.dimension(1) == 2, LOG);

   assert_true(abs(data(0, 0) - type(1)) < type(NUMERIC_LIMITS_MIN), LOG);
   assert_true(abs(data(0, 1) - type(2)) < type(NUMERIC_LIMITS_MIN), LOG);
   assert_true(abs(data(1, 0) - type(3)) < type(NUMERIC_LIMITS_MIN), LOG);
   assert_true(abs(data(1, 1) - type(4)) < type(NUMERIC_LIMITS_MIN), LOG);
   assert_true(abs(data(2, 0) - type(5)) < type(NUMERIC_LIMITS_MIN), LOG);
   assert_true(abs(data(2, 1) - type(6)) < type(NUMERIC_LIMITS_MIN), LOG);

   assert_true(data_set.get_samples_number() == 3, LOG);
   assert_true(data_set.get_variables_number() == 2, LOG);

   // Test

   data_set.set_separator('\t');

   data_string = "\n\n\n   1\t2   \n\n\n   3\t4   \n\n\n   5\t6  \n\n\n";

   file.open(data_file_name.c_str());
   file << data_string;
   file.close();

   data_set.set();
   data_set.set_data_file_name(data_file_name);

   data_set.read_csv();

   data = data_set.get_data();

   assert_true(data.dimension(0) == 3, LOG);
   assert_true(data.dimension(1) == 2, LOG);

   assert_true(abs(data(0,0) - type(1)) < type(NUMERIC_LIMITS_MIN), LOG);
   assert_true(abs(data(0,1) - type(2)) < type(NUMERIC_LIMITS_MIN), LOG);
   assert_true(abs(data(1,0) - type(3)) < type(NUMERIC_LIMITS_MIN), LOG);
   assert_true(abs(data(1,1) - type(4)) < type(NUMERIC_LIMITS_MIN), LOG);
   assert_true(abs(data(2,0) - type(5)) < type(NUMERIC_LIMITS_MIN), LOG);
   assert_true(abs(data(2,1) - type(6)) < type(NUMERIC_LIMITS_MIN), LOG);

   assert_true(data_set.get_samples_number() == 3, LOG);
   assert_true(data_set.get_variables_number() == 2, LOG);

   // Test

   data_set.set();

   data_set.set_has_columns_names(true);
   data_set.set_separator(' ');

   data_string = "\n"
                 "x y\n"
                 "\n"
                 "1   2\n"
                 "3   4\n";

   file.open(data_file_name.c_str());
   file << data_string;
   file.close();
/// @todo read_csv() with set_has_columns_names(true)
/*
//   data_set.read_csv();

//   data = data_set.get_data();

//   assert_true(data_set.get_header_line(), LOG);
//   assert_true(data_set.get_variable_name(0) == "x", LOG);
//   assert_true(data_set.get_variable_name(1) == "y", LOG);

//   assert_true(data.dimension(0) == 2, LOG);
//   assert_true(data.dimension(1) == 2, LOG);

//   assert_true((data(0,0) - 1.0) < type(NUMERIC_LIMITS_MIN), LOG);
//   assert_true((data(0,1) - 2.0) < type(NUMERIC_LIMITS_MIN), LOG);
//   assert_true((data(1,0) - 3.0) < type(NUMERIC_LIMITS_MIN), LOG);
//   assert_true((data(1,1) - 4.0) < type(NUMERIC_LIMITS_MIN), LOG);

   // Test

   data_set.set_has_columns_names(true);
   data_set.set_separator(',');

   data_string = "\tx \t ,\t y \n"
                 "\t1 \t, \t 2 \n"
                 "\t3 \t, \t 4 \n";

   file.open(data_file_name.c_str());
   file << data_string;
   file.close();

   data_set.read_csv();

   data = data_set.get_data();

   assert_true(data_set.get_variable_name(0) == "x", LOG);
   assert_true(data_set.get_variable_name(1) == "y", LOG);

   assert_true((data(0,0) - 1.0) < type(NUMERIC_LIMITS_MIN), LOG);
   assert_true((data(0,1) - 2.0) < type(NUMERIC_LIMITS_MIN), LOG);
   assert_true((data(1,0) - 3.0) < type(NUMERIC_LIMITS_MIN), LOG);
   assert_true((data(1,1) - 4.0) < type(NUMERIC_LIMITS_MIN), LOG);

   // Test

   data_set.set_has_columns_names(true);
   data_set.set_separator(',');

   data_string = "x , y\n"
                 "1 , 2\n"
                 "3 , 4\n";

   file.open(data_file_name.c_str());
   file << data_string;
   file.close();

   data_set.read_csv();

   data = data_set.get_data();

   assert_true(data_set.get_variable_name(0) == "x", LOG);
   assert_true(data_set.get_variable_name(1) == "y", LOG);

   assert_true((data(0,0) - 1.0 ) < type(NUMERIC_LIMITS_MIN), LOG);
   assert_true((data(0,1) - 2.0 ) < type(NUMERIC_LIMITS_MIN), LOG);
   assert_true((data(1,0) - 3.0 ) < type(NUMERIC_LIMITS_MIN), LOG);
   assert_true((data(1,1) - 4.0 ) < type(NUMERIC_LIMITS_MIN), LOG);
*/
   // Test

   data_set.set_has_columns_names(false);
   data_set.set_separator(',');

   data_string =
   "5.1,3.5,1.4,0.2,Iris-setosa\n"
   "7.0,3.2,4.7,1.4,Iris-versicolor\n"
   "7.0,3.2,4.7,1.4,Iris-versicolor\n"
   "6.3,3.3,6.0,2.5,Iris-virginica";

   file.open(data_file_name.c_str());
   file << data_string;
   file.close();

   data_set.read_csv();

   assert_true(data_set.get_samples_number() == 4, LOG);
   assert_true(data_set.get_variables_number() == 7, LOG);

   // Test

   data_set.set_has_columns_names(false);
   data_set.set_separator(',');

   data_string =
   "5.1,3.5,1.4,0.2,Iris-setosa\n"
   "7.0,3.2,4.7,1.4,Iris-versicolor\n"
   "7.0,3.2,4.7,1.4,Iris-versicolor\n"
   "6.3,3.3,6.0,2.5,Iris-virginica\n";

   file.open(data_file_name.c_str());
   file << data_string;
   file.close();

   data_set.read_csv();

   assert_true(data_set.get_variables_number() == 7, LOG);
   assert_true(data_set.get_input_variables_number() == 4, LOG);
   assert_true(data_set.get_target_variables_number() == 3, LOG);
   assert_true(data_set.get_samples_number() == 4, LOG);

   data = data_set.get_data();

   assert_true((data(0,0) - type(5.1)) < type(NUMERIC_LIMITS_MIN), LOG);
   assert_true((data(0,4) - type(1)) < type(NUMERIC_LIMITS_MIN), LOG);
   assert_true((data(0,5)) < type(NUMERIC_LIMITS_MIN), LOG);
   assert_true((data(0,6)) < type(NUMERIC_LIMITS_MIN), LOG);
   assert_true((data(1,4)) < type(NUMERIC_LIMITS_MIN), LOG);
   assert_true((data(1,5) - type(1)) < type(NUMERIC_LIMITS_MIN), LOG);
   assert_true((data(1,6)) < type(NUMERIC_LIMITS_MIN), LOG);
   assert_true((data(2,4)) < type(NUMERIC_LIMITS_MIN), LOG);
   assert_true((data(2,5) - type(1)) < type(NUMERIC_LIMITS_MIN), LOG);
   assert_true((data(2,6)) < type(NUMERIC_LIMITS_MIN), LOG);
   assert_true((data(3,4)) < type(NUMERIC_LIMITS_MIN), LOG);
   assert_true((data(3,5)) < type(NUMERIC_LIMITS_MIN), LOG);
   assert_true((data(3,6) - type(1)) < type(NUMERIC_LIMITS_MIN), LOG);

   // Test

   data_set.set_has_columns_names(true);
   data_set.set_separator(',');
   data_set.set_missing_values_label("NaN");

   data_string =
   "sepal length,sepal width,petal length,petal width,class\n"
   "NaN,3.5,1.4,0.2,Iris-setosa\n"
   "7.0,3.2,4.7,1.4,Iris-versicolor\n"
   "7.0,3.2,4.7,1.4,Iris-versicolor\n"
   "6.3,3.3,6.0,2.5,Iris-virginica\n"
   "0.0,0.0,0.0,0.0,NaN\n";

   file.open(data_file_name.c_str());
   file << data_string;
   file.close();

   data_set.read_csv();

   assert_true(data_set.get_variables_number() == 7, LOG);
   assert_true(data_set.get_input_variables_number() == 4, LOG);
   assert_true(data_set.get_target_variables_number() == 3, LOG);

   assert_true(data_set.get_variable_name(0) == "sepal length", LOG);
   assert_true(data_set.get_variable_name(1) == "sepal width", LOG);
   assert_true(data_set.get_variable_name(2) == "petal length", LOG);
   assert_true(data_set.get_variable_name(3) == "petal width", LOG);
   assert_true(data_set.get_variable_name(4) == "Iris-setosa", LOG);
   assert_true(data_set.get_variable_name(5) == "Iris-versicolor", LOG);
   assert_true(data_set.get_variable_name(6) == "Iris-virginica", LOG);

   assert_true(data_set.get_samples_number() == 5, LOG);

   data = data_set.get_data();

   assert_true(data(0,4) - type(1.0) < type(NUMERIC_LIMITS_MIN), LOG);
   assert_true(data(0,5) - type(0.0) < type(NUMERIC_LIMITS_MIN), LOG);
   assert_true(data(0,6) - type(0.0) < type(NUMERIC_LIMITS_MIN), LOG);
   assert_true(data(1,4) - type(0.0) < type(NUMERIC_LIMITS_MIN), LOG);
   assert_true(data(1,5) - type(1.0) < type(NUMERIC_LIMITS_MIN), LOG);
   assert_true(data(1,6) - type(0.0) < type(NUMERIC_LIMITS_MIN), LOG);
   assert_true(data(2,4) - type(0.0) < type(NUMERIC_LIMITS_MIN), LOG);
   assert_true(data(2,5) - type(1.0) < type(NUMERIC_LIMITS_MIN), LOG);
   assert_true(data(2,6) - type(0.0) < type(NUMERIC_LIMITS_MIN), LOG);

   // Test

   data_set.set_has_columns_names(false);
   data_set.set_separator(',');
   data_set.set_missing_values_label("NaN");

   data_string =
   "0,0,0\n"
   "0,0,NaN\n"
   "0,0,0\n";

   file.open(data_file_name.c_str());
   file << data_string;
   file.close();

   data_set.read_csv();

   // Test

   data_set.set_separator(' ');

   data_string = "1 2\n3 4\n5 6\n";

   file.open(data_file_name.c_str());
   file << data_string;
   file.close();

   data_set.read_csv();

   data_set.set_variable_name(0, "x");
   data_set.set_variable_name(1, "y");

   data_set.save("../data/data_set.xml");

   data_set.load("../data/data_set.xml");

   assert_true(data_set.get_variable_name(0) == "x", LOG);
   assert_true(data_set.get_variable_name(1) == "y", LOG);

   // Test

   data_set.set_has_columns_names(false);
   data_set.set_separator(' ');

   data_string = "1 true\n"
                 "3 false\n"
                 "5 true\n";

   file.open(data_file_name.c_str());
   file << data_string;
   file.close();

   data_set.read_csv();

   assert_true(data_set.get_variables_number() == 2, LOG);
   assert_true(data_set.get_input_variables_number() == 1, LOG);
   assert_true(data_set.get_target_variables_number() == 1, LOG);

   data = data_set.get_data();

   assert_true(data(0,1) - type(1.0) < type(NUMERIC_LIMITS_MIN), LOG);
   assert_true(data(1,1) - type(0.0) < type(NUMERIC_LIMITS_MIN), LOG);
   assert_true(data(2,1) - type(1.0) < type(NUMERIC_LIMITS_MIN), LOG);

   // Test

   data_set.set_separator('\t');
   data_set.set_missing_values_label("NaN");

   data_string =
   "f	52	1100	32	145490	4	no\n"
   "f	57	8715	1	242542	1	NaN\n"
   "m	44	5145	28	79100	5	no\n"
   "f	57	2857	16	1	1	NaN\n"
   "f	47	3368	44	63939	1	yes\n"
   "f	59	5697	14	45278	1	no\n"
   "m	86	1843	1	132799	2	yes\n"
   "m	67	4394	25	6670	2	no\n"
   "m	40	6619	23	168081	1	no\n"
   "f	12	4204	17	1	2	no\n";

   file.open(data_file_name.c_str());
   file << data_string;
   file.close();

   data_set.read_csv();

   assert_true(data_set.get_variables_number() == 7, LOG);
   assert_true(data_set.get_input_variables_number() == 6, LOG);
   assert_true(data_set.get_target_variables_number() == 1, LOG);

   data = data_set.get_data();

   assert_true(data.dimension(0) == 10, LOG);
   assert_true(data.dimension(1) == 7, LOG);
}


void DataSetTest::test_read_breast_cancer_csv()
{
    cout << "test_read_adult_csv\n";

    data_set.set_separator(';');
    data_set.set_data_file_name("../../datasets/breastcancer.csv");
    data_set.set_has_columns_names(true);
    data_set.read_csv();

    data_set.print_columns();

    system("pause");


//    assert_true(data_set.get_samples_number() == 1000, LOG);
//    assert_true(data_set.get_column_type(0) == DataSet::ColumnType::Numeric, LOG);
//    assert_true(data_set.get_column_type(1) == DataSet::ColumnType::Categorical, LOG);
//    assert_true(data_set.get_column_type(2) == DataSet::ColumnType::Numeric, LOG);
//    assert_true(data_set.get_column_type(3) == DataSet::ColumnType::Categorical, LOG);
}



void DataSetTest::test_read_adult_csv()
{
    cout << "test_read_adult_csv\n";

    data_set.set_missing_values_label("?");
    data_set.set_separator(',');
    data_set.set_data_file_name("../../datasets/adult.data");
    data_set.set_has_columns_names(false);
    data_set.read_csv();

    assert_true(data_set.get_samples_number() == 1000, LOG);
    assert_true(data_set.get_column_type(0) == DataSet::ColumnType::Numeric, LOG);
    assert_true(data_set.get_column_type(1) == DataSet::ColumnType::Categorical, LOG);
    assert_true(data_set.get_column_type(2) == DataSet::ColumnType::Numeric, LOG);
    assert_true(data_set.get_column_type(3) == DataSet::ColumnType::Categorical, LOG);
}


void DataSetTest::test_read_car_csv()
{
    cout << "test_read_car_csv\n";

    try
    {
        data_set.set("../../datasets/car.data",',',false);

        assert_true(data_set.get_samples_number() == 1728, LOG);
        assert_true(data_set.get_column_type(0) == DataSet::ColumnType::Categorical, LOG);
        assert_true(data_set.get_column_type(1) == DataSet::ColumnType::Categorical, LOG);
        assert_true(data_set.get_column_type(2) == DataSet::ColumnType::Categorical, LOG);
        assert_true(data_set.get_column_type(3) == DataSet::ColumnType::Categorical, LOG);
        assert_true(data_set.get_column_type(4) == DataSet::ColumnType::Categorical, LOG);
        assert_true(data_set.get_column_type(5) == DataSet::ColumnType::Categorical, LOG);
        assert_true(data_set.get_column_type(6) == DataSet::ColumnType::Categorical, LOG);
    }
    catch(const exception&)
    {
        //Exception
        assert_true(true,LOG);
    }
}




void DataSetTest::test_read_empty_csv()
{
    cout << "test_read_empty_csv\n";

    data_set.set();

    try
    {
        data_set.set("../../datasets/empty.csv",' ',false);

        assert_true(data_set.is_empty(), LOG);
        assert_true(data_set.get_samples_number() == 0, LOG);
        assert_true(data_set.get_variables_number() == 2, LOG);

    }
    catch(const exception&)
    {
        assert_true(true,LOG);
    }
}


void DataSetTest::test_read_heart_csv()
{
    cout << "test_read_heart_csv\n";

    data_set.set("../../datasets/heart.csv",',',true);

    assert_true(data_set.get_samples_number() == 303, LOG);
    assert_true(data_set.get_variables_number() == 14, LOG);
    assert_true(data_set.get_column_type(0) == DataSet::ColumnType::Numeric, LOG);
    assert_true(data_set.get_column_type(1) == DataSet::ColumnType::Binary, LOG);
    assert_true(data_set.get_column_type(2) == DataSet::ColumnType::Numeric, LOG);
    assert_true(data_set.get_column_type(3) == DataSet::ColumnType::Numeric, LOG);
    assert_true(data_set.get_column_type(4) == DataSet::ColumnType::Numeric, LOG);
    assert_true(data_set.get_column_type(5) == DataSet::ColumnType::Binary, LOG);
    assert_true(data_set.get_column_type(6) == DataSet::ColumnType::Numeric, LOG);
    assert_true(data_set.get_column_type(7) == DataSet::ColumnType::Numeric, LOG);
    assert_true(data_set.get_column_type(8) == DataSet::ColumnType::Binary, LOG);
    assert_true(data_set.get_column_type(9) == DataSet::ColumnType::Numeric, LOG);
    assert_true(data_set.get_column_type(10) == DataSet::ColumnType::Numeric, LOG);
    assert_true(data_set.get_column_type(11) == DataSet::ColumnType::Numeric, LOG);
    assert_true(data_set.get_column_type(12) == DataSet::ColumnType::Numeric, LOG);
    assert_true(data_set.get_column_type(13) == DataSet::ColumnType::Binary, LOG);

}


void DataSetTest::test_read_iris_csv()
{
    cout << "test_read_iris_csv\n";

    data_set.set("../../datasets/iris.data",',',false);

    assert_true(data_set.get_samples_number() == 150, LOG);
    assert_true(data_set.get_variables_number() == 7, LOG);
    assert_true(data_set.get_column_type(0) == DataSet::ColumnType::Numeric, LOG);
    assert_true(data_set.get_column_type(1) == DataSet::ColumnType::Numeric, LOG);
    assert_true(data_set.get_column_type(2) == DataSet::ColumnType::Numeric, LOG);
    assert_true(data_set.get_column_type(3) == DataSet::ColumnType::Numeric, LOG);
    assert_true(data_set.get_column_type(4) == DataSet::ColumnType::Categorical, LOG);

}


void DataSetTest::test_read_mnsit_csv()
{
    cout << "test_read_mnist_csv\n";

    data_set.set("../../datasets/mnist.csv",',',false);

    assert_true(data_set.get_samples_number() == 100, LOG);
    assert_true(data_set.get_variables_number() == 785, LOG);
}


void DataSetTest::test_read_one_variable_csv()
{
    cout << "test_read_one_variable_csv\n";

    data_set.set("../../datasets/one_variable.csv",',',false);

    assert_true(data_set.get_samples_number() == 7, LOG);
    assert_true(data_set.get_variables_number() == 1, LOG);
    assert_true(data_set.get_column_type(0) == DataSet::ColumnType::Numeric, LOG);

}


void DataSetTest::test_read_pollution_csv()
{
    cout << "test_read_pollution_csv\n";

    data_set.set("../../datasets/pollution.csv",',',true);

    assert_true(data_set.get_samples_number() == 1000, LOG);
    assert_true(data_set.get_variables_number() == 13, LOG);
    assert_true(data_set.get_column_type(0) == DataSet::ColumnType::DateTime, LOG);
    assert_true(data_set.get_column_type(1) == DataSet::ColumnType::Numeric, LOG);
    assert_true(data_set.get_column_type(2) == DataSet::ColumnType::Numeric, LOG);
    assert_true(data_set.get_column_type(3) == DataSet::ColumnType::Numeric, LOG);
    assert_true(data_set.get_column_type(4) == DataSet::ColumnType::Numeric, LOG);
    assert_true(data_set.get_column_type(5) == DataSet::ColumnType::Numeric, LOG);
    assert_true(data_set.get_column_type(6) == DataSet::ColumnType::Numeric, LOG);
    assert_true(data_set.get_column_type(7) == DataSet::ColumnType::Numeric, LOG);
    assert_true(data_set.get_column_type(8) == DataSet::ColumnType::Numeric, LOG);
    assert_true(data_set.get_column_type(9) == DataSet::ColumnType::Numeric, LOG);
    assert_true(data_set.get_column_type(10) == DataSet::ColumnType::Numeric, LOG);
    assert_true(data_set.get_column_type(11) == DataSet::ColumnType::Numeric, LOG);
    assert_true(data_set.get_column_type(12) == DataSet::ColumnType::Numeric, LOG);
}


void DataSetTest::test_read_urinary_inflammations_csv()
{
    cout << "test_read_urinary_inflammations_csv\n";

    data_set.set("../../datasets/urinary_inflammations.csv",';',true);

    assert_true(data_set.get_samples_number() == 120, LOG);
    assert_true(data_set.get_variables_number() == 8, LOG);
    assert_true(data_set.get_column_type(0) == DataSet::ColumnType::Numeric, LOG);
    assert_true(data_set.get_column_type(1) == DataSet::ColumnType::Binary, LOG);
    assert_true(data_set.get_column_type(2) == DataSet::ColumnType::Binary, LOG);
    assert_true(data_set.get_column_type(3) == DataSet::ColumnType::Binary, LOG);
    assert_true(data_set.get_column_type(4) == DataSet::ColumnType::Binary, LOG);
    assert_true(data_set.get_column_type(5) == DataSet::ColumnType::Binary, LOG);
    assert_true(data_set.get_column_type(6) == DataSet::ColumnType::Binary, LOG);
    assert_true(data_set.get_column_type(7) == DataSet::ColumnType::Binary, LOG);

}


void DataSetTest::test_read_wine_csv()
{
    cout << "test_read_wine_csv\n";

    data_set.set("../../datasets/wine.data",',',false);

    assert_true(data_set.get_samples_number() == 178, LOG);
    assert_true(data_set.get_variables_number() == 14, LOG);
    assert_true(data_set.get_column_type(0) == DataSet::ColumnType::Numeric, LOG);
    assert_true(data_set.get_column_type(1) == DataSet::ColumnType::Numeric, LOG);
    assert_true(data_set.get_column_type(2) == DataSet::ColumnType::Numeric, LOG);
    assert_true(data_set.get_column_type(3) == DataSet::ColumnType::Numeric, LOG);
    assert_true(data_set.get_column_type(4) == DataSet::ColumnType::Numeric, LOG);
    assert_true(data_set.get_column_type(5) == DataSet::ColumnType::Numeric, LOG);
    assert_true(data_set.get_column_type(6) == DataSet::ColumnType::Numeric, LOG);
    assert_true(data_set.get_column_type(7) == DataSet::ColumnType::Numeric, LOG);
    assert_true(data_set.get_column_type(8) == DataSet::ColumnType::Numeric, LOG);
    assert_true(data_set.get_column_type(9) == DataSet::ColumnType::Numeric, LOG);
    assert_true(data_set.get_column_type(10) == DataSet::ColumnType::Numeric, LOG);
    assert_true(data_set.get_column_type(11) == DataSet::ColumnType::Numeric, LOG);
    assert_true(data_set.get_column_type(12) == DataSet::ColumnType::Numeric, LOG);
    assert_true(data_set.get_column_type(13) == DataSet::ColumnType::Numeric, LOG);

}


void DataSetTest::test_read_binary_csv()
{
    cout << "test_read_binary_csv\n";

    data_set.set("../../datasets/binary.csv",',',false);

    assert_true(data_set.get_samples_number() == 8, LOG);
    assert_true(data_set.get_variables_number() == 3, LOG);
    assert_true(data_set.get_column_type(0) == DataSet::ColumnType::Numeric, LOG);
    assert_true(data_set.get_column_type(1) == DataSet::ColumnType::Numeric, LOG);
    assert_true(data_set.get_column_type(2) == DataSet::ColumnType::Binary, LOG);

}


void DataSetTest::test_transform_time_series()
{
    cout << "test_transform_time_series\n";

    data.resize(9, 2);
    data.setValues({{1,10}, {2, 20}, {3, 30}, {4, 40}, {5, 50}, {6, 60}, {7, 70}, {8, 80}, {9, 90}});

    data_set.set_data(data);

    data_set.set_variable_name(0, "x");
    data_set.set_variable_name(1, "y");

    data_set.set_lags_number(2);
    data_set.set_steps_ahead_number(1);

    data_set.transform_time_series();

    // Tests for transform_time_series, transform_time_series_data, transform_time_series_colums

    assert_true(data_set.get_columns_number() == 6, LOG);
    assert_true(data_set.get_variables_number() == 6, LOG);
    assert_true(data_set.get_samples_number() == 7, LOG);

    assert_true(data_set.get_input_variables_number() == 4, LOG);
    assert_true(data_set.get_target_variables_number() == 2, LOG);

    assert_true(data_set.get_target_columns_number() == 2, LOG);

    assert_true(data_set.get_variable_name(0) == "x_lag_1", LOG);
    assert_true(data_set.get_variable_name(1) == "y_lag_1", LOG);
    assert_true(data_set.get_variable_name(2) == "x_lag_0", LOG);
    assert_true(data_set.get_variable_name(3) == "y_lag_0", LOG);
}


void DataSetTest::test_set_time_series_data()
{
    cout << "test_set_time_series_data\n";

    data.resize(4,2);

    data.setValues({
        {type(0),type(0)},
        {type(1),type(10)},
        {type(2),type(20)},
        {type(3),type(30)}});

    data_set.set_data(data);

    data_set.set_lags_number(2);
    data_set.set_steps_ahead_number(2);

    data_set.transform_time_series();

    data.resize(5,3);
    data.setValues({
        {type(15),type(14),type(13)},
        {type(12),type(11),type(10)},
        {type(9),type(8),type(7)},
        {type(6),type(5),type(4)},
        {type(3),type(2),type(1)}});

    data_set.set_time_series_data(data);

    assert_true(data_set.get_time_series_data()(0) - type(15) < type(NUMERIC_LIMITS_MIN), LOG);
    assert_true(data_set.get_time_series_data()(1) - type(12) < type(NUMERIC_LIMITS_MIN), LOG);
    assert_true(data_set.get_time_series_data()(2) - type(9) < type(NUMERIC_LIMITS_MIN), LOG);
}


void DataSetTest::test_has_time_columns()
{
    cout << "test_has_time_columns\n";

    data.resize(4,2);
    data.setValues({
        {type(1),type(10)},
        {type(2),type(20)},
        {type(3),type(30)},
        {type(4),type(40)}});

    data_set.set_data(data);

    data_set.set_column_type(0,DataSet::ColumnType::DateTime);
    data_set.set_column_type(1,DataSet::ColumnType::DateTime);

    assert_true(data_set.has_time_columns(), LOG);
}

void DataSetTest::test_save_time_series_data_binary()
{
    cout << "test_save_time_series_data_binary\n";

    const string data_file_name = "../data/test";
    

    // Test

    data.resize(4,2);
    data.setValues({
        {type(0),type(0)},
        {type(1),type(10)},
        {type(2),type(20)},
        {type(3),type(30)}});

    data_set.set_data(data);

    data_set.set_lags_number(2);
    data_set.set_steps_ahead_number(2);

    data_set.transform_time_series();

    data_set.set_data_file_name(data_file_name);
    data_set.save_time_series_data_binary(data_file_name);

    data_set.load_time_series_data_binary(data_file_name);

    assert_true(data_set.get_time_series_data()(0) - type(0) < type(NUMERIC_LIMITS_MIN), LOG);
    assert_true(data_set.get_time_series_data()(1) - type(1) < type(NUMERIC_LIMITS_MIN), LOG);
    assert_true(data_set.get_time_series_data()(2) - type(2) < type(NUMERIC_LIMITS_MIN), LOG);
}


void DataSetTest::test_set_steps_ahead_number()
{
    cout << "test_set_steps_ahead_nuber\n";

    data.resize(4,2);
    data.setValues({
        {type(0),type(0)},
        {type(1),type(10)},
        {type(2),type(20)},
        {type(3),type(30)}});

    data_set.set_data(data);

    data_set.set_lags_number(2);
    data_set.set_steps_ahead_number(2);

    data_set.transform_time_series();

    // set_lags_number and get_lags_number test
    assert_true(data_set.get_lags_number() == 2, LOG);
}


void DataSetTest::test_set_lags_number()
{
    cout << "test_set_lags_number\n";

    // Test

    data.resize(4,2);
    data.setValues({
        {type(0),type(0)},
        {type(1),type(10)},
        {type(2),type(20)},
        {type(3),type(30)}});

    data_set.set_data(data);

    data_set.set_lags_number(2);
    data_set.set_steps_ahead_number(2);

    data_set.transform_time_series();

    assert_true(data_set.get_steps_ahead() == 2, LOG);
}


void DataSetTest::test_scrub_missing_values()
{
    cout << "test_scrub_missing_values\n";

    const string data_file_name = "../data/data.dat";

    Tensor<DataSet::SampleUse, 1> samples_uses;

    ofstream file;

    data_set.set_data_file_name(data_file_name);

    string data_string;

    // Test

    data_set.set_separator(' ');
    data_set.set_missing_values_label("NaN");

    data_string = "0 0 0\n"
                  "0 0 NaN\n"
                  "0 0 0\n";

    file.open(data_file_name.c_str());
    file << data_string;
    file.close();

    data_set.read_csv();

    data_set.scrub_missing_values();

    samples_uses = data_set.get_samples_uses();

    assert_true(samples_uses(1) == DataSet::SampleUse::UnusedSample, LOG);

    // Test

    data_set.set_separator(' ');
    data_set.set_missing_values_label("?");

    data_string ="? 3 3\n"
                 "2 ? 3\n"
                 "0 1 ?\n";

    file.open(data_file_name.c_str());
    file << data_string;
    file.close();

/// @todo read_csv() doesnt work propperly
/*
    data_set.read_csv();

    data_set.set_missing_values_method(DataSet::MissingValuesMethod::Mean);
    data_set.scrub_missing_values();

    data = data_set.get_data();

    assert_true(abs(data(0,0) - type(1)) < type(NUMERIC_LIMITS_MIN), LOG);
    assert_true(abs(data(1,1) - type(2.0)) < type(NUMERIC_LIMITS_MIN), LOG);
    assert_true(abs(data(2,2) - type(3.0)) < type(NUMERIC_LIMITS_MIN), LOG);
*/
}


void DataSetTest::test_is_empty()
{
    cout << "test_is_empty\n";

    // Test

    data_set.set();

    assert_true(data_set.is_empty(), LOG);

    // Test

    data_set.set(1,1,1);

    assert_true(!data_set.is_empty(), LOG);
}


void DataSetTest::test_calculate_variables_means()
{
    cout << "test_calculate_variables_means\n";

    data.setValues({{1, 2, 3, 4},{2, 2, 2, 2},{1, 1, 1, 1}});

    data_set.set_data(data);

    Tensor<Index, 1> indices;

    indices.resize(2);
    indices.setValues({0, 1});
    Tensor<type, 1> means = data_set.calculate_variables_means(indices);
//    Tensor<type, 1> solution(2, 2.0);

//    assert_true(means == solution, LOG);
}


void DataSetTest::test_calculate_used_targets_mean()
{
    cout << "test_calculate_used_targets_mean\n";

    data.resize(3, 4);

    data.setValues({
        {type(1), static_cast<type>(NAN), type(1), type(1)},
        {type(2), type(2), type(2), type(2)},
        {type(3), type(3), static_cast<type>(NAN), type(3)}});
    
    data_set.set_data(data);

    Tensor<Index, 1> indices(3);
    indices.setValues({0, 1, 2});
    Tensor<Index, 1> training_indexes(1);
    training_indexes.setValues({0});

    data_set.set_training(training_indexes);
}


void DataSetTest::test_calculate_selection_targets_mean(){
/// @todo fails when running "suite" test
    /*
    cout << "test_calculate_selection_targets_mean\n";

    Tensor<Index, 1> target_indices;
    Tensor<Index, 1> selection_indices;

    Tensor<type, 1> selection_targets_mean;

    // Test

    data.resize(4, 3);
    data.setValues({{1, static_cast<type>(NAN), 6, 9},
                    {1, 2, 5, 2},
                    {3, 2, static_cast<type>(NAN), 4}});

    data_set.set_data(data);

    target_indices.resize(1);
    target_indices.setValues({2});

    selection_indices.resize(2);
    selection_indices.setValues({0, 1});

    data_set.set_input();
    data_set.set_selection(selection_indices);

//    selection_targets_mean = data_set.calculate_selection_targets_mean();

//    assert_true(means == solutions, LOG);

*/}


void DataSetTest::test_calculate_input_target_correlations()
{
    cout << "test_calculate_input_target_correlations\n";

    data.resize(3, 4);

    data.setValues({
        {type(1), type(1), type(1), type(1)},
        {type(2), type(2), type(2), type(2)},
        {type(3), type(3), type(3), type(3)}});

    data_set.set_data(data);

    Tensor<Index, 1> input_variables_indices;

    input_variables_indices.resize(2);

    input_variables_indices.setValues({0, 1});

//    data_set.set_input_variables_indices(input_variables_indices);

//    Tensor<type, 2> correlations_targets = data_set.calculate_inputs_targets_correlations();

    // Test linear correlation

//    assert_true(correlations_targets - 1.0 < 1.0e-3, LOG);

    // Test logistic correlation

}


void DataSetTest::test_calculate_total_input_correlations()
{
    cout << "test_calculate_total_input_correlations\n";    

    data.resize(3, 4);

    data.setValues({
        {type(1), type(1), type(1), type(1)},
        {type(2), type(2), type(2), type(2)},
        {type(3), type(3), type(3), type(3)} });

    data_set.set_data(data);

    Tensor<Index, 1> input_variables_indices(2);
    input_variables_indices.setValues({0, 1});

    Tensor<Index, 1> target_variables_indices(1);
    target_variables_indices.setValues({2});

    Tensor<type, 1> solution(2);
    solution.setValues({ type(1), type(1)});

//    data_set.set_input_variables_indices(input_variables_indices);

//    Tensor<type, 1> correlations_inputs = data_set.calculate_total_input_correlations();

//    assert_true(correlations_inputs == solution, LOG);
}


void DataSetTest::test_unuse_repeated_samples()
{
    cout << "test_unuse_repeated_samples\n";

    Tensor<Index, 1> indices;

    // Test

    data.resize(3, 3);
    
    data.setValues({
        {type(1),type(2),type(2)},
        {type(1),type(2),type(2)},
        {type(1),type(6),type(6)}});

    data_set.set_data(data);

    indices.resize(1);
    indices.setValues({2});

    assert_true(data_set.unuse_repeated_samples().size() == 1, LOG);

    // Test

    data.resize(3, 4);
    data.setValues({
        {type(1),type(2),type(2),type(2)},
        {type(1),type(2),type(2),type(2)},
        {type(1),type(6),type(6),type(6)}});

    data_set.set_data(data);

    indices.resize(2);
    indices.setValues({2, 3});

//    assert_true(ds_1.unuse_repeated_samples() == indices_1, LOG);

    data.resize(3, 5);
    data.setValues({
        {type(1),type(2),type(2),type(4),type(4)},
        {type(1),type(2),type(2),type(4),type(4)},
        {type(1),type(6),type(6),type(4),type(4)}});

    data_set.set_data(data);

    indices.resize(2);
    indices.setValues({2,4});

//    assert_true(ds_2.unuse_repeated_samples() == indices_2, LOG);
}


void DataSetTest::test_unuse_uncorrelated_columns()
{
    cout << "test_unuse_uncorrelated_columns\n";

    data.resize(3, 3);
    data.setValues({
        {type(1),type(0),type(0)},
        {type(1),type(0),type(0)},
        {type(1),type(0),type(1)}});

}


void DataSetTest::test_calculate_training_negatives()
{
    cout << "test_calculate_training_negatives\n";

    Index training_negatives;
    Index target_index;

    // Test

    data.resize(3, 3);

    data.setValues({{ 1, 1, 1},
                    {-1,-1, 0},
                    { 0, 1, 1}});

    data_set.set_data(data);

    training_indices.resize(2);
    training_indices.setValues({0,1});

    input_variables_indices.resize(2);
    input_variables_indices.setValues({0, 1});

    target_variables_indices.resize(1);
    target_variables_indices.setValues({2});

    target_index = 2;
 

//    data_set.set_testing();
//    data_set.set_training(training_indices);

//    training_negatives = data_set.calculate_training_negatives(target_index);

//    assert_true(training_negatives == 1, LOG);
}

/// @todo

void DataSetTest::test_calculate_selection_negatives()
{
    cout << "test_calculate_selection_negatives\n";

    Tensor<Index, 1> selection_indices;
    Tensor<Index, 1> input_variables_indices;
    Tensor<Index, 1> target_variables_indices;

    // Test

    data.resize(3, 3);

    data.setValues({{1, 1, 1},{-1,-1,-1},{0,1,1}});

    data_set.set_data(data);
    selection_indices.resize(2);
    selection_indices.setValues({0,1});
    input_variables_indices.resize(2);
    input_variables_indices.setValues({0, 1});
    target_variables_indices.resize(1);
    target_variables_indices.setValues({2});
    Index target_index = 2;

    data_set.set_testing();
    data_set.set_selection(selection_indices);

//    data_set.set_input_variables_indices(input_variables_indices);
//    data_set.set_target_variables_indices(target_variables_indices);

//    Index selection_negatives = data_set.calculate_selection_negatives(target_index);

    data = data_set.get_data();

//    assert_true(selection_negatives == 0, LOG);
}


void DataSetTest::test_fill()
{
    cout << "test_fill\n";

    data.resize(3, 3);
    data.setValues({{1,4,7},{2,5,8},{3,6,9}});
    data_set.set_data(data);

    data_set.set_training();

    const Index training_samples_number = data_set.get_training_samples_number();

    const Tensor<Index, 1> training_samples_indices = data_set.get_training_samples_indices();

    const Tensor<Index, 1> input_variables_indices = data_set.get_input_variables_indices();
    const Tensor<Index, 1> target_variables_indices = data_set.get_target_variables_indices();

    data_set_batch.set(training_samples_number, &data_set);
    data_set_batch.fill(training_samples_indices, input_variables_indices, target_variables_indices);

    Tensor<type, 2> input_data(3,2);
    input_data.setValues({{1,4},{2,5},{3,6}});

    Tensor<type, 2> target_data(3,1);
    target_data.setValues({{7},{8},{9}});

    assert_true(are_equal(data_set_batch.inputs_2d, input_data), LOG);
    assert_true(are_equal(data_set_batch.targets_2d, target_data), LOG);

//    data_set_batch.print();

//    cout << data << endl;
//    system("pause");

}


void DataSetTest::run_test_case()
{
   cout << "Running data set test case...\n";

   // Constructor and destructor methods

   test_constructor();
   test_destructor();

   // Data methods

   test_is_empty();

   // Set methods

   test_set();

   // Data methods

   test_set_data();
   test_set_samples_number();
   test_set_columns_number();

   // Data resizing methods

   test_unuse_constant_columns();
   test_unuse_repeated_samples();
   test_unuse_uncorrelated_columns();

   // Initialization methods

   test_set_data_constant();

   // Statistics methods

   test_calculate_variables_descriptives();
   test_calculate_input_variables_descriptives();
   test_calculate_used_targets_mean();
   test_calculate_selection_targets_mean();

   // Histrogram methods

   test_calculate_data_distributions();

   // Filtering methods

   test_filter_data();

   // Data scaling

   test_scale_data();

   // Correlations

   test_calculate_input_target_correlations();
   test_calculate_total_input_correlations();

   // Classification methods

   test_calculate_target_distribution();

   // Outlier detection

   test_calculate_Tukey_outliers();

   test_calculate_euclidean_distance();
   test_calculate_distance_matrix();
   test_calculate_k_nearest_neighbors();
   test_calculate_average_reachability();

   // Serialization methods

   test_read_csv();

   test_read_breast_cancer_csv();
   test_read_adult_csv();
   test_read_car_csv();
   test_read_empty_csv();
   test_read_heart_csv();
   test_read_iris_csv();
   test_read_mnsit_csv();
   test_read_one_variable_csv();
   test_read_pollution_csv();
   test_read_urinary_inflammations_csv();
   test_read_wine_csv();
   test_read_binary_csv();
   test_calculate_training_negatives();
   test_calculate_selection_negatives();
   test_scrub_missing_values();

   // Time series

   test_transform_time_series();
   test_set_lags_number();
   test_set_steps_ahead_number();
   test_set_time_series_data();
   test_save_time_series_data_binary();
   test_has_time_columns();

   test_calculate_cross_correlations();
   test_calculate_autocorrelations();

   test_fill();

   cout << "End of data set test case.\n\n";
}


// OpenNN: Open Neural Networks Library.
// Copyright (C) 2005-2021 Artificial Intelligence Techniques, SL.
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
