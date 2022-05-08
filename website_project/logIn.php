<?php
    session_start();
?>

<!--Author: Run Zhang, Boming Jin -->
<!DOCTYPE html>
<html lang = "en">

    <head>
        <!--Title that showed in the title bar-->
        <title>Log In</title>

        <meta charset="UTF-8">
        <!--let the website look good on all devices-->
        <meta name="viewport" content="width=device-width, initial-scale = 1.0">

        <!--link to the external css file-->
        <link rel="stylesheet" href="css/bootstrap.css">
        <link rel="stylesheet" href="css/main.css">
        <!--Google fonts-->
        <link href="//fonts.googleapis.com/css?family=Ubuntu+Mono:400italic,400,700italic,700" rel="stylesheet" type="text/css">
        <!--Animation Library-->
        <link
        rel="stylesheet"
        href="https://cdnjs.cloudflare.com/ajax/libs/animate.css/4.1.1/animate.min.css"
        />

        <!--External JavaScript file-->
        <script src="https://ajax.googleapis.com/ajax/libs/jquery/3.5.1/jquery.min.js"></script>
        <script src="javascript/index.js"></script>
        <!--Set where the window should been opened when clicking hyperlink. Open the document in the same window-->
        <base target = "_self">
    </head>

    <body>
        <div class = "header">
            <div class = "navBar"> 
                <a href = "index.php">To Main Page</a>
            </div>
        </div>
        <div class = "borderForInputs">
            <div class = "captionForInoutBoxes">
            <h1><span class = "TitleSize">Log In</span></h1>
            </div>

            <!--Showing message-->
            <?php
                if(isset($_SESSION['session_mess'])){
                    if(!empty($_SESSION['session_mess'])){
                        $message = $_SESSION['session_mess'];
                        $_SESSION['session_mess'] = '';
                        echo '<div class = "alert alert-danger" style = "text-align: center" role = "alert">' . $message . '</div>';
                    }
                }
            
            
            ?>

            <!--For future to retrieving information-->
            <div class = "InputBox">
                <form method = "post" action="/Toolman/php/signin.php" onsubmit = "return validationForLogIn(this);">
                    <label for = "email">E-mail Address</label>
                    <br/>
                    <input id = "email" type = "text" name = "EMailAddress" value = "<?php 
                                                                                        if(isset($_SESSION['session_status'])){
                                                                                            if(!empty($_SESSION['session_status'])){
                                                                                                if ($_SESSION['session_status'] == 'middle'){
                                                                                                    $emailInput = $_SESSION['email'];
                                                                                                    echo "$emailInput";
                                                                                                }
                                                                                            }
                                                                                        }?>">
                    <br/>
                    <span id = "emailErr" class="error"></span>
                    <br/>

                    <label for = "userpw">Password</label>
                    <br/>
                    <input id = "userpw" type = "password" name = "Userpw">
                    <br/>
                    <span id = "passErr" class="error"></span>
                    <br/>
                    <checkbox>
                    <br/>
                    <input id = "logInButton" type = "submit" value = "Log In">
                    
                </form>
            </div>
        </div>

        <div class = "footer">
                <p>Author: Run Zhang, Boming Jin &copy; 2021-10-08</p>
        </div>
    </body>


</html>
<!--Author: Run Zhang, Boming Jin -->