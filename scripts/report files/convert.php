<html>
<head>
	<title> Online Sensor Log </title> 
</head>
<body>
<?php
 $page = $_SERVER['PHP_SELF'];
 $sec = "4";
 header("Refresh: $sec; url=$page");
 
 
$data_size = 28;
 
$filename = "log_spi.dat"; 
$handle = fopen($filename, "rb"); 
$fsize = filesize($filename); 
$count = $fsize / $data_size;

$contents = fread($handle, $fsize); 
$byteArray = unpack("C*",$contents); 
$n = 0;

$filename1 = "log_uart.dat"; 
$handle1 = fopen($filename1, "rb"); 
$fsize1 = filesize($filename1); 
$count1 = $fsize1 / $data_size;

$contents1 = fread($handle1, $fsize1); 
$byteArray1 = unpack("C*",$contents1); 
$n1 = 0;
 
    
 ?> 




 <div style="float:left; height:70%;width:48%;border:0px  #ccc;font:16px/26px Georgia, Garamond, Serif;overflow:auto;">
 <table border = "1" style="float: left;"  > 
 <tr><th colspan = 6> Transceiver 1 (SPI) </th></tr> 
   <tr>  <td align = "center" >Net Id: </td>  <td align="center" >Address: </td>  <td align = "center" >Sensor ID: </td>  <td align="center"  >Value: </td>  <td align="center"  >TimeStamp: </td>  <td align="center" >LQI: </td></tr>
   <?php   
    
    
/*for($n = 0; $n < $count - 1 ; $n++)
{ 
    echo  "<tr>". " <td align=center> " . dechex($byteArray[$n*23 + 2+$n]) . dechex($byteArray[$n*23 + 1+$n]) . "  </td> " ;
    
    echo " <td align=center> " . dechex($byteArray[$n*23 + 3+$n]). dechex($byteArray[$n*23 + 4+$n]). dechex($byteArray[$n*23 + 5+$n]). dechex($byteArray[$n*23 + 6+$n]). dechex($byteArray[$n*23 + 7+$n]). dechex($byteArray[$n*23 + 8+$n]). dechex($byteArray[$n*23 + 9+$n]). dechex($byteArray[$n*23 + 10+$n]). "  </td> ";
    
    echo "   <td align=center> " . dechex($byteArray[$n*23 + 12+$n]). " </td>  ";
  
    echo "   <td align=center>" . dechex($byteArray[$n*23 + 13+$n]). dechex($byteArray[$n*23 + 14+$n]). dechex($byteArray[$n*23 + 15+$n]). dechex($byteArray[$n*23 + 16+$n]). dechex($byteArray[$n*23 + 17+$n]). dechex($byteArray[$n*23 + 18+$n]). "  </td> ";
 
    echo "   <td align=center> " . date('r', ($byteArray[$n*23 + 20+$n]<<24)|($byteArray[$n*23 + 21+$n]<<16)|($byteArray[$n*23 + 22+$n]<<8)|($byteArray[$n*23 + 23+$n]) )." </td>  ";
  
    echo "   <td align=center> " . dechex($byteArray[$n*23 + 24+$n]). dechex($byteArray[$n*23 + 25+$n]) . "  </td></tr> ";
}*/



for($n = $count-1; $n >=0 ; $n--)
{ 
    echo  "<tr>". " <td align=center> " . dechex($byteArray[$n*28 + 2]) . dechex($byteArray[$n*28 + 1]) . "  </td> " ;
    
    echo " <td align=center> " . dechex($byteArray[$n*28 + 3]). dechex($byteArray[$n*28 + 4]). dechex($byteArray[$n*28 + 5]). dechex($byteArray[$n*28 + 6]). dechex($byteArray[$n*28 + 7]). dechex($byteArray[$n*28 + 8]). dechex($byteArray[$n*28 + 9]). dechex($byteArray[$n*28 + 10]). "  </td> ";
    
    echo "   <td align=center> " . dechex($byteArray[$n*28 + 12]). " </td>  ";
  
    echo "   <td align=center>" . dechex($byteArray[$n*28 + 13]). dechex($byteArray[$n*28 + 14]). dechex($byteArray[$n*28 + 15]). dechex($byteArray[$n*28 + 16]). dechex($byteArray[$n*28 + 17]). dechex($byteArray[$n*28 + 18]). "  </td> ";
 
    echo "   <td align=center> " . date('r', ($byteArray[$n*28 + 24]<<24)|($byteArray[$n*28 + 23]<<16)|($byteArray[$n*28 + 22]<<8)|($byteArray[$n*28 + 21]) )." </td>  ";
  
    echo "   <td align=center> " . dechex($byteArray[$n*28 + 26]). dechex($byteArray[$n*28 + 27]) . "  </td></tr> ";
 }
 ?>
</table>
</div>




<div style=" float:right;height:70%;width:48%;border:0px #ccc;font:16px/26px Georgia, Garamond, Serif;overflow:auto;">
<table border = "1"  > 
   <tr><th colspan = 6> Transceiver 2 (UART) </th></tr>
   <tr>  <td align = "center" >Net Id: </td>  <td align="center" >Address: </td>  <td align = "center" >Sensor ID: </td>  <td align="center"  >Value: </td>  <td align="center"  >TimeStamp: </td>  <td align="center" >LQI: </td></tr>
   <?php   
    
    
    
    
    
/*for($n1 = 0; $n1 < $count1 - 1 ; $n1++)
{ 
    echo  "<tr>". " <td align=center> " . dechex($byteArray1[$n1*23 + 2+$n1]) . dechex($byteArray1[$n1*23 + 1+$n1]) . "  </td> " ;
    
    echo " <td align=center> " . dechex($byteArray1[$n1*23 + 3+$n1]). dechex($byteArray1[$n1*23 + 4+$n1]). dechex($byteArray1[$n1*23 + 5+$n1]). dechex($byteArray1[$n1*23 + 6+$n1]). dechex($byteArray1[$n1*23 + 7+$n1]). dechex($byteArray[$n1*23 + 8+$n1]). dechex($byteArray1[$n1*23 + 9+$n1]). dechex($byteArray1[$n1*23 + 10+$n1]). "  </td> ";
    
    echo "   <td align=center> " . dechex($byteArray1[$n1*23 + 12+$n1]). " </td>  ";
  
    echo "   <td align=center>" . dechex($byteArray1[$n1*23 + 13+$n1]). dechex($byteArray1[$n1*23 + 14+$n1]). dechex($byteArray1[$n1*23 + 15+$n1]). dechex($byteArray1[$n1*23 + 16+$n1]). dechex($byteArray1[$n1*23 + 17+$n1]). dechex($byteArray1[$n1*23 + 18+$n1]). "  </td> ";
 
    echo "   <td align=center> " . date('r', ($byteArray1[$n1*23 + 20+$n1]<<24)|($byteArray1[$n1*23 + 21+$n]<<16)|($byteArray1[$n1*23 + 22+$n1]<<8)|($byteArray1[$n1*23 + 23+$n1]) )." </td>  ";
  
    echo "   <td align=center> " . dechex($byteArray1[$n1*23 + 24+$n1]). dechex($byteArray1[$n1*23 + 25+$n1]) . "  </td></tr> ";
 }
 ?>*/


for($n1 = $count1-1; $n1 >=0 ; $n1--)
{ 
    echo  "<tr>". " <td align=center> " . dechex($byteArray1[$n1*28 + 2]) . dechex($byteArray1[$n1*28 + 1]) . "  </td> " ;
    
    echo " <td align=center> " . dechex($byteArray1[$n1*28 + 3]). dechex($byteArray1[$n1*28 + 4]). dechex($byteArray1[$n1*28 + 5]). dechex($byteArray1[$n1*28 + 6]). dechex($byteArray1[$n1*28 + 7]). dechex($byteArray1[$n1*28 + 8]). dechex($byteArray1[$n1*28 + 9]). dechex($byteArray1[$n1*28 + 10]). "  </td> ";
    
    echo "   <td align=center> " . dechex($byteArray1[$n1*28 + 12]). " </td>  ";
  
    echo "   <td align=center>" . dechex($byteArray1[$n1*28 + 13]). dechex($byteArray1[$n1*28 + 14]). dechex($byteArray1[$n1*28 + 15]). dechex($byteArray1[$n1*28 + 16]). dechex($byteArray1[$n1*28 + 17]). dechex($byteArray1[$n1*28 + 18]). "  </td> ";
 
    echo "   <td align=center> " . date('r', ($byteArray1[$n1*28 + 24]<<24)|($byteArray1[$n1*28 + 23]<<16)|($byteArray1[$n1*28 + 22]<<8)|($byteArray1[$n1*28 + 21]) )." </td>  ";
  
    echo "   <td align=center> " . dechex($byteArray1[$n1*28 + 26]). dechex($byteArray1[$n1*28 + 27]) . "  </td></tr> ";
 }
 ?>

 
 </table>
 </div>
<center><a href="<?php echo $url; ?>" >REFRESH </a></center>

 




