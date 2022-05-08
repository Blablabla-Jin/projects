<!--Author: Run Zhang, Boming Jin -->
<!DOCTYPE html>
<html lang = "en">

    <head>
        <!--Title that showed in the title bar-->
        <title>Sign Up</title> 
        
        <meta charset="UTF-8">
        <!--let the website look good on all devices-->
        <meta name="viewport" content="width=device-width, initial-scale = 1.0">
        
        <!--link to the external css file-->
        <link rel="stylesheet" href="css/bootstrap.min.css">
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
        <?php
        $emailErr;
        $phoneErr;
        $passErr;
        $userNameErr;

        function test_input($input) {
            $input = trim($input);
            $input = stripslashes($input);
            $input = htmlspecialchars($input);
            return $input;
          }
        ?>
        <div class = "header">
            <div class = "navBar"> 
                <a href = "index.php">To Main Page</a>
            </div>
        </div>
        <div class = "borderForInputs">
            <div class = "captionForInoutBoxes">
                <h1><span class = "TitleSize">Sign Up</span></h1>
            </div>

            <!--Showing message-->
            <div id = "alrt" class="alert alert-success" role="alert" style = "display:none; text-align: center">
                <p class = "title m-0"></p>
            </div>
            <div id = "alrtdanger" class="alert alert-danger" role="alert" style = "display:none; text-align: center">
                <p class = "title m-0"></p>
            </div>

            <!--For future to post information to server sides-->
            <div class = "InputBox">
                <form id = "signUp" method = "post">
                    <label for = "phonenum">Phone Number</label>
                    <br/>
                    <input id = "phonenum" type = "text" name = "PhoneNumber">
                    <br/>
                    <span id = "phoneErr" class="error"></span>
                    <br/>

                    <label for = "email">E-mail Address</label>
                    <br/>
                    <input id = "email" type = "text" name = "EMailAddress">
                    <br/>
                    <span id = "emailErr" class="error"></span>
                    <br/>

                    <label for = "userpw">Password</label>
                    <br/>
                    <input id = "userpw" type = "password" name = "Userpw">
                    <br/>
                    <span class = "notice">*Text/numbers 8-32 long</span>
                    <br/>
                    <span id = "passErr" class="error"></span>
                    <br/>
                    
                    <label for = "username">Username</label>
                    <br/>
                    <input id = "username" name = "Username">
                    <br/>
                    <span class = "notice">*Only text 8-12 long</span>
                    <br/>
                    <span id = "unErr" class="error"></span>
                    <br/>

                    <!--Choose one of two genders-->
                    <label for="male">Male</label>
                    <input id="male" type="radio" name="gender" value="Male">
                    <label for="female">Female</label>
                    <input id="female" type="radio" name="gender" value="Female">
                    
                    <br/><br/>
                    <input id = "submitButton" type = "button" value = "submit" onclick = "signUp();">
                    <input id = "resetButton" type = "reset" value = "reset">
                </form>
            </div>
            
        </div>

        <div class = "footer">
            <p>Author: Run Zhang, Boming Jin &copy; 2021-10-08</p>
        </div>
        
        

    </body>


</html>
<!--Author: Run Zhang, Boming Jin -->
