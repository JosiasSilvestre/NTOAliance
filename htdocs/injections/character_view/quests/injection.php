        <div class='message'>
        <div class='title'>Quest</div>
        <div class='content'>

<?php
if ( ! defined('BASEPATH')) exit('No direct script access allowed');
$characterPageQuests = array();
/* A list of quests for character/view page. It will be listed on the page as a table to show acomplished missions.
Array contains array of quests which includes STORAGE ID, STORAGE VALUE (Required to finish quest) and NAME 
To create new quest copy line accross and change values.
*/
$player = $GLOBALS['player'];
/* Eg. $characterPageQuests[] = array('storage'=>5000, 'value'=>1, 'name'=>'Scret Quest'); */
$characterPageQuests[] = array('storage'=>19882, 'value'=>1, 'name'=>'Vale do Fim Quest');
$characterPageQuests[] = array('storage'=>19883, 'value'=>1, 'name'=>'Cascata Quest');
$characterPageQuests[] = array('storage'=>19884, 'value'=>1, 'name'=>'CascataTwo Quest');
$characterPageQuests[] = array('storage'=>19885, 'value'=>1, 'name'=>'CascataThree Quest');
$characterPageQuests[] = array('storage'=>19886, 'value'=>1, 'name'=>'Desert Quest');
$characterPageQuests[] = array('storage'=>19887, 'value'=>1, 'name'=>'Tumba Quest');
$characterPageQuests[] = array('storage'=>19890, 'value'=>1, 'name'=>'Catatumba Quest');
$characterPageQuests[] = array('storage'=>2397, 'value'=>1, 'name'=>'Chakra Armor Quest');
$characterPageQuests[] = array('storage'=>19888, 'value'=>1, 'name'=>'Dual Katana Quest');
$characterPageQuests[] = array('storage'=>19889, 'value'=>1, 'name'=>'Jounin Glove Quest');
$characterPageQuests[] = array('storage'=>7449, 'value'=>1, 'name'=>'Sasori Quest');


 if(count($characterPageQuests) != 0) {
		echo "<table width='100%'>";
		echo "<tr><td width='90%'><b>Nome da Quest</b></td><td><b>Status</b></td></tr>";
		$SQL = POT::getInstance()->getDBHandle();
		foreach($characterPageQuests as $value) {
			$quest = $SQL->query("SELECT `value` FROM `player_storage` WHERE `player_id` = ".$player->getId()." AND `key` = '".$value['storage']."' AND `value` = '".$value['value']."'")->fetch();
			$status = ($quest) ? "true" : "false";
			echo "<tr><td width='90%'>".$value['name']."</td><td><center><img src='../../../public/images/$status.gif'></center></td></tr>";
		}
		echo "</table>";
	}
?>
</div></div>