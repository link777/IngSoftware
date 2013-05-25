<?php 
	session_start();
	include('lib/nusoap.php');


	$rut = isset($_POST['rut']) ? $_POST['rut'] : null ;
	$pass = isset($_POST['pass']) ? $_POST['pass'] : null ;

		$passup = strtoupper($pass); // contraseña normal a mayusculas
			$passhash = hash('sha256', $passup); // contraseña en mayusculas a hash sha256

	$parametros = array('rut'=>$rut,'password'=>$passhash); 

	$cliente = new nusoap_client('http://informatica.utem.cl:8011/dirdoc-auth/ws/auth?wsdl','wsdl');
	$error = $cliente->getError();

	
	if ($error)
	{
	 echo '<h2>Constructor error</h2><pre>' . $error . '</pre>';
	}


	$resultado = $cliente->call('autenticar',$parametros); //ingresar el rut y el pass a la operacion 'autenticar'

	$return = $resultado["return"]; 
	$codigo = $return["codigo"]; // obtengo el codigo del resultado del registro, 1 = exito

	
	if($codigo == "1")
        {
			$_SESSION["conectado"] = true;
            header("location:index.php");
        }
        else
	        {
			exit ("<h2>Nombre de usuario o contraseña incorrecta</h2> <a href='javascript:history.back(-1)'>Volver</a>");
	        }
	        


	if ($cliente->fault)
	{
	 echo '<h2>Falla</h2><pre>';
	  print_r($resultado);
	 echo '</pre>';
	} else
		{
		 // Revisa errores
		 $error = $cliente->getError();
		 if ($error)
		 {
		  // Muestra el error
		  echo '<h2>Error</h2><pre>' . $error . '</pre>';
		 } else
			 {
			  // Muestra el resultado
			  echo '<h2>Resultado</h2><pre>';
			   print_r($resultado);
			  echo '</pre>';
			 }
		}

echo '<h2>Debug</h2><pre>' . htmlspecialchars($cliente->debug_str, ENT_QUOTES) . '</pre>';
?>

// 169130264
// 2dd675166dc383a6a52f3164564fa838247ead80f8a45330d20a9cdf64671471