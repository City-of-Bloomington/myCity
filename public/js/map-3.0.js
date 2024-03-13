'use strict';
let map;
async function initMap()    
{
    const { Map } = await google.maps.importLibrary("maps");
    const { AdvancedMarkerElement, PinElement } = await google.maps.importLibrary("marker");

    const map = new Map(document.getElementById('map'), {
        zoom:       20,
        center:     {lat:   LATITUDE,   lng:    LONGITUDE },
        mapId:      'myBloomington_map',
        mapTypeId:  'satellite',
        fullscreenControl: false,
        streetViewControl: false,
        mapTypeControl:    false
    });

    const pinScaled = new PinElement({
        scale: 2.5,
      });

    const marker = new AdvancedMarkerElement({
        map,
        position: { lat:   LATITUDE,   lng:    LONGITUDE },
        content: pinScaled.element,
      });
}
