cmake_minimum_required(VERSION 3.4)
project(Library)

#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
        include/Brightness.h
        include/CImg.h
        include/Contrast.h
        include/Negative.h
        include/Enlarge.h
        include/Shrink.h
        include/Engine.h
        include/Help.h
        include/FlipHorizontal.h
        include/FlipVertical.h
        include/FlipDiagonal.h
        include/GeometricMeanFilter.h
        include/AlphaTrimmedMeanFilter.h
        include/MeanSquareError.h
        include/PeakMeanSquareError.h
        include/SignalToNoiseRatio.h
        include/PeakSignalToNoiseRatio.h
        include/MaximumDifference.h
        include/Histogram.h
        include/EFPDF.h
        include/Mean.h
        include/StandardDeviation.h
        include/Variance.h
        include/VariationCoefficient.h
        include/VariationCoefficient2.h
        include/AssymetryCoefficient.h
        include/FlatteningCoefficient.h
        include/InformationSourceEntropy.h
        include/LinearFilter.h
        include/LinearFilterOptimized.h
        include/RobertsOperator2.h
        include/Dilation.h
        include/Erosion.h
        include/Opening.h
        include/Closing.h
        include/HitAndMiss.h
        include/M2.h
        include/RegionGrowing.h
        include/SFT.h
        include/FFT.h
        include/LowPassFilter.h
        include/HighPassFilter.h
        include/BandPassFilter.h
        include/BandCutFilter.h
            src/Brightness.cpp
            src/Contrast.cpp
            src/Negative.cpp
            src/Enlarge.cpp
            src/Shrink.cpp
            src/Engine.cpp
            src/Help.cpp
            src/FlipHorizontal.cpp
            src/FlipVertical.cpp
            src/FlipDiagonal.cpp
            src/GeometricMeanFilter.cpp
            src//AlphaTrimmedMeanFilter.cpp
            src/MeanSquareError.cpp
            src/PeakMeanSquareError.cpp
            src/SignalToNoiseRatio.cpp
            src/PeakSignalToNoiseRatio.cpp
            src/MaximumDifference.cpp
            src/Histogram.cpp
            src/EFPDF.cpp
            src/Mean.cpp
            src/StandardDeviation.cpp
            src/Variance.cpp
            src/VariationCoefficient.cpp
            src/VariationCoefficient2.cpp
            src/AssymetryCoefficient.cpp
            src/FlatteningCoefficient.cpp
            src/InformationSourceEntropy.cpp
            src/LinearFilter.cpp
            src/LinearFilterOptimized.cpp
            src/RobertsOperator2.cpp
            src/Dilation.cpp
            src/Erosion.cpp
            src/Opening.cpp
            src/Closing.cpp
            src/HitAndMiss.cpp
            src/M2.cpp
            src/RegionGrowing.cpp
            src/SFT.cpp
            src/FFT.cpp
            src/LowPassFilter.cpp
            src/HighPassFilter.cpp
            src/BandPassFilter.cpp
            src/BandCutFilter.cpp

)

add_library(Library ${SOURCE_FILES})

#add 'include' directory with header files from 'Library' project to paths
target_include_directories(Library PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)



include_directories(
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)


target_link_libraries (
        Library
        )

