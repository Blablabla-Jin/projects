<?php 
    //Database class for connect to the database
    include_once 'database.php';
    
    $searchbox = $_GET["search"];
    $star = $_GET["star"];
    $i = 0;
    //Connect to database by using PDO
    $database = new Database();
    $db = $database->getConnection();
    if($db['status'] == '0'){
        echo "Connection to database failed: " . $db['message'];
    }else{
        try {
            if(empty($searchbox)){
                $query = "select * from restaurants where rate ='$star'";
            }else{
                $query = "select * from restaurants where name ='$searchbox' ";
            }
            $conn = $db['connection'];
            $request = $conn->prepare($query);
            $request->execute();
            while($row =$request->fetch(PDO::FETCH_ASSOC)){
                $arrays[$i]=$row;
                $i++;
            }
            echo json_encode($arrays);
        }
        catch (Exception $e) {
            die("something went wrong".$e->getMessage());
        }
    }
?>