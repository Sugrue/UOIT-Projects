

<?php

require_once "utilities.php";

class ssh {
	private $username, $password, $address, $cmd, $output, $error, $port, $con, $steam, $shell, $logMsg;
	
	function ssh ($fcnUsername, $fcnPassword, $fcnAddress)
	{
		$this->username = $fcnUsername;
		$this->password = $fcnPassword;
		$this->address = $fcnAddress;	
		$this->port = 22;
		
		$logMsg = new logging;
	}
	
	function setUsername ($fcnUsername)
	{
		$this->username = $fcnUsername;
	}
	
	function setPassword ($fcnPassword)
	{
		$this->password = $fcnPassword;
	}
	
	function setAddress ($fcnAddress) 
	{
		$this->address = $fcnAddress;
	}
	
	function setPort ($fcnPort) 
	{
		$this->port = $fcnPort;
	}
	function getPort () {
		return $this->port;			
	}
	function getAddress() {
		return $this->address;
	}
	function getUsername() {
		return $this->username;	
	}
	function getError () {
		return $this->error;
	}
	
	function PRINTSSH ()  {
		echo "SSH CONNECTION INTO:<br>$this->username:$this->password@$this->address:$this->port<br>";			
	}
	function connect() {
		if (!function_exists("ssh2_connect")) {
			$this->error = "Function dos not exist.";
			return FALSE;			
		}
		if (!($this->con = ssh2_connect($this->address, $this->port))) {
			$this->error = "Could not connect to server.";
			return FALSE;
		} else {
			if (!(ssh2_auth_password($this->con, $this->username, $this->password))) {
				$this->error = "Could not authenticate with server.";	
				return FALSE;
			} else {
				$this->error = '';
				return TRUE;	
			}
		}
			
	}
	function close () {
		//fclose($this->shell);
		return true;		
	}
	
	function cmd ($cmd) {		
		$data = "";
		foreach ($cmd as $command) {
			$this->connect();
			if (!($this->stream = ssh2_exec($this->con, $command))) {
				$this->error = "Unable to issue command.";
				return "ERROR";
			} else {
				stream_set_blocking ($this->stream, true);
				while ($buf = fread($this->stream, 4096)) {
					$data .=$buf;
				}
				
			}
			$data .= "\n";
		}
		return "$data";

	}
		
	function multiCmd($cmd) {
		//$this->PRINTSSH();
		$output = array();
		$data = "";
		$this->connect();
		$shell=@ssh2_shell($this->con, 'vt102', null, 80, 24, SSH2_TERM_UNIT_CHARS); 
		
		foreach ($cmd as $command) {
			fwrite($shell, $command.PHP_EOL); 
			sleep(1);
			$temp = "";
		    while($line = fgets($shell)) {
                flush();
				$temp .= $line;
        	}
			array_push($output, $temp);
		}
		return $output;
	}

	
};

?>