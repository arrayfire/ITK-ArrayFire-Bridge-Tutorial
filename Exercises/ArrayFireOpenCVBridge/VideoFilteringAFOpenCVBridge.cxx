/*=========================================================================
 *
 *  Copyright Insight Software Consortium
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *         http://www.apache.org/licenses/LICENSE-2.0.txt
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 *=========================================================================*/
#include <iostream>

#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <itkImage.h>
#include <itkCastImageFilter.h>
#include <itkCannyEdgeDetectionImageFilter.h>
#include <itkRescaleIntensityImageFilter.h>
#include <itkOpenCVImageBridge.h>
#include <itkArrayFireImageBridge.h>

af::array sobelFilter(const af::array &in)
{
    af::array Gx, Gy;
    af::sobel(Gx, Gy, in.as(f32), 3);
    // Find magnitude and direction
    return af::hypot(Gx, Gy);
}

af::array normalize(const af::array &in)
{
    float mx = af::max<float>(in);
    float mn = af::min<float>(in);
    return (in-mn)/(mx-mn);
}

cv::Mat processFrame(const cv::Mat& inputImage)
{
    af::array in = itk::CVMatToArray(inputImage);

    af::array e = sobelFilter(in);
    af::array n = normalize(e);

    af::array disp = (n*255).as(u8);

    return itk::ArrayToCVMat(disp, true);
}

void processAndDisplayVideo(cv::VideoCapture& vidCap, int choice)
{
    const double frameRate = vidCap.get(CV_CAP_PROP_FPS);
    const int width        = vidCap.get(CV_CAP_PROP_FRAME_WIDTH);
    const int height       = vidCap.get(CV_CAP_PROP_FRAME_HEIGHT);

    const std::string windowName = "Basic Video Filtering Using ArrayFire/OpenCV";
    cv::namedWindow(windowName, CV_WINDOW_FREERATIO);
    cvResizeWindow(windowName.c_str(), width, height+50);

    const unsigned int delay = 1000 / frameRate;

    cv::Mat frame;
    while (vidCap.read(frame))
    {
        cv::Mat outputFrame = processFrame(frame);
        cv::imshow(windowName, outputFrame);

        if (cv::waitKey(delay) >= 0)
            break;
    }
}

int main ( int argc, char **argv )
{
    if (argc < 2) {
        std::cout << "Usage: " << argv[0] <<" input_video [0]" << std::endl;
        return EXIT_FAILURE;
    }

    cv::VideoCapture vidCap(argv[1]);
    if (!vidCap.isOpened()) {
        std::cerr << "Unable to open video file: "<< argv[1] << std::endl;
        return EXIT_FAILURE;
    }

    int filterLibraryChoice = argc < 3 ? 0 : atoi(argv[2]);

    try {
        processAndDisplayVideo(vidCap, filterLibraryChoice);
    } catch(itk::ExceptionObject & err) {
        std::cerr << "Error: " << err << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
