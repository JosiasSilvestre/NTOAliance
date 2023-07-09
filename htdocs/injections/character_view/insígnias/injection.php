<div class='message'>
<div class='title'>Mission Assassin Bosses</div>

<?php
if ( ! defined('BASEPATH')) exit('No direct script access allowed');
$characterPageQuests = array();
$player = $GLOBALS['player'];
$characterPageQuests[] = array('storage'=>7449, 'value'=>1, 'name'=>'Sasori - Poderoso Ninja da Akatsuki - Polegar Direito');


   if(count($characterPageQuests) != 0) {
		echo "<table width='100%'>";
		echo "<tr><td width='90%'><center><b>Bosses</b></center></td><td><b><center>Status</center></b></td></tr>";
		$SQL = POT::getInstance()->getDBHandle();
		foreach($characterPageQuests as $value) {
			$quest = $SQL->query("SELECT `value` FROM `player_storage` WHERE `player_id` = ".$player->getId()." AND `key` = '".$value['storage']."' AND `value` = '".$value['value']."'")->fetch();
			$status = ($quest) ? "conclusao" : "missao";
			echo "<tr><td width='90%'>".$value['name']."</td><td><center><img src='../../../public/images/$status.gif'></center></td></tr>";
		}
		echo "</table>";
	}
?>

<?php
if ( ! defined('BASEPATH')) exit('No direct script access allowed');
$characterPageQuests = array();
$player = $GLOBALS['player'];
$characterPageQuests[] = array('storage'=>19891, 'value'=>1, 'name'=>'Hidan - Poderoso Ninja da Akatsuki - Indicador Direito');


   if(count($characterPageQuests) != 0) {
		echo "<table width='100%'>";

		$SQL = POT::getInstance()->getDBHandle();
		foreach($characterPageQuests as $value) {
			$quest = $SQL->query("SELECT `value` FROM `player_storage` WHERE `player_id` = ".$player->getId()." AND `key` = '".$value['storage']."' AND `value` = '".$value['value']."'")->fetch();
			$status = ($quest) ? "conclusao" : "missao";
			echo "<tr><td width='90%'>".$value['name']."</td><td><center><img src='../../../public/images/$status.gif'></center></td></tr>";
		}
		echo "</table>";
	}
?>

<?php
if ( ! defined('BASEPATH')) exit('No direct script access allowed');
$characterPageQuests = array();
$player = $GLOBALS['player'];
$characterPageQuests[] = array('storage'=>19892, 'value'=>1, 'name'=>'Kakuzu - Poderoso Ninja da Akatsuki - Médio Direito');


   if(count($characterPageQuests) != 0) {
		echo "<table width='100%'>";

		$SQL = POT::getInstance()->getDBHandle();
		foreach($characterPageQuests as $value) {
			$quest = $SQL->query("SELECT `value` FROM `player_storage` WHERE `player_id` = ".$player->getId()." AND `key` = '".$value['storage']."' AND `value` = '".$value['value']."'")->fetch();
			$status = ($quest) ? "conclusao" : "missao";
			echo "<tr><td width='90%'>".$value['name']."</td><td><center><img src='../../../public/images/$status.gif'></center></td></tr>";
		}
		echo "</table>";
	}
?>

<?php
if ( ! defined('BASEPATH')) exit('No direct script access allowed');
$characterPageQuests = array();
$player = $GLOBALS['player'];
$characterPageQuests[] = array('storage'=>19893, 'value'=>1, 'name'=>'Deidara - Poderoso Ninja da Akatsuki - Indicador Esquerdo');


   if(count($characterPageQuests) != 0) {
		echo "<table width='100%'>";
	
		$SQL = POT::getInstance()->getDBHandle();
		foreach($characterPageQuests as $value) {
			$quest = $SQL->query("SELECT `value` FROM `player_storage` WHERE `player_id` = ".$player->getId()." AND `key` = '".$value['storage']."' AND `value` = '".$value['value']."'")->fetch();
			$status = ($quest) ? "conclusao" : "missao";
			echo "<tr><td width='90%'>".$value['name']."</td><td><center><img src='../../../public/images/$status.gif'></center></td></tr>";
		}
		echo "</table>";
	}
?>

<?php
if ( ! defined('BASEPATH')) exit('No direct script access allowed');
$characterPageQuests = array();
$player = $GLOBALS['player'];
$characterPageQuests[] = array('storage'=>19894, 'value'=>1, 'name'=>'Itachi - Poderoso Ninja da Akatsuki - Anular Esquerdo');


   if(count($characterPageQuests) != 0) {
		echo "<table width='100%'>";

		$SQL = POT::getInstance()->getDBHandle();
		foreach($characterPageQuests as $value) {
			$quest = $SQL->query("SELECT `value` FROM `player_storage` WHERE `player_id` = ".$player->getId()." AND `key` = '".$value['storage']."' AND `value` = '".$value['value']."'")->fetch();
			$status = ($quest) ? "conclusao" : "missao";
			echo "<tr><td width='90%'>".$value['name']."</td><td><center><img src='../../../public/images/$status.gif'></center></td></tr>";
		}
		echo "</table>";
	}
?>

<?php
if ( ! defined('BASEPATH')) exit('No direct script access allowed');
$characterPageQuests = array();
$player = $GLOBALS['player'];
$characterPageQuests[] = array('storage'=>19895, 'value'=>1, 'name'=>'Pain - Poderoso Ninja da Akatsuki - Polegar Esquerdo');


   if(count($characterPageQuests) != 0) {
		echo "<table width='100%'>";
		
		$SQL = POT::getInstance()->getDBHandle();
		foreach($characterPageQuests as $value) {
			$quest = $SQL->query("SELECT `value` FROM `player_storage` WHERE `player_id` = ".$player->getId()." AND `key` = '".$value['storage']."' AND `value` = '".$value['value']."'")->fetch();
			$status = ($quest) ? "conclusao" : "missao";
			echo "<tr><td width='90%'>".$value['name']."</td><td><center><img src='../../../public/images/$status.gif'></center></td></tr>";
		}
		echo "</table>";
	}
?>

<?php
if ( ! defined('BASEPATH')) exit('No direct script access allowed');
$characterPageQuests = array();
$player = $GLOBALS['player'];
$characterPageQuests[] = array('storage'=>30006, 'value'=>1, 'name'=>'Konan - Poderoso Ninja da Akatsuki - Médio Esquerdo');


   if(count($characterPageQuests) != 0) {
		echo "<table width='100%'>";

		$SQL = POT::getInstance()->getDBHandle();
		foreach($characterPageQuests as $value) {
			$quest = $SQL->query("SELECT `value` FROM `player_storage` WHERE `player_id` = ".$player->getId()." AND `key` = '".$value['storage']."' AND `value` = '".$value['value']."'")->fetch();
			$status = ($quest) ? "conclusao" : "missao";
			echo "<tr><td width='90%'>".$value['name']."</td><td><center><img src='../../../public/images/$status.gif'></center></td></tr>";
		}
		echo "</table>";
	}
?>

<?php
if ( ! defined('BASEPATH')) exit('No direct script access allowed');
$characterPageQuests = array();
$player = $GLOBALS['player'];
$characterPageQuests[] = array('storage'=>30007, 'value'=>1, 'name'=>'Kisame - Poderoso Ninja da Akatsuki - Anular Direito');


   if(count($characterPageQuests) != 0) {
		echo "<table width='100%'>";
		
		$SQL = POT::getInstance()->getDBHandle();
		foreach($characterPageQuests as $value) {
			$quest = $SQL->query("SELECT `value` FROM `player_storage` WHERE `player_id` = ".$player->getId()." AND `key` = '".$value['storage']."' AND `value` = '".$value['value']."'")->fetch();
			$status = ($quest) ? "conclusao" : "missao";
			echo "<tr><td width='90%'>".$value['name']."</td><td><center><img src='../../../public/images/$status.gif'></center></td></tr>";
		}
		echo "</table>";
	}
?>


</div>
<br>