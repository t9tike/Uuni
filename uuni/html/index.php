<!DOCTYPE html>
<meta name="viewport" content="width=device-width, initial-scale=1">
<html lang="en">
<head>
<style>
.content{
    text-align:center;
    font-size: 2rem;
    color: #FFC300;  
}



</style>
    <meta charset="UTF-8" />
    <meta name="viewport" content="width=device-width, initial-scale=1.0" />
</head>
<body class="content" style="background-color:#2C3E50">
<header>
          <nav>
              <h1>UUNI</h1>
          </nav>
      </header>
  <div id="show" align="center"></div>
  <div align="center">
	<img src="images/1.jpeg" alt="Uunin näyttö" id="uuni">
  </div>
  
  <script type="text/javascript" src="jquery.js"></script>
  <script type="text/javascript">
	  
	  
	  
        $(document).ready(function() {
				d =new Date();
                $('#show').load('db_connection.php')
                $('#uuni').attr("src", "images/1.jpeg?"+d.getTime());
                refresh();                              
        });
        
        function refresh(){
			setTimeout(function (){
				d =new Date();
                $('#show').load('db_connection.php')
                $('#uuni').attr("src", "images/1.jpeg?"+d.getTime());
                refresh();
            }, 1000);
		}
        
  </script>

          <iframe width="285" height="345" src="https://www.youtube.com/embed/8pPGqp05clI">
          </iframe>    
          
          
          
           
  </body>
</html>
