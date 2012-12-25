//
//  objectDetector.h
//  FP_ADL_Detector
//
//  Created by Yahoo on 11/10/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef FP_ADL_Detector_objectDetector_h
#define FP_ADL_Detector_objectDetector_h

#include <stdlib.h>
#include <iostream>
#include "haar_cascade.h"
#include "frames.h"

#define MAX_DETECTION_BOX 600
#define MIN_DETECTION_BOX 200

using namespace std;

class ObjectDetector{
	
    
public:
	
    //variable
    string name;
    string name_of_frames;
    
    //public functions
    bool detect(FrameModel* frames);
    
    //constructor
	ObjectDetector();
	~ObjectDetector();
    
private:
    Haar_cascade myHaar_cascade = Haar_cascade("mug_cascade.xml");
};



#endif
