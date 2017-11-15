<?PHP

$a = array (
);

$m = 3;

for ($i=0;$i<$m;$i++) {
    for ($j=0; $j<$m; $j++) {
        $a[$i][$j] = ' ';
    }
}
$mid = $m / 2 ;
$a[0][$mid] = '*';
$a[$m-1][$mid] = '*';

for ($i=1; $i<=$mid; $i++) {
    $k = $mid  - $i;
    $a[$i][$k] = '*';
    $k = $mid + $i ;
    $a[$i][$k] = '&';
}
$count  = 0;
for ($i=$mid+1; $i<$m-1; $i++) {
    $count ++;
    $k = $i - $mid;
    $a[$i][$k] = '*';
    $k = $m - $count;
    $a[$i][$k] = '&';
}
for ($i=0;$i<$m;$i++) {
    for ($j=0; $j<$m; $j++) {
        print $a[$i][$j];
    }
    print PHP_EOL;
}
