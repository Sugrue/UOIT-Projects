<?php
	require_once "IOS_device.php";
	require_once "utilities.php";
	require_once "computer.php";
	
	class redirect {
		private $computer, $source, $destIP, $devicePath, $nextHopPath, $db;
		
		function redirect ($fcnComputer, $fcnSource, $fcnDb) {
			$this->devicePath = array();
			$this->nextHopPath = array();
			$this->setComputer($fcnComputer);
			$this->setDb($fcnDb);
			$this->setSource($fcnSource);
		}
		function load ($input) { ##WRONG VALUE IS BEING ADDED...
			if ($input != false) {
				if (!empty($input['instanceData'])) {// && array_key_exists(1,$input['instanceData'])) {
					//$this->setDevicePath($input['instanceData'][1]);	
					$this->setNextHopPath($input['instanceData']);
					$temp =  array();
					foreach ($this->getNextHopPath() as $hop) {
						array_push($temp,$this->getDb()->getNetworkDevice($hop));	
					}
					$this->setDevicePath($temp);
				}
				return true;
			}
			return false;
		}
		function save() {
			return array ( 
					'DestGateway' => $this->getDestIP(),
					'Gateway' => $this->getSource()->getRID(),
					'instanceData' => $this->getNextHopPath(),//$this->getDevicePath(),
					'IP' => $this->getComputer()->getIP(),
					'MAC' => $this->getComputer()->getMac(),
					);
			

		}
		function setDevicePath($fcnDevicePath) {
			$this->devicePath = $fcnDevicePath;	
		}
		function setNextHopPath($fcnNextHopPath) {
			$this->nextHopPath = $fcnNextHopPath;
		}
		function setDb ($fcnDb) {
			$this->db = $fcnDb;	
		}
		function getDb () {
			return $this->db;	
		}
		function setComputer ($fcnComputer) {
			$this->computer=$fcnComputer;
		}
		function getComputer () {
			return $this->computer;
		}
		function setSource ($fcnSource) {
			$this->source = $fcnSource;	
		}
		function getSource () {
			return $this->source;	
		}
		function setDestIP ($fcnDestIP) {
			$this->destIP = $fcnDestIP;	
		}
		function getDestIP () {
			return $this->destIP;	
		}
		function getDestName () {
			if (!($this->getDb()->getNetworkDeviceName($this->getDestIP()))) {
				return "No Redirection is Currently Being Applied";	
			}
			return $this->getDb()->getNetworkDeviceName($this->getDestIP());
		}
		function getDevicePath() {
			return $this->devicePath;	
		}
		function getNextHopPath() {
			return $this->nextHopPath;	
		}
		function isBeingRedirected() {
			if (sizeof($this->getNextHopPath()) < 1 ) {
				return false;	
			}
			return true;
		}
		function findPath ($fcnDestIP) {
			$device = $this->getSource();
			$this->setNextHopPath(array());
			$this->setDevicePath(array());
			array_push($this->nextHopPath, $this->getSource()->getRID());
			
			
			$path = array();
			$this->setDestIP($fcnDestIP);
			$db = $this->getDb();
			
			$LOOPPREVENT = 10;
			do {
				array_push($this->devicePath, $device);
				$temp = $device->getNextHop($this->getDestIP());
				array_push($this->nextHopPath, $temp);
				$device = $db->getNetworkDevice($temp);
				if ($LOOPPREVENT == 1) {
					print "ERROR LOOPPREVENTION TRIGGERED";
					break;	
				} else {
					$LOOPPREVENT -= 1;
				}
			} while ($device->getRID() != $this->getDestIP());
			return true;
		}
		function applyPath () {
			//loop through the path an apply the correct ACL
			$devicePath = $this->getDevicePath();
			
			for ($i = 0; $i < sizeof($devicePath); $i++) {
				$command = array(
							'1' => "conf t",
							'2' => "ip access-list standard NR-OTTAWA-ACL",
							'3' => "permit host ".$this->getComputer()->getIP(),
							);
				$temp = $devicePath[$i]->sendMultiCMD($command);
			}
			
		}
		function removePath() {
			$devicePath = $this->getDevicePath();	
			for ($i = 0; $i < sizeof($devicePath); $i++) {
				$command = array(
							'1' => "conf t",
							'2' => "ip access-list standard NR-OTTAWA-ACL",
							'3' => "no permit host ".$this->getComputer()->getIP(),
							);
				$temp = $devicePath[$i]->sendMultiCMD($command);
				//echo "Removed ACL FROM: ".$devicePath[$i]->getRID()." ";
			}		
			$this->setDevicePath(array());
			$this->setNextHopPath(array());
		}
	

}
?>