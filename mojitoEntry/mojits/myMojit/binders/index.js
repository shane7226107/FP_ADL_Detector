/*
 * Copyright (c) 2012 Yahoo! Inc. All rights reserved.
 */
/*jslint anon:true, sloppy:true, nomen:true*/
YUI.add('myMojitBinderIndex', function(Y, NAME) {

/**
 * The myMojitBinderIndex module.
 *
 * @module myMojitBinderIndex
 */

    /**
     * Constructor for the myMojitBinderIndex class.
     *
     * @class myMojitBinderIndex
     * @constructor
     */
    Y.namespace('mojito.binders')[NAME] = {

        /**
         * Binder initialization method, invoked after all binders on the page
         * have been constructed.
         */
        init: function(mojitProxy) {
            this.mojitProxy = mojitProxy;
        },

        /**
         * The binder method, invoked to allow the mojit to attach DOM event
         * handlers.
         *
         * @param node {Node} The DOM node to which this mojit is attached.
         */
        bind: function(node) {
            var me = this;
            this.node = node;
            /**
             * Example code for the bind method:
             */
             node.all('dt').on('mouseenter', function(evt) {
                evt.target.addClass('sel');
                Y.log('\n\n\nmouseenter');
              });
              node.all('dt').on('mouseleave', function(evt) {
                
                evt.target.removeClass('sel');
                Y.log('\n\n\nmouseleave');

              });
              node.all('a').on('mouseenter', function(evt) {
                evt.target.addClass('sel');
                Y.log('\n\n\nmouseenter');
              });
              node.all('a').on('mouseleave', function(evt) {
                
                evt.target.removeClass('sel');
                Y.log('\n\n\nmouseleave');

              });
             
        }

    };

}, '0.0.1', {requires: ['event-mouseenter', 'mojito-client']});
