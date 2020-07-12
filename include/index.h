const char MAIN_page[] = R"=====(<!DOCTYPE html>
<html>
<head>
  <meta name="viewport" content="width=device-width,initial-scale=1,maximum-scale=1,user-scalable=no">
  <meta http-equiv="X-UA-Compatible" content="IE=edge,chrome=1">
  <meta name="HandheldFriendly" content="true">
  <link rel=\"icon\" href=\"data:,\">
  <style>
    html {
      font-family: Helvetica;
      display: inline-block;
      margin: 0px auto;
      text-align: center;
    }

    body {
      margin: 0;
      height: 100vh;
    }

    .button {
      background-color: #4CAF50;
      border: none;
      color: white;
      height: 80px;
      width: 100px;
      text-decoration: none;
      font-size: 25px;
      margin: 2px;
      cursor: pointer;
    }

    .button2 {
      background-color: #555550;
      border: none;
      color: white;
      height: 80px;
      width: 100px;
      text-decoration: none;
      font-size: 25px;
      margin: 2px;
      cursor: pointer;
    }

    @media screen and (max-width: 1060px) {
      #primary {
        width: 67%;
      }

      #secondary {
        width: 30%;
        margin-left: 3%;
      }
    }

    @media screen and (max-width: 768px) {
      #primary {
        width: 100%;
      }

      #secondary {
        width: 100%;
        margin: 0;
        border: none;
      }
    }

    .video-container {
      height: calc(100vh - 300px);
    }

    .video-container iframe,
    .video-container object,
    .video-container embed {
      max-width: 100%;
      height: 100%;
    }
</style>
</head>
 
  <body><h1>Robot Navigation</h1>
  <div class="video-container">
  <iframe width="510" height="315" src="http://youtube.com" 
  frameborder="0" allow="accelerometer; autoplay; encrypted-media; gyroscope; picture-in-picture" allowfullscreen></iframe>
  </div>
<p>Enter W,S,A,D,Q..
<input id="myInput"  value=""></p>
<p><button     id='F' class="button2" onclick="sendData('f')">Front</button></p>
	<p><button id='L' class="button2" onclick="sendData('l')">Left</button>
	   <button id='S' class="button2" onclick="sendData('s')">Stop</button>
	   <button id='R' class="button2" onclick="sendData('r')">Right</button></p>
	<p><button id='B' class="button2" onclick="sendData('b')">Back</button></p>

	
  <script>
	var input = document.getElementById("myInput");

	input.addEventListener("keyup", function(event) {
	   event.preventDefault();
	  if (event.keyCode === 87 || event.keyCode === 119) {
	   document.getElementById("F").click();
	   
	  }else if (event.keyCode === 97 || event.keyCode === 65){
		document.getElementById("L").click();
		
	  }else if (event.keyCode === 81 || event.keyCode === 113){
		document.getElementById("S").click();
		
	  }else if (event.keyCode === 68 || event.keyCode === 100){
		document.getElementById("R").click();
		
	  }else if (event.keyCode === 115 || event.keyCode === 83){
		document.getElementById("B").click();
	  }
	  document.getElementById("myInput").value = "";
	});
  
    function sendData(flag) 
    {	
      var ID;
      var xhttp = new XMLHttpRequest();
      xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      ID = this.responseText;
      toggleClass(ID);
    }
  };
	    xhttp.open("GET",""+flag, true);
	    xhttp.send();
	  }
    
    function toggleClass(id)
	  {
      var ids , i, ilen;
	    ids = ['F', 'L' ,'S' , 'R' , 'B'];
	    ilen = ids.length;
      for(i=0 ; i<ilen ;i++){
        if(ids[i] == id){document.getElementById(id).className = 'button';}	
        else{document.getElementById(ids[i]).className = 'button2';}       
       }
	  }
	</script>
 	
  </body></html>)=====";