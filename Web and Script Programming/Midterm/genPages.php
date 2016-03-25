<!--Kyle Sugrue - 100483306
INFR 3120 - Improved Website (Midterm)-->
<!DOCTYPE html>
<head>
<script src="http://ajax.googleapis.com/ajax/libs/jquery/1.11.1/jquery.min.js"></script>
<link rel="stylesheet" type="text/css" href="styles.css">
<?php
//PHP to write the files and redirect, input in santized and a basic check is performed.
//1 array is used to store all information regarding the website
//$WebSite 	-> header (website header)
//			-> numWebPage (number of webpages)
//			-> CSS (css file used)
//			-> WebPage
//				-> # (index is numbered, 0-3)
//					->title (title)
//					->linkName (link name)
//					->content (content)
//					->code (HTML code to be used for the page)
// Information is stored in to the array, then the code is generated for each webpage based on the array. A template is used/concatenated with the correct variables (IE. "<html><header><h1>".$WebSite["header"]."  (etc.) everything is then written to the files.

		if ($_SERVER["REQUEST_METHOD"] == "POST") {

			if (!empty($_POST["header"]) && !empty($_POST["numWebpage"])) {
				
				$WebSite = array(
					"header" => sanitize($_POST["header"]),
					"numWebPage" => sanitize($_POST["numWebpage"]),
					"CSS" => 		  " header {
											background-color:#686868;
											color:white;
											text-align:center;
											padding:5px;
										}
										nav {
											line-height:30px;
											background-color:#0066FF;
											text-align:center;
											padding:5px;
										}
										nav ul {
											list-style-type: none;
											margin: 0;
											padding: 0;	
										}
										nav li {
											display: inline;	
										}
										nav a:link, a:visited {
											display: inline-block;
											font-weight: bold;
											color: #FFFFFF;
											background-color: #acd6e1;
											width: 150px;
											text-align:center;
											padding: 4px;
											text-decoration:none;		
										}
										nav a:hover, a:active {
											background-color: #blue	
										}
										article{
											width:100%;
											float:left;
											padding:10px;
										}
										h1 {
											text-transform: uppercase;	
											font-family:\"Times New Roman\", Times, serif;
											font-size:32px;
											color:#0066FF;
										}
										h2 {
											font-family:\"Times New Roman\", Times, serif;
											font-size:24px;
											color:#0099FF;
										}",
									"WebPage" => array(),
									"NavBar" => "",
				);
				
		
				for ($i = 1; $i <= $WebSite["numWebPage"]; $i++) {
					if (!empty($_POST["title".$i]) && !empty($_POST["linkName".$i]) && !empty($_POST["content".$i])) {
						$WebPageTemp = array (
								
								"number" => $i,
								"title" => sanitize($_POST["title".$i]),
								"linkName" => sanitize($_POST["linkName".$i]),
								"content" => sanitize($_POST["content".$i]),
								
							);		
						array_push($WebSite["WebPage"],$WebPageTemp);
						$WebSite["NavBar"] = $WebSite["NavBar"]."<li><a href=\"page".$i.".html\">".$WebSite["WebPage"][$i-1]["linkName"]."</a></li>\r\n";
					} else {
						if (empty($_POST["title".$i])) { $error = $error."<p>Please ensure Page Number ".$i."'s <b>Title</b> is assigned a value.</p>"; }
						if (empty($_POST["linkName".$i])) { $error = $error."<p>Please ensure Page Number ".$i."'s <b>Link Name</b> is assigned a value.</p>"; }
						if (empty($_POST["content".$i])) { $error = $error."<p>Please ensure Page Number ".$i."'s <b>Content</b> is assigned a value.</p>"; }
					}
					
				}
				foreach ($WebSite["WebPage"] as $page) {
						$code = "
											<!DOCTYPE html>
											<html>
												<head>
													<title>".$WebSite["header"]."</title>
													<link rel=\"stylesheet\" href=\"pageCSS.css\">
												</head>
											  <body>
											
												<header>
												<h1>".$WebSite["header"]."</h1>
												</header>
											
												<nav>
													<ul>
														".$WebSite["NavBar"]."
													</ul>
												</nav>
											
											
												<center>	   
												<article>
													<h2>".$WebSite["WebPage"][$page["number"]-1]["title"]."</h2>
													".$WebSite["WebPage"][$page["number"]-1]["content"]."
													<br><br><br>
													<p> Created with WebPage GENERATOR: Kyle Sugrue - 100483306</p>
												</article>
												<cente
											</body> 
											</html>";
						$WebSite["WebPage"][$page["number"]-1]["code"]=$code;

				}

				$myFile = fopen("pageCSS.css","w") or die("Unable to open file!");
				fwrite($myFile, $WebSite["CSS"]);
				fclose($myFile);
				
				foreach ( $WebSite["WebPage"] as $page) {
					$myFile = fopen("page".$page["number"].".html","w") or die("Unable to open file!");
					fwrite($myFile, $page["code"]);
					fclose($myFile);	
					
				}
			} else {
				if (empty($_POST["header".$i])) { $error = "<p>Please ensure that the <b>Header</b> is assigned a value</p>".$error; }
				if (empty($_POST["numWebpage".$i])) { $error = "<p>Please ensure the <b>Number of WebPages</b> is assigned a value</p>".$error; }	
			
			}
				
				if ($error == "") {
					header("Location: page1.html");
				}			
		}
		
		function sanitize ($data) {
			return 	htmlspecialchars(stripslashes(trim($data)));
		}	
?>
<script src="https://ajax.googleapis.com/ajax/libs/jquery/1.11.1/jquery.min.js"></script>
<script>

//javascript is used to generate the textboxes needed which depends on the number entered. The same idea is followed where strings are concatenated then appended to the form within a div.
"use strict";

var webPageBlock = "";
var numberWebPage = 0;

$(document).ready(function(){
 
  $("#numWebpage").on("input prepertychange paste click", function () {
	var value = parseInt(document.getElementById('numWebpage').value);
	
		
	 if (value < 0 || value >= 5 || value == "") {
	 	$("#submit").prop('disabled', true);
		if (!($("#jsError").is(":visible"))) {
			$("#jsError").slideToggle("fast");
		}
		$("#webPageCfg").empty();
		numberWebPage = 0;
	 } else if (value < 5) {
		if ($("#jsError").is(":visible")) {
			$("#jsError").slideToggle("fast");
		}
		 
			 do {
		 		if (value < numberWebPage) {
			 		$("#webPageCfg .webPageBlock:nth-child("+numberWebPage+")").remove();
					numberWebPage = numberWebPage - 1;
					$("#submit").prop('disabled', false);
				 } else if (value > numberWebPage){
			 		
					numberWebPage = numberWebPage +1;
					
					webPageBlock = '<div class="webPageBlock" id="webPageBlock' + numberWebPage.toString() + '"> \
					<h3>Page Number '+numberWebPage.toString()+'</h3><table>\
					<tr><td>Title:</td> <td><input type="text" name="title'+numberWebPage.toString()+'" value="<?php echo $WebSite["WebPage"][numberWebPage-1]["title"]; ?>"></td></tr> \
					<tr><td>Link Name:</td> <td><input type="text" name="linkName'+numberWebPage.toString()+'" value="<?php echo $WebSite["WebPage"][numberWebPage-1]["linkName"]; ?>"><br></td></tr> \
					<tr><td>Content:</td> <td><input type="text" name="content'+numberWebPage.toString()+'" value="<?php echo $WebSite["WebPage"][numberWebPage-1]["title"]; ?>"><br></td></tr></table></div> \
					';

					$("#webPageCfg").append(webPageBlock);
					$("#submit").prop('disabled', false);
			 	} 
			 } while (value != numberWebPage);
			 
	 } 
	  
  });
});

</script>
<title>Webpage GENERATOR</title>
</head>
<body>
<center>
<div id="webPageCreator">
 
  <form method="post" action="<?php echo htmlspecialchars($_SERVER["PHP_SELF"]); ?>">
    <div id="basicInfo">
    <h1>Webpage GENERATOR</h1>
    <table>
    <tr>
      <td>Header:</td>
      <td><input type="text" name="header" value="<?php echo $WebSite["header"]; ?>"></td>
    </tr>
    <tr>
      <td>Number of Webpages:</td>
      <td><input type="text" name="numWebpage" id="numWebpage" value="" ></td>
    </tr>

    </tr>
    </table>
    </div>
    
     <div id="webPageCfg"></div>
     <div class="error">
	<div id="jsError">Number of WebPages must be between 1 and 4.</div>
	<div id="phpError"><?php echo $error; $error =""?></div>
</div>
    <input type="submit" name="create" value="Create" id="submit" disabled/>
  </form>
  <br>
  <p> By Kyle Sugrue - 100483306</p>
</div>


</body>
</html>