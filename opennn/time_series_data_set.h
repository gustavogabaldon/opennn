//   OpenNN: Open Neural Networks Library
//   www.opennn.net
//
//   T I M E   S E R I E S   D A T A S E T   C L A S S   H E A D E R        
//
//   Artificial Intelligence Techniques SL
//   artelnics@artelnics.com

#ifndef TIMESERIESDATASET_H
#define TIMESERIESDATASET_H

// System includes

#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
#include <limits>
#include <math.h>

// OpenNN includes

#include "config.h"
#include "data_set.h"

namespace opennn
{

class TimeSeriesDataSet : public DataSet
{

public:

   // DEFAULT CONSTRUCTOR

    explicit TimeSeriesDataSet();

    explicit TimeSeriesDataSet(const string&, const char&, const bool&, const Codification& = Codification::UTF8);

    void transform_time_series();
    void transform_time_series_raw_variables();
    void transform_time_series_data();
    void fill_time_series_gaps();

    Index get_time_series_data_rows_number() const;

    const Index& get_lags_number() const;
    const Index& get_steps_ahead() const;

    Index get_time_series_raw_variables_number() const;
    Tensor<RawVariable, 1> get_time_series_raw_variables() const;

    Index get_input_time_series_raw_variables_number() const;
    Index get_target_time_series_raw_variables_number() const;

    Tensor<Index, 1> get_input_time_series_raw_variables_indices() const;
    Tensor<Index, 1> get_target_time_series_raw_variables_indices() const;

    const string& get_time_column() const;

    void set_time_series_data(const Tensor<type, 2>&);
    void set_time_series_raw_variables_number(const Index&);

    Tensor<type, 2> get_time_series_raw_variable_data(const Index&) const;
    const string& get_group_by_column() const;

    void set_lags_number(const Index&);
    void set_steps_ahead_number(const Index&);

    void set_time_column(const string&);
    void set_group_by_column(const string&);

    Tensor<type, 2> calculate_autocorrelations(const Index& = 10) const;
    Tensor<type, 3> calculate_cross_correlations(const Index& = 10) const;

    void load_time_series_data_binary(const string&);

    void save_time_series_data_binary(const string&) const;

    Index get_time_series_variables_number() const;
    Tensor<string, 1> get_time_series_variables_names() const;

    const Tensor<type, 2>& get_time_series_data() const;

    void write_XML(tinyxml2::XMLPrinter&) const;
    void from_XML(const tinyxml2::XMLDocument&);

    Tensor<string, 1> get_time_series_raw_variables_names() const;

    Index get_time_series_time_raw_variable_index() const;

    void impute_missing_values_mean();

private:

    /// Number of lags.

    Index lags_number = 0;

    /// Number of steps ahead.

    Index steps_ahead = 0;

    /// Time series data matrix.
    /// The number of rows is the number of samples before time series transformation.
    /// The number of raw_variables is the number of variables before time series transformation.

    Tensor<type, 2> time_series_data;

    Tensor<RawVariable, 1> time_series_raw_variables;

    /// Index where time variable is located for forecasting applications.

    string time_column;

    Index time_variable_index;

    string group_by_column;

    Index group_by_raw_variable_index;

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