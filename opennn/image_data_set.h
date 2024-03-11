//   OpenNN: Open Neural Networks Library
//   www.opennn.net
//
//   I M A G E   D A T A S E T   C L A S S   H E A D E R
//
//   Artificial Intelligence Techniques SL
//   artelnics@artelnics.com

#ifndef IMAGEDATASET_H
#define IMAGEDATASET_H

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

// #include <filesystem>
//#include <experimental/filesystem>

// Filesystem namespace

// #ifdef __APPLE__
//  #include <Availability.h> // for deployment target to support pre-catalina targets without fs
// #endif
// #if((defined(_MSVC_LANG) && _MSVC_LANG >= 201703L) || (defined(__cplusplus) && __cplusplus >= 201703L)) && defined(__has_include)
// #if __has_include(<filesystem>) && (!defined(__MAC_OS_X_VERSION_MIN_REQUIRED) || __MAC_OS_X_VERSION_MIN_REQUIRED >= 101500)
// #define GHC_USE_STD_FS
// #include <filesystem>
// namespace fs = filesystem;
//  #endif
// #endif
//  #ifndef GHC_USE_STD_FS
//  #include "filesystem.h"
//  namespace fs = ghc::filesystem;
// #endif

// using namespace fs;

namespace opennn
{

class ImageDataSet : public DataSet
{

public:

    // DEFAULT CONSTRUCTOR

    explicit ImageDataSet();

    explicit ImageDataSet(const Index&, const Index&, const Index&, const Index&, const Index&);

    Index get_channels_number() const;
    Index get_image_width() const;
    Index get_image_height() const;
    Index get_image_padding() const;
    Index get_image_size() const;

    bool get_augmentation() const;
    bool get_random_reflection_axis_x() const;
    bool get_random_reflection_axis_y() const;
    type get_random_rotation_minimum() const;
    type get_random_rotation_maximum() const;
    type get_random_horizontal_translation_minimum() const;
    type get_random_horizontal_translation_maximum() const;
    type get_random_vertical_translation_minimum() const;
    type get_random_vertical_translation_maximum() const;

    void set(const Index&, const Index&, const Index&, const Index&, const Index&);

    void set_image_data_source_path(const string&);

    void set_channels_number(const int&);
    void set_image_width(const int&);
    void set_image_height(const int&);
    void set_image_padding(const int&);
    void set_images_number(const Index&);

    void set_augmentation(const bool&);
    void set_random_reflection_axis_x(const bool&);
    void set_random_reflection_axis_y(const bool&);
    void set_random_rotation_minimum(const type&);
    void set_random_rotation_maximum(const type&);
    void set_random_horizontal_translation_minimum(const type&);
    void set_random_horizontal_translation_maximum(const type&);
    void set_random_vertical_translation_minimum(const type&);
    void set_random_vertical_translation_maximum(const type&);

    void set_categories_number(const Index&);

    void fill_image_data(const string&, const vector<string>&, const vector<string>&, const vector<int>&, const int&, const int&, const int&, const Tensor<type, 2>&);

    void from_XML(const tinyxml2::XMLDocument&);
    void write_XML(tinyxml2::XMLPrinter&) const;

private:

    string image_data_source_path;

    Index images_number = 0;
    Index channels_number = 0;
    Index image_width = 0;
    Index image_height = 0;
    Index padding = 0;

    bool augmentation = false;
    bool random_reflection_axis_x = false;
    bool random_reflection_axis_y = false;
    type random_rotation_minimum = type(0);
    type random_rotation_maximum = type(0);
    type random_horizontal_translation_minimum = type(0);
    type random_horizontal_translation_maximum = type(0);
    type random_vertical_translation_minimum = type(0);
    type random_vertical_translation_maximum = type(0);

    Index categories_number = 0;

    Tensor<string, 1> labels_tokens;

    Index width_no_padding = 0;

    Index regions_number = 1000; // Number of region proposals per image
    Index region_rows = 6; // Final region width to warp
    Index region_raw_variables = 6; // Final region height to warp

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