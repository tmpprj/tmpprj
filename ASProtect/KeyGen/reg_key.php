<?php
$Name=$_GET['name'];
$HardwareId=$_GET['hwid'];
//print( "Content-type: text/html\n\n" );
system( "./keygen $Name $HardwareId" );
?>
