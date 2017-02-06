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

#include <arrayfire.h>
#include <iostream>
#include <string>

using namespace af;

af::array normalize(const af::array& in)
{
    float mn = af::min<float>(in);
    float mx = af::max<float>(in);
    return (in-mn)/(mx-mn);
}

int main (int argc, char **argv)
{
    if (argc < 4) {
        std::cerr << argv[0] << " inputImageFile radiusX radiusY [outputImageFile]" << std::endl;
        return -1;
    }

    af::info();

    af::array inputImage = loadImage(argv[1], false); //Boolean indicates to load color image
    af::array outputImage= medfilt(inputImage, atoi(argv[2]), atoi(argv[3]));

    if(argc < 5)
    {
        af::Window window("Median Filter Demo");

        std::cout << "Press ESC while the window is in focus to exit" << std::endl;

        window.grid(1, 2);

        while(!window.close()) {
            window(0, 0).image(normalize(inputImage));
            window(0, 1).image(normalize(outputImage));
            window.show();
        }
    } else {
        af::saveImage(argv[4], outputImage);
    }

    return 0;
}
