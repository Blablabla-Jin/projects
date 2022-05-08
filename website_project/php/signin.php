<?php 
    session_start();
    //Database class for connect to the database
    include_once 'database.php';
    include_once 'hashPass.php';
    
    $email = $_POST["EMailAddress"];
    $password = $_POST["Userpw"];

    //Check validation of the input
    $newemail = test_input($email);
    $newpassword = test_input($password);

    if ($_SERVER["REQUEST_METHOD"] == "POST"){
        if(isset($email) && isset($password)){
            if(!empty($email) && !empty($password)){

                if(!filter_var($newemail, FILTER_VALIDATE_EMAIL)){
                    $_SESSION['session_status'] = 'middle';
                    $_SESSION['email'] = $newemail;//used for maintain the input of user entered also checked validation
                    $_SESSION['session_mess'] = $_SESSION['session_mess'] . 'Invalid Email';
                }

                if(!preg_match('/^[a-zA-Z0-9]{1,}$/', $newpassword)){
                    $_SESSION['session_status'] = 'middle';
                    $_SESSION['email'] = $newemail;//used for maintain the input of user entered also checked validation
                    $_SESSION['session_mess'] = $_SESSION['session_mess'] . 'Invalid Password';
                }
                if(!empty($_SESSION['session_mess'])){
                    header('Location: /Toolman/logIn.php');
                    exit("Invalid Input(s)");
                }
                else{
                    //Connect to database by using PDO
                    $database = new Database();
                    $db = $database->getConnection();
                    $conn = $db['connection'];
                    if($db['status'] == '0'){
                        echo "Connection to database failed: " . $db['message'];
                    }
                    else{
                        try {
                            //Fetch out the users password from the database
                            $query = "select password from user where email='$email'";
                            $request = $conn->prepare($query);
                            $request->execute();
                            $result = $request->fetchAll(PDO::FETCH_ASSOC);
                            if(!empty($result)){
                                //$result returned array of arrays so need to fetch out the password
                                $pass = $result[0]['password'];
                                
                                //hash the password that users entered for checking
                                $hash = new hashPassword();
                                
                                //check if the password entered by the user is correct
                                if ($hash->verifyPass($password, $pass)){
                                    $query = "select `sec_q` from user where email='$email'";
                                    $request = $conn->prepare($query);
                                    $request->execute();
                                    $result = $request->fetchAll(PDO::FETCH_ASSOC);
            
                                    //$result returned array of arrays so need to fetch out the password
                                    $userName = $result[0]['sec_q'];
                                    //setup super global SESSION things session_status = true for valid, false for invalid, middle for wrong password but have an account
                                    $_SESSION['session_status'] = 'true';
                                    $_SESSION['email'] = $email;//used for maintain the input of user entered
                                    $_SESSION['session_mess'] = '';
                                    header('Location: /Toolman/index.php');
                                }
                                else{
                                    $_SESSION['session_status'] = 'middle';
                                    $_SESSION['email'] = $email;//used for maintain the input of user entered
                                    $_SESSION['session_mess'] = 'Wrong Password';
                                    header('Location: /Toolman/logIn.php');
                                }
                            } 
                            else{
                                $_SESSION['session_status'] = 'false';
                                $_SESSION['session_mess'] = 'No account yet, go sign up';
                                header('Location: /Toolman/logIn.php');
                            }       
                        }
                        catch (Exception $e) {
                            die("something went wrong".$e->getMessage());
                        }
        
                    }
                }
                
            }
            else{
                $_SESSION['session_status'] = 'false';
                $_SESSION['session_mess'] = 'Some fields missing';
                header('Location: /Toolman/logIn.php');
            }   
        
        }
        else{
            $_SESSION['session_status'] = 'false';
            $_SESSION['session_mess'] = 'Invalid input';
            header('Location: /Toolman/logIn.php');
        }
    }
    else{
        $_SESSION['session_status'] = 'false';
        $_SESSION['session_mess'] = 'Invalid mehtod';
        header('Location: /Toolman/logIn.php');
    }

    function test_input($data) {
        $data = trim($data);
        $data = stripslashes($data);
        $data = htmlspecialchars($data);
        return $data;
    }
    
?>