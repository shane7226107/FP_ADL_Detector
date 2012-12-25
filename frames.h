//
//  frames.h
//  FP_ADL_Detector
//
//  Created by Yahoo on 11/10/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef FP_ADL_Detector_frames_h
#define FP_ADL_Detector_frames_h

#include <stdlib.h>
#include <iostream>
#include <vector>
#include <cv.h>
#include <highgui.h>
#include <cxcore.h>

using namespace std;
using namespace cv;

class frameNode{

public:
    
    IplImage* frame;
    vector<float> feature;
    vector< vector<Rect> > result_list;

};


class FrameModel{
	
    
public:
	
    //variable
    string name;
    vector<frameNode> frameList;
    int FPS;
    int frame_count;
    int num_frames;
    int num_features;
    vector<string> feature_name;
    
    //constructor
	FrameModel();
	~FrameModel();
    
    //public functions
    int getFPS();
    bool loadVideo(string path);
    bool loadVideo(string path,int start , int end);//if end < 0 ,the whole video will be loaded
    bool playVideo();
    bool showFeature(int index);
    bool showDetectionResult();
    bool playVideo_with_detected_results(bool pause_when_detected);
};

#endif
