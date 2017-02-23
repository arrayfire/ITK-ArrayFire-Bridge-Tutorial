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

#include <itkRGBPixel.h>
#include <itkImageFileReader.h>
#include <itkImageFileWriter.h>
#include <itkMedianImageFilter.h>
#include <itkArrayFireImageBridge.h>

af::array normalize(const af::array &in)
{
    float mx = af::max<float>(in);
    float mn = af::min<float>(in);
    return (in-mn)/(mx-mn);
}

int main( int argc, char * argv [] )
{
    if( argc < 5 )
    {
        std::cerr << "Usage: " << std::endl;
        std::cerr << argv[0] << "  inputImageFile   outputImageFile  radiusX  radiusY" << std::endl;
        return EXIT_FAILURE;
    }

    const unsigned int Dimension = 2;

    typedef itk::RGBPixel<unsigned char>      PixelType;
    typedef itk::Image<PixelType, Dimension>  ImageType;
    typedef itk::ImageFileReader<ImageType>   ReaderType;
    typedef itk::ImageFileWriter<ImageType>   WriterType;

    ReaderType::Pointer reader = ReaderType::New();
    WriterType::Pointer writer = WriterType::New();

    reader->SetFileName(argv[1]);
    writer->SetFileName(argv[2]);

    try {
        reader->Update(); //Without Update call, GetOutput will return garbage pointer

        af::array inputImage = itk::ArrayFireImageBridge::ITKImagetoAfArray(reader->GetOutput());
        af::array outputImage = af::medfilt(inputImage, atoi(argv[3]), atoi(argv[4]));

        ImageType::Pointer itkImg = itk::ArrayFireImageBridge::AfArrayToITKImage<ImageType>(outputImage);

        writer->SetInput(itkImg);

        writer->Update();
    } catch(af::exception &e) {
        std::cerr<< e.what() << std::endl;
        return EXIT_FAILURE;
    } catch(itk::ExceptionObject & excp) {
        std::cerr << excp << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
