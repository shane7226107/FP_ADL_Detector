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

            console.log('Index');
            ac.done({
                        status: 'Good',
                        data: 'Welcome'
                    });
                       
        },

        ADL: function(ac){
            /*Declaration*/
            var exec = require('child_process').exec,
                params = ac.params.getFromUrl(),
                run_crf = params.run_crf || "false",
                show_result = params.show_result || "false",
                show_pause = params.show_pause || "false",
                params_for_adl = null;

            function run_ADL(param){
                var result = "nothing";

                console.log('running_ADL...');

                exec(param, 
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

            /*Processing*/
            console.log("\n\n\n" + params.video + "\n\n\n");
            
            params_for_adl = "~/Documents/CMLab/Master/FP_ADL_Detector/DerivedData/FP_ADL_Detector/Build/Products/Debug/FP_ADL_Detector " + 
                             "~/Desktop/ADL_VIDEOS_FOR_Mojito/"+ params.video + " " + 
                             run_crf + " " +
                             show_result + " " +
                             show_pause + " " +
                             params.start + " " +
                             params.end;
            /*
            ac.done({
                                status: 'good',
                                data: params_for_adl
                            });
            */               
            run_ADL(params_for_adl);
        }


    };

}, '0.0.1', {requires: ['mojito', 'myMojitModelFoo']});
