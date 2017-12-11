<meta charset='utf-8' />
<?PHP

$strFunction = $_GET['name'];

$strFile = 'src/'.$strFunction.'.html';

if (file_exists($strFile)) {
    print file_get_contents($strFile);
}
