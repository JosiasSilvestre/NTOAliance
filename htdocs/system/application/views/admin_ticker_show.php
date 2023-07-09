    <?php  
    echo "<div class='toolbar'>"; 
    echo "<a href='".WEBSITE."/index.php/admin/add_ticker'>Add ticker</a> | "; 
    echo "</div>"; 
    $this->load->helper('text'); 
    if(count($news) == 0)  
        alert("There is no tickers yet."); 
    else { 
        echo "<table width='100%'>"; 
        echo "<tr><td><center><b>ID</b></center></td><td><center><b>Created</b></center></td><td><center><b>Introduce</b></center></td><td><center><b>Edit</b></center></td></tr>"; 
        foreach($news as $value) { 
            echo "<tr class='highlight'><td><center>".$value['id']."</center></td><td><center>".UNIX_TimeStamp($value['date'])."</center></td><td><center>".word_limiter($value['text'], $wordLimit)."</center></td><td><center><a href='#' onClick=\"if(confirm('Are you sure you want to remove?')) window.location.href='".WEBSITE."/index.php/admin/delete_ticker/".$value['id']."';\"><img src='".WEBSITE."/public/images/false.gif'></a></center></td></tr>"; 
        } 
        echo "</table>"; 
    } 

    echo "<center>".$pages."</center>"; 
    ?>