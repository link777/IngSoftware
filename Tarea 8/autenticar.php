<?php 
	include('lib/nusoap.php');

	$rut = $_POST['rut'];
	$pass = $_POST['pass'];
		$passup = strtoupper($pass); // contraseña normal a mayusculas
		$passhash = hash('sha256', $passup); // contraseña en mayusculas a hash sha256

	$parametros = array('rut'=>$rut,'password'=>$passhash);

	$cliente = new nusoap_client('http://informatica.utem.cl:8011/dirdoc-auth/ws/auth?wsdl','wsdl');
	$error = $cliente->getError();

	if ($error)
	{
	 echo '<h2>Constructor error</h2><pre>' . $error . '</pre>';
	}


	$resultado = $cliente->call('autenticar',$parametros);

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