<?php 
//Database class for connect to the database
include_once 'database.php';

class hashPassword
{
    public function hashPass($passInserted){
        $hashedPass = password_hash($passInserted, PASSWORD_BCRYPT);
        return $hashedPass;
    }

    //verify if entered password is the same as the one stored in the database
    public function verifyPass($passInserted, $hashedPass){
        return password_verify($passInserted, $hashedPass);
    }
}
?>