/**
* This file is part of ORB-SLAM3
*
* Copyright (C) 2017-2021 Carlos Campos, Richard Elvira, Juan J. Gómez Rodríguez, José M.M. Montiel and Juan D. Tardós, University of Zaragoza.
* Copyright (C) 2014-2016 Raúl Mur-Artal, José M.M. Montiel and Juan D. Tardós, University of Zaragoza.
*
* ORB-SLAM3 is free software: you can redistribute it and/or modify it under the terms of the GNU General Public
* License as published by the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* ORB-SLAM3 is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even
* the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License along with ORB-SLAM3.
* If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef ORBEXTRACTOR_INTEL_H
#define ORBEXTRACTOR_INTEL_H

#include <vector>
#include <list>
#include <opencv2/opencv.hpp>
#include <orb_extractor.h>


namespace ORB_SLAM3
{

class ExtractorNode
{
public:
    ExtractorNode():bNoMore(false){}

    void DivideNode(ExtractorNode &n1, ExtractorNode &n2, ExtractorNode &n3, ExtractorNode &n4);

    std::vector<cv::KeyPoint> vKeys;
    cv::Point2i UL, UR, BL, BR;
    std::list<ExtractorNode>::iterator lit;
    bool bNoMore;
};

class ORBextractor : public orb_extractor
{
public:
    
    enum {HARRIS_SCORE=0, FAST_SCORE=1 };

    ORBextractor(int nfeatures, float scaleFactor, int nlevels,
                 int iniThFAST, int minThFAST);

    ~ORBextractor(){}

    // Compute the ORB features and descriptors on an image.
    // ORB are dispersed on the image using an octree.
    // Mask is ignored in the current implementation.
    int operator()( cv::InputArray _image, cv::InputArray _mask,
                    std::vector<cv::KeyPoint>& _keypoints,
                    cv::OutputArray _descriptors, std::vector<int> &vLappingArea);

    int inline GetLevels(){
        return (int)get_num_scale_levels();}

    float inline GetScaleFactor(){
        return get_scale_factor();}

    std::vector<float> inline GetScaleFactors(){
        return get_scale_factors() ;
    }

    std::vector<float> inline GetInverseScaleFactors(){
        return get_inv_scale_factors();
    }

    std::vector<float> inline GetScaleSigmaSquares(){
        return get_level_sigma_sq();
    }

    std::vector<float> inline GetInverseScaleSigmaSquares(){
        return get_inv_level_sigma_sq() ;
    }

    void GetImagePyramid(std::vector<MatType> &image_pyramid){
        get_image_pyramid(image_pyramid);
    }

    //std::vector<cv::Mat> mvImagePyramid;

};

} //namespace ORB_SLAM

#endif

