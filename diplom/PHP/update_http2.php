<?php
// Установка соединения с базой данных
$con = @mysql_connect($host,$user,$psw);
if (!$con)
{
	die('Could not connect: ' . mysql_error());
 }
// Выбор базы данных
 mysql_select_db("pcap2mysql_data", $con)
	or die("Ошибка выбора базы данных");

// Выполнение запроса
$result_id = mysql_query("select * from pcap_weka")
	or die("Нельзя выполнить запрос");

$flag1=0; 

while ($row = mysql_fetch_row($result_id)) {			
	for ($i=0; $i < mysql_num_fields($result_id); $i++){
		if ($row[8]==80){ 
			if($flag1==0){
				$flag1=1; 
							
				$query=sprintf("update pcap_weka set pcap_weka.tcp_flow_dir=1,  pcap_weka.app_proto=1, pcap_weka.app_proto_name='http' where pcap_weka.id=%d",$row[0]);
				mysql_query($query) or die("Нельзя выполнить запрос, 1"); 
			}else{
				$query=sprintf("update pcap_weka set pcap_weka.tcp_flow_dir=1,  pcap_weka.app_proto=1, pcap_weka.app_proto_name='http' where pcap_weka.id=%d",$row[0]);
				mysql_query($query) or die("Нельзя выполнить запрос, 2"); 
			}			
		}
		if ($row[7]==80){ 
			if($flag1==1){
				$query=sprintf("update pcap_weka set pcap_weka.tcp_flow_dir=2,  pcap_weka.app_proto=1, pcap_weka.app_proto_name='http' where pcap_weka.id=%d",$row[0]);
				mysql_query($query) or die("Нельзя выполнить запрос, 3"); 
			}
		} 	
 	} 	 		
  } 
  
 mysql_free_result($result_id);
 mysql_close($con);
?>