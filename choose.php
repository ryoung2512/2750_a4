<?php
    $user = $_POST["username"];
    exec('./parser choose.wpml ' . $user. ' 2>&1', $arr);
    foreach($arr as $a)
        echo $a;
    exec('./a2/list_streams.py ' . $user . ' 2>&1', $return);
    foreach($return as $b)
        echo $b;
?>
