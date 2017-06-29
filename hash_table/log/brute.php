<?PHP

$strFileA   = "./a.log";
$strFileB   = "./b.log";

$arrA   = hashx($strFileA);
$arrB   = hashx($strFileB);
output($arrA, $arrB);

function hashx($strFile) {
    assert(file_exists($strFile));
    $arr    = array ();
    $fp = fopen($strFile, "r");
    assert($fp);
    while(!feof($fp)) {
        $strLine    = trim(fgets($fp));
        if (strlen($strLine) == 0) continue;
        $arrTmp = explode(' ', $strLine);
        $id = $arrTmp[0];
        assert($id);
        $arr[$id] = $strLine;
    }

    return $arr;
}


function output($arrA, $arrB) {
    $fp = fopen("./all_brute.log", "w");
    assert($fp);
    foreach ($arrA as $k=>$line) {
        fwrite($fp, $line.PHP_EOL);
    }

    foreach ($arrB as $k=>$line) {
        if (isset($arrA[$k])) {
            continue;
        }
        fwrite($fp, $line.PHP_EOL);
    }
}

