<?php /* Smarty version 3.0rc1, created on 2013-05-15 13:20:32
         compiled from "templates/naruto\index.tpl" */ ?>
<?php /*%%SmartyHeaderCode:2395151937d9079df68-77934790%%*/if(!defined('SMARTY_DIR')) exit('no direct access allowed');
$_smarty_tpl->decodeProperties(array (
  'file_dependency' => 
  array (
    'bdd254507a8c80c0444dffa8c1d14b5462e39ed0' => 
    array (
      0 => 'templates/naruto\\index.tpl',
      1 => 1368620421,
    ),
  ),
  'nocache_hash' => '2395151937d9079df68-77934790',
  'function' => 
  array (
  ),
  'has_nocache_code' => false,
)); /*/%%SmartyHeaderCode%%*/?>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
	<head>
		<meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
		<meta name="distribution" content="Global" />
		<meta name="author" content="Vean" />
		<meta name="robots" content="index,follow" />
		<meta name="description" content="Site Description." />
		<meta name="keywords" content="ots, open tibia server, ..." />
		<?php echo $_smarty_tpl->getVariable('head')->value;?>

		<title>.:: Naruto Online Shinobi ::.</title>
		<link rel="stylesheet" type="text/css" href="<?php echo $_smarty_tpl->getVariable('path')->value;?>
/templates/naruto/main.css" />
		<link href="<?php echo $_smarty_tpl->getVariable('path')->value;?>
/templates/naruto/favicon.ico" rel="shortcut icon" />
	</head>
	<!--Google-->
	<script type="text/javascript">

	  var _gaq = _gaq || [];
	  _gaq.push(['_setAccount', 'UA-15249041-2']);
	  _gaq.push(['_trackPageview']);

	  (function() {
	    var ga = document.createElement('script'); ga.type = 'text/javascript'; ga.async = true;
	    ga.src = ('https:' == document.location.protocol ? 'https://ssl' : 'http://www') + '.google-analytics.com/ga.js';
	    var s = document.getElementsByTagName('script')[0]; s.parentNode.insertBefore(ga, s);
	  })();

	</script>
	<body>
		<div id="vt_page">
			<div id="vt_header"></div>
			<div id="vt_container">
				<div id="vt_menu">
					<div id="vt_news_menu">
<center>
						<div class="header"></div></center>
						<ul>
							<li><a href="<?php echo $_smarty_tpl->getVariable('path')->value;?>
">Novidades</a></li>
							<li><a href="<?php echo $_smarty_tpl->getVariable('path')->value;?>
/index.php/bugtracker">Bugs Reportados</a></li>
						</ul>
					</div>
					<div id="vt_account_menu"><center>
						<div class="serv"></div></center>
						<ul>
							<?php if ($_smarty_tpl->getVariable('logged')->value==1){?>
							<li><a href="<?php echo $_smarty_tpl->getVariable('path')->value;?>
/index.php/account/">Minha Conta</a></li>
							<?php }else{ ?>
							<li><a href="<?php echo $_smarty_tpl->getVariable('path')->value;?>
/index.php/account/create">Criar Conta</a></li>
							<li><a href="<?php echo $_smarty_tpl->getVariable('path')->value;?>
/index.php/account/login">Login</a></li>
							<?php }?>
						</ul>
					</div>
					<div id="vt_community_menu">
						<div class="comu"></div>
						<ul>
							<li><a href="<?php echo $_smarty_tpl->getVariable('path')->value;?>
/index.php/character/view">Procurar Personagem</a></li>
							<li><a href="<?php echo $_smarty_tpl->getVariable('path')->value;?>
/index.php/guilds">Guilds</a></li>
							<li><a href="<?php echo $_smarty_tpl->getVariable('path')->value;?>
/index.php/p/v/fragers">Top fraggers</a></li>	
							<li><a href="<?php echo $_smarty_tpl->getVariable('path')->value;?>
/index.php/video">Videos</a></li>	
							<li><a href="<?php echo $_smarty_tpl->getVariable('path')->value;?>
/index.php/houses/main">Casas</a></li>	
							<li><a href="<?php echo $_smarty_tpl->getVariable('path')->value;?>
/index.php/p/v/deaths">Ultimas Mortes</a></li>
							<li><a href="<?php echo $_smarty_tpl->getVariable('path')->value;?>
/index.php/p/v/gallery">Galeria</a></li>						
							<li><a href="<?php echo $_smarty_tpl->getVariable('path')->value;?>
/index.php/highscores">Ranking</a></li>	
							<li><a href="<?php echo $_smarty_tpl->getVariable('path')->value;?>
/index.php/profile/community">Comunidade</a></li>
		                 	<li><a href="<?php echo $_smarty_tpl->getVariable('path')->value;?>
/index.php/character/online">Online</a></li>

						</ul>
					</div>
					<div class="info"></div>
					<ul>
					       <li><a href="<?php echo $_smarty_tpl->getVariable('path')->value;?>
/index.php/p/v/perso">INFO Personagem</a></li>
					       <li><a href="<?php echo $_smarty_tpl->getVariable('path')->value;?>
/index.php/p/v/mapa">Mapa</a></li>
							<li><a href="<?php echo $_smarty_tpl->getVariable('path')->value;?>
/index.php/p/v/staff">Equipe NTO</a></li>
							<li><a href="<?php echo $_smarty_tpl->getVariable('path')->value;?>
/index.php/p/v/bans">Banidos NTO</a></li>
							<li><a href="<?php echo $_smarty_tpl->getVariable('path')->value;?>
/index.php/p/v/bandeira">Evento Bandeira NTO</a></li>
							</ul>
					</div>
				<div id="vt_content">
					<?php echo $_smarty_tpl->getVariable('main')->value;?>

				</div>
				<div id="vt_panel">
					<div class="top">
						<div class="bot">
							<div id="vt_panel_buttons">
								<a href="http://www.mediafire.com/?zjrwhwotu9o4dqo" class="button">
									 <span></span>
								</a>
								
								<a href="<?php echo $_smarty_tpl->getVariable('path')->value;?>
/index.php/p/v/gifts" class="button2"></a>
								<a href="x" class="button1"></a></div>
							<div class="vt_panel_module"><center>
								<div class="header">Server Status</div></centeR>
								<?php  $_smarty_tpl->tpl_vars['world'] = new Smarty_Variable;
 $_smarty_tpl->tpl_vars['id'] = new Smarty_Variable;
 $_from = $_smarty_tpl->getVariable('worlds')->value; if (!is_array($_from) && !is_object($_from)) { settype($_from, 'array');}
if (count($_from) > 0){
    foreach ($_from as $_smarty_tpl->tpl_vars['world']->key => $_smarty_tpl->tpl_vars['world']->value){
 $_smarty_tpl->tpl_vars['id']->value = $_smarty_tpl->tpl_vars['world']->key;
?>
								<div>
									<b>Servidor:</b> <?php echo $_smarty_tpl->getVariable('world')->value;?>
 <br />
									<b>Status:</b>  
									<?php if ($_smarty_tpl->getVariable('serverOnline')->value[$_smarty_tpl->getVariable('id')->value]){?>
										<span style="color: green;font-weight: bold;">Online</span><br />
										<b>Uptime:</b> <?php echo $_smarty_tpl->getVariable('serverUptime')->value[$_smarty_tpl->getVariable('id')->value];?>
 <br />
										<b>Players:</b> <?php echo $_smarty_tpl->getVariable('serverPlayers')->value[$_smarty_tpl->getVariable('id')->value];?>
/<?php echo $_smarty_tpl->getVariable('serverMax')->value[$_smarty_tpl->getVariable('id')->value];?>
<br /><br />
									<?php }else{ ?>
										<span style="color: red;font-weight: bold;">Offline</span>
									<?php }?>
								</div>

<center>
<div class="header">FACEBOOK!</div>
<a href="http://www.facebook.com/pages/NTOShinobi/149810838495212">
<img src="http://img196.imageshack.us/img196/2865/facebookzu.png" width="250" height="250"></a>
</center>
<div>
<?php echo $_smarty_tpl->getVariable('poll')->value;?>
 <br />
</div> 
								<?php }} ?>
							</div>
						</div>
					</div>
				</div>
			</div>
			<div id="vt_footer">
				<div class="column first">
					<a href=""><img src="<?php echo $_smarty_tpl->getVariable('path')->value;?>
/templates/naruto/images/authornote.png" alt="Designed by Eddy" /></a>
				</div>
				<div class="column second">
					<p>2013 - NtoForce			<p><small>Page rendered in: <?php echo $_smarty_tpl->getVariable('renderTime')->value;?>
 <?php echo $_smarty_tpl->getVariable('admin')->value;?>
</small></p>
				</div>
				<div class="column third">

				</div>
			</div>
		</div>
	</body>
</html>