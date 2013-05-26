<?php 
	header("Content-type: text/html; charset=utf8");
	session_start();
	include('lib/nusoap.php');


	$rut = isset($_POST['rut']) ? $_POST['rut'] : null ;
	$pass = isset($_POST['password']) ? $_POST['password'] : null ;

		$passup = strtoupper($pass); // contraseña normal a mayusculas
			$passhash = hash('sha256', $passup); // contraseña en mayusculas a hash sha256

	$parametros = array('rut'=>$rut,'password'=>$passhash); 

	$cliente = new nusoap_client('http://informatica.utem.cl:8011/dirdoc-auth/ws/auth?wsdl','wsdl');
	$error = $cliente->getError();

	
	if ($error)
	{
	 echo '<txt>Constructor error</txt><pre>' . $error . '</pre>';
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
			exit ("<txt>Rut o contraseña incorrecta</txt> <a href='javascript:history.back(-1)'>Volver</a>");
	        }
	        

/* 

// Funciones que guardan los errores

	if ($cliente->fault)
	{
	 echo '<txt>Falla</txt><pre>';
	  print_r($resultado);
	 echo '</pre>';
	} else
		{
		 // Revisa errores
		 $error = $cliente->getError();
		 if ($error)
		 {
		  // Muestra el error
		  echo '<txt>Error</txt><pre>' . $error . '</pre>';
		 } else
			 {
			  // Muestra el resultado
			  echo '<txt>Resultado</txt><pre>';
			   print_r($resultado);
			  echo '</pre>';
			 }
		}

// Debug en caso de error

echo '<txt>Debug</txt><pre>' . htmlspecialchars($cliente->debug_str, ENT_QUOTES) . '</pre>';
*/
?>
