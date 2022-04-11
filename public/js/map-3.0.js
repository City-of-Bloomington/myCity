'use strict';
const coords = document.getElementById('coordinates');
const point  = { lat: parseFloat(coords.dataset.latitude), lng: parseFloat(coords.dataset.longitude) };
let   map    = new google.maps.Map(document.getElementById("map"), {
                   center:    point,
                   zoom:      17,
                   mapTypeId: 'satellite'
               });
const marker = new google.maps.Marker({
                   position: point,
                   map: map,
                   icon: {
                       url: BASE_URI + '/js/images/map-crosshair.png',
                       anchor: { x: 35, y: 35 }
                   }
               });