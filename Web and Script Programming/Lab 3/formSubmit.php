<!DOCTYPE html>
<!-- Kyle Sugrue - 100483306 | Dalton Ross - 100481035 -->
<head>
<?php 
function post($data) {
	return sanitize($_POST[$data]);	
}

function sanitize ($data) {
	return 	htmlspecialchars(stripslashes(trim($data)));
}


if ($_SERVER["REQUEST_METHOD"] == "POST") {
			$name = post("name");
			$email = post("email");
			$message = post("message");
				
			if ($name != "" && $email != "" && $message != "") {
				$result = "<h1>Thank you for you email!</h1>";
				$result = $result."<p>Hello <b>".$name."</b>,<br>";	
				$result = $result."Thank you for your email. A representative will send a reply to <b>".$email."</b> as soon as possible.</p><br>";
				
			} else {
				$error = "<div id=\"error\" style=\"color:red\"><h1>Error</h1><p>";
				if ($name == "") { $error = $error."Please enter your name.<br>"; }
				if ($email == "") { $error = $error."Please enter your email address.<br>"; }
				if ($message == "") { $error = $error."Please enter your message.<br>"; }
				$error = $error."</p></div>";
				
				$error = $error."<p>Click <a href=\"contact.php\">here</a> to go back.";
			}
}


?>

<title>Thank you!</title>
</head>



<body>

<?php echo $error; ?>
<?php echo $result; ?>
</body>
</html>