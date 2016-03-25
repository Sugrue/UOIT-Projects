<?php
require_once "computer.php";
require_once "utilities.php";
require_once "IOS_device.php";
require_once "network.php";

class database {
	private $db, $username, $password, $address, $dbName, $logMsg;
	
	function database ($fctUsername, $fctPassword, $fctAddress, $fctDbName) {
		$this->setAddress($fctAddress);
		$this->setUsername($fctUsername);
		$this->setPassword ($fctPassword);
		$this->setDbName ($fctDbName);
		
		$this->connect();
		$this->initilize();
		
		$this->logMsg = new logging();
		
	}
	function setAddress ($fctAddress) {
		$this->address = $fctAddress;
	}
	function setUsername ($fctUsername) {
		$this->username = $fctUsername;
	}
	function setPassword ($fctPassword) {
		$this->password = $fctPassword;
	}
	function setDbName ($fctDbName) {
		$this->dbName = $fctDbName;	
	}
	function initilize () {
		$sql =  array (
			'0' => "CREATE DATABASE IF NOT EXISTS network",
			'1' => "use network",
			'2' => "CREATE TABLE IF NOT EXISTS networkDevice (name CHAR(30), type CHAR(30)  NOT NULL, RID CHAR(30) NOT NULL, Username CHAR(30) NOT NULL, Password CHAR(30) NOT NULL, Port CHAR(6), DHCP BOOL , IPs VARCHAR(340) NOT NULL, PRIMARY KEY (RID))",
			'3' => "CREATE TABLE IF NOT EXISTS DHCP (name CHAR(30), IP CHAR(30), MAC CHAR(30) NOT NULL, ExpirationDate CHAR(30), ExpirationDateTS INT NOT NULL, Username CHAR(30), OFFLINE BOOL, CHECKED BOOL, PRIMARY KEY (MAC))",
			'4' => "CREATE TABLE IF NOT EXISTS networkRedirect (IP CHAR(30) NOT NULL, MAC CHAR(30) NOT NULL, Gateway CHAR(30) NOT NULL, DestGateway CHAR(30) NOT NULL, instanceData VARCHAR(1000), PRIMARY  KEY (MAC))",
			'5' => "CREATE TABLE IF NOT EXISTS netCache (cacheTimestamp CHAR(30) NOT NULL, ID CHAR(250) NOT NULL, data VARCHAR(6000), PRIMARY KEY (ID))",
		);
		
		$this->multiQuery($sql);
	}
	function connect () {
		$this->db = new mysqli($this->address, $this->username, $this->password, $this->dbName);

		if ($this->db->connect_error) {
			die("Could not connect to MySQL: ".$this->db->connect_error);
		}
	}
	function multiQuery ($fctMultiQuery) {
		$result = array();
		foreach ($fctMultiQuery as $query) {
			array_push ($result, $this->query($query.";"));
		}
		return $result;
	}
	function query ($fctQuery) {
		try {
			if (!$this->db->connect_error) {		
				if ($result = $this->db->query($fctQuery)) {
					//$this->logMsg->logMsg(3, "database","Query Completed Successfully");
				
					return $result;
				} else {
					//$this->logMsg->logMsg(2,"database","ERROR completing Query:<b>$fctQuery</b>");
					return false;
				}
			} else {
				$this->logMsg->logMsg(1,"database", "ERROR: not connect yet.");	
				return false;
			}
		} catch (Exception $e){
					$this->logMsg->logMsg(1,"database","ERROR: Caught exception");
		}

	}
	function close () {
		$this->db->close();		
	}
	function PRINTDB() {
		echo "DB@".$this->address;	
		return "DB@".$this->address;	
	}
	function addComputer ($fctComputer) {
			$sql = array (
				'1' => "INSERT INTO DHCP (ExpirationDate, ExpirationDateTS, IP, MAC, name, Username, CHECKED) 
				VALUES ('".$fctComputer->getExpireDate()."','".$fctComputer->getExpireTimeStamp()."','". $fctComputer->getIP()."','".$fctComputer->getMac()."','". $fctComputer->getName()."','". $fctComputer->getUser()."',TRUE)",		
			);		
		 	return $this->multiQuery($sql);
	}
	function addComputers ($fctComputers) {
		foreach ($fctComputers as $computer) {
			$this->addComputer($computer);	
		}		
	}
	function updateComputers ($fctComputers) {
		foreach ($fctComputers as $computer) {
				//check mac address			
			$sql = array ('1' => "SELECT * FROM DHCP WHERE MAC='".$computer->getMac()."'",);
			
			$result = $this->multiQuery($sql);
		
			if ($result[0]->num_rows == 1) {	
				//found mac address match	
				$this->logMsg->logMsg(3,"database","Updating Host: MAC Address found: ".$computer->getMac());
				
				$row = $result[0]->fetch_assoc();
				//check if IP Matches
				if ($row['IP'] != $computer->getIP()) {	
					//Not found	
					$this->logMsg->logMsg(3,"database","Updating Host:".$computer->getMac()." MAC Address found: IP address does not match (DHCP/DB)".$computer->getIP()."/".$row['IP']);
					//Update IP, set Checked
					$sql = array ('1' => "UPDATE DHCP SET IP='".$computer->getIP()."', OFFLINE='', CHECKED=TRUE WHERE MAC='".$computer->getMac()."'");
					
					$result = $this->multiQuery($sql);
					$this->logMsg->logMsg(3,"database","UPDATED Host:".$computer->getMac()." MAC Address found: IP address does not match (DHCP/DB)".$computer->getIP()."/".$row['IP']);
				} else {
					
					//Match, set Checked
					$sql = array ('1' => "UPDATE DHCP SET CHECKED=TRUE WHERE MAC='".$computer->getMac()."'");
					
					$this->multiQuery($sql);	
				}
				$sql = array ('1' => "UPDATE DHCP SET ExpirationDateTS='".$computer->getExpireTimeStamp()."', ExpirationDate='".$computer->getExpireDate()."' WHERE MAC='".$computer->getMac()."'");
				$this->multiQuery($sql);
			} else if ($result[0]->num_rows == 0) {
				//Not found - Check for a matching IP
				
				$sql = array ('1' => "SELECT * FROM DHCP WHERE IP='".$computer->getIP()."'");
			
				$result = $this->multiQuery($sql);
		
				if ($result[0]->num_rows > 0) {
					//remove IP from the found host, set the host to Offline, set that host to checked
					$sql = array ('1' => "UPDATE DHCP SET IP='', OFFLINE=TRUE, ExpirationDateTS='', ExpirationDate='', CHECKED=TRUE WHERE MAC='".$computer->getMac()."'");
			
					$result = $this->multiQuery($sql);
					
					
				}
				$this->addComputer($computer);
				
			} else {
				$this->logMsg->logMsg(1,"database","CRITICAL ERROR duplicate MAC addresses");	
			}
		}
		
		//search for all entries with check not set and remove their IPs
		
		//remove check from everyone
		$sql = array ('1' => "UPDATE DHCP SET IP='', OFFLINE=TRUE WHERE CHECKED=FALSE");
			
		$result = $this->multiQuery($sql);
		$sql = array ('1' => "UPDATE DHCP SET CHECKED=FALSE");
			
		$result = $this->multiQuery($sql);
		
		
		$sql = array ("SELECT * FROM DHCP WHERE NAME != ''");
		
		$result = $this->multiQuery($sql);
		if ($result[0]->num_rows > 0) {
			$temp = array (array(),array());
			while ($row = $result[0]->fetch_assoc()) {
				array_push($temp[0],$row['MAC']);
				array_push($temp[1],$row['name']);				
			}
			for ($i = 0; $i < sizeof($fctComputers); $i++) {
				for ($y = 0; $y <  sizeof($temp[0]); $y++) {
					if ($temp[0][$y] == $fctComputers[$i]->getMac()) {
						$fctComputers[$i]->setName($temp[1][$y]);
					}
				}
				
			}				
		}
		
		return $fctComputers;
		
	}
	function updateComputer ($computer) {
		$sql = array ("UPDATE DHCP SET name='".$computer->getName()."', Username='".$computer->getUser()."' WHERE MAC='".$computer->getMac()."'");
		$result = $this->multiQuery($sql);
	}
	function getComputerMAC ($fctMac) {	
		$sql = array ('1' => "SELECT * FROM DHCP WHERE MAC='".$fctMac."'",);
			
		$result = $this->multiQuery($sql);
		
		if ($result[0]->num_rows > 0) {	
				//found mac address match	
				
				$row = $result[0]->fetch_assoc();
				$computer = new computer($row['IP'],$row['MAC'],$row['ExpirationDateTS']);
				
				$computer->setName($row['name']);
				$computer->setUser($row['Username']);
				
				return $computer;				
		} else {
			$this->logMsg->logMsg(2,"database","ERROR could not locate host MAC");
			//return false;
		}
	}
	function getComputerIP ($fctIP) {	
		$sql = array ('1' => "SELECT * FROM DHCP WHERE IP='".$fctIP."'",);
		$result = $this->multiQuery($sql);
		
		if ($result[0]->num_rows > 0) {	
				//found mac address match	
				
				$row = $result[0]->fetch_assoc();
				$computer = new computer($row['IP'],$row['MAC'],$row['ExpirationDateTS']);

				$computer->setName($row['name']);
				$computer->setUser($row['Username']);
				
				return $computer;				
		} else {
			$this->logMsg->logMsg(2,"database","ERROR could not locate host IP");
			//return false;
		}
	}
//	function updateComputer ($fctComputer) {
//		$computer = $this->getComputerMAC($fctComputer->getMac());
//		
//		if ($computer->getIP() == $fctComputer->getIP()) {
//			$sql = array ('1' => "UPDATE DHCP SET NAME='".$fctComputer->getName()."', USERNAME='".$fctComputer->getUser()."' WHERE MAC='".$fctCompter->getMac()."'");
//			$result = $this->multiQuery($sql);
//			$this->logMsg->logMsg(3,"database","INFO: Computer Updated MAC:".$fctComputer->getMac());
//		} else {
//			$this->logMsg->logMsg(2,"database","INFO: IPs are different, not implemented yet.");	
//		}		
//	}
	function formatIP ($fcnIP) {
		$IPs = $fcnIP[0];
		unset($fcnIP[0]);
		foreach ($fcnIP as $IP) {
			$IPs .= ":".$IP;
		}
		return $IPs;
	}
	function addNetworkDevice ($fcnDevice) {
			$sql = array (
				'1' => "INSERT INTO networkDevice (RID, Username, Password, Port, type, DHCP, Name, IPs) 
				VALUES ('".$fcnDevice->getRID()."','".$fcnDevice->getUsername()."','".$fcnDevice->getPassword()."','".$fcnDevice->getPort()."','".$fcnDevice->getType()."','".$fcnDevice->getDHCP()."','".$fcnDevice->getName()."','".$this->formatIP($fcnDevice->getIP())."')",
			);		
		 	return $this->multiQuery($sql);
	}
	function getNetworkDevice ($fcnIP) {
		$sql = array ("SELECT * FROM networkDevice WHERE IPs LIKE '%".$fcnIP."%'");
		$result = $this->multiQuery($sql);
		
		if ($result[0]->num_rows > 0) {
			$row = $result[0]->fetch_assoc();
			return new IOS_device($row['RID'],$row['Username'],$row['Password'],$row['type'],$row['DHCP']);
		} else {
			return FALSE;
		}
	}
	function getNetworkDeviceName ($fcnIP) {
		
		if($fcnIP == "") {return FALSE;};
		$sql = array ("SELECT * FROM networkDevice WHERE IPs LIKE '%".$fcnIP."%'");
		$result = $this->multiQuery($sql);
		
		if ($result[0]->num_rows > 0) {
			$row = $result[0]->fetch_assoc();
			return $row['name'];
		} else {
			return FALSE;
		}
	}
	function getRedirectLocation ($fcnMAC) {
		
		if($fcnMAC == "") {return FALSE;};
		
		$sql = array ("SELECT * FROM networkRedirect WHERE MAC='".$fcnMAC."'");
		$result = $this->multiQuery($sql);
		if ($result[0]->num_rows > 0) {
			$row = $result[0]->fetch_assoc();
			if (!($row['DestGateway'] == "")) {
				return $this->getNetworkDeviceName($row['DestGateway']);
			}
		}
			return "No Redirection is Currently Being Applied";
		
	}	
	function cacheCmd($fcnID,$fcnCmd,$fcnData,$fcnTimestamp) {
		
		if (!($this->cacheCheck($fcnID, $fcnCmd))) {
			$sql = array (
				'1' => "INSERT INTO netCache (cacheTimestamp, data, ID) 
				VALUES ('".$fcnTimestamp."','".$fcnData."','".$fcnID.".".$fcnCmd."')",		
			);		
		 	return $this->multiQuery($sql);
		} else {
			$sql = array (
				'1' => "UPDATE netCache SET cacheTimestamp='".$fcnTimestamp."', data='".$fcnData."' WHERE ID='".$fcnID.$fcnCmd."')",
			);		
		 	return $this->multiQuery($sql);				
		}
	}
	function cacheCheck($fcnID, $fcnCmd) {
		$sql = array ('1' => "SELECT * FROM netCache WHERE ID='".$fcnID.".".$fcnCmd."'",);
			
		$result = $this->multiQuery($sql);
		
		if ($result[0]->num_rows > 0) {	
				$row = $result[0]->fetch_assoc();
				return $row['data'];
		} else {
			return false;
		}
			
			
	}
	function cleanCache($fcnTimestamp) {
		$fcnTimestamp -= 360;
		
		$sql = array ('1' => "DELETE FROM netCache WHERE cacheTimeStamp < '".$fcnTimestamp."'",);
			
		return $this->multiQuery($sql);
		
	}
	function cleanCacheMac ($fcnMAC, $fcnTimestamp) {
		$fcnTimestamp -= 360;
		$sql = array ('1' => "DELETE FROM netCache WHERE MAC LIKE '%".$fcnMAC."%'",);	
		return $this->multiQuery($sql);
	}
	function storeNetworkRedirect ($input) {
		$sql = array ("SELECT * FROM networkRedirect WHERE MAC='".$input['MAC']."'");
		$result = $this->multiQuery($sql);
		
		if ($result[0]->num_rows > 0) {
			$sql = array ("UPDATE networkRedirect SET IP='".$input['IP']."', DestGateway='".$input['DestGateway']."', Gateway='".$input['Gateway']."', instanceData='".json_encode($input['instanceData'])."' WHERE MAC='".$input['MAC']."'");

			return $this->multiQuery($sql);	
			
		} else {
			$sql = array (
					'1' => "INSERT INTO networkRedirect (IP, MAC, DestGateway, Gateway, instanceData)
							VALUES ('".$input['IP']."','".$input['MAC']."','".$input['DestGateway']."','".$input['Gateway']."','".json_encode($input['instanceData'])."')",
						);
			return $this->multiQuery($sql);	
		}
	}
	function retriveNetworkRedirect ($fcnMAC) {
		$sql = array ("SELECT * FROM networkRedirect WHERE MAC='".$fcnMAC."'");
		$result = $this->multiQuery($sql);	
		$output  = array ( 
			'instanceData' => array(),
			);
		if ($result[0]->num_rows != 1) { return false; }	
		$row = $result[0]->fetch_assoc();
		$output = array (
				'IP' => $row['IP'],
				'MAC' => $row['MAC'],
				'DestGateway' => $row['DestGateway'],
				'Gateway' => $row['Gateway'],
				'instanceData' => json_decode($row['instanceData'], true),
				);
		return $output;
		
	}
	function removeRedirect ($fcnComputer) {
		$sql = array ("DELETE FROM networkRedirect WHERE MAC='".$fcnComputer->getMac()."'");
		return $this->multiQuery($sql);		
	}
	function cleanNetworkRedirect() {
		$sql = array("SELECT * FROM networkRedirect");
		$NRresult = $this->multiQuery($sql);
		if ($NRresult[0]->num_rows > 0) {
			while ($NR = $NRresult[0]->fetch_assoc()) {
				$computer = $this->getComputerMAC($NR['MAC']);
				if ($computer->getIP() != $NR['IP']) {
					$temp = $this->retriveNetworkRedirect($computer->getMac());
					$network = new redirect($computer, $this->getNetworkDevice($temp['DestGateway']), $this);
					$network->load($temp);
					$network->removePath();
					$this->removeRedirect($computer);			
				}
			}
			
		}
		
	}
	
};
?>