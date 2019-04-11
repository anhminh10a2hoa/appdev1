<?php
$log_file = 'testcurl.txt';
$values = $_POST['db'];
$str = date("M d Y H:i:s",time()).' '.$values."\n";

echo "This is from the sever";
//now we open the file
if(file_exists($log_file)){
	$fp=fopen($log_file,a); // the file is opened as append mode
	fwrite($fp, $str);
	fclose($fp);
}else{		// the file doesn't exist, so open a new one.
	$fp = fopen($log_file,w);
	fwrite($fp, $str);
	fclose($fp);
}
?>