//
//  temporalPyramid.cpp
//  FP_ADL_Detector
//
//  Created by Yahoo on 11/10/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include "temporalPyramid.h"

vector<string> split(string& str,const char* c)
{
    char *cstr, *p;
    vector<string> res;
    cstr = new char[str.size()+1];
    strcpy(cstr,str.c_str());
    p = strtok(cstr,c);
    while(p!=NULL)
    {
        res.push_back(p);
        p = strtok(NULL,c);
    }
    return res;
}


TemporalPyramid::TemporalPyramid(){
}

TemporalPyramid::~TemporalPyramid(){
}

bool TemporalPyramid::observationSampling(){
    
    return true;
}

bool TemporalPyramid::loadFrames(FrameModel* frames){
    
    //Clear the pyramid first
    pyramid.clear();
    
    //Setting the 'frame per node' number
    //frame_per_node = FPN;
    frame_per_node = frames->FPS;
    num_of_features = frames->num_features;
    
    cout << "FPN: " << frame_per_node << endl;
    //Build the first level pyramid
    vector<node> tmp__node_array;
    for(int f = 0 ; f + frame_per_node < frames->frame_count ; f = f + frame_per_node){
        
        //create a node with the same number of features in a frame
        node tmp_node;
        for (int i = 0 ; i < frames->num_features ; i++){
            tmp_node.feature.push_back(frames->frameList[f].feature[i]);
        }
        
        //Summing frame features in a interval(FPN)
        for (int j = f+1; j < f + frame_per_node ; j++) {
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
    
    num_of_levels = (int)pyramid.size();
    
    return true;
}

bool TemporalPyramid::activity_detect(FrameModel *frames){
    
    //Output file for CRF++
    
    int level = 1;
    
    vector<string> feature_names;
    
    //run through the nodes in the level 
    for (int node = 0 ;  node < pyramid[level].size(); node++) {
        
        float max = 0;
        string feature_name = "";
        
        //run through the features in the node
        for (int _feature = 0; _feature < pyramid[level][node].feature.size() ; _feature++) {
                        
            if (pyramid[level][node].feature[_feature] > max && pyramid[level][node].feature[_feature] > frame_per_node/3) {
                max = pyramid[level][node].feature[_feature];
                feature_name = frames->feature_name[_feature];
            }
        }
        
        feature_names.push_back(feature_name);
    }
    
    
    for (int i  = 0 ;  i < feature_names.size() ; i ++) {
        //cout << feature_names[i] << endl;
    }
    
    FILE* fp;
    fp = fopen("crf/test.crf", "w");
    
    fprintf(fp, "%s\n",feature_names[0].c_str());
    fprintf(fp, "%s\n",feature_names[1].c_str());
    fprintf(fp, "%s\n",feature_names[2].c_str());
    
    fclose(fp);
    
    //Run CRF++
    system("crf_test -m crf/model.crf crf/test.crf > crf/result.txt");
    
    //Read result 
    string line;
    vector<string> tmp;
    ifstream myfile("crf/result.txt");
    if (myfile.is_open())
    {   
        cout << "Reading reulst from CRF++\n";
        while ( myfile.good() )
        {
            getline (myfile,line);
            tmp.push_back(line);
            //cout << line <<endl;
        }
        
    }else {
        cout << "Unable to open file";
    }
    
    /*
    for (int i  = 0 ;  i < tmp.size() ; i ++) {
        cout << tmp[i] << endl;
    }
    */
    
    cout << "Resu from CRF++:" << tmp[tmp.size() - 3 ] << endl;
    
    myfile.close();
    return true;
}




