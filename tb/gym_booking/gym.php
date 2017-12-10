<?PHP
// http://php.net/manual/en/function.date-default-timezone-set.php
# 这里一定要改成你们那里的时区。
// http://php.net/manual/en/timezones.php
date_default_timezone_set('Asia/Chongqing');
error_reporting( E_ALL ); 
ini_set("display_errors", 1);
ini_set("display_startup_errors", 1); 

// http://php.net/manual/en/pdo.construct.php
// connect to mysql
$dsn    = 'mysql:dbname=xuyi;host=127.0.0.1';
$user   = 'root';
$pwd    = '1234567890';
try {
    $dbh = new PDO($dsn, $user, $pwd);
} catch (PDOException $e) {
    echo 'Connection failed: ' . $e->getMessage();
    die();
}

$errorMsg = "";
function doGet() {
    global $errorMsg;
    global $dbh;

    // listing in the first menu only classes 
    // which have places left at one of the dates and times it runs 
    $arrPlaceLeftByClass = array ();


    $sql    = "SELECT * FROM classes"; 
    $rs     = $dbh->query($sql);

    $arrClasses = array ();
    foreach ($rs as $row) {
        $id = $row['id'];
        $arrClasses[$id] = $row['class_name'];
        $arrPlaceLeftByClass[$id] = 0;
    }
    $className = "";
    if (!empty($_POST['class_id'])) {
        $id = $_POST['class_id'];
        $className = htmlspecialchars($arrClasses[$id]);
    }
    // classes should be ordered alphabetically 
    // http://php.net/manual/en/function.asort.php
    // http://php.net/manual/en/function.sort.php
    asort($arrClasses, SORT_STRING | SORT_FLAG_CASE);


    $sql = "SELECT * FROM class_times WHERE 1";
    $rs2 = $dbh->query($sql);

    $arrTimes   = array ();
    $arrTmp     = array ();
    $arrTmp2    = array ();
    foreach ($rs2 as $k=>$row) {
        // http://php.net/manual/en/function.strtotime.php
        $time   = strtotime($row['time_name']);
        $id     = $row['id'];

        $arrTmp[$id]    = $time;
        $arrTmp2[$id]   = $row;
        $class_id = $row['class_id'];
        $arrPlaceLeftByClass[$class_id] += $row['capacity_left'];
    }

    // the dates and times should be ordered chronologically. 
    asort($arrTmp, SORT_NUMERIC);
    // copy from arrTmp2 to arrTimes
    foreach ($arrTmp as $id=>$time) {
        $arrTimes[$id] = $arrTmp2[$id];
    }

    $timeName = "";
    if (!empty($_POST['time_id'])) {
        $id = $_POST['time_id'];
        $timeName = htmlspecialchars($arrTimes[$id]['time_name']);
    }


    $classOptions = "";
    $timeOptions = "";
    foreach ($arrClasses as $class_id=>$class_name) {
        // listing in the first menu only classes 
        // which have places left at one of the dates and times it runs 
        if (empty($arrPlaceLeftByClass[$class_id])) {
            continue;
        }
        $selected = "";
        if (isset($_POST['class_id']) && $_POST['class_id'] == $class_id) {
            $selected = "selected";
        }
        $classOptions .= "<option $selected value=".$class_id.">" .$class_name. "</option>";
    }

    if (!empty($_POST['class_id'])) {
        foreach ($arrTimes as $row) {
            // in the second menu only list the dates and times 
            // at which the selected class still has places left
            if ($row['capacity_left'] == 0) {
                continue;
            }
            if ($row['class_id'] == $_POST['class_id']) {
                $selected = "";
                if (isset($_POST['time_id']) && $_POST['time_id'] == $row['id']) {
                    $selected =  "selected";
                }
                $timeOptions.= "<option $selected value=".$row['id'].">" .$row['time_name']. "</option>";
            }
        }
    }

    // For example, if name and phone number were valid, 
    // but there were no places left on the selected class, 
    // then the system would ideally be programmed in such a way 
    // that there is no need to enter name and phone number again.
    $name   = "";
    $mobile = "";
    if (isset($_POST['name'])) {
        // http://php.net/manual/en/function.htmlspecialchars.php
        // escape html characters.
        $name = htmlspecialchars($_POST['name']);
        $mobile = htmlspecialchars($_POST['mobile']);
    }

    $form = <<<FORM_HTML
    <form method=POST>
    class<select name="class_id" onChange="this.form.submit();">
    <option value=0> select a class </option>
    $classOptions
    </select> <br /> <br />
    time <select name="time_id">
    <option value=0> select a date time </option>
    $timeOptions
    </select> <br /> <br />
     name <input type=text name="name" value="$name"/> <br /> <br />
    mobile<input type=text name="mobile" value="$mobile"/> <br /> <br />
    <input type=submit name='Submit' value='Submit' />
    </form>
FORM_HTML
;
    // If none of the classes at any date and time has places left, 
    // then the system should inform the user about this 
    // and not show any drop-down menus or text fields.
    if (empty($arrTimes)) {
        $form = "<div>none of the classes at any date and time has places left</div>";
    }
    // booking details.
    $bookingDetail = "";
    if (!empty($_POST['Submit'])) {
        $bookingDetail = "booking detail:  <br />";
        if (!empty($className)) {
            $bookingDetail .= "class: $className <br />";
        }
        if (!empty($timeName)) {
            $bookingDetail .= "time: $timeName <br />";
        }
        if (!empty($name)) {
            $bookingDetail .= "name: $name<br />";
        }
        if (!empty($mobile)) {
            $bookingDetail .= "mobile: $mobile<br />";
        }
    }

    $html = <<<HTML_DOC
    <html>
    <head>
    <style>
    body {
        font-size: 18px;
    }
    .error_msg {
        color: red;
        margin: 20px;
    }
    .booking_detail {
        margin: 20px;
    }
    </style>
    </head>
    <body style="margin-left:100px;">
    <div class="booking_detail">
    $bookingDetail
    </div>
    <div class="error_msg">
    $errorMsg
    </div>
    $form
    </body>
    </html>
HTML_DOC
;
    print $html;
}

function isValidName() {
    $name = $_POST['name'];
    if (strlen($name) == 0) {
        return false;
    }
    // http://php.net/manual/en/function.preg-match.php
    // A name only consist of letters (a-z and A-Z), hyphens, apostrophes and spaces; 
    // starts with a letter.
    if (!preg_match('#^[a-z][ a-z\-\']*$#i', $name)) {
        return false;
    }
    // http://php.net/manual/en/function.strpos.php
    // contains no sequence of two or more of the characters hyphen and apostrophe
    if (strpos($name, "--") !== false) {
        return false;
    }
    if (strpos($name, "''") !== false) {
        return false;
    }
    if (strpos($name, "'-") !== false) {
        return false;
    }
    if (strpos($name, "-'") !== false) {
        return false;
    }
    return true;
}

function isValidMobile() {
    $mobile = $_POST['mobile'];
    if (strlen($mobile) == 0) {
        return false;
    }
    // only consists of digits and spaces
    // starts with the digit 0
    if (!preg_match('#^0[0-9 ]+$#', $mobile)) {
        return false;
    }
    // contains either nine or ten digits
    // remove spaces, then the left characters are all digits.
    $mobile = str_replace(' ', '', $mobile);
    if (strlen($mobile) == 9 || strlen($mobile) == 10) {
        return true;
    }
    return false;
}

function doBooking() {
    $mobile     = $_POST['mobile'];
    $name       = $_POST['name'];
    $class_id   = $_POST['class_id'];
    $time_id    = $_POST['time_id'];

    global $dbh;
    // http://php.net/manual/en/pdo.begintransaction.php
    $dbh->beginTransaction();
    // still has at least one place left
    // reduced by one 
    // http://php.net/manual/en/function.intval.php
    // convert time_id to int,  to avoid sql injection.
    $sql = "UPDATE class_times SET capacity_left = capacity_left-1 WHERE id = ".intval($time_id)." AND capacity_left > 0" ;
    // http://php.net/manual/en/pdo.exec.php
    $affectedRows = $dbh->exec($sql);
    // 有并发抢最后一个名额的情况下，
    // 只会有一个用户的affectedRows为1
    // 表示修改了class_times表中的一条数据: 
    // 把capacity_left 减1， 之后，capacity_left = 0)， 
    // 其它用户的affectedRows为0
    // 表示未做出任何修改。因为不满足 capacity_left > 0的条件
    if ($affectedRows != 1) {
        // http://php.net/manual/en/pdo.rollback.php
        $dbh->rollback();
        return false;
    }

    // http://php.net/manual/en/pdo.prepare.php
    // record of the booking will be kept in the database, including the class, date and time, name and phone number.
    $sql    = "INSERT INTO booking_records SET class_id= :class_id, time_id= :time_id, name= :name, mobile= :mobile";
    $sth    = $dbh->prepare($sql, array(PDO::ATTR_CURSOR => PDO::CURSOR_FWDONLY));
    $ok     = $sth->execute(array(
        ':class_id' => $class_id, 
        ':time_id'  => $time_id,
        ':name'     => $name,
        ':mobile'   => $mobile,
    ));
    // insert failed.
    if (!$ok) {
        $dbh->rollback();
        return false;
    }
    
    // http://php.net/manual/en/pdo.commit.php
    $dbh->commit();
    return true;
}

function doPost() {
    global $errorMsg;

    if (empty($_POST['class_id'])) {
        $errorMsg = "pls select a class";
        return doGet();
    }

    // the user does not select time_id
    if (empty($_POST['time_id'])) {
        $errorMsg = "pls select a date time";
        return doGet();
    }
    if (!isValidName()) {
        $errorMsg = "invalid name";
        return doGet();
    }
    if (!isValidMobile($_POST['mobile'])) {
        $errorMsg = "invalid mobile";
        return doGet();
    }

    if (!doBooking()) {
        $errorMsg = "no places left on the selected class at the selected date and time";
        return doGet();
    }
    $errorMsg = "<span style='color:GREEN'>successful<span>";
    return doGet();
}

if (!empty($_POST['Submit'])) {
    // user click Submit button
    doPost();
} else {
    // GET
    // or auto submit when change a class.
    doGet();
}
