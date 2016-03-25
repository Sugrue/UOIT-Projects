<?php
class logMessage {
	private $severity, $process, $message;
	
	function logMessage ($fctSeverity, $fctProcess, $fctMessage) {
		$this->message = $fctMessage;
		$this->process = $fctProcess;
		$this->severity = $fctSeverity;
	}
	function getMessage() {
		return "[".$this->severity."] : ".$this->process." - ".$this->message;
	}
};

class logging {
	private $log =  array();

	function logMsg($fctSeverity, $fctProcess, $fctMessage) {
		$message =  new logMessage($fctSeverity, $fctProcess, $fctMessage);
		array_push ($this->log,$message->getMessage());
		
		//echo $this->log[sizeof($this->log)-1]."<br>";	
	}
	function PrintLog () {
		//echo "L#   Svr    Locat   Message<br>";
		foreach ($this->log as $msg) {
			//echo $msg."<br>";		
			
		}
	}
	function PrintLast () {
		//echo $this->log[sizeof($this->log)]->getMessage()."<br>";	
	}
	function livePrint ($fctBool) { }
};
?>
