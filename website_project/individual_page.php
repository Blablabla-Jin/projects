<?php
    session_start();
?>

<!DOCTYPE html>
<!--Author: Run Zhang, Boming Jin -->
<html lang = "en">
    <head>
        <title>Object Page</title>
        <meta charset="UTF-8">
        <meta name="viewport" content="width=device-width, initial-scale = 1.0">
        <link rel="stylesheet" href="https://cdnjs.cloudflare.com/ajax/libs/font-awesome/4.7.0/css/font-awesome.min.css">
        <link rel="stylesheet" href="css/bootstrap.css">
        <link rel="stylesheet" href="css/bootstrap.css">
        <link rel="stylesheet" href="css/main.css">
        <!--Google fonts-->
        <link href="//fonts.googleapis.com/css?family=Ubuntu+Mono:400italic,400,700italic,700" rel="stylesheet" type="text/css">
        <!--Animation Library-->
        <link
        rel="stylesheet"
        href="https://cdnjs.cloudflare.com/ajax/libs/animate.css/4.1.1/animate.min.css"
        />

        <meta name="keywords" content="Sample object information, Rate, Review">
        <meta name="description" content="Sample object information">
        <!--Facebook’s-->
        <meta property="og:title" content="Sample object information" />
        <meta property="og:type" content="review" />
        <meta property="og:description" content="Sample object information" />
        <!--Twitter’s Cards validator-->
        <meta name="twitter:card" content="Sample object information">
        <meta property="og:description" content="Sample object information" />
        <!--save page on moblie screeen-->
        <link rel="shortcut icon" sizes="196x196" href="/images/mobileicon.jpg">
        <meta name="mobile-web-app-capable" content="yes">
        <meta name="apple-mobile-web-app-capable" content="yes">

        <!--External JavaScript file-->
        <script src="https://ajax.googleapis.com/ajax/libs/jquery/3.5.1/jquery.min.js"></script>
        <script src="javascript/individualMap.js"></script>

        <!--Set where the window should been opened when clicking hyperlink. Open the document in the same window-->
        <base target = "_self">
    </head>

    <body>
        <?php 
            //Database class for connect to the database
            include '../Toolman/php/database.php';
            
            $id = $_GET['resturantId'];
            //Connect to database by using PDO
            $database = new Database();
            $db = $database->getConnection();
            if($db['status'] == '0'){
                echo "Connection to database failed: " . $db['message'];
            }else{
                try {
                    $conn = $db['connection'];
                    $query_res = "select * from restaurants where id ='$id' ";
                    $query_review = "select review from reviews where rest_id ='$id' ";
                    $request_res = $conn->query($query_res);
                    $request_review = $conn->query($query_review);
                    $rows_res = $request_res->fetch(PDO::FETCH_ASSOC);
                    $rows_review = $request_review->fetchAll(PDO::FETCH_ASSOC);
                }
                catch (Exception $e) {
                    die("something went wrong".$e->getMessage());
                }
            }
        ?>
        <!--navigation menu temporarily set to navigate to main page-->
        <div class = "header">
            <div class = "navBar"> 
                <a href = "index.php">To Main Page</a>
            </div>
        </div>

        <!--should be a side bar later but for now just reviews-->
        <div class = "leftside">
            <h1 id = "rstant_name" style="text-shadow: 2px 2px 5px grey;"><?php echo $rows_res['name'];?></h1>
            <p><?php echo $rows_res['address'];?></p>
            <table id = "rest_detail" style="width:100%">
              <tr>
                <th>Latitude</th>
                <th>Longitude</th>
              </tr>
              <tr>
                <td id ="res_lat">
                    <?php
                    echo $rows_res['latitude'];
                    ?>
                </td>
                <td id ="res_lng">
                    <?php
                    echo $rows_res['longitude'];
                    ?>
                </td>
              </tr>
            </table>

            <p>-----------------------------</p>   
            </br>

            <!--Lists of sample reviews-->
            <h3><em>Reviews</em></h3>

                <p id = "restaurant_reviews" style = "margin-left: 15%; margin-right: 15%;width:70%; word-wrap: break-word;"><?php
                if(!empty($rows_review)){
                    foreach($rows_review as $row => $reviews){
                    echo "<br/>" . $reviews['review'] . "<br/>";
                    }
                if(!empty($rows_rate))
                    foreach($rows_rate as $row => $rates){
                        echo "<br/>" . $rates['rate'] . "<br/>";
                    }
                }
                else{
                    echo "<br/>No reviews right now, add some now!<br/>";
                }?>
                </p>

            
            <p>-----------------------------</p>

             <!--Showing message-->
            <div id = "alrt" class="alert alert-success" role="alert" style = "display:none; text-align: center">
                <p class = "title m-0"></p>
            </div>
            <div id = "alrtdanger" class="alert alert-danger" role="alert" style = "display:none; text-align: center">
                <p class = "title m-0"></p>
            </div>

            <form id="reviews">
            <textarea  rows="4" cols="40" placeholder="Write your review here..." id = "usertext"></textarea>
            <br/>
            <br/>
            <select id = "individualRate" name="rating" class="todrop">
                <option selected disabled>Rating</option>
                <option value="1star">1 star</option>
                <option value="2star">2 star</option>
                <option value="3star">3 star</option>
                <option value="4star">4 star</option>
                <option value="5star">5 star</option>
            </select>
            <br/>
            <br/>
            <button id = "submitreview" type = "button" onclick="updatereview()">Submit</button>
            <br/>
            <br/>
            </form>


            <div class = "footer">
                <p>Author: Run Zhang, Boming Jin &copy; 2021-10-08</p>
            </div>
            
        </div>

        <div class = "rightside">
            <div id="map"></div>
            <script async src="https://maps.googleapis.com/maps/api/js?key=AIzaSyALMSVQoum8gtfksfpEQ4QcZvMqUt8Vez0&callback=initMap&libraries=&v=weekly"></script>
        </div>

        
    </body>
</html>
