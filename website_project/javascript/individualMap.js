var map, marker, infoWindow;
function initMap() {
    //set up map object by initializing the zoom index and the position: lat, lag
    map = new google.maps.Map(document.getElementById("map"),{
        zoom: 13, 
        center: {lat:43.24458199937876,  lng: -79.87154251830432}});
        //set up marker object

        marker = new google.maps.Marker({
            map: map,
        });

        var examplemarker = {
            lat: parseFloat($("#res_lat").text()), 
            lng: parseFloat($("#res_lng").text())
        };

        
        marker.setPosition(examplemarker);//set the location of marker
        map.setCenter(examplemarker, 9)//reset the centre of the map
        marker.setAnimation(google.maps.Animation.DROP);
        marker.addListener("mouseover", bounceanimation);
}

var updatereview =  function(){
    let content = $('#usertext').val();
    let name = $('#rstant_name').text();
    let searchParams = new URLSearchParams(window.location.search);
    let restid = searchParams.get('resturantId');
    // if (content == ''){
    //     alert("input empty");
    //     return false;
    // }
    $.ajax({
            type:"GET",
            url:"/Toolman/php/review_data.php",
            data: {'review': content, 'restaurant_name': name, 'rest_id': restid},
            async : false,
            success:function(result){
               var data = JSON.parse(result);
               if(data.response_status == '0'){
                   $("#alrtdanger").fadeIn("slow").delay(1500).fadeOut(700);
                   $('#alrtdanger .title').html(data.response_mess);
                   
               }
               else{
                   var resulthtml = "";
                   $("#alrt").fadeIn("slow").delay(1500).fadeOut(700);
                   $('#alrt .title').html(data.response_mess);
                   if(data.rest_reviews != ''){
                       
                        $.each(data.rest_reviews, function(i){
                            $.each(data.rest_reviews[i], function(key, value){
                                resulthtml += ("<br/>" + value + "<br/>");
                            })
                        });
                        $("#restaurant_reviews").html(resulthtml);
                    }
                    
               }
            }
        });
    }