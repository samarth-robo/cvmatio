/*
 * Software License Agreement (BSD License)
 *
 *  Copyright (c) 2012, Willow Garage, Inc.
 *  All rights reserved.
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *
 *   * Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *   * Redistributions in binary form must reproduce the above
 *     copyright notice, this list of conditions and the following
 *     disclaimer in the documentation and/or other materials provided
 *     with the distribution.
 *   * Neither the name of Willow Garage, Inc. nor the names of its
 *     contributors may be used to endorse or promote products derived
 *     from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 *  FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 *  COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 *  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 *  BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 *  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 *  CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 *  LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 *  ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 *  POSSIBILITY OF SUCH DAMAGE.
 *
 */

/*! \mainpage Matlab Mat File Parser for C++ OpenCV
 *
 * MatlabIO provides the ability to read .Mat files generated by Matlab
 * into C++ programs. MatlabIO stores matrices in the OpenCV cv::Mat format
 * and is intrinsically designed for computer vision research and applications,
 * though other fields may find use in the features it provides. It has a simple,
 * easy to use interface for parsing files, searching for particular variables
 * and extracting the data in OpenCV native formats.
 */

#include <string>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "MatlabIO.hpp"
#include "MatlabIOContainer.hpp"
using namespace cv;
using namespace std;

int main(int argc, char **argv) {

    // get the Matlab .Mat file from the command line
    string filename(argv[1]);

    // create a new reader
    MatlabIO matio;
    bool ok = matio.open(filename, "r");
    if (!ok) return -1;

    // read all of the variables in the file
    vector<MatlabIOContainer> variables;
    variables = matio.read();

    // close the file
    matio.close();

    // display the file info
    matio.whos(variables);

    // search for a variable named "im" and "gray"
    Mat gray;
    Mat im;
    for (int n = 0; n < variables.size(); ++n) {
    	if (variables[n].name().compare("im") == 0) {
    		im = variables[n].data<Mat>();
    		cvtColor(im, im, CV_RGB2BGR);
    	}
    	if (variables[n].name().compare("gray") == 0) {
    		gray = variables[n].data<Mat>();
    	}
    }

    imshow("im", gray);
    waitKey(0);
    return 0;
}