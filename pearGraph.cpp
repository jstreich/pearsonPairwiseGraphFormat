/////////////////////////////////////////////////////////////////////
// This was drafted with ChatGPT, but debugged and edited by me
// Author: ChatGPT and jared Streich
// Calculates pearson values for all rows in a file in graph format
// Created 2023-02-19
// email: ju0@ornl.gov, or if not at ORNL streich.jared@gmail.com
// Version: 0.1.0
/////////////////////////////////////////////////////////////////////



/////////////////////////////////////////////////////////////////////
////////////////////////// Include Libraries ////////////////////////
/////////////////////////////////////////////////////////////////////

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <cmath>


using namespace std;


/////////////////////////////////////////////////////////////////////
///////////////////////////// Functions /////////////////////////////
/////////////////////////////////////////////////////////////////////


///// Pearson Cor Coef
double pearson(vector<double> x, vector<double> y) {
    double sum_x = 0, sum_y = 0, sum_xy = 0, sum_x2 = 0, sum_y2 = 0;
    int n = x.size();

    for (int i = 0; i < n; i++) {
        sum_x += x[i];
        sum_y += y[i];
        sum_xy += x[i] * y[i];
        sum_x2 += x[i] * x[i];
        sum_y2 += y[i] * y[i];
    }

    double numerator = n * sum_xy - sum_x * sum_y;
    double denominator = sqrt((n * sum_x2 - sum_x * sum_x) * (n * sum_y2 - sum_y * sum_y));
    return numerator / denominator;
}



/////////////////////////////////////////////////////////////////////
//////////////////////////// Start Script ///////////////////////////
/////////////////////////////////////////////////////////////////////


int main(int argc, char** argv) {
    ///// Arguments
    if (argc != 3) {
        cerr << "Usage: " << argv[0] << " input_file output_file" << endl;
        return 1;
    }

    ///// Open Input File
    ifstream infile(argv[1]);
    if (!infile) {
        cerr << "Unable to open file: " << argv[1] << endl;
        return 1;
    }

    ///// Define Output File
    ofstream outfile(argv[2]);
    if (!outfile) {
        cerr << "Unable to open file: " << argv[2] << endl;
        return 1;
    }

    ///// Read Input
    vector<vector<double>> data;
    vector<string> sample_names;
    string line;

    ///// Iterate across file rows
    while (getline(infile, line)) {
        vector<double> row;
        string sample_name;
        double value;

        ///// Parse lines
        istringstream iss(line);
        iss >> sample_name;
        while (iss >> value) {
            row.push_back(value);
        }

        /////// Actual Pearson Calc.
        for (int i = 0; i < data.size(); i++) {
            double p = pearson(row, data[i]);
            outfile << sample_name << "\t" << sample_names[i] << "\t" << p << endl;
        }

        ////// Append Data to Row
        data.push_back(row);
        sample_names.push_back(sample_name);
    }

    ////// Close Input and Output Files
    infile.close();
    outfile.close();

    return 0;
}
