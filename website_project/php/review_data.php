<?php 
    session_start();

    //Database class for connect to the database
    include_once 'database.php';
    
    $review = $_GET["review"];
    $restaurant_name = $_GET["restaurant_name"];
    $rest_id = $_GET["rest_id"];

    //validate the input
    $newreview = test_input($review);
    $newrest_id = test_input($rest_id);

    $response['rest_reviews'] = '';

    $i = 0;
    if ($_SERVER["REQUEST_METHOD"] == "GET"){
         //check if loged in 
         if(isset($_SESSION['session_status'])){
            //check the satus of log in is fine
            if(!empty($_SESSION['session_status'])){
                if($_SESSION['session_status'] == 'true'){
                    if(isset($newreview) && isset($newrest_id)){
                        if(!empty($newreview) && !empty($newrest_id)){
                            //Connect to database by using PDO
                            $database = new Database();
                            $db = $database->getConnection();
                            if($db['status'] == '0'){
                                echo "Connection to database failed: " . $db['message'];
                            }else{
                                try {
                                    //check if we have this restaurant in our db
                                    $conn = $db['connection'];
                                    $query = "select name from restaurants where id = '$newrest_id' and name = '$restaurant_name'";
                                    $request = $conn->prepare($query);
                                    $request->execute();
                                    $result = $request->fetchAll(PDO::FETCH_ASSOC);
                                    if(empty($result)){
                                        $response['response_status'] = '0';
                                        $response['response_mess'] = 'We do not have this restaurant';
                                        echo json_encode($response);

                                    }
                                    else{
                                        //inserting the reviews
                                        $query = "insert into reviews(id,restaurant_name,review,rest_id) VALUES (null, '$restaurant_name','$newreview','$newrest_id')";
                                        $request = $conn->prepare($query);
                                        $result = $request->execute();

                                        //select reviews for current restaurant
                                        $query_review = "select review from reviews where rest_id ='$newrest_id'";
                                        $request_review = $conn->query($query_review);
                                        $request_review->execute();
                                        $rows_review = $request_review->fetchAll(PDO::FETCH_ASSOC);

                                        if(!empty($result)){
                                            $response['response_status'] = '1';
                                            $response['response_mess'] = 'Success!';
                                            //give the query result back to the ajax for partially change the page
                                            $response['rest_reviews'] = $rows_review;
                                            echo json_encode($response);
                                        }
                                    }
                                }
                                catch (Exception $e) {
                                    die("something went wrong".$e->getMessage());
                                }
                            }
                        }
                        else{
                            $response['response_status'] = '0';
                            $response['response_mess'] = 'Need to write something';
                            echo json_encode($response);

                        }
                    }
                    else{
                        $response['response_status'] = '0';
                        $response['response_mess'] = 'Invalid input';
                        echo json_encode($response);

                    }
                }
                else{
                    $response['response_status'] = '0';
                    $response['response_mess'] = 'Not log in yet, go log in';
                    echo json_encode($response);

                }    
            }
            else{
                $response['response_status'] = '0';
                $response['response_mess'] = 'Something wrong with log in status';
                echo json_encode($response);

            }
        }
        else{
            $response['response_status'] = '0';
            $response['response_mess'] = 'Not log in yet, go log in';
            echo json_encode($response);

        }
    }   
    else{
        $response['response_status'] = '0';
        $response['response_mess'] = 'Invalid method';
        echo json_encode($response);

    }         

    function test_input($data) {
        $data = trim($data);
        $data = stripslashes($data);
        $data = htmlspecialchars($data);
        return $data;
    }
?>
