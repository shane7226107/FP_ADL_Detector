/*
 * Copyright (c) 2012 Yahoo! Inc. All rights reserved.
 */
/*jslint anon:true, sloppy:true, nomen:true*/
YUI.add('myMojit', function(Y, NAME) {

/**
 * The myMojit module.
 *
 * @module myMojit
 */

    /**
     * Constructor for the Controller class.
     *
     * @class Controller
     * @constructor
     */
    Y.namespace('mojito.controllers')[NAME] = {

        init: function(config) {
            this.config = config;
        },

        /**
         * Method corresponding to the 'index' action.
         *
         * @param ac {Object} The ActionContext that provides access
         *        to the Mojito API.
         */
        index: function(ac) {
            var exec = require('child_process').exec;

            function run_ADL(callback){
                var result = "nothing";

                console.log('running_ADL...');

                exec('~/Documents/CMLab/Master/FP_ADL_Detector/DerivedData/FP_ADL_Detector/Build/Products/Debug/FP_ADL_Detector ~/Desktop/ADL_videos/by_hand/raw_video/beverage/1.mp4 show crf 550 650', 
                    function (error, stdout, stderr) {

                        console.log(stdout);
                        ac.done({
                            status: 'Good',
                            data: stdout
                        });
                        
                        if (error !== null) {
                            console.log('stderr: ' + stderr);
                            console.log('exec error: ' + error);
                            ac.done({
                                status: 'Error',
                                data: stdout
                            });
                        }
                    });  
            }

            /*process*/
            run_ADL();            
        }

    };

}, '0.0.1', {requires: ['mojito', 'myMojitModelFoo']});
