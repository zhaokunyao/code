<?PHP

$dir = './src/';

if (is_dir($dir)) {
    if ($dh = opendir($dir)) {
        while (($file = readdir($dh)) !== false) {
            if ($file == '.' || $file == '..') {
                continue;
            }
            $arrPathParts = pathinfo($file);
            $file = $arrPathParts['filename'];
            printf('<div><a href="./function.php?name=%s">%s</a></div>', urlencode($file), htmlspecialchars($file));
        }
        closedir($dh);
    }
}

