#!/usr/bin/php
<?php

$device = find_tty();

function find_tty() {
		$devs = array("/dev/rfcomm0", "/dev/ttyUSB0", "/dev/ttyUSB1");
		foreach($devs as $device) {
				if (@stat($device) !== false) {
						return $device;
				}
		}
		return "/dev/null";
}

printf("device selected: %s\n", $device);


$cmd=sprintf("stty -F %s cs8 9600 ignbrk -brkint -icrnl -imaxbel -opost -onlcr -isig -icanon -iexten -echo -echoe -echok -echoctl -echoke noflsh -ixon -crtscts", $device);
shell_exec($cmd);

function get_lightness($i, $base_light, $max_peak) {
		$pi = 3.14159;
		$result = $max_peak * sin($pi * $i);
		return ($result<0)?$base_light:($base_light+$result);
}


for ($i=0; $i<1; $i = $i + 0.075) {
		$core = get_lightness($i, 10, 79);
		$body = get_lightness($i, 10, -79);
		$msg = sprintf("%02d0000%02d000000\n", 99-$core, $core);
		file_put_contents($device, $msg);
}
usleep(20);
for ($i=0; $i<1; $i = $i + 0.075) {
		$core = get_lightness($i, 10, 79);
		$body = get_lightness($i, 10, -79);
		$msg = sprintf("%02d0000%02d000000\n", 99-$core, $core);
		file_put_contents($device, $msg);
}

