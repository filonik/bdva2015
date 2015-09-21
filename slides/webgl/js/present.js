/*jshint jquery:true laxbreak:true */
/*global window document*/
/*
 * Present.js
 * Quick and dirty code for a slideshow.
 */
;(function($, window, document, undefined) {

    function clamp (x, min, max) {
        if (x < min)
            x = min;
        else if (x > max)
            x = max;
        return x;
    }

    // Return total height, including margin and padding, of the slide.
    function getSlideHeight () {
        return $('#slides article').outerHeight(true);
    }

    // Get current slide number we're on
    function getSlideNumber () {
        var slideHeight = getSlideHeight();
        var total = $('#nav li').size();
        var currentScroll = $('body').scrollTop();
        var slideNumber = Math.round(currentScroll / slideHeight);
        slideNumber = clamp(slideNumber, 0, total - 1);
        return slideNumber;
    }

    // Change background based on the slide you're on
    function updateBackground (number) {
        var meta = {duration: 200, queue: false};
        var slides = $('#slides article');
        var background = $(slides[number]).data('background');
        if (background)
            $('body').animate({backgroundColor: background}, meta);
        else
            $('body').animate({backgroundColor: 'black'}, meta);
    }

    // Scroll to slide
    function toSlide(number) {
        var meta = {duration: 350, queue: false};
        var slideHeight = getSlideHeight();
        var height = number * (slideHeight);
        $('body')
            .stop(true, true)
            .data('scrolling', true)
            .animate({scrollTop: height}, meta, 'swing', function () {
                $('body').data('scrolling', false);
                updateBackground(number);
            });
    }

    // Set up controls and metadata
    $(document).ready(function () {
        // Count the number of slides and insert nav hints
        var slides = $('#slides article');
        var nav = $('<ul id="nav">');
        slides.each(function (i, x) {
            var slide = $(x);
            var item = $('<li>');
            var name = slide.attr('title');
            item.data('number', i);
            item.html(name);
            nav.append(item);
        });
        $('body').append(nav);

        // Auto update current slide navigation helper
        $(document).scroll(function (event) {
            // Update navigation
            var number = getSlideNumber();
            var navs = $('#nav > li');
            navs.removeClass('active');
            $(navs[number]).addClass('active');
            updateBackground(getSlideNumber());
        });

        //////////////////////////////////////////
        // Controls
        $('#nav li').click(function (event) {
            var number = $(event.target).closest('li').data('number');
            toSlide(number);
        });

        var KEY_UP = 38,
            KEY_DOWN = 40;
        $(document).keydown(function (event) {
            var total = $('#nav > li').size();
            var number = getSlideNumber();
            if (event.which === KEY_UP) {
                if ($('body').data('scrolling') == "true")
                    number--;
                number = clamp(number, 0, total - 1);
                toSlide(number - 1);
            } else if (event.which === KEY_DOWN) {
                if ($('body').data('scrolling') == "true")
                    number++;
                number = clamp(number, 0, total - 1);
                toSlide(number + 1);
            }
        });
    });
})(jQuery, window, document);