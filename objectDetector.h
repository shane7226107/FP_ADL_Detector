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
#include <vector>
#include "haar_cascade.h"
#include "frames.h"

#define MAX_DETECTION_BOX 600
#define MIN_DETECTION_BOX 100

using namespace std;

class ObjectDetector{
	
    
public:
	
    //variable
    string name;
    string name_of_frames;
    int num_of_detectors;
    
    //public functions
    bool detect(FrameModel* frames);
    
    //constructor
	ObjectDetector();
	~ObjectDetector();
    
private:
    
    vector<Haar_cascade> myHaars;
    /*
    Haar_cascade active_beverage_cascade = Haar_cascade("cascade_active_beverage.xml");
    Haar_cascade active_laptop_cascade = Haar_cascade("cascade_active_laptop.xml");
    Haar_cascade active_mug_cascade = Haar_cascade("cascade_active_mug.xml");
    Haar_cascade active_water_dispenser_cascade = Haar_cascade("cascade_active_water_dispenser.xml");
     */
};



#endif
