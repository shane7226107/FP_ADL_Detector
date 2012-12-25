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
     */
    if (argv[1] == NULL){
        cout << "missing argv[1] : input video path\n";
        return 0;
    }
    string input_video = string(argv[1]);
    cout  << "input video:" << input_video << endl;
    
    
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
    bool pause_when_detected = true;
    myFrames->playVideo_with_detected_results(pause_when_detected);
    
    /*
     Building temporal pyramid
     */
    cout << "Building temporal pyramid\n";
    myTemporalPyramid->loadFrames(myFrames, myFrames->FPS);
    myTemporalPyramid->showPyramid(0);
    myTemporalPyramid->buildPyramid(2);
    cout << "number of levels : " << myTemporalPyramid->num_of_levels << endl;
    myTemporalPyramid->showPyramid(1);
    
    
    /*
     Sampling
     */
    
    
    delete myFrames;
    delete myTemporalPyramid;
    
    return 0;
}


