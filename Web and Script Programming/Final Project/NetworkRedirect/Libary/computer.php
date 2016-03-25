<?php
class computer {
	private $ip , $mac , $expireTimeStamp , $name , $user;
	
	function computer ($fcnIP , $fcnMac , $fcnExpireTimeStamp) {
		$this->setIP($fcnIP);
		$this->setMac($fcnMac);
		$this->setExpireTimeStamp($fcnExpireTimeStamp);
		
	}
	function setIP ($fcnIP) {
		$this->ip = $fcnIP;	
	}
	function setMac ($fcnMac) {
		$this->mac = $fcnMac;	
	}
	function setExpireTimeStamp ($fcnExpireTimeStamp) {
		$this->expireTimeStamp = $fcnExpireTimeStamp;	
	}
	function setName ($fcnName) {
		$this->name = $fcnName;	
	}
	function setUser ($fcnUser) {
		$this->user = $fcnUser;	
	}
	
	function updateIP ($fcnIP, $fcnExpireTimeStamp) {
		$this->setIP($fncIP);
		$this->setExpireTimeStanp($fcnExpireTimeStamp);	
	}
	function getExpireTimeStamp () {
		if ($this->expireTimeStamp == 0) {
			return "Device is Offline";
		} 
		return $this->expireTimeStamp;	
	}
	function getExpireDate () { 
		if ($this->getExpireTimeStamp() == "Device is Offline") {
			return "Device is Offline";
		} 
		$hour = $this->getExpireTimeStamp ()/ 3600 % 24;   
		$minute = $this->getExpireTimeStamp ()/ 60 % 60;   
		$second = $this->getExpireTimeStamp ()% 60; 
		
		return date("H:i:s d/m/y", $this->getExpireTimeStamp());    
	}
	function getUser() {
		return $this->user;	
	}
	function getName() {
		return $this->name;	
	}
	function getIP() {
		if ($this->ip == "") {
			return "Device is Offline";
		} 
		return $this->ip;	
		
	}
	function getMac() {
		return $this->mac;	
	}
	function PRINTCOMPUTER () {
		echo "COMPUTER INFORMATION:<br>
				Name:".$this->getName()."<br>
				IP:".$this->getIP()."<br>
				Mac:".$this->getMac()."<br>
				Lease Exp.:".$this->getExpireDate()." (H:M:S D/M/Y)<br>
				Lease ExpTS:".$this->getExpireTimeStamp()."<br>";
		
	}
	function getComputer() {
		return array(
			'Name' => $this->getName(),
			'IP' => $this->getIP(),
			'MAC' => $this->getMac(),
			'ExpireDate' => $this->getExpireDate(),
			'ExpireTimeStamp' => $this->getExpireTimeStamp(),
			
		);
	}
}
?>