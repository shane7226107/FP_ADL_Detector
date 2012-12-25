//
//  objectDetector.cpp
//  FP_ADL_Detector
//
//  Created by Yahoo on 11/10/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include "objectDetector.h"

ObjectDetector::ObjectDetector(){
    
    Haar_cascade tmp = Haar_cascade("cascade_active_beverage.xml" , "active_beverage");
    myHaars.push_back(tmp);
    
    tmp = Haar_cascade("cascade_active_laptop.xml" , "active_laptop");
    myHaars.push_back(tmp);
    tmp = Haar_cascade("cascade_active_mug.xml" , "active_mug");
    myHaars.push_back(tmp);
    tmp = Haar_cascade("cascade_active_water_dispenser.xml" , "active_water_dispenser");
    myHaars.push_back(tmp);
}

ObjectDetector::~ObjectDetector(){
}

/*
    Batch frame detection
    LARGE memory usage
 */
bool ObjectDetector::detect(FrameModel* frames){
    
    name_of_frames = frames->name;
    
    frames->num_features = (int)myHaars.size();//Equal to num of object detectors
    
    //Detection using the cascades in myHaars
    for (int cls = 0 ; cls < frames->num_features ; cls ++){
        
        frames->feature_name.push_back(myHaars[cls].name);
        for (int i = 0 ; i < frames->frameList.size() ; i ++){
            
            cout << "detecting:" << i << "/" << frames->frameList.size()-1 << endl; 
            vector<Rect> result_list = myHaars[cls].detect(frames->frameList[i].frame,MIN_DETECTION_BOX,MAX_DETECTION_BOX);
            frames->frameList[i].feature.push_back(result_list.size());
            frames->frameList[i].result_list.push_back(result_list);
        }
        
    }
    
    return true;
}