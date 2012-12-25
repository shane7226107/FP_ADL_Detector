//
//  frames.cpp
//  FP_ADL_Detector
//
//  Created by Yahoo on 11/10/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include "frames.h"
#include "objectDetector.h"

int FrameModel::getFPS(){

    return FPS;
}
bool FrameModel::loadVideo(string path){
    
    CvCapture *capture;
    IplImage *frame;
    int start;
    int end;
    
    ////Laoding video file
    cout << "Laoding video file\n";
    capture = cvCaptureFromAVI(path.c_str());
    
    frame_count = cvGetCaptureProperty(capture,CV_CAP_PROP_FRAME_COUNT);
    cout << "Frame Count : " << frame_count << endl;
    FPS = cvGetCaptureProperty(capture,CV_CAP_PROP_FPS);
    cout << "FPS :"<< FPS <<endl;
    
    cout << "start:";
    cin >> start;
    cout << "end:";
    cin >> end;
    
    ////Grabbing frames from video
    cout << "Grabbing frames from the video\n";
    if(end < 0 || end > frame_count)
        end = frame_count;
    if(start < 0 || start > frame_count)
        start = 0;
    
    frame_count = end - start + 1;
    
    for(int i = 0 ; i <= end ; i ++)
    {   
        
        frame  = cvQueryFrame(capture);
        
        if(i < start)continue;//Skip the frames not in range
        
        cout << i - start + 1<< "/" << frame_count << endl;
        
        if(frame)
        {   
            frameNode temp;
            temp.frame = cvCloneImage(frame);            
            
            frameList.push_back(temp);
        }
        else
        {
            break;
        }
    }
    
    
    cvReleaseCapture(&capture);
    
    
    return true;
}



bool FrameModel::loadVideo(string path,int start , int end){
    
    CvCapture *capture;
    IplImage *frame;
    
    ////Laoding video file
    cout << "Laoding video file\n";
    capture = cvCaptureFromAVI(path.c_str());
    
    frame_count = cvGetCaptureProperty(capture,CV_CAP_PROP_FRAME_COUNT);
    ////cout << "Frame Count : " << frame_count << endl;
    FPS = cvGetCaptureProperty(capture,CV_CAP_PROP_FPS);
    ////cout << "FPS :"<< FPS <<endl;
    
    ////Grabbing frames from video
    cout << "Grabbing frames from the video\n";
    if(end < 0 ||end > frame_count)
        end = frame_count;
    if(start < 0 || start > frame_count)
        start = 0;
    
    frame_count = end - start + 1;
    
    for(int i = 0 ; i <= end ; i ++)
    {   
        frame  = cvQueryFrame(capture);
        
        if(i < start)continue;//Skip the frames not in range
        
        cout << i - start + 1<< "/" << frame_count << endl;
        
        if(frame)
        {   
            frameNode temp;
            temp.frame = cvCloneImage(frame);            
            
            frameList.push_back(temp);
        }
        else
        {
            break;
        }
    }
    
        
    cvReleaseCapture(&capture);
    
    
    return true;
}

bool FrameModel::playVideo(){
    
    if (frameList.size() < 1) {
        return false;
    }
    
    cvNamedWindow("AVI player",0);
    
    ////Show frames grabed
    cout << "Playing the selected frames\n";
    for(unsigned int i = 0; i < frameList.size(); ++i){
        
        cvShowImage("AVI player",frameList[i].frame);
        
        if(cvWaitKey(10) >= 0)
            break;
    }
    
    cvWaitKey();
    cvDestroyWindow("AVI player");
    
    return true;
}

bool FrameModel::showFeature(int index){
    
    if (frameList.size() < index + 1) {
        return false;
    }
    
    /*
     Show frames
     */
    cout << "frame:" << index << " fetures:\n";
    for(unsigned int i = 0; i < frameList[index].feature.size(); ++i){
        cout << frameList[index].feature[i]<< " ";
    }
    
    cout << endl;
    
    return true;
}

bool FrameModel::showDetectionResult(){
    
    if (frameList.size() < 1) {
        return false;
    }
    
    IplImage* tempFrame = cvCreateImage(cvSize(frameList[0].frame[0].width,   
                                               frameList[0].frame[0].height), IPL_DEPTH_8U, frameList[0].frame[0].nChannels);
    
    ////Show frames grabed
    cout << "Playing the selected frames\n";
    for(unsigned int i = 0; i < frameList.size(); ++i){
        
        cout << "frameList index : " << i << endl;
        
        for(int feature_index = 0 ; feature_index < num_features ; feature_index ++)
        {   
            cout << "feature_index : " << feature_index << endl;
            cout << "num of detections : " << frameList[i].result_list[feature_index].size() << endl;
            
            if(frameList[i].result_list[feature_index].size() > 0){
                
                cvCopy(frameList[i].frame, tempFrame, 0);
                
                for (int box = 0 ; box < frameList[i].result_list[feature_index].size() ; box++){     
                    cout << "drawing bboxes : " << box << endl;
                    CvPoint point1, point2;  
                    
                    point1.x = frameList[i].result_list[feature_index][box].x;  
                    point2.x = frameList[i].result_list[feature_index][box].x + frameList[i].result_list[feature_index][box].width;  
                    point1.y = frameList[i].result_list[feature_index][box].y;  
                    point2.y = frameList[i].result_list[feature_index][box].y + frameList[i].result_list[feature_index][box].height;  
                    //cout << "x1:" << point1.x << " x2:" << point2.x << " y1:"<< point1.y << " y2:" <<point2.y <<endl;
                    cvRectangle(tempFrame, point1, point2, CV_RGB(0,255,0), 3, 8, 0);
                    
                    /*
                     Put the object name on the box
                     */
                    CvFont font;
                    cvInitFont(&font, CV_FONT_HERSHEY_SIMPLEX, 1.0, 1.0, 0, 1, CV_AA);
                    cvPutText(tempFrame, feature_name[feature_index].c_str(), cvPoint(point2.x+10, point2.y), &font, cvScalar(255, 255, 255, 0));
                }  
                
                /*
                 scale down the image since it's 720x1280 sometimes exceeds the monitor size
                 */
                IplImage *dst = 0;       
                float scale = 0.5; 
                CvSize dst_cvsize;      
                dst_cvsize.width = tempFrame->width * scale;
                dst_cvsize.height = tempFrame->height * scale;
                dst = cvCreateImage( dst_cvsize, tempFrame->depth, tempFrame->nChannels);
                cvResize(tempFrame, dst, CV_INTER_LINEAR);
                
                
                /*
                 Show the result in the window.  
                 */
                cvNamedWindow("Obj Detection Result", CV_WINDOW_AUTOSIZE);
                cvShowImage("Obj Detection Result", dst);
                cvMoveWindow("Obj Detection Result", 100, 0);
                cvWaitKey(0);  
                cvDestroyWindow("Obj Detection Result");  
                
            }
        }
        
        if(cvWaitKey(10) >= 0)
            break;
    }
    
    return true;
}

bool FrameModel::playVideo_with_detected_results(bool pause_when_detected){
    
    if (frameList.size() < 1) {
        return false;
    }
    
    IplImage* tempFrame = cvCreateImage(cvSize(frameList[0].frame[0].width,   
                                               frameList[0].frame[0].height), IPL_DEPTH_8U, frameList[0].frame[0].nChannels);
    
    cvNamedWindow("Obj Detection Result", CV_WINDOW_AUTOSIZE);
    cvMoveWindow("Obj Detection Result", 100, 0);
    
    ////Show frames grabed
    cout << "Playing the selected frames\n";
    for(unsigned int i = 0; i < frameList.size(); ++i){
        
        cout << "frameList index : " << i << endl;
        
        for(int feature_index = 0 ; feature_index < num_features ; feature_index ++)
        {   
            cout << "feature_index : " << feature_index << endl;
            cout << "num of detections : " << frameList[i].result_list[feature_index].size() << endl;
                
                cvCopy(frameList[i].frame, tempFrame, 0);
                
                for (int box = 0 ; box < frameList[i].result_list[feature_index].size() ; box++){     
                    cout << "drawing bboxes : " << box << endl;
                    CvPoint point1, point2;  
                    
                    point1.x = frameList[i].result_list[feature_index][box].x;  
                    point2.x = frameList[i].result_list[feature_index][box].x + frameList[i].result_list[feature_index][box].width;  
                    point1.y = frameList[i].result_list[feature_index][box].y;  
                    point2.y = frameList[i].result_list[feature_index][box].y + frameList[i].result_list[feature_index][box].height;  
                    //cout << "x1:" << point1.x << " x2:" << point2.x << " y1:"<< point1.y << " y2:" <<point2.y <<endl;
                    cvRectangle(tempFrame, point1, point2, CV_RGB(0,255,0), 3, 8, 0);
                    
                    /*
                     Put the object name on the box
                     */
                    CvFont font;
                    cvInitFont(&font, CV_FONT_HERSHEY_SIMPLEX, 1.0, 1.0, 0, 1, CV_AA);
                    cvPutText(tempFrame, feature_name[feature_index].c_str(), cvPoint(point2.x+10, point2.y), &font, cvScalar(255, 255, 255, 0));
                }  
                
                /*
                 scale down the image since it's 720x1280 sometimes exceeds the monitor size
                 */
                IplImage *dst = 0;       
                float scale = 0.5; 
                CvSize dst_cvsize;      
                dst_cvsize.width = tempFrame->width * scale;
                dst_cvsize.height = tempFrame->height * scale;
                dst = cvCreateImage( dst_cvsize, tempFrame->depth, tempFrame->nChannels);
                cvResize(tempFrame, dst, CV_INTER_LINEAR);
                
                
                /*
                 Show the result in the window.  
                 */
                cvShowImage("Obj Detection Result", dst);
                if(pause_when_detected && frameList[i].result_list[feature_index].size() > 0)
                    cvWaitKey(0);  
                
            }
        
        if(cvWaitKey(10) >= 0)
            break;
    }
    cvDestroyWindow("Obj Detection Result"); 
    return 0;
}

FrameModel::FrameModel(){
}

FrameModel::~FrameModel(){
}