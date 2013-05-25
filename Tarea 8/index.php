 <?php session_start(); ?> 
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">

<html xmlns="http://www.w3.org/1999/xhtml">

<head>
<meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
<title>T! Panel de Login by Fullvice - Home</title>
    <?php
if(isset($_SESSION["conectado"]) && $_SESSION["conectado"] == true){
  	echo '<script type="text/javascript">alert("Su usuario ingreso correctamente.");</script>'; 
	    echo '<h2>Pagina solo para usuarios registrados</h2><br />';
	echo '<a align="left" href="logout.php">Logout<a>';
	
	}
	else
	{
    
	echo 'Debes estar conectado para poder ver el contenido... ';	
	echo '<a href="login.php"> <family="sans-serif">Identificarse</font><a>';
	
}
?> 

</head>

<body>
</body>

</html> 