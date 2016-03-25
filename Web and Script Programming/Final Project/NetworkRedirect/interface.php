<?php
//dev
require_once "Libary/IOS_device.php";
require_once "Libary/computer.php";
require_once "Libary/ssh.php";
require_once "Libary/utilities.php";
require_once "Libary/database.php";
require_once "Libary/network.php";
require_once "Libary/adLDAP/src/adLDAP.php";


$query               = array();
$username            = "web";
$password            = "webtest";
$database            = "network";
$address             = "localhost";
$timestamp           = time();
$computerArray       = array();
$ip                  = "";
$host                = "";
$ID                  = "ALL";
$gateway             = NULL;
$gatewayInfo         = getGateway();
$output              = array();
$adldap              = new adLDAP();
$credential          = array(
	'username' => "",
	'password' => ""
);
$userGroup           = array(
	'computerGroup' => array()
);
$userComputer        = array();
$computerArrayUpdate = false;
$network             = NULL;
$multiCache          = false;
$authenicatedID      = "";


if (!empty($_SERVER['HTTP_CLIENT_IP'])) {
	$ip = $_SERVER['HTTP_CLIENT_IP'];
} elseif (!empty($_SERVER['HTTP_X_FORWARDED_FOR'])) {
	$ip = $_SERVER['HTTP_X_FORWARDED_FOR'];
} else {
	$ip = $_SERVER['REMOTE_ADDR'];
}

$db = new database($username, $password, $address, $database);
cleanCache();
$computerArray = getComputerArray();
$computerArray = $db->updateComputers($computerArray);


$ID            = $ip;
$host          = $db->getComputerIP($ID);


if ($host == FALSE) {
	$gateway       = new IOS_device($gatewayInfo['IP'], $username, $password, $gatewayInfo['type'], $gatewayInfo['DHCP']);
	$computerArray = $gateway->getClient();
	$host          = $db->getComputerIP($ID);
	if ($host == FALSE) {
		$host = $db->getComputerMAC("OONH");
	}
}

if (array_key_exists('q', $_GET)) {
	$q       = clean_input($_GET['q']);
} else if (array_key_exists('q', $_POST)) {
	$q       = clean_input($_POST['q']);	
} else {
	die ();	
}
$command = explode(";", $q);
array_pop($command);
$match = preg_grep("/.stats./", $command);
if (sizeof($match) > 1) {
	$pc = array();
	foreach ($match as $statPull) {
		$statPull = explode('.', $statPull);
		array_push($pc, $statPull[3]);
	}
	if (sizeof(array_unique($pc)) > 1) {
		$multiCache = true;
		//echo "Multi Cache";
	}
}
foreach ($command as $cmd) {
	$q   = $cmd;
	$cmd = explode(".", $cmd);
	switch ($cmd[0]) {
		case "data":
			output("DATA");
			break;
		case "host":
			switch ($cmd[1]) {
				case "PC":
					switch ($cmd[2]) {
						case "0":
							switch ($cmd[3]) {
								case "ip":
									output($host->getIP());
									break;
								case "lease":
									output($host->getExpireDate());
									break;
								case "band":
									output("Deprecated, please use stats.band");
									break;
								case "mac":
									output($host->getMac());
									break;
								case "name":
									 if ($host->getName() != "" ) {
										output($host->getName());
									}else{
										output("Un-named PC");
									}
									break;
								case "stats":
									$stats = getStats();
									if ($cmd[4] == "band") {
										output($stats['BW']);
									}
									output("Please Login");
									break;
								case "redirect":
									switch ($cmd[4]) {
										case "ottawa":
											if (redirect("ottawa", $host)) {
												output("Redirection to Ottawa Complete");
											} else {
												die("ERROR REDIRECTING src=dst;");
											}
											break;
										case "oshawa":
											if (redirect("oshawa", $host)) {
												output("Redirection to Oshawa Complete");
											} else {
												die("ERROR REDIRECTING src=dst;");
											}
											break;
										case "currentRedirect":
											if (!empty($network)) {
												output($network->getDestName());
											} else {
												output($db->getRedirectLocation($host->getMac()));
											}
											break;
										default:
											output("ERROR: $cmd[4]/$q");
											break;
									}
									break;
								default:
									output("ERROR: $cmd[3]/$q");
									break;
							}
							break;
						default:
							output("ERROR: $cmd[2]/$q");
							break;
					}
					break;
				default:
					output("ERROR: $cmd[1]/$q");
					break;
			}
			break;
		case "account":
			//authenticate the user
			if ($authenicatedID != $cmd[0] . "." . $cmd[1]) {
				$temp                   = explode(':', $cmd[1]);
				$credential['username'] = $temp[0];
				$credential['password'] = $temp[1];
				if (!($adldap->authenticate($credential['username'], $credential['password']))) {
					output("Incorrect Username and/or Password");
					continue;
				}
				$userGroup['computerGroup'] = getUserGroup();
				$userComputer               = getUserComputer();
				$ID                         = $credential['username'] . "@" . $host->getIP();
				$authenicatedID             = $cmd[0] . "." . $cmd[1];
			}
			switch ($cmd[2]) {
				case "login":
					output("Login Successful");
					continue;
					break;
				case "numberOfPC":
					output(sizeof($userComputer));
					break;
				case "PC":
					$num = (int) $cmd[3];
					if ($num >= sizeof($userComputer)) {
						die("ERROR: $cmd[3]/$q");
					}
					switch ($cmd[4]) {
						case "ip":
							output($userComputer[$num]->getIP());
							break;
						case "mac":
							output($userComputer[$num]->getMac());
							break;
						case "lease":
							output($userComputer[$num]->getExpireDate());
							break;
						case "band":
							output("Deprecated Please use stats.band");
							break;
						case "name":
							if (array_key_exists('5', $cmd) && array_key_exists('6', $cmd)) {
								switch ($cmd[5]) {
									case "set":
										$userComputer[$num]->setName($cmd[6]);
										$db->updateComputer($userComputer[$num]);
										output("Computer Name Was Successfully Updated");
										cleanCacheMac($userComputer[$num]->getMac());
										break;
									default:
										output("ERROR: $cmd[5]/$q");
										break;
								}
							} elseif (array_key_exists('5', $cmd) && !(array_key_exists('6', $cmd))) {
								output("ERROR: Please Specify a Name");
							} else {
								
								
								if ($userComputer[$num]->getName() != "") {
										output($userComputer[$num]->getName());
									}else{
										output("PC ".($num + 1 ));
									}
								
							}
							break;
						case "removePCfromUser":
							removePCfromUser($userComputer[$num]);
							output("This PC has been removed from your account");
							break;	
						case "stats":
							if ($multiCache) {
								getMultiPCstats($userComputer, $gatewayInfo);
								//echo " MultiCache, setting to false/calling function<br>";
								$multiCache = false;
							}
							$PCstats = getPCStats($userComputer[$num], $gatewayInfo);
							switch ($cmd[5]) {
								case "MTU":
									output($PCstats['MTU']);
									break;
								case "band":
									output($PCstats['BW']);
									break;
								case "delay":
									output($PCstats['delay']);
									break;
								case "reliability":
									output($PCstats['reliability']);
									break;
								case "transmitLoad":
									output($PCstats['transmitLoad']);
									break;
								case "receiveLoad":
									output($PCstats['receiveLoad']);
									break;
								case "duplex":
									output($PCstats['duplex']);
									break;
								case "speed":
									output($PCstats['speed']);
									break;
								case "5minuteInputBS":
									output($PCstats['5minuteInputBS']);
									break;
								case "5minuteInputPS":
									output($PCstats['5minuteInputPS']);
									break;
								case "5minuteOutputBS":
									output($PCstats['5minuteOutputBS']);
									break;
								case "5minuteOutputPS":
									output($PCstats['5minuteOuputPS']);
									break;
								case "inputByte":
									output($PCstats['inputByte']);
									break;
								case "outputByte":
									output($PCstats['outputByte']);
									break;
								case "inputPacket":
									output($PCstats['inputPacket']);
									break;
								case "outputPacket":
									output($PCstats['outputPacket']);
									break;
								case "description":
									output($PCstats['description']);
									break;
								default:
									output("ERROR: $cmd[5]/$q");
									break;
							}
							break;
						case "redirect":
							switch ($cmd[5]) {
								case "ottawa":
									if (redirect("ottawa", $userComputer[$num])) {
										output("Redirection to Ottawa Complete");
									} else {
										die("ERROR REDIRECTING src=dst;");
									}
									break;
								case "oshawa":
									if (redirect("oshawa", $userComputer[$num])) {
										output("Redirection to Oshawa Complete");
									} else {
										die("ERROR REDIRECTING src=dst;");
									}
									break;
								case "currentRedirect":
									if ($userComputer[$num]->getIP() == "Device is Offline") {
										output("Device is Offline");
										continue;
									}
									if (!empty($network)) {
										output($network->getDestName());
									} else {
										output($db->getRedirectLocation($userComputer[$num]->getMac()));
									}
									break;
							}
							break;
						default:
							output("ERROR: $cmd[4]/$q");
							break;
					}
					break;
				case "addPCtoUser":
					addPCtoUser();
					output("This PC has been added to your account");
					break;
				case "removePCfromUser":
					removePCfromUser($host);
					output("This PC has been removed from your account");
					break;				
				default:
					output("ERROR: $cmd[2]/$q");
					break;
			}
			break;
			break;
		case "register":
			if (!(array_key_exists(1, $cmd) && array_key_exists(2, $cmd) && array_key_exists(3, $cmd) && array_key_exists(4, $cmd) && array_key_exists(5, $cmd) && array_key_exists(6, $cmd))) {
				output("Missing Arguments");
				continue;
			}
			$attributes = array(
				"username" => $cmd[1],
				"logon_name" => $cmd[1],
				"password" => $cmd[2],
				"firstname" => $cmd[3],
				"surname" => $cmd[4],
				"email" => $cmd[5] . "@" . $cmd[6],
				"container" => array(
					"NR-Users"
				),
				"enabled" => 1,
				"company" => "",
				"department" => "",
				"address_city" => "",
				"address_code" => "",
				"address_country" => "",
				"address_pobox" => "",
				"address_state" => "",
				"address_street" => "",
				"change_password" => "",
				"description" => "",
				"expires" => "",
				"home_directory" => "",
				"home_drive" => "",
				"initials" => "",
				"manager" => "",
				"office" => "",
				"profile_path" => "",
				"script_path" => "",
				"title" => "",
				"telephone" => "",
				"mobile" => "",
				"pager" => "",
				"ipphone" => "",
				"web_page" => "",
				"fax" => "",
				"homephone" => "",
				"group_sendpermission" => "",
				"group_rejectpermission" => "",
				"exchange_homemdb" => "",
				"exchange_mailnickname" => "",
				"exchange_proxyaddress" => "",
				"exchange_usedefaults" => "",
				"exchange_policyexclude" => "",
				"exchange_policyinclude" => "",
				"exchange_addressbook" => "",
				"exchange_altrecipient" => "",
				"exchange_deliverandredirect" => "",
				"exchange_hidefromlists" => "",
				"contact_email" => ""
			);
			if ($adldap->user()->create($attributes)) {
				output("User Created Successfully");
			} else {
				output("ERROR: Unable to Create User");
			}
			break;
			break;
		default:
			output("ERROR: $cmd[0]/$q");
			break;
	}
}
foreach ($output as $temp) {
	echo $temp . ";";
}
function clean_input($data)
{
	return trim(stripslashes(htmlspecialchars($data)));
}
function getGateway()
{
	return array(
		'IP' => "10.255.254.101",
		'type' => "IOS_Switch",
		'DHCP' => '1'
	);
}
function getComputerArray()
{
	global $gatewayInfo, $gateway, $db, $ID, $timestamp, $username, $password;
	$cmd = "getComputerArray";
	if ($db->cacheCheck($ID, $cmd) == FALSE) {
		$gateway       = new IOS_device($gatewayInfo['IP'], $username, $password, $gatewayInfo['type'], $gatewayInfo['DHCP']);
		$computerArray = $gateway->getClient();
		$jsonTemp      = array();
		foreach ($computerArray as $cmp) {
			array_push($jsonTemp, $cmp->getComputer());
		}
		$db->cacheCmd($ID, $cmd, json_encode($jsonTemp), $timestamp);
		updateComputerGroup($computerArray);
		$db->cleanNetworkRedirect();
	} else {
		$jsonTemp      = json_decode($db->cacheCheck($ID, $cmd), true);
		$computerArray = array();
		foreach ($jsonTemp as $temp) {
			$computer = new computer($temp['IP'], $temp['MAC'], $temp['ExpireTimeStamp']);
			$computer->setName($temp['Name']);
			array_push($computerArray, $computer);
		}
	}
	return $computerArray;
}
function updateComputerGroup($fcnComputerArray)
{
	global $adldap;
	// Raw data array returned, returns bool = true
	foreach ($fcnComputerArray as $computer) {
		$result = $adldap->group()->info("NR-" . $computer->getMac());
		if ($result["count"] == 0) {
			$attributes = array(
				"group_name" => "NR-" . $computer->getMac(),
				"description" => "NR AUTO GROUP - COMPUTER AUTHORIZED USER GROUP",
				"container" => array(
					"Groups",
					"NR",
					"Computers"
				)
			);
			if (!($adldap->group()->create($attributes))) {
				die("ERROR CREATING GROUP");
			}
		}
	}
}
function getUserComputer()
{
	global $credential, $computerArray, $db, $adldap, $userGroup;
	$userComputer = array();
	foreach ($userGroup['computerGroup'] as $MAC) {
		array_push($userComputer, $db->getComputerMAC($MAC));
	}
	return $userComputer;
}
function getUserGroup()
{
	global $credential, $adldap;
	$userGroup = array();
	$result    = $adldap->user()->groups($credential['username']);
	foreach ($result as $group) {
		$temp = explode("-", $group);
		if ($temp[0] == "NR") {
			array_push($userGroup, $temp[1]);
		}
	}
	return $userGroup;
}
function addUserToGroup($fcnGroup)
{
	global $adldap, $credential;
	$result = $adldap->group()->addUser($fcnGroup, $credential["username"]);
}
function removeUserFromGroup($fcnGroup)
{
	global $adldap, $credential;
	$result = $adldap->group()->removeUser($fcnGroup, $credential["username"]);
}
function addPCtoUser()
{
	global $host;
	addUserToGroup("NR-" . $host->getMac());
}
function removePCfromUser($fcnComputer)
{
	global $host;
	removeUserFromGroup("NR-" . $fcnComputer->getMac());
}
function getStats()
{
	global $gatewayInfo, $gateway, $db, $ID, $timestamp, $username, $password, $host;
	$cmd = "getStats";
	//changed ID to IP of PC
	if ($db->cacheCheck($host->getMac(), $cmd) === FALSE) {
		$gateway  = new IOS_device($gatewayInfo['IP'], $username, $password, $gatewayInfo['type'], $gatewayInfo['DHCP']);
		$jsonTemp = $gateway->getStat($host);
		$jsonTemp = array_map("commaFilter", $jsonTemp);
		$db->cacheCmd($host->getMac(), $cmd, json_encode($jsonTemp), $timestamp);
		return $jsonTemp;
	} else {
		return json_decode($db->cacheCheck($host->getMac(), $cmd), true);
	}
}
function getPCStats($fcnComputer, $fcnGatewayInfo)
{
	global $db, $ID, $timestamp, $username, $password;
	$cmd = "getStats";
	if ($db->cacheCheck($fcnComputer->getMac(), $cmd) === FALSE) {
		//echo "<br>GETTING NEW INFO FOR: ".$fcnComputer->getMac()."<br>";
		if (empty($gateway)) {
			$gateway = new IOS_device($fcnGatewayInfo['IP'], $username, $password, $fcnGatewayInfo['type'], $fcnGatewayInfo['DHCP']);
		}
		$jsonTemp = $gateway->getStat($fcnComputer);
		$jsonTemp = array_map("commaFilter", $jsonTemp);
		$db->cacheCmd($fcnComputer->getMac(), $cmd, json_encode($jsonTemp), $timestamp);
		return $jsonTemp;
	} else {
		return json_decode($db->cacheCheck($fcnComputer->getMac(), $cmd), true);
	}
}
function getMultiPCstats($fcnComputers, $fcnGatewayInfo)
{
	global $db, $ID, $timestamp, $username, $password, $gateway;
	$cmd = "getStats";
	for ($i = 0; $i < sizeof($fcnComputers); $i++) {
		if ($db->cacheCheck($fcnComputers[$i]->getMac(), $cmd)) {
			unset($fcnComputers[$i]);
		}
	}
	if (empty($fcnComputers)) {
		return;
	}
	$fcnComputers = array_values($fcnComputers);
	if (empty($gateway)) {
		$gateway = new IOS_device($fcnGatewayInfo['IP'], $username, $password, $fcnGatewayInfo['type'], $fcnGatewayInfo['DHCP']);
	}
	$output = $gateway->getStatMultiComp($fcnComputers);
	//echo "<pre>";
	for ($i = 0; $i < sizeof($output); $i++) {
		$jsonTemp = $output[$i];
		$jsonTemp = array_map("commaFilter", $jsonTemp);
		//echo "CACHED: ".$fcnComputers[$i]->getMac().$cmd.json_encode($jsonTemp).$timestamp."<br>";
		$db->cacheCmd($fcnComputers[$i]->getMac(), $cmd, json_encode($jsonTemp), $timestamp);
	}
}
function commaFilter($value)
{
	return trim(trim(preg_replace('/\s\s+/', ' ', $value)), ",");
}
function cleanCache()
{
	global $db, $timestamp;
	$db->cleanCache($timestamp);
}
function cleanCacheMac($mac)
{
	global $db, $timestamp;
	$db->cleanCacheMac($mac, $timestamp);
}
function output($value)
{
	global $output;
	array_push($output, $value);
}
function redirect($fcnDestination, $pc)
{
	global $gateway, $gatewayInfo, $db, $network, $username, $password;
	switch ($fcnDestination) {
		case "ottawa":
			$dstIP = "10.255.254.2";
			break;
		case "oshawa":
			$dstIP = "10.255.254.101";
			break;
		default:
			die("WRONG DESTINATION;");
			break;
	}
	if ($gateway == NULL) {
		$gateway = new IOS_device($gatewayInfo['IP'], $username, $password, $gatewayInfo['type'], $gatewayInfo['DHCP']);
	}
	if (empty($network)) {
		$network = new redirect($pc, $gateway, $db);
		//NEED TO BE CHANGED TO PC IN QUESTION MAC
	}
	$network->load($db->retriveNetworkRedirect($pc->getMac()));
	if ($gateway->getRID() == $dstIP && $network->isBeingRedirected()) {
		$network->removePath();
		//remove redirect
	} elseif ($gateway->getRID() == $dstIP) {
		//ERROR
		return false;
	} else {
		//lets get shit done	
		$network->findPath($dstIP);
		$network->applyPath();
	}
	$db->storeNetworkRedirect($network->save());
	return true;
}
?>