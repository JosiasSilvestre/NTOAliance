<?php  
echo error(validation_errors()); 
echo form_open("admin/add_ticker"); 
echo "<textarea name='text' class='tinymce'>".set_value('body')."</textarea><br />"; 
echo "<input type='submit' value='Add ticker'>"; 
echo "</form>"; 

?>