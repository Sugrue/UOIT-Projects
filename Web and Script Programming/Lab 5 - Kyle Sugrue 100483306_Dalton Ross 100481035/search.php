<?php
//Kyle Sugrue - 100483306
//Dalton Ross - 100481035
//Web and script Lab 5

	$address = "localhost";
	$username = "root";
	$password = "";
	$database = "lab4";

	
	$html = array ('<html><body>
	<h1>Search Employee</h1>
<p>Welcome to Lab 6-1 Employee Search Page</p>
<form  method="post" action="'.htmlspecialchars($_SERVER["PHP_SELF"]).'">
                                <p>Id: </p><input type="text" id="id" name="id">
                                <p>First Name: </p><input type="text" id="firstName" name="firstName"> 
								<p>Last Name: </p><input type="text" id="lastName" name="lastName">  
                                <p>Department: </p>
                               <select name="department" id="department">
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
	
	//GET FLOORS
	array_push($html,'</select>
					<p>Floor:</p>
					<select name="floor" id="floor">
					<option value="Select..." >Select...</option>');
	$result = $db->query("SELECT * FROM departments");
	
	while ($row = $result->fetch_assoc()) {
		array_push($html, "<option vlaue=".$row['floor'].">".$row['floor']."</option>");	
	}	
	
	array_push($html, '<select>
						<br><input type="submit" value="Enter">
						</form>');

//IF REQUEST, add all the requirements to an array, loop through the array, append " AND " where needed, then append to sql query						
if($_SERVER["REQUEST_METHOD"] == "POST"){	
	$sql = 	"SELECT * from employees INNER JOIN departments on employees.dept=departments.deptID WHERE ";	
	$temp = array();			
	if (!empty($_POST['id'])) {
		array_push($temp," userid ='".post('id')."'");
	}
	if (!empty($_POST['firstName'])) {
		array_push($temp," firstName ='".post('firstName')."'");
	}
	if (!empty($_POST['lastName'])) {
		array_push($temp," lastName ='".post('lastName')."'");
	}
	if (post('department') != "Select...") {
		array_push($temp," deptName ='".post('department')."'");
	}
	if (post('floor') != "Select...")  {
		array_push($temp ," floor ='".post('floor')."'");
	}
	
	for ($i = 0; $i < sizeof($temp) -1 && sizeof($temp) != 1; $i++) { $sql .= $temp[$i]." AND "; }
	
	$sql .= $temp[sizeof($temp)-1];
	$sql .= ";";
	
	
	//If items have been set, query and display
	if ($sql != 	"SELECT * from employees INNER JOIN departments on employees.dept=departments.deptID WHERE ;") {
		$result = $db->query($sql);
		array_push($html, "<h3>Results</h3>");
		
		for ($i = 0; $row = $result->fetch_assoc(); $i++) {
			array_push($html, "<p>".(string)$i."  -  ");
			foreach ($row as $feild) {
				array_push($html, $feild." : "); 
			}
			array_push($html, "</p>");
		}
		array_push($html, "<p>Query: ".$sql."</p>");
	}
}

//push the HTML code
array_push($html, "</body></html>");
	foreach ($html as $temp) {
		echo $temp;	
	}
	
	function clean($data) { return trim(stripslashes(htmlspecialchars($data)));}
	function post($id) { return clean($_POST[$id]); };

?>
