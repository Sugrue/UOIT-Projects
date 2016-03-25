<?php
	require_once "ssh.php";
	require_once "../Libary/IOS_Device.php";
	require_once "../Libary/computer.php";
	
	$switch = new IOS_device("10.255.254.101","web","webtest","IOS_Switch","1");
	
	$cmd = array("terminal length 0","show ip int b","show vlan b");
	$output = $switch->sendMultiCMD($cmd);
	echo "<pre>";
	
	var_dump($output);
		

?>