<?php
require_once "ssh.php";
require_once "computer.php";
require_once "utilities.php";



class IOS_device {
	private $hostname, $RID, $username, $password, $IP, $sshConnection, $logMsg, $output, $type, $DHCP; 	

	function IOS_device ($fcnIP, $fcnUsername, $fcnPassword, $fcnType, $fcnDHCP) {
		$this->setPassword($fcnPassword);
		$this->setUsername($fcnUsername);
		$this->setType($fcnType);
		$this->setRID($fcnIP);
		$this->IP = array ();
		if (!($this->sshConnection = new ssh($this->getUsername(),$this->getPassword(),$this->getRID()))) {
			die ($this->sshConnection->PRINTSSH());
		}
		//$this->sshConnection->PRINTSSH();
		$this->getInterface();
		$this->setDHCP($fcnDHCP);		
		$this->logMsg = new logging ();
		$this->output =  array(
			'MTU' => "Not Set",
			'BW' => "Not Set",
			'delay' => "Not Set",
			'reliability' => "Not Set",
			'transmitLoad' => "Not Set",
			'receiveLoad' => "Not Set",
			'duplex' => "Not Set",
			'speed' => "Not Set",
			'5minuteInputBS' => "Not Set",
			'5minuteInputPS' => "Not Set",
			'5minuteOutputBS' => "Not Set",
			'5minuteOutputPS' => "Not Set",
			'inputByte' => "Not Set",
			'inputPacket' =>  "Not Set",
			'outputPacket' => "Not Set",
			'outputByte' => "Not Set",
			'description' => "Not Set",
			);
		
		$this->logMsg->logMsg(3,"IOS Device", "Device Setup: Complete");
		
	}
	function setPort ($fcnPort) {
		$this->sshConnection->setPort($fcnPort);	
	}
	function getPort () {
		return $this->sshConnection->getPort();	
	}
	function setType ($fcnType) {
		$this->type = $fcnType;
	}
	function getType () {
		return $this->type;	
	}
	function setDHCP ($fcnDHCP) {
		$this->DHCP=$fcnDHCP;	
	}
	function getDHCP () {
		return $this->DHCP;	
	}
	function connect () {
		$this->logMsg->logMsg(3,"IOS Device",  "ATTEMPTING TO CONNECT");
		$status = $this->sshConnection->connect();
		
		if ($status == TRUE) {
				$this->logMsg->logMsg(2,"IOS Device",  "Connected");
		} else {
			$status = $this->sshConnection->getError();
			$this->logMsg->logMsg(1,"IOS Device",  "<br><br>==========================<br>$status<br>==========================<br>");	
		}
		return $status;
	}
	function disconnect () {
		$this->sshConnection->close();
	}
	function getUsername () {
		return $this->username;	
	}
	function setUsername ($fctUsername) {
		$this->username = $fctUsername;
	}
	function getPassword () {
		return $this->password;	
	}
	function setPassword ($fctUsername) {
		$this->password = $fctUsername;
	}
	function setRID ($fctRID) {
		$this->RID = $fctRID;	
	}
	function getRID() {
		return $this->RID;	
	}
	function addIP ($fctIP) {
		array_push($this->IP, $fctIP);
	}
	function getIP () {
		return $this->IP;	
	}
	function getName () {
		return $this->hostname;	
	}
	function setName($fcnName) {
		$this->hostname = $fcnName;
	}
	function sendCMD ($cmd) {
			return $this->sshConnection->cmd($cmd);
	}
	function sendMultiCMD($cmd) {
		array_unshift($cmd,"terminal length 0");
		return $this->sshConnection->multiCmd($cmd);
		
	}
	function initilizeDevice () {
		//TEST FUNCTION: to get running config and analyse it
				
		if ($this->connect()) {
				$cmd = array("show run","exit");
				$output = $this->sshConnection->cmd($cmd);
				$testOutSection = explode("!",$output);
				
				//\r splits it by line
				
				echo "<pre>";
				$i=0;
				foreach ($testOutSection as $tempSection) {
						echo "SECTION $i<br>";
						$tempLine = explode ("\r",$tempSection);
						$j=0;
						foreach ($tempLine as $temp) {
							echo "           LINE $j: $temp<br>";
							$j++;	
						}
						//echo "LINE $i:$temp<br>";
						$i++;
				}
				echo "</pre>";
		}
		
	}
	
	function getClient () {
		$j = 0;
		$computerArray = array();
		$mac = '';
		
		$commands = array("show ip dhcp bind");
		$output = $this->sendCMD($commands);
		
		$byLine = explode("\n", $output);
		array_pop($byLine);
		foreach ($byLine as $line) {
			if (!($line[0] == 1)) {
				continue;
			}
			$temp = explode(" ", $line);
			$temp = preg_grep('/^\s*\z/', $temp, PREG_GREP_INVERT);
			$temp = array_values($temp);
			
			$ip = $temp[0];
	
			$strTemp = $temp[1];
			if ($strTemp[0] == '0' && $strTemp[1] == '1') {
				$i = 2;
			} else {
				$i = 0;	
			}
			for ($i=$i; $i<strlen($temp[1]); $i++) {
				if (!($strTemp[$i] == ".")) {
					$mac = $mac . $strTemp[$i];
				}	
			}
			
			$expire = strtotime("$temp[2] $temp[3] $temp[4] $temp[5] $temp[6]");
	
			$temp = new computer($ip,$mac,$expire);
			
			array_push ($computerArray, $temp);
			
			$ip = $mac = $expire = '';
			$j++;
		}
		return $computerArray;
	
	}
	function getStat($fctComputer) {
		$commands = array("show mac address-table | include Fa0/");
		$data = array();
		$output = $this->sendCMD($commands);
		
		$byLine = explode("\n", $output);
		foreach ($byLine as $line) {
			$bySection = explode(" ",$line);
			$temp = array();
			foreach ($bySection as $section) {
				if ($section != "") {
					array_push($temp,$section);	
				}
			}
			array_push($data,$temp);
		
		}
		//echo "DATA: ";
		//var_dump($data);
		foreach ($data as $entry) {
			if (empty($entry)) {continue; }
			$macpart = explode(".",$entry[1]);
			$mac ="";
			foreach ($macpart as $temp) { $mac .= $temp; } 
			
			
			//echo "<br>".$fctComputer->getMac() ."==". $mac; 
			if ($fctComputer->getMac() == $mac) {
				//echo "MATCH";
				$commands = array("show interface ".$entry[3]);
				$output = $this->sendCMD($commands);
		
				$byLine = explode("\n", $output);
				
				//get interface name
				$temp = explode(" ",$byLine[1]);
				$temp = array_values($temp);
				$this->output['interface'] = $temp[0];
				
			//interface description
				$temp = explode(" ",$byLine[3]);
				unset ($temp[0]);
				unset ($temp[1]);
				unset ($temp[2]);
				$desc = "";
				foreach ($temp as $t) { $desc .= $t; }
				$desc = trim(preg_replace('/\s\s+/', ' ', $desc));
				$this->output['description'] = $desc;
				
				
				$temp = explode(" ",$byLine[4]);
				$this->output["MTU"] = $temp[3]." ".$temp[4];
				$this->output["BW"] = $temp[6]." ".$temp[7];
				$this->output["delay"] = $temp[9]." ".$temp[10];
				
				$temp = explode(" ",$byLine[5]);
				$this->output["reliability"] = $temp[6];
				$this->output["transmitLoad"] = $temp[8];
				$this->output["receiveLoad"] = $temp[10];
				
				$temp = explode(" ",$byLine[8]);
				$this->output["duplex"] = $temp[2];
				$this->output["speed"] = $temp[3];
				
				$temp = explode(" ",$byLine[16]);
				$temp[9] = trim(preg_replace('/\s\s+/', ' ', $temp[9]));
				$this->output["5minuteInputBS"] = $temp[6]." ".$temp[7];
				$this->output["5minuteInputPS"] = $temp[8]." ".$temp[9];

				$temp = explode(" ", $byLine[17]);
				$temp[9] = trim(preg_replace('/\s\s+/', ' ', $temp[9]));
				$this->output["5minuteOutputBS"] = $temp[6]." ".$temp[7];
				$this->output["5minuteOutputPS"] = $temp[8]." ".$temp[9];
				
				$temp = explode(" ",$byLine[18]);
				$this->output["inputPacket"] = $temp[5]." ".$temp[6];
				$this->output["inputByte"] = $temp[8]." ".$temp[9];		
				
				$temp = explode(" ",$byLine[24]);
				$this->output["outputPacket"] = $temp[5]." ".$temp[6];	
				$this->output["outputByte"] = $temp[8]." ".$temp[9];
							
				//$this->output = array_map('trim',$this->output);												
				return $this->output;
				//DEMO OUTPUT:
//FastEthernet0/5 is up, line protocol is up (connected) 
//Hardware is Fast Ethernet, address is 0017.9536.8885 (bia 0017.9536.8885) 
//Description: [SW]---[10.0.0.64/29]---[KYLE] 
//MTU 1500 bytes, BW 100000 Kbit, DLY 100 usec, 
//reliability 255/255, txload 1/255, rxload 1/255 
//Encapsulation ARPA, loopback not set 
//Keepalive set (10 sec) 
//Full-duplex, 100Mb/s, media type is 10/100BaseTX 
//input flow-control is off, output flow-control is unsupported 
//ARP type: ARPA, ARP Timeout 04:00:00 
//Last input 00:13:30, output 00:00:00, output hang never 
//Last clearing of "show interface" counters never 
//Input queue: 0/75/0/0 (size/max/drops/flushes); Total output drops: 0 
//Queueing strategy: fifo 
//Output queue: 0/40 (size/max) 
//5 minute input rate 11000 bits/sec, 11 packets/sec 
//5 minute output rate 507000 bits/sec, 35 packets/sec 
//200918041 packets input, 2697219914 bytes, 0 no buffer 
//Received 322428 broadcasts (0 multicasts) 
//0 runts, 1 giants, 0 throttles 
//432 input errors, 431 CRC, 0 frame, 0 overrun, 0 ignored 
//0 watchdog, 243936 multicast, 0 pause input 
//0 input packets with dribble condition detected 
//344878752 packets output, 2547993942 bytes, 2587586 underruns 
//0 output errors, 0 collisions, 1 interface resets 
//0 babbles, 0 late collision, 0 deferred 
//0 lost carrier, 0 no carrier, 0 PAUSE output 
//2587586 output buffer failures, 0 output buffers swapped out
				
				
			}
		}
			return  array(
			'MTU' => "Device is Offline",
			'BW' => "Device is Offline",
			'delay' => "Device is Offline",
			'reliability' => "Device is Offline",
			'transmitLoad' => "Device is Offline",
			'receiveLoad' => "Device is Offline",
			'duplex' => "Device is Offline",
			'speed' => "Device is Offline",
			'5minuteInputBS' => "Device is Offline",
			'5minuteInputPS' => "Device is Offline",
			'5minuteOutputBS' => "Device is Offline",
			'5minuteOutputPS' => "Device is Offline",
			'inputByte' => "Device is Offline",
			'inputPacket' =>  "Device is Offline",
			'outputPacket' => "Device is Offline",
			'outputByte' => "Device is Offline",
			'description' => "Device is Offline",
			);
	}
	function getStatMultiComp ($fcnComputers) {
		$commands = array("show mac address-table | include Fa0/");
		$data = array();
		$output = $this->sendCMD($commands);
		$macArray = array(array(), array());
		
		$byLine = explode("\n", $output);
		foreach ($byLine as $line) {
			$bySection = explode(" ",$line);
			$temp = array();
			foreach ($bySection as $section) {
				if ($section != "") {
					array_push($temp,$section);	
				}
			}
			array_push($data,$temp);
		
		}
		foreach ($data as $entry) {
			if (empty($entry)) { continue; }
			$macpart = explode(".",$entry[1]);
			$mac ="";
			foreach ($macpart as $temp) { $mac .= $temp; } 
			array_push($macArray[0], $mac);
			array_push($macArray[1], $entry[3]);
		}
		
		$command = array();
		foreach ($fcnComputers as $computer) {
			for ($i = 0; $i < sizeof($macArray[0]); $i++) {
				if ($computer->getMac() === $macArray[0][$i]) {
					array_push($command, "show int ".$macArray[1][$i]);	
					continue 2;
				}
			}
			array_push($command, "");
		}
		
		//echo "<br>COMMAND<br /><pre>";
		//var_dump($command);
		
		//var_dump($fcnComputers);
		//echo "MULTIOUT<br />";
		
		$multiOutput = $this->sendMultiCMD($command);
		//var_dump($multiOutput);
		unset($multiOutput[0]);
		$PCstats = array();
		foreach ($multiOutput as $output) {
				if (strlen($output) < 20) { 
				$stats =  array(
			'MTU' => "Device is Offline",
			'BW' => "Device is Offline",
			'delay' => "Device is Offline",
			'reliability' => "Device is Offline",
			'transmitLoad' => "Device is Offline",
			'receiveLoad' => "Device is Offline",
			'duplex' => "Device is Offline",
			'speed' => "Device is Offline",
			'5minuteInputBS' => "Device is Offline",
			'5minuteInputPS' => "Device is Offline",
			'5minuteOutputBS' => "Device is Offline",
			'5minuteOutputPS' => "Device is Offline",
			'inputByte' => "Device is Offline",
			'inputPacket' =>  "Device is Offline",
			'outputPacket' => "Device is Offline",
			'outputByte' => "Device is Offline",
			'description' => "Device is Offline",
			);
				
				array_push($PCstats,$stats);
				
				continue;}
				$stats = array();
				$byLine = explode("\n", $output);
				
				unset($byLine[0]);
				$temp = explode(" ",$byLine[1]);
				$temp = array_values($temp);
				$stats['interface'] = $temp[0];
				
		//Description Line 4
				$temp = explode(" ",$byLine[3]);
				unset ($temp[0]);
				unset ($temp[1]);
				unset ($temp[2]);
				$desc = "";
				foreach ($temp as $t) { $desc .= $t; }
				$desc = trim(preg_replace('/\s\s+/', ' ', $desc));
				$stats['description'] = $desc;
				
		//5
				$temp = explode(" ",$byLine[4]);
				$stats["MTU"] = $temp[3]." ".$temp[4];
				$stats["BW"] = $temp[6]." ".$temp[7];
				$stats["delay"] = $temp[9]." ".$temp[10];
				
				$temp = explode(" ",$byLine[5]);
				$stats["reliability"] = $temp[6];
				$stats["transmitLoad"] = $temp[8];
				$stats["receiveLoad"] = $temp[10];
				
				$temp = explode(" ",$byLine[8]);
				$stats["duplex"] = $temp[2];
				$stats["speed"] = $temp[3];
				
				$temp = explode(" ",$byLine[16]);
				$temp[9] = trim(preg_replace('/\s\s+/', ' ', $temp[9]));
				$stats["5minuteInputBS"] = $temp[6]." ".$temp[7];
				$stats["5minuteInputPS"] = $temp[8]." ".$temp[9];

				$temp = explode(" ", $byLine[17]);
				$temp[9] = trim(preg_replace('/\s\s+/', ' ', $temp[9]));
				$stats["5minuteOutputBS"] = $temp[6]." ".$temp[7];
				$stats["5minuteOutputPS"] = $temp[8]." ".$temp[9];
				
				$temp = explode(" ",$byLine[18]);
				$stats["inputPacket"] = $temp[5]." ".$temp[6];
				$stats["inputByte"] = $temp[8]." ".$temp[9];		
				
				$temp = explode(" ",$byLine[24]);
				$stats["outputPacket"] = $temp[5]." ".$temp[6];	
				$stats["outputByte"] = $temp[8]." ".$temp[9];	
			
				array_push($PCstats,$stats);
		}
		
		return $PCstats;
		
	}
	function getOutput($fctOutput) {
		if (array_key_exists($fctOutput, $this->output)) {
			return $this->output[$fctOutput];
		} else {
			return "Invalid Index, ".$fctOutput;
		}
			
	}
	function getInterface() {	
		$command = array("show ip int b | ex unass");
		$output = $this->sendCMD($command);
		
		$byLine = explode("\n", $output);
		unset($byLine[0], $byLine[1]);
		array_pop($byLine);
		
		if ($this->getType() == "IOS_Switch") {
			foreach ($byLine as $line) {
				$temp = explode(" ", $line);
				$temp = preg_grep('/^\s*\z/', $temp, PREG_GREP_INVERT);
				$temp = array_values($temp);
				$this->addIP($temp[1]);
			}	
		} else if ($this->getType() == "IOS_Router") {
			array_pop($byLine);
			foreach ($byLine as $line) {
				$temp = explode(" ", $line);
				$temp = preg_grep('/^\s*\z/', $temp, PREG_GREP_INVERT);
				$temp = array_values($temp);
				$this->addIP($temp[1]);
			}			
		} else {
			die("INNCORRECT DEVICE TYPE");	
		}
	}
	function getNextHop($fcnIP) {
		$command = array("show ip route | in ".$fcnIP);
		$output = $this->sendCMD($command);
		
		$byLine = explode("\n", $output);
		$temp = explode(" ", $byLine[0]);
		if ($temp[0] == 'C') {
				return $fcnIP;
		} 
		if ($this->getType() == "IOS_Switch") {
				return trim($temp[10],",");
		} else {
			return trim($temp[11],",");
		}
	}
}
?>