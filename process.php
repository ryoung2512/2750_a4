<?php
    /* just a simple function to call different parser commands if they are logged in or not */
    function printFile($u, $s, $counter, $limit, $sorting, $file, $logged_in)
    {
        if ($logged_in == FALSE)
        {
            exec('./parser ' . $file . ' 2>&1', $arr);
            foreach($arr as $a)
                echo $a;
        }
        else
        {
            exec('./parser ' . $file . ' ' . $u . ' ' . $s . ' ' . $counter . ' ' . $limit . ' ' . $sorting . ' 2>&1', $arr);
            foreach($arr as $a)
                echo $a;
        }
    }

    $user = $_POST["username"];
    $stream = $_POST["stream"];
    $counter = (int)$_POST["counter"];
    $button = $_POST["name"];
    $limit = $_POST["limit"];
    $sorting = $_POST["sorted"];

    /* check which button was pressed this way we dont need a bunch of different pages */
    if($button == "Mark all read")
    {
        // special case cant use printFile
        if (isset($_POST["username"]) && isset($_POST["stream"]))
        {
            printFile($user, $stream, $counter, $limit, $sorting, 'header.wpml', TRUE);
            exec('./a2/mark_read.py ' . $user . ' ' . $stream . ' 1 ' . $limit . ' 2>&1', $arr);
            foreach($arr as $a)
                echo $a;
        }
        else
        {
            printFile($user, $stream, $counter, $limit, $sorting, 'header.wpml', FALSE);
            echo "Please <a href=\"index.php\">login</a> and <a href=\"choose.php\">choose</a> a stream before you can perform that action";
            echo "</body></html>";
        }
    }
    else if ($button == "Add or remove Author") /* author pag */
    {
        if (isset($_POST["username"]) && isset($_POST["stream"]))
        {
            printFile($user, $stream, $counter, $limit, $sorting, 'authorcontrol.wpml', TRUE);
        }
        else
        {
            printFile($user, $stream, $counter, $limit, $sorting, 'authorcontrol.wpml', FALSE);
        }
    }
    else if ($button == "Post new message") /* post page */
    {
        if (isset($_POST["username"]) && isset($_POST["stream"]))
        {
            printFile($user, $stream, $counter, $limit, $sorting, 'createpost.wpml', TRUE);
        }
        else
        {
            printFile($user, $stream, $counter, $limit, $sorting, 'header.wpml' ,FALSE);
            echo "Please <a href=\"index.php\">login</a> and <a href=\"choose.php\">choose</a> a stream before posting";
            echo "</body></html>";
        }
    }
    else if ($button == "authorAstreamAremoveA") /*submit author */
    {
        if ($_POST["authorA"] == $user || !isset($_POST["username"]) || !isset($_POST["stream"]))
            printFile($user, $stream, $counter, $limit, $sorting, 'header.wpml', FALSE);
        else
            printFile($user, $stream, $counter, $limit, $sorting,  'header.wpml',  TRUE);

        if ($_POST["removeA"] != "-r")
        {
            exec('./a2/addauthor ' . $_POST["authorA"]. ' ' . $_POST["streamA"] . ' 2>&1', $arr);
            foreach($arr as $a)
                echo $a;
        }
        else
        {
            exec('./a2/addauthor -r ' . $_POST["authorA"]. ' '. $_POST["streamA"] . ' 2>&1', $arr);
            foreach($arr as $a)
                echo $a;
        }
    }
    else if ($button == "streamP")/* submit post */
    {
        if (isset($_POST["username"]) && isset($_POST["stream"]))
        {
            printFile($user, $stream, $counter, $limit, $sorting, 'header.wpml', TRUE);
        }
        else
        {
            printFile($user, $stream, $counter, $limit, $sorting, 'header.wpml', FALSE);
        }
        $stream_post = $_POST["streamP"];
        $post = $_POST["post"];
        $f = fopen("temp.txt", "a");
        $post = str_replace(array("\r\n", "\r", "\n"), "<br />", $post);
        fwrite($f, $post);
        exec('./a2/post ' . $stream_post . ' ' . $user . ' 2>&1', $ret);
        foreach($ret as $b)
            echo $b;
        fclose($f);
    }
?>
