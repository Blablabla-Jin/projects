var lat, lng;
//Initialize the Google Map API
function initMap() {
    //set up map object by initializing the zoom index and the position: lat, lag
    map = new google.maps.Map(document.getElementById("map"),{
        zoom: 13, 
        center: {lat:43.24458199937876,  lng: -79.87154251830432}});

        infoWindow = new google.maps.InfoWindow;

        //set up marker object
        marker = new google.maps.Marker({
            map: map,
        });
    //set rightclick listener
    google.maps.event.addListener(map, "rightclick", function(event) {
    lat = event.latLng.lat();
    lng = event.latLng.lng();
    document.getElementById('latitude').value = lat;
    document.getElementById('longitude').value = lng;

    onemarkeronly(map, event.latLng);

    });
}
    //use if to make sure only one marker on map
function onemarkeronly(map, position) {
        if (!marker || !marker.setPosition) {
            marker = new google.maps.Marker({
                position: position,
                map: map,
            });
        } else {
            marker.setPosition(position);
        }
    }