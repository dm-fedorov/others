<?php
//
// Заполнили таблицу time_packet, где было пустое поле с временными отметками
// 
$con = @mysql_connect("localhost","root","toor123");
if (!$con)
{
	die('Could not connect: ' . mysql_error());
 }
mysql_select_db("pcap2mysql_data", $con)
	or die("Ошибка выбора базы данных");

$result_id = mysql_query("select * from time_packet")
	or die("Нельзя выполнить запрос");

// ----------------------------------------

$i=1; 	    // инкрементный счетчик
while ($row = mysql_fetch_row($result_id)) {
   	
	if ($i%2){ // текущее значение - нечетное
	
		$tv_sec1=$row[2];
		$tv_usec1=$row[3];	
	}
		
	if (!($i%2)){ // текущее значение - четное
		
		$tv_sec2=$row[2];
		$tv_usec2=$row[3];		

		$tv_sec=$tv_sec2-$tv_sec1;
		$tv_usec=$tv_usec2-$tv_usec1;
		
		if($tv_usec < 0){
			$tv_sec--;	
			$tv_usec+=1000000;
		}
		
		$res=$tv_sec*1000+$tv_usec/1000;	
		
		if($res<0){
			$res=0;
		}
			
		$query=sprintf("update time_packet set time_packet.packet_time=%d where time_packet.pos=%d",$res*1000, $i-1);				
		mysql_query($query) or die("Нельзя выполнить запрос 1"); 
   	}           
   $i++;
}

mysql_free_result($result_id);
mysql_close($con);

// ----------------------------------------


$con = @mysql_connect("localhost","root","toor123");
if (!$con)
{
	die('Could not connect: ' . mysql_error());
 }
mysql_select_db("pcap2mysql_data", $con)
	or die("Ошибка выбора базы данных");

$result_id = mysql_query("select * from time_packet")
	or die("Нельзя выполнить запрос");

// ----------------------------------------
$i=1;
$flag_space=0;

while ($row = mysql_fetch_row($result_id)) {
   	
  if ($flag_space==1) {			
	if (!($i%2)){ // текущее значение - четное
	
		$tv_sec1=$row[2];
		$tv_usec1=$row[3];	
	}
		
	if ($i%2){ // текущее значение - нечетное
		
		$tv_sec2=$row[2];
		$tv_usec2=$row[3];		

		$tv_sec=$tv_sec2-$tv_sec1;
		$tv_usec=$tv_usec2-$tv_usec1;
		
		if($tv_usec < 0){
			$tv_sec--;	
			$tv_usec+=1000000;
		}
		
		$res=$tv_sec*1000+$tv_usec/1000;		
		
		if($res<0){
			$res=0;
		}
				
		$query=sprintf("update time_packet set time_packet.packet_time=%d where time_packet.pos=%d",$res*1000, $i-1);				
		mysql_query($query) or die("Нельзя выполнить запрос 1"); 
   	}           
     }	
   	
   $i++;
     
   $flag_space=1;   
}
// ----------------------------------------

// 
// Удалить последнюю строку с нулем
// 

mysql_free_result($result_id);
mysql_close($con);

?>

