<?php
class Database
{
    private $servername = "localhost";
    private $dbName = "main";
    private $username = "root";
    private $password = "Nicksuper1!";
    public $conn;

    public function getConnection(){
        try{
            $this->conn = new PDO("mysql:host=$this->servername;dbname=$this->dbName", $this->username, $this->password);
            $this->conn->setAttribute(PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION);
            
            //status = '1' for connect to the database properly status = '0' for connect to the databse failed
            $response['status'] = '1';
            $response['connection'] = $this->conn;
            return $response;
        }catch(PDOException $e){
            $response['status'] = '0';
            $response['message'] = $e->getMessage();
            return $response;
        }
        
    }
}   
?>