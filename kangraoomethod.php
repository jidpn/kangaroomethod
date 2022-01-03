<?php
$x = array();
$y = array();
$max_diff = 0;
	$i;
	for($i=0;$i<360;$i++){
		$x[$i] = sin(pi()*$i /180);
		$y[$i] = cos(pi()*$i /180);
	}
	for($i=0;$i<359;$i++){
		$max_diff = $max_diff > abs($y[$i]	-$y[$i+1]) ? $max_diff:abs($y[$i]-$y[$i+1]);
	}
	$max_diff = $max_diff > abs($y[359]	-$y[0]) ? $max_diff:abs($y[359]-$y[0]);
	simplemethod(0.5);
	kangaroomethod(0.5);

function simplemethod($intersection){
	global $x,$y,$max_diff;	
	$counter = 0;
	print("simple method\n");
	for($i=0;$i<359;$i++){
		$counter++;
		if(($y[$i] < $intersection && $y[$i+1] > $intersection) || (($y[$i] > $intersection && $y[$i+1] < $intersection))){
			print("{$i}\n");		 	
		}
	}
	if(($y[359] < $intersection && $y[0] > $intersection) || (($y[359] > $intersection && $y[0] < $intersection))){
			print("359\n");		 
	}
	print("counter {$counter}\n");
}
function kangaroomethod($intersection){
	global $x,$y,$max_diff;	
	$jump = 0;
	$counter = 0;
	print("kangaroo method\n");
	for($i=0;$i<359;){
		$counter++;
		if(($y[$i] < $intersection && $y[$i+1] > $intersection) || (($y[$i] > $intersection && $y[$i+1] < $intersection))){
			print("{$i}\n");		 }	

		$jump = ((double)((double)abs($y[$i] - $intersection)) / (double)$max_diff) -1;
		if($jump < 1){
			$i++;
		}else{
			$i+=(int)$jump;
		}
	}
	if(($y[359] < $intersection && $y[0] > $intersection) || (($y[359] > $intersection && $y[0] < $intersection))){
			print("359\n");		 
	}

	print("counter {$counter}\n");
}
