//
//  temporalPyramid.cpp
//  FP_ADL_Detector
//
//  Created by Yahoo on 11/10/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include "temporalPyramid.h"

TemporalPyramid::TemporalPyramid(){
}

TemporalPyramid::~TemporalPyramid(){
}

bool TemporalPyramid::observationSampling(){
    
    return true;
}

bool TemporalPyramid::loadFrames(FrameModel* frames,int FPN){
    
    //Clear the pyramid first
    pyramid.clear();
    
    //Setting the 'frame per node' number
    frame_per_node = FPN;
    num_of_features = frames->num_features;
    
    cout << "FPN: " << FPN << endl;
    //Build the first level pyramid
    vector<node> tmp__node_array;
    for(int f = 0 ; f + FPN < frames->frame_count ; f = f + FPN){
        
        //create a node with the same number of features in a frame
        node tmp_node;
        for (int i = 0 ; i < frames->num_features ; i++){
            tmp_node.feature.push_back(frames->frameList[f].feature[i]);
        }
        
        //Summing frame features in a interval(FPN)
        for (int j = f+1; j < f + FPN ; j++) {
            for (int i = 0 ; i < frames->num_features ; i++){
                //cerr << "f:" << f <<" j:"<< j <<" i:" << i << endl;
                tmp_node.feature[i] = frames->frameList[j].feature[i] + tmp_node.feature[i];
            } 
        }
        
        tmp__node_array.push_back(tmp_node);
    }
    
        
    pyramid.push_back(tmp__node_array);
    num_of_levels = (int)pyramid.size();
    
    return true;
}

bool  TemporalPyramid::showPyramid(int level_index){
    
    if ( level_index >= pyramid.size()) {
        cout << "failed\n";
        return false;
    }
    
    cout << "Number of nodes in level " << level_index  << " => " << pyramid[level_index].size() <<endl;;
    cout << "Node features" << endl;
    for (int i = 0 ;  i < pyramid[level_index].size(); i++) {
        for (int j = 0; j < pyramid[level_index][i].feature.size() ; j++) {
            cout << pyramid[level_index][i].feature[j] <<" "; 
        }
        cout << " | ";
    }
    cout << "\n";
    
    return true;
}

bool TemporalPyramid::buildPyramid(int level_required){
    
    if (num_of_levels > 1) {
        cout << "Pyramid already built. Use 'loadFrames' to re-initial the pyramid first.\n";
        return false;
    }
    
    if (level_required < 2) {
        cout << "Invalid number for levels\n";
        return false;
    }
    
    for (int level = 1 ;  level < level_required ; level++) {
        
        vector<node> tmp__node_array;
        for(int n = 0 ; n < pyramid[level-1].size() ; n = n + 2){
            
            //create a node with the same number of features
            node tmp_node;
            for (int i = 0 ; i < num_of_features ; i++){
                tmp_node.feature.push_back(pyramid[level-1][n].feature[i]);
            }
            
            //In case the number of nodes in the last level is not even
            if (n+1 < pyramid[level-1].size()) {
                //Summing node features in a interval and avrage them(2 nodes)
                for (int k = 0; k < num_of_features; k++) {
                    tmp_node.feature[k] = (tmp_node.feature[k] + pyramid[level-1][n+1].feature[k])/2;
                }
            }            
            
            tmp__node_array.push_back(tmp_node);
        }
        
        pyramid.push_back(tmp__node_array);
    }
    
    num_of_levels = pyramid.size();
    
    return true;
}





