<?php 
    //Database class for connect to the database
    include_once 'database.php';
    include_once 'hashPass.php';
    if($_SERVER["REQUEST_METHOD"] == "POST"){
        
        $phone_number = $_POST["PhoneNumber"];
        $email = $_POST["EMailAddress"];
        $password = $_POST["Userpw"];
        $sec_q = $_POST["Username"];

        //Check validation of the input
        $newphone_number = test_input($phone_number);
        $newemail = test_input($email);
        $newpassword = test_input($password);
        $newsec_q = test_input($sec_q);
        $response['response_mess'] = "";
        
        //validation php
        if (isset($newphone_number) && isset($newemail) && isset($newpassword) && isset($newsec_q)){
            if(!empty($newphone_number) && !empty($newemail) && !empty($newpassword) && !empty($newsec_q)){
                if(!preg_match('/^(\+1)?[\s\-]?\(?[0-9]{3}\)?[\s\-]?[0-9]{3}[\s\-]?[0-9]{4}$/', $newphone_number)){
                    $response['response_status'] = '0';
                    $response['response_mess'] = $response['response_mess'] . " Invalid Phone Number";
                }
                if(!filter_var($newemail, FILTER_VALIDATE_EMAIL)){
                    $response['response_status'] = '0';
                    $response['response_mess'] = $response['response_mess'] . " Invalid Email";
                }
                if(!preg_match('/^[a-zA-Z0-9]{8,32}$/', $newpassword)){
                    $response['response_status'] = '0';
                    $response['response_mess'] = $response['response_mess'] . " Invalid Password";
                }
                if(!preg_match('/^[a-zA-Z]{8,12}$/', $newsec_q)){
                    $response['response_status'] = '0';
                    $response['response_mess'] = $response['response_mess'] . " Invalid User Name";
                }
                if(!empty($response['response_mess'])){
                    echo json_encode($response);
                    exit("Invalid Input(s)");
                }
                else{
                    //Connect to database by using PDO
                    $database = new Database();
                    $db = $database->getConnection();
                    if($db['status'] == '0'){
                        $response['response_status'] = '0';
                        $response['response_mess'] = "Connection to database failed: " . $db['message'];
                        echo json_encode($response);
                    }
                    else{
                        //Inserting data into the database
                        try {
                            //Hash the password when we could connect to the database
                            $hash = new hashPassword();
                            $hashedPass = $hash->hashPass($password);

                            $conn = $db['connection'];
                            $query = "select `email` from `user` where `email` = '$email'";
                            $statement = $conn->prepare($query);
                            $statement->execute();
                            $result = $statement->fetchAll(PDO::FETCH_ASSOC);
                            if(!empty($result)){
                                $response['response_status'] = '0';
                                $response['response_mess'] = "You have already Signed Up, Please Log In!";
                                echo json_encode($response);
                            } 
                            else{
                                $query = "insert into user(email,password,phone_number,sec_q,id) VALUES ('$newemail','$hashedPass','$newphone_number','$newsec_q',null)";
                                $statement = $conn->prepare($query);
                                $res = $statement->execute();
                                if(!empty($res)){
                                    $response['response_status'] = '1';
                                    $response['response_mess'] = 'Success!';
                                    echo json_encode($response);

                                }       
                            }
                        }
                        catch (Exception $e) {
                            die("something went wrong".$e->getMessage());
                        }
                    }
                }
            }
            else{
                $response['response_status'] = '0';
                $response['response_mess'] = "All fields must be filed";
                echo json_encode($response);
            }   
        }
        else{
            $response['response_status'] = '0';
            $response['response_mess'] = "Invalid data";
            echo json_encode($response);
        }
        
        
    }
    else{
        $response['response_status'] = '0';
        $response['response_mess'] = "Invalid method Please try again";
        echo json_encode($response);
    }
    
    function test_input($data) {
        $data = trim($data);
        $data = stripslashes($data);
        $data = htmlspecialchars($data);
        return $data;
    }
    
?>