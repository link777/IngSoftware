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
<link rel="stylesheet" type="text/css" href="estilo/estilo.css" />
<script type="text/javascript" src="http://code.jquery.com/jquery-latest.min.js"></script>
<script src="http://www.modernizr.com/downloads/modernizr-latest.js"></script>
<script type="text/javascript" src="jquery/jquery.js" ></script>
<script type="text/javascript" src="jquery/jquery.validate.js"></script>
<script type="text/javascript" src="jquery/jquery.Rut.js"></script> 
<script>
  $(document).ready(function()
  {
      $("#login").validate(
          $('#rut').Rut({
            on_error: function(){ alert('Rut incorrecto'); },
            format_on: 'keyup'
          })
      );
  });
</script>

<script>
  $.validator.addMethod("rut", function(value, element) {
    return this.optional(element) || $.Rut.validar(value);
  }, "Debe tener un rut valido.");

  $("#jq-validation").validate();
  $.validator.messages.required = 'Debe llenar este campo.';
</script>


<script>
/*
jQuery.extend(jQuery.validator.messages, {
    required: "This field is required.",
    remote: "Please fix this field.",
    email: "Please enter a valid email address.",
    url: "Please enter a valid URL.",
    date: "Please enter a valid date.",
    dateISO: "Please enter a valid date (ISO).",
    number: "Please enter a valid number.",
    digits: "Please enter only digits.",
    creditcard: "Please enter a valid credit card number.",
    equalTo: "Please enter the same value again.",
    accept: "Please enter a value with a valid extension.",
    maxlength: jQuery.validator.format("Please enter no more than {0} characters."),
    minlength: jQuery.validator.format("Please enter at least {0} characters."),
    rangelength: jQuery.validator.format("Please enter a value between {0} and {1} characters long."),
    range: jQuery.validator.format("Please enter a value between {0} and {1}."),
    max: jQuery.validator.format("Please enter a value less than or equal to {0}."),
    min: jQuery.validator.format("Please enter a value greater than or equal to {0}.")
});*/
</script>



</head>
<body body onload="rut.focus()">
<form  id="login" action="autenticar.php"  method="post" class="login">
    <div><label>Rut</label><input name="rut" id="rut" type="text" class="required rut" maxlength="12" placeholder="Rut" autocomplete="off" required></div>
    <div><label>Password</label><input name="pass" type="password" placeholder="Constraseña" required> </div>
    <div><input name="login"  type="submit" value="Autenticar"></div>
</form>

</body>
</html>