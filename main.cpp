//
//  main.cpp
//  FP_ADL_Detector
//
//  Created by Yahoo on 11/10/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//
#include "main.h"

int main (int argc, const char * argv[])
{   
    cout << "FP_ADL_Detector\n";
    
    /*
     Input arguments checking
     argv[1] : video path
     argv[2] : [show]show detection result , [show_result]show detection and pause when detected
     argv[3] : [crf]run CRF++ for activity recognition
     */
    if (argv[1] == NULL){
        cout << "missing argv[1] : input video path\n";
        return 0;
    }
    string input_video = string(argv[1]);
    bool do_activity_detection = false;
    bool show_detection_result = false;
    bool pause_when_detected = false;
    cout  << "input video:" << input_video << endl;
    
    if (argc >= 3) {
        show_detection_result  = true;
        string tmp;
        tmp.assign(argv[2]);
        if(tmp.compare("show_pause") == 0)
            pause_when_detected = true;
    }
    
    if (argc >= 4) {
        string tmp;
        tmp.assign(argv[3]);
        if(tmp.compare("crf") == 0)
            do_activity_detection = true;
    }
    
    
    /*
     Components initializtion
     */
    FrameModel* myFrames = new FrameModel();
    TemporalPyramid* myTemporalPyramid = new TemporalPyramid();    
    
    /*
     Loading input video(feature detection included)
     */
    myFrames->loadVideo(input_video);
    cout << "Frames : " << myFrames->frame_count << endl;
    
    /*
     Show detection result
     */
    /*
    myFrames.feature_name.push_back("fake_object");
    Rect fake;
    fake.x = 280;
    fake.y = 880;
    fake.width = 120;
    fake.height = 120;
    myFrames.frameList[3].result_list[0].push_back(fake);
    */
    if(show_detection_result)
        myFrames->playVideo_with_detected_results(pause_when_detected);
    
    /*
     Building temporal pyramid
     */
    cout << "Building temporal pyramid\n";
    myTemporalPyramid->loadFrames(myFrames);
    myTemporalPyramid->showPyramid(0);
    myTemporalPyramid->buildPyramid(2);
    cout << "number of levels : " << myTemporalPyramid->num_of_levels << endl;
    myTemporalPyramid->showPyramid(1);
    
    
    /*
     Activity Detection
     */
    if(do_activity_detection)
        myTemporalPyramid->activity_detect(myFrames);
    
    
    
    delete myFrames;
    delete myTemporalPyramid;
    
    return 0;
}


