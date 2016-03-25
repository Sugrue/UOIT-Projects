<?php 
//Kyle Sugrue - 100483306
//Dalton Ross - 100481035
//Web and script Lab 5

	$address = "localhost";
	$username = "root";
	$password = "";
	$database = "lab4";
	
	
$html = array ('<html><body><h1>Add Employee</h1><p>Welcome to Lab 5-1 Add Employee Page</p><form method="POST" action='.htmlspecialchars($_SERVER["PHP_SELF"]).'>
<p>First Name:</p><input type="text" id="firstName" name="firstName">
<p>Last Name:</p><input type="text" id="lastName" name="lastName"> 
<p>Department:</p><select name="department" id="department">
			<option value= "Select..." >Select...</option>');

$db = new mysqli($address, $username, $password, $database);
	if ($db->connect_error) {
		die("Could not connect to MySQL: ".$db->connect_error);
	}
	
	//GET DEPARTMENTS
	$result = $db->query("SELECT * FROM departments");
	
	while ($row = $result->fetch_assoc()) {
		array_push($html, "<option vlaue=".$row['deptName'].">".$row['deptName']."</option>");	
	}
	
	array_push($html, '<select>
						<br><input type="submit" value="Add Employee">
						</form>');
	
	
	//If form has been submitted, and all values are set, insert into table
	if($_SERVER["REQUEST_METHOD"] == "POST"){
		if (!empty($_POST['firstName'])	&& !empty($_POST['lastName'])	 && post('department') != "Select..."){
			
			//get department, name
			$sql = "SELECT deptID from departments WHERE deptName='".post('department')."'";
			$result = $db->query($sql);
			$row = $result->fetch_assoc();
			$deptID = $row['deptID'];
			
			
			//pull all the userID, keeping the last one in memory, +1, then assignment to the new user
			$sql = "SELECT userid from employees";
			$result = $db->query($sql);
			while ($row = $result->fetch_assoc()) {$userid = (int)$row['userid'];}
			$userid += 1;			
			
			$sql = "INSERT INTO employees (dept, firstName, lastName, userid) VALUES ('".$deptID."','".post('firstName')."','".post('lastName')."','".$userid."')";
			
			$db->query($sql);
			array_push($html, "<p>User Created</p><p>Query: $sql</p>");
		}
		
	}
	array_push($html, "</body></html>");
	
	//echo HTML code.
	foreach ($html as $temp) {
		echo $temp;	
	}


	function clean($data) { return trim(stripslashes(htmlspecialchars($data)));}
	function post($id) { return clean($_POST[$id]); };
?>

