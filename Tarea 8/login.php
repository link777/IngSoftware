<?php 
	session_start(); 
	if(isset($_SESSION["conectado"])){
    header("Location: index.php");
	}
?> 

<!DOCTYPE html>
<head>
<meta charset="utf-8">
<title>Login</title>
<meta name="description" content="slick Login">
<meta name="author" content="Webdesigntuts+">
<link rel="stylesheet" type="text/css" href="estilo.css" />
<script type="text/javascript" src="http://code.jquery.com/jquery-latest.min.js"></script>
<script src="http://www.modernizr.com/downloads/modernizr-latest.js"></script>
<script type="text/javascript" src="placeholder.js"></script>
</head>
<body>
<form  action="autenticar.php"  method="post" class="login">
    <div><label>Rut</label><input name="rut" type="text" placeholder="Rut" required autocomplete="off"></div>
    <div><label>Password</label><input name="pass" type="password" placeholder="Constraseña" required> </div>
    <div><input name="login" type="submit" value="Autenticar"></div>
</form>

</body>
</html>