// JavaScript Document
var cache = new Array();
var ID = "host";
var username = "Log In"
var password = "";
var login = false;
var numComp = 1;
var command = new Array(new Array, new Array);
var xmlhttp;
var redLoc;
var timeout = 9000;
var timeoutCounter = 0;
var currentPC = 0;
var rowId = "";


var email = "email.com"
var firstName = "muchTest";
var lastName = "wow"
var passVer = "suchVerify";



var success = '<div class="alert alert-success" id = "success">\
        <a href="#" class="close" data-dismiss="alert" >&times;</a>\
        <p id = "sucinfo"><i class="fa fa-refresh fa-spin"> </i><strong> Loading,</strong>\
</i> Something Totally Worked. Waiting on Response</p>\
    </div>';


var warn = '<div class="alert alert-danger alert-dismissable">\
   				<button type="button" class="close" data-dismiss="alert" \
      						aria-hidden="true">\
     							 &times;\
   						</button>\
  					<i class="fa fa-exclamation-triangle"></i> Error ! Invalid Username or Password.\
						</div>';





function request(cmd, id) {
   // if (cache[command] != null) {
    //    document.getElementById(id).innerHTML = cache[cmd];
	//	console.log("USING CACHE");
     //   //alert ("USED CACHE " + cache[command]);
      //  return;
   // } else {
        command[0].push(cmd); //array of data
        command[1].push("ID:" + id); //html
        //Queue Commands
        return;
    //}
}

function requestSp(cmd, fct) {
    var nonCached = new Array();

    for (i = 0; i < cmd.length; i++) {
       // if (cache[cmd[i]] != null) {
		//	console.log("USING CACHE");
         //   var fn = window[fct];
          //  if (typeof fn === 'function') {
           //     fn(cache[cmd[0]]);
            //} else {
            //    console.log("requestFct(", cmd[0], ",", fct, " - Undefined Function")
           // }
        //} else {
            nonCached.push(cmd[i]);
        //}
    }
    if (nonCached.length > 1) {
        command[0].push(nonCached[0]);
        command[1].push("[FUNCTION:" + fct);

        for (i = 1; i < nonCached.length - 1; i++) {
            command[0].push(nonCached[i]);
            command[1].push("FUNCTION:" + fct);
        }

        command[0].push(nonCached[nonCached.length - 1]);
        command[1].push("FUNCTION]:" + fct);
    } else if (nonCached.length = 1) {
        command[0].push(nonCached[0]);
        command[1].push("FUNCTION:" + fct);
    } else {
        console.log("requestSp all commands were in cache");
    }
}
function publish(responseText) {
    timeoutCounter = 0;
    console.log("PUBLISHING: " + responseText);
    responseText = responseText.split(";");
    var multiReturn = false;
    var multiReturnData = new Array();

    for (i = 0; i < responseText.length - 1; i++) {
        temp = command[1][0].split(":");

        cache[command[0][0]] = responseText[i];
        if (temp[0] == "ID") {
            console.log(command[0][0], " = ", cache[command[0][0]], " GOING TO ", command[1][0]);
            document.getElementById(temp[1]).innerHTML = cache[command[0][0]];

        } else if (temp[0] == "[FUNCTION") {
            multiReturn = true;
            multiReturnData.push(cache[command[0][0]]);

        } else if (temp[0] == "FUNCTION") {
            if (!multiReturn) {
                var fn = window[temp[1]];
                if (typeof fn === 'function') {
                    fn(new Array(cache[command[0][0]]));
                } else {
                    console.log("publish - Undefined Function")
                }
            } else {
                multiReturnData.push(cache[command[0][0]]);
            }
        } else if (temp[0] == "FUNCTION]") {
            multiReturn = false;
            multiReturnData.push(cache[command[0][0]]);
            var fn = window[temp[1]];

            if (typeof fn === 'function') {
                fn(multiReturnData);
            } else {
                console.log("publish - Undefined Function")
            }
            multiReturnData = new Array();

        } else {
            console.log("Unknown Publish Type");
        }
        command[0].splice(0, 1);
        command[1].splice(0, 1);
    }
    //alert ("REQUESTED " + cache[command]);
    return;
}

setInterval(function sendRequest() {
    if (command[0].toString() != "" && timeoutCounter == 0) {
        console.log("COMMAND ARRAY: ", command[0].toString());
        cmd = "";
        for (i = 0; i < command[0].length; i++) {
            cmd += command[0][i] + ";"
        }
        console.log("SENDING: " + cmd);
        if (window.XMLHttpRequest) {
            // code for IE7+, Firefox, Chrome, Opera, Safari
            xmlhttp = new XMLHttpRequest();
        } else { // code for IE6, IE5
            xmlhttp = new ActiveXObject("Microsoft.XMLHTTP");
        }
        xmlhttp.onreadystatechange = function() {
                if (xmlhttp.readyState == 4 && xmlhttp.status == 200) {
                    console.log("XMLRESPONSE: ", xmlhttp.responseText);
                    publish(xmlhttp.responseText.trim());
                    return true;
                }
            }
            //xmlhttp.open("GET","interface.php?q="+cmd,true);
        xmlhttp.open("POST", "interface.php", true);
        xmlhttp.setRequestHeader("Content-type", "application/x-www-form-urlencoded");
        xmlhttp.send("q=" + cmd);
    }
    timeoutCounter = (timeoutCounter + 500) % timeout;
}, 500);

function pageLoad() {
   
    if (!(checkCookie())) {
		tablePop();
	}
    
	$( "#logoutBut" ).toggle();
	
	




}






function loginFunction() {
   



    username = document.getElementById("userid").value
    password = document.getElementById("passwordinput").value;

    if (username.length < 2 || password.length < 2) {
        alert("Invalid Login");

        $('#alertInfo').prepend(warn);
    } else {




        ID = "account." + username + ":" + password;



        $('#alertInfo').prepend(success);
        $("#success").attr('class', 'alert alert-warning');


        requestSp(new Array(ID + ".login", ID + ".numberOfPC"), "loginVerify");

    }
}

function loginVerify(login) {
   

    if (login[0] == "Login Successful") {

        numComp = login[1];
		console.log("LOGIN 0:" + login[0], " LOGIN 1: "+login[1])
        $("#success").attr('class', 'alert alert-success');
        request(ID + ".login", "sucinfo");
        login = true;
		
		setCookie("username", username, 30);
		setCookie("password", password,30);
		setCookie("numComp", numComp,30);
		
		$( "#logoutBut" ).toggle();
		$( "#loginBut" ).toggle();
		$('#removePCBut').prop('disabled', false)
	    $('#addPCBut').prop('disabled', false)
		
		

        tablePop();

    }

    if (login[0] == "Incorrect Username and/or Password") {
        $("#success").attr('class', 'alert alert-danger');
        request(ID + ".login", "sucinfo");
        logoutFunction();
    }
}




function logoutFunction() {
   

    ID = "host";
    username = "Login"
	
	setCookie("username", username, 30);
	setCookie("password", "",30);
	numComp = 1;
	setCookie("numComp", numComp,30);
    tablePop();

    login = false;
	$( "#logoutBut" ).toggle();
	$( "#loginBut" ).toggle();
	$('#removePCBut').prop('disabled', true)
	  $('#addPCBut').prop('disabled', true)
	
}



function register() {
    
    username = document.getElementById("useridsign").value
    password = document.getElementById("passwordsign").value
    email = document.getElementById("email").value
    firstName = document.getElementById("userFirst").value
    lastName = document.getElementById("userLast").value
    passVer = document.getElementById("reenterpassword").value

    if (password != passVer) {
        
        alert("Passwords do not match");
		logoutFunction();


    } else {

        $('#alertInfo').prepend(success);
        $("#success").attr('class', 'alert alert-warning');


        //register.username.password.firstname.lastname.email.com 
        requestSp(new Array("register." + username + "." + password + "." + firstName + "." + lastName + "." + email), "registerVerify");
        //alert("register." + username + "." + password + "." + firstName + "." + lastName + "." + email);
    }

}

function registerVerify(reg) {
   

    if (reg[0] == "User Created Successfully") {

        $("#success").attr('class', 'alert alert-success');
        request("register." + username + "." + password + "." + firstName + "." + lastName + "." + email, "sucinfo");
        logoutFunction();

    } else {
        $("#success").attr('class', 'alert alert-danger');
        request("register." + username + "." + password + "." + firstName + "." + lastName + "." + email, "sucinfo");
        logoutFunction();


    }


}


function removeComp(){
	
	
//request (account.test:password.removePCfromUser, 
$('#alertInfo').prepend(success);

$("#success").attr('class', 'alert alert-success');
request(ID +".PC." + currentPC + ".removePCfromUser", "sucinfo");	


numComp = numComp - 1;
tablePop();
	
	
}


// Radio button for Location Switch
$(function() {
    $("#locBut").click(function() {
        //alert($("input[name=optionsRadios]:checked").val());
        redLoc = $("input[name=optionsRadios]:checked").val();
        $('#alertInfo').prepend(success);
        request(ID + ".PC.0.redirect." + redLoc, "sucinfo");

    });
});

function redirectFunction() {
    
    location = $("input[name=optionsRadios]:checked").val();

    request(ID + ".PC."+currentPC+".network.redirect." + location, "sucinfo");


}

function addComp() {
    $('#alertInfo').prepend(success);

    request(ID + ".addPCtoUser", "sucinfo");
	requestSp(new Array(ID + ".login", ID + ".numberOfPC"), "loginVerify");
	
	numComp = numComp + 1;
	tablePop();
	



}

function tableLoadComplete(){
	 $(function() {
        $('.table-hover tr').click(function() {
			
			
			
            rowId = $(this).attr("row-key");
			console.log(rowId);
			currentPC = rowId;
			detailPop();
			$(".tableBold").css({ "font-weight": "normal" });
			$(this).css({ "font-weight": "bold" });
			
        });
  });
	
}
 

function tablePop() {
    console.log("this is the tablepop function");

    document.getElementById("user").innerHTML = username;
    console.log("Username = ", username);
    console.log("ID = ", ID);
 	
    $(".tableRow").remove();
    $(".dropdown").remove();
	var detailVar = ' <tr>\
												<td id ="compDetTable" class="tableRow" ></td>\
												<td id ="mtuTable" class="tableRow" ></td>\
                                                <td id ="bandTable" class="tableRow"></td>\
                                                <td id ="delayTable" class="tableRow"></td>\
                                                <td id = "reliTable" class="tableRow"></td>\
                                                <td id = "speedTable" class="tableRow"></td>\
												<td id = "5outTable" class="tableRow"></td>\
												<td id = "5inTable" class="tableRow"></td>\
												<td id = "descTable" class="tableRow"></td>\
                                           </tr>';
	
	
	
	
	
    for (i = 0; i < numComp; i++) {
        d = i + 1;

        var row = '\
                                            <tr row-key="'+ i + '" class ="tableBold">\
												<td id ="hostPcNum' + i.toString() + '" class="tableRow" >' + d.toString() + '</td>\
												<td id ="hostPcName' + i.toString() + '"class="tableRow" ></td>\
                                                <td id ="hostMacTable' + i.toString() + '" class="tableRow"></td>\
                                                <td id ="hostIpTable' + i.toString() + '"class="tableRow"></td>\
                                                <td id = "hostLeaseTable' + i.toString() + '"class="tableRow"></td>\
                                                <td id = "hostBandTable' + i.toString() + '"class="tableRow"></td>\
												 <td id = "locationTable' + i.toString() + '"class="tableRow"></td>\
                                           </tr>';
        var dropdown = '<a href="#"  class="dropdown" ><p id ="dropdown' + i.toString() + '">User PC</p></a>';
		




        $('#tableBody').append(row);
		
		
        $('#dmenu').append(dropdown);
		


        //alert(ID + ".PC." + i.toString() + ".ip");
        request(ID + ".PC." + i + ".name", "hostPcName" + i);
        request(ID + ".PC." + i + ".name", "dropdown" + i);
        request(ID + ".PC." + i + ".ip", "hostIpTable" + i);
        request(ID + ".PC." + i + ".mac", "hostMacTable" + i);
        request(ID + ".PC." + i + ".stats.inputPacket", "hostBandTable" + i);
        request(ID + ".PC." + i + ".lease", "hostLeaseTable" + i);
        request(ID + ".PC." + i + ".redirect.currentRedirect", "locationTable" + i);



	tableLoadComplete();
	
    }
	$('#detailBody').append(detailVar);		
	 


}


function detailPop(){

	
	
	

	 request(ID + ".PC." + currentPC + ".name", "compDetTable"); 									   
	 request(ID + ".PC." + currentPC + ".stats.MTU", "mtuTable"); 	
	 request(ID + ".PC." + currentPC + ".stats.band", "bandTable"); 
	 request(ID + ".PC." + currentPC + ".stats.delay", "delayTable"); 
	 request(ID + ".PC." + currentPC + ".stats.reliability", "reliTable");
	 request(ID + ".PC." + currentPC + ".stats.speed", "speedTable");	
	 request(ID + ".PC." + currentPC + ".stats.5minuteOutputPS", "5outTable"); 	
	 request(ID + ".PC." + currentPC + ".stats.5minuteInputPS", "5inTable"); 
	  request(ID + ".PC." + currentPC + ".stats.description", "descTable"); 							   
										   
			
	
}

function compName() {

    var name = document.getElementById("compName").value;



    $('#alertInfo').prepend(success);


    request(ID + ".PC.0.name.set." + name, "sucinfo");

    tablePop();




}





///////////////////////////////////////COOKIES///////////////////////////////


function setCookie(cname,cvalue,exdays) {
    var d = new Date();
    d.setTime(d.getTime() + (exdays*24*60*60*1000));
    var expires = "expires=" + d.toGMTString();
    document.cookie = cname+"="+cvalue+"; "+expires;
}

function getCookie(cname) {
    var name = cname + "=";
    var ca = document.cookie.split(';');
    for(var i=0; i<ca.length; i++) {
        var c = ca[i];
        while (c.charAt(0)==' ') c = c.substring(1);
        if (c.indexOf(name) != -1) {
            return c.substring(name.length, c.length);
        }
    }
    return "";
}

function checkCookie() {
    username = getCookie("username");
    if (username != "" && username != "Login") {
        alert("Welcome Back " + username);
		password = getCookie("password");
		numComp = getCookie("numComp");
		
		 ID = "account." + username + ":" + password;

        $('#alertInfo').prepend(success);
        $("#success").attr('class', 'alert alert-warning');


        requestSp(new Array(ID + ".login", ID + ".numberOfPC"), "loginVerify");
		return true;
    } else {
       username = "Log In";
	   $('#removePCBut').prop('disabled', true)
	   $('#addPCBut').prop('disabled', true)
	   
	   
       return false;
    }
}








/////////////////////////////













