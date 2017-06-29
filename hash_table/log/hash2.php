<?PHP

$strFileA   = "./a.log";
$strFileB   = "./b.log";


$count  = 3;
$dirA   = "./a/";
$dirB   = "./b/";

hashx($strFileA, $dirA);
hashx($strFileB, $dirB);
merge($dirA, $dirB);


function hashx($strFile, $dir) {
    global $count;
    if (!is_dir($dir)) {
        mkdir($dir);
    }
    assert(is_dir($dir));
    $fp = fopen($strFile, "r");
    assert($fp);
    $arrFP  = array ();
    for($i =0 ;$i<$count; $i++) {
        $arrFP[$i] = fopen($dir ."/". $i, "w");
    }

    while(!feof($fp)) {
        $strLine    = trim(fgets($fp));
        if ($strLine == "") continue;
        $arrTmp = explode(" ", $strLine);
        $id = $arrTmp[0];
        $id_hash = $id % $count;
        $fp2 = $arrFP[$id_hash];
        fwrite($fp2, $strLine.PHP_EOL);
    }
    for($i =0 ;$i<$count; $i++) {
        fclose($arrFP[$i]);
    }

}

function merge($dirA, $dirB) {
    global $count;
    $strOutFile = "./all_hash.log";
    $fp = fopen($strOutFile, "w"); assert($fp);
    for ($i=0; $i<$count; $i++) {
        $arr    = array ();
        $strFileA = "./a/".$i;
        $strFileB = "./b/".$i;
        if (file_exists($strFileA) && file_exists($strFileB)) {
            $fp_a = fopen($strFileA, "r");
            $fp_b = fopen($strFileB, "r");
            while(!feof($fp_a)) {
                $strLine = trim(fgets($fp_a));
                if ($strLine =="") continue;
                $arrTmp = explode(" ", $strLine);
                $id = $arrTmp[0];
                $arr[$id] = $strLine;
            }
            while(!feof($fp_b)) {
                $strLine = trim(fgets($fp_b));
                if ($strLine =="") continue;
                $arrTmp = explode(" ", $strLine);
                $id = $arrTmp[0];
                if (isset($arr[$id]))  continue;
                $arr[$id] = $strLine;
            }
            fclose($fp_a);
            fclose($fp_b);
        } else if (file_exists($strFileA)) {
            $arr = file($strFileA);
        } else if (file_exists($strFileB)) {
            $arr = file($strFileB);
        }

        foreach ($arr as $k=>$line) {
            fwrite($fp, $line.PHP_EOL);
        }
    }
    fclose($fp);
}



