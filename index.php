<?php
    exec('./parser index.wpml', $arr);
    foreach($arr as $a)
        echo $a;
?>
