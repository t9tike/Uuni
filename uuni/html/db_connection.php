<?php
$conn = new mysqli('', '', '', '');
if ($conn->connect_error){
    die("Connection error: " . $conn->connection_error);
}
$result1 = $conn->query("SELECT * FROM NTC1 ORDER BY temperature_id DESC LIMIT 1");
$result2 = $conn->query("SELECT * FROM NTC2 ORDER BY temperature_id DESC LIMIT 1");
$result3 = $conn->query("SELECT * FROM KTYPE1 ORDER BY temperature_id DESC LIMIT 1");
$result4 = $conn->query("SELECT * FROM KTYPE2 ORDER BY temperature_id DESC LIMIT 1");
if($result1->num_rows > 0) {
    while($row = $result1->fetch_assoc()) {
		echo "<tr>";
        ?><td style="padding:10px; border:2px solid #FFC300; text-align: center; color:color:#FFC300; font-size:2.0rem;>"<?php
        echo "<td border='1'>Anturi 1</td>";
        ?><td style="border:1px solid #FFC300; text-align: center; color:#FF5733; font-size:2.25rem;>"<?php
	echo "<td border='1'>".$row['temperature']."</td>";
	?><td style="border:1px solid #FFC300; text-align: center; color:#FFC300; font-size:2.25rem;>"<?php
	echo "<td border='1'>".$row['time']."</td>";         
        
    }
}
if($result2->num_rows > 0) {
    while($row = $result2->fetch_assoc()) {
        	echo "<tr>";
        ?><td style="padding:10px; border:2px solid #FFC300; text-align: center; color:color:#FFC300; font-size:2.0rem;>"<?php
        echo "<td border='1'>Anturi 2</td>";
        ?><td style="border:1px solid #FFC300; text-align: center; color:#FF5733; font-size:2.25rem;>"<?php
	echo "<td border='1'>".$row['temperature']."</td>";
	?><td style="border:1px solid #FFC300; text-align: center; color:#FFC300; font-size:2.25rem;>"<?php
	echo "<td border='1'>".$row['time']."</td>";          
                 
        
    }
}
if($result3->num_rows > 0) {
    while($row = $result3->fetch_assoc()) {
        	echo "<tr>";
        ?><td style="padding:10px; border:2px solid #FFC300; text-align: center; color:color:#FFC300; font-size:2.0rem;>"<?php
        echo "<td border='1'>Anturi 3</td>";
        ?><td style="padding:10px; border:1px solid #FFC300; text-align: center; color:#FF5733; font-size:2.25rem;>"<?php
	echo "<td border='1'>".$row['temperature']."</td>";
	?><td style="padding:10px; border:1px solid #FFC300; text-align: center; color:#FFC300; font-size:2.25rem;>"<?php
	echo "<td border='1'>".$row['time']."</td>";            
                 
        
    }
}
if($result4->num_rows > 0) {
    while($row = $result4->fetch_assoc()) {
        	echo "<tr>";
        ?><td style="padding:10px; border:2px solid #FFC300; text-align: center; color:color:#FFC300; font-size:2.0rem;>"<?php
        echo "<td border='1'>Anturi 4</td>";
        ?><td style="border:1px solid #FFC300; text-align: center; color:#FF5733; font-size:2.25rem;>"<?php
	echo "<td border='1'>".$row['temperature']."</td>";
	?><td style="border:1px solid #FFC300; text-align: center; color:#FFC300; font-size:2.25rem;>"<?php
	echo "<td border='1'>".$row['time']."</td>";         
                 
        
    }
}



?>
