<!--Kyle Sugrue - 100483306
INFR 3120 - Improved Website (Midterm)-->

<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head>
<meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
<title>Webpage GENERATOR</title>
<link rel="stylesheet" type="text/css" href="styles.css">
<script src="http://ajax.googleapis.com/ajax/libs/jquery/1.11.1/jquery.min.js"></script>
<script>
//Javascript to control the textboxes, IE. adding text to indicate what each feild is used for. 
	$(document).ready(function () {
		$(document).click(function () {
			if ($("#username").val() == "" && !($("#username").is(":focus")) && !($(".loginButton").is(":focus"))) {
				if ($("#username").attr('class') == "loginTextEmpty") {
					$("#username").val("Username");	
				}
			}
			if ($("#password").val() == "" && !($("#password").is(":focus")) && !($(".loginButton").is(":focus"))) {
				if ($("#password").attr('class') == "loginTextEmpty") {
					$("#password").val("Password");	
					$("#password").attr("type", "text");
				}
			}
		});
		
		$("#username").click (function () {
			if ($("#username").val() == "Username") {
				$("#username").val("");
			}
		});
		$("#password").click (function () {
			if ($("#password").val() == "Password") {
				$("#password").val("");
				$("#password").attr("type", "password");
			}
		});
		$("#username").keyup (function () {
			if ($("#username").val() == "") {
				$("#username").removeClass("loginTextData");
				$("#username").addClass("loginTextEmpty");
			}
		});
		$("#username").keydown (function () {
			if ($("#username").val() != "") {
				$("#username").removeClass("loginTextEmpty");
				$("#username").addClass("loginTextData");
			}
		});
		$("#password").keyup (function () {
			if ($("#password").val() == "") {
				$("#password").removeClass("loginTextData");
				$("#password").addClass("loginTextEmpty");
				$("#password").attr("type" ,"text");
			}
		});
		$("#password").keyup (function () {
			if ($("#password").val() != "") {
				$("#password").removeClass("loginTextEmpty");
				$("#password").addClass("loginTextData");
				$("#password").attr("type" , "password");
			}
		});
	});
	


</script>
</head>

<body>
<?php
//PHP Stores the values in a text file, username password combos are seperated by a |, where as usernames and passwords are divided with a :
//the following conditions are checked: if the username is Username and password is Password, if the user has already been created, and if the username/password combo matches
		$username = $password = "";
		
		if ($_SERVER["REQUEST_METHOD"] == "POST") {
			if (!empty($_POST["create"])) {
				
				if (!empty($_POST["username"]) && !empty($_POST["password"]) && sanitize($_POST["username"]) != "Username" && sanitize($_POST["password"]) != "Password") {
					$duplicate = FALSE;
					
					$myFile = fopen("myFile.txt","r");	
					$userInfo = fgets($myFile);
					$username = sanitize($_POST["username"]);
					$password = sanitize($_POST["password"]);		
					
					$userInfo = explode('|',$userInfo);
					
					foreach ($userInfo as $i) {
						$user = explode(':',$i);
						
						if ($user[0] == $username) {
							$duplicate = TRUE;
							$error = "<p>Username already exists</p>";
							break;
						}
					}
						
						
					if (!$duplicate) {	
						$myFile = fopen("myFile.txt","a") or die("Unable to open file!");
						fwrite($myFile, sanitize($_POST["username"]).":");
						fwrite($myFile, sanitize($_POST["password"])."|");
						fclose ($myFile);	
						$status="<p>User has been created</p>";
					}
       	 		}	else {
					$error = "<p>";
					if (sanitize($_POST["username"]) == "Username") {$error = $error."Username cannot be 'Username'<br>";}
					if (sanitize($_POST["password"]) == "Password") {$error = $error."Password cannot be 'Password'";}
					if (empty($_POST["username"])) {$error = $error."Username is required";}
					if (empty($_POST["password"])) {$error = $error."Password is required";}
					$error = $error."</p>";	
				}
			}
			if (!empty($_POST["login"])) {
				if (!empty($_POST["username"]) && !empty($_POST["password"])) {
					$myFile = fopen("myFile.txt","r");	
					$userInfo = fgets($myFile);
					$username = sanitize($_POST["username"]);
					$password = sanitize($_POST["password"]);		
					
					$userInfo = explode('|',$userInfo);
					
					foreach ($userInfo as $i) 
						if ($username.":".$password == $i) {
							$status = "<p>User found, redirecting...</p>";
							header("Location: genPages.php");
						}
					$error = "<p>Inncorrect Username or Password</p>";
				}
				
			}
		}
		
		function sanitize ($data) {
			return 	htmlspecialchars(stripslashes(trim($data)));
		}	
?>
<center>
<div id="loginPortal">
  <h1>Webpage GENERATOR</h1>
  <form method="post" action="<?php echo htmlspecialchars($_SERVER["PHP_SELF"]); ?>">
    <input type="text" name="username" class="loginTextEmpty" id="username" value="Username">
    <br />
    <input type="text" name="password" class="loginTextEmpty" id="password" value="Password">
    <br />
    <input class="loginButton" type="submit" name="create" value="Create"/>
    <input class="loginButton" type="submit" name="login" value="Login" />
  </form>
  <div class="error"><?php echo $error ?></div>
  <div class="status"><?php echo $status ?></div>
  <br/><p> By Kyle Sugrue - 100483306</p>
</div>

</center>
</body>
</html>
