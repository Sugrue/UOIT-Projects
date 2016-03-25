<?php
	

	require_once "../Libary/IOS_device.php";
	require_once "../Libary/computer.php";
	require_once "../Libary/ssh.php";
	require_once "../Libary/utilities.php";
	require_once "../Libary/database.php";
	require_once "../Libary/network.php";
	
	$logMsg = new logging();
	$db = new database("web","webtest","localhost","network");
	
	$logMsg->logMsg(3, "index", "Setting up Switch");
	$Switch = new IOS_device("10.255.254.101", "web", "webtest", "IOS_Switch", "1");
	
	 
	$logMsg->logMsg(3, "index","Initilizing Device");
	
	$logMsg->logMsg(3, "index","calling getClient");
	$computerArray = $Switch->getClient();
	
	$db->updateComputers($computerArray);
	


	
	if (!empty($_SERVER['HTTP_CLIENT_IP'])) {
    	$ip = $_SERVER['HTTP_CLIENT_IP'];
	} elseif (!empty($_SERVER['HTTP_X_FORWARDED_FOR'])) {
   		$ip = $_SERVER['HTTP_X_FORWARDED_FOR'];
	} else {
    	$ip = $_SERVER['REMOTE_ADDR'];
	}
	
	$host = $db->getComputerIP($ip);
	$temp = $Switch->getStat($host);
	
	echo '<div id="debuging" style="width: 100%; border: 3px black solid"><h3><b>Debug</b></h3>';
	
		$network = new redirect($host,$Switch,"10.255.254.2",$db);
	
	echo "</div>";
?>
<html>
<head>

<title>Network</title>
</head>
<body>
<header>
  <center>
    <h1>Network</h1>
  </center>
</header>
<script src="https://ajax.googleapis.com/ajax/libs/jquery/1.11.1/jquery.min.js"></script>
<script>
function updateHost () {
	$("#hostIP").empty()
	$("#hostIP").append(<?php echo "'".$host->getIP()."'"; ?>);

	$("#hostMAC").empty()
	$("#hostMAC").append(<?php echo "'".$host->getMac()."'"; ?>);
	
	$("#hostName").empty()
	$("#hostName").append(<?php echo "'".$host->getName()."'"; ?>);
		
	$("#hostExpiryDate").empty()
	$("#hostExpiryDate").append(<?php echo "'".$host->getExpireDate()."'"; ?>);
	
	$("#hostExpiryTimeStamp").empty()
	$("#hostExpiryTimeStamp").append(<?php echo "'".$host->getExpireTimeStamp()."'"; ?>);
}

function updateStat () {
	$("#interface").empty();
	$("#interface").append(<?php echo "'".$Switch->getOutput('interface')."'"; ?>);	
	$("#MTU").empty();
	$("#MTU").append(<?php echo "'".$Switch->getOutput('MTU')."'"; ?>);
	$("#BW").empty();
	$("#BW").append(<?php echo "'".$Switch->getOutput('BW')."'"; ?>);
	$("#reliability").empty();
	$("#reliability").append(<?php echo "'".$Switch->getOutput('reliability')."'"; ?>);	
	$("#transmitLoad").empty();
	$("#transmitLoad").append(<?php echo "'".$Switch->getOutput('transmitLoad')."'"; ?>);	
	$("#description").empty();
	$("#description").append(<?php echo "'".$Switch->getOutput("description")."'"; ?>);	
	$("#duplex").empty();
	$("#duplex").append(<?php echo "'".$Switch->getOutput('duplex')."'"; ?>);	
	$("#5minuteInputBS").empty();
	$("#5minuteInputBS").append(<?php echo "'".$Switch->getOutput('5minuteInputBS')."'"; ?>);	
	$("#5minuteInputPS").empty();
	$("#5minuteInputPS").append(<?php echo "'".$Switch->getOutput('5minuteInputPS')."'"; ?>);	
	$("#5minuteOutputPS").empty();
	$("#5minuteOutputPS").append(<?php echo "'".$Switch->getOutput('5minuteOutputPS')."'"; ?>);	
	$("#5minuteOutputBS").empty();
	$("#5minuteOutputBS").append(<?php echo "'".$Switch->getOutput('5minuteOutputBS')."'"; ?>);		
	$("#inputPacket").empty();
	$("#inputPacket").append(<?php echo "'".$Switch->getOutput('inputPacket')."'"; ?>);	
	$("#outputPacket").empty();
	$("#outputPacket").append(<?php echo "'".$Switch->getOutput('outputPacket')."'"; ?>);	
	$("#inputByte").empty();
	$("#inputByte").append(<?php echo "'".$Switch->getOutput('inputByte')."'"; ?>);	
	$("#outputByte").empty();
	$("#outputByte").append(<?php echo "'".$Switch->getOutput('outputByte')."'"; ?>);		
	
}

$(document).ready( function () {
	updateHost();
	updateStat();
});





</script>
<div id="hostInformation" style="float:left; width:49%; height:60%; border: 3px black solid">
  <h3><b>Current Host</b></h3>
  <table>
    <tr>
      <td>IP Address:</td>
      <td id="hostIP"></td>
    </tr>
    <tr>
      <td>MAC Address:</td>
      <td id="hostMAC"></td>
    <tr>
      <td>Host Name:</td>
      <td id="hostName"></td>
    </tr>
    <tr>
      <td>Expiry Date:</td>
      <td id="hostExpiryDate"></td>
    </tr>
    
      <td>Expiry TimeStamp</td>
      <td id="hostExpiryTimeStamp"></td>
    </tr>
  </table>
</div>
<div id="networkOption" style="float:right; width:49%; height:60%; border: 3px black solid">
	<h3><b>Options</b></h3>
  <form action="#" method="post">
    <table>
      <tr>
        <td>Redirect Location:</td>
        <td><select name="Redirect Options">
            <option value="oshawa">Oshawa</option>
            <option value="ottawa">Ottawa</option>
            <option value="tor">TOR</option>
          </select></td>
      </tr>
      
        <td>Host Name:</td>
        <td><input type="text" name="name" /></td>
      </tr>
    </table>
    <input type="submit" value="submit" name="Apply"/>
  </form>
</div>
<div style="clear:both; height:2%;"> </div>
<div id="stat" style="clear:both; width: 99.8%; height: 30%; border: 3px black solid">
  <center><h3><b>Statistics</b></h3></center>
  <div id="left" style="width: 50%; float:left;">
    <table>
      <tr>
        <td>Interface:</td>
        <td id="interface"></td>
      </tr>
      <tr>
        <td>MTU:</td>
        <td id="MTU"></td>
      </tr>
      <tr>
        <td>Reliability:</td>
        <td id="reliability"></td>
      </tr>
      <tr>
        <td>Transmit Load:</td>
        <td id="transmitLoad"></td>
      </tr>
      <tr>
        <td>Interface Description:</td>
        <td id="description"></td>
      </tr>
      <tr>
        <td>Duplex:</td>
        <td id="duplex"></td>
      </tr>
      <tr>
        <td>Bandwidth (link speed):</td>
        <td id="BW"></td>
      </tr>
    </table>
  </div>
  <div id="right" style="width:50%; float:right;">
    <table>
      <tr>
        <td>5 Minute input rate:</td>
        <td id="5minuteInputBS"></td>
        <td id="5minuteInputPS"></td>
      </tr>
      <tr>
        <td>5 Minute output rate:</td>
        <td id="5minuteOutputBS"></td>
        <td id="5minuteOutputPS"></td>
      </tr>
      <tr>
        <td>input packets:</td>
        <td id="inputPacket"></td>
      </tr>
      <tr>
        <td>input bytes:</td>
        <td id="inputByte"></td>
      </tr>
      <tr>
        <td>input Broadcasts:</td>
        <td id="inputBroadcast"></td>
      </tr>
      <tr>
        <td>ouput  packets:</td>
        <td id="outputPacket"></td>
      </tr>
      <tr>
        <td>ouput bytes:</td>
        <td id="outputByte"></td>
      </tr>
    </table>
  </div>
</div>
</body>
</html>