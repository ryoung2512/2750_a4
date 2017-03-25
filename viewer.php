<?php
    $user = $_POST["username"];
    $stream = $_POST["stream"];
    $counter = (int)$_POST["counter"];
    $limit = $_POST["limit"];
    $sorting = $_POST["sorted"];

    if (isset($_POST["name"]))
    {
        $button = $_POST["name"];
        if ($button == "Next Post")
        {
            if ($counter + 1 <= (int)$limit)
                $counter++;
        }
        else if ($button == "choose" || $button == "Check for new posts")
        {
            exec('./a2/count_posts.py ' . $user . ' ' . $stream, $limit_ret);
            $limit = $limit_ret[0];
        }
        else if ($button == "Sorting")
        {
            if ($sorting == "0")
                $sorting = "1";
            else
                $sorting = "0";
        }
        else {
            if ($counter - 1 >= 0)
                $counter--;
        }
    }

    if(isset($_POST["username"]) && isset($_POST["stream"]))
    {
        exec('./parser header.wpml ' . $user . ' ' . $stream . ' ' . $counter . ' ' . $limit . ' ' . $sorting . ' 2>&1', $arr);
        foreach($arr as $a)
            echo $a;
        exec('./a2/viewer.py ' . $user . ' ' . $stream . ' ' . $counter . ' ' . $limit . ' ' . $sorting .' 2>&1', $return);
        foreach($return as $b)
            echo $b;

    }
    else
    {
        exec('./parser header.wpml', $arr);
        foreach($arr as $a)
            echo $a;
        echo "Please <a href=\"index.php\">login</a> and <a href=\"choose.php\">choose</a> a stream to view posts!<br>";
        echo "</body></html>";
    }
?>
