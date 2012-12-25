//
//  objectDetector.cpp
//  FP_ADL_Detector
//
//  Created by Yahoo on 11/10/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include "objectDetector.h"

ObjectDetector::ObjectDetector(){
    
    //myHaar_cascade = Haar_cascade("mug_cascade.xml");
    myHaar_cascade.name = "my haar cascade";
    cout << myHaar_cascade.get_name() <<endl;

}

ObjectDetector::~ObjectDetector(){
}

/*
    Batch frame detection
    LARGE memory usage
 */
bool ObjectDetector::detect(FrameModel* frames){
    
    name_of_frames = frames->name;
    
    frames->num_features = 1;//Equal to num of object detectors
    
    ////Detecting
    for (int i = 0 ; i < frames->frameList.size() ; i ++){
        
        cout << "detecting:" << i << "/" << frames->frameList.size()-1 << endl; 
        vector<Rect> result_list = myHaar_cascade.detect(frames->frameList[i].frame,MIN_DETECTION_BOX,MAX_DETECTION_BOX);
        frames->frameList[i].feature.push_back(result_list.size());
        frames->frameList[i].result_list.push_back(result_list);
    }
    
    return true;
}