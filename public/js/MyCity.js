"use strict";

var MyCity = {
    init: function() {
        var mapCanvas  = document.getElementById('map-canvas'),
            myLatLon   = new google.maps.LatLng( mapCanvas.getAttribute('data-latitude'), mapCanvas.getAttribute('data-longitude')),
            mapOptions = {
              center: myLatLon,
              scrollwheel: false,
              disableDefaultUI: true,
              zoom: 12
            },
            myMap     = new google.maps.Map(mapCanvas, mapOptions);

        if (mapCanvas.getAttribute('data-title')) {
            var myMarker  = new google.maps.Marker({
                position: myLatLon,
                map: myMap,
                title: mapCanvas.getAttribute('data-title')
            });
            myMap.setZoom(15);
            myMap.panBy(0, 50);
        }
    }
}

google.maps.event.addDomListener(window, 'load', MyCity.init);
