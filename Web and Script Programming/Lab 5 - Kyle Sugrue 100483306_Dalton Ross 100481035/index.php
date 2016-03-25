<?php
	$address = "webtest.th";
	$username = "web";
	$password = "webtest";
	$dbName = "lab4";
	
	$db = new mysqli($address, $username, $password, $dbName);
	
	if ($db->connect_error) {
			die("Could not connect to MySQL: ".$db->connect_error);
	}
	echo "<h1>EMPLOYEES</h1><table>";
	$result = $db->query("SELECT * FROM employees");
	$row = $result->fetch_assoc();
	while ($row != NULL) {
		echo "<tr>";
		foreach ($row as $item) {
			echo"<td>$item</td>";
		}
		$row = $result->fetch_assoc();
		echo "</tr>";	
	}
	echo "</table>";
	
	echo "<h1>DEPARTMENTS</h1><table>";
	$result = $db->query("SELECT * FROM departments");
	$row = $result->fetch_assoc();
	while ($row != NULL) {
		echo "<tr>";
		foreach ($row as $item) {
			echo"<td>$item</td>";
		}
		$row = $result->fetch_assoc();
		echo "</tr>";	
	}
	echo "</table>";

?>
