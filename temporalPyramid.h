//
//  temporalPyramid.h
//  FP_ADL_Detector
//
//  Created by Yahoo on 11/10/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef FP_ADL_Detector_temporalPyramid_h
#define FP_ADL_Detector_temporalPyramid_h

#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <vector>
#include "frames.h"

using namespace std;


class node{
    
public:
    vector<float> feature;
    
};


class TemporalPyramid{
	
    
public:
	
    ////variable
    string name;
    int frame_per_node;
    int num_of_features;
    int num_of_levels;
    vector< vector<node> > pyramid;
    
    ////constructor
	TemporalPyramid();
	~TemporalPyramid();
    
    ////public functions
    //load frames and build the first level pyramid(nodes)
    bool loadFrames(FrameModel* frames);
    bool buildPyramid(int level_required);//level 'counts' => positive integer : 1,2,3...
    bool observationSampling();
    bool showPyramid(int level_index);//start from level 0
    bool activity_detect(FrameModel* frames);
};

#endif
