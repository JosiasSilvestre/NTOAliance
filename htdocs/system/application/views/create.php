<div class='errors'> <?php echo error(validation_errors()); ?> </div>
<?php include("public/js/keyboard.php");
global $config;
?>
<script>
	function createAccount() {
		$('.loader').show();
		var form = $('#createAccount').serialize();
		$.ajax({
			url: '<?php echo WEBSITE; ?>/index.php/account/create/1',
			  type: 'post',
			  data: form,
			  success: function(data) {
			  	$('.errors').html(data);
			  	$('.loader').hide();
			  }
		});
	}
</script>
<link rel="stylesheet" type="text/css" href="<?php echo WEBSITE; ?>/public/css/keyboard.css">
<div class='message'>
	<div class='title'>Create an Account</div>
	<div class='content'> <?php echo form_open('account/create', array('id'=>'createAccount')); ?>
		<fieldset>
			<legend >Account Info</legend>
			<div class="table">
				<ul style="width:30%">
					<li class="even">
						<label for="name">Account Name</label>
					</li>
					<li class="odd">
						<label for="nickname">Nickname</label>
					</li>
					<li class="even">
						<label for="email">E-mail</label>
					</li>
					<li class="odd">
						<label for="password">Password</label>
					</li>
					<li class="even">
						<label for="repeat">Repeat</label>
					</li>
				</ul>
				<ul style="width:70%">
					<li class="even">
						<input type="text" value="<?php echo set_value('name'); ?>" id="name" class="keyboardInput" name="name"/>
					</li>
					<li class="odd">
						<input type='text' name='nickname' id="nickname" value='<?php echo set_value('nickname'); ?>' />
					</li>
					<li class="even">
						<input  type="text" value="<?php echo set_value('email'); ?>" id="email" name="email"/>
					</li>
					<li class="odd">
						<input type="password" class="keyboardInput" id="password" name="password"/>
					</li>
					<li class="even">
						<input type="password" class="keyboardInput" id="repeat" name="repeat"/>
					</li>
				</ul>
			</div>
		</fieldset>
		<fieldset>
			<legend>Character Info</legend>
			<div class="table">
				<ul style="width:30%">
					<li class="even">
						<label for="character_name">Character name:</label>
					</li>
					<li class="odd">
						<label for="sex">Sex:</label>
					</li>
					<li class="even">
						<label for="vocation">Choose vocation:</label>
					</li>
					<li class="odd">
						<label for="city">Choose city:</label>
					</li>
					<li class="even">
						<label for="world">World:</label>
					</li>
				</ul>
				<ul style="width:70%">
					<li class="even">
						<input  type="text" id="character_name" value="<?php echo set_value('character_name'); ?>" name="character_name"/>
					</li>
					<li class="odd">
						<input name="sex" type="radio" id="sex" value="1" checked="checked" />
						male &nbsp;
						<input type="radio" id="sex" name="sex" value="0" />
						female </li>
					<li class="even">
						<select name="vocation" class="keyboardInput" id="vocation">
							<option value="1">Naruto</option>
							<option value="13">Sasuke</option>
							<option value="25">Lee</option>
							<option value="34">Sakura</option>
							<option value="50">Gaara</option>
							<option value="70">Neji</option>
							<option value="90">Kiba</option>
							<option value="110">Shikamaru</option>
							<option value="130">Hinata</option>
							<option value="150">Tenten</option>
							<option value="170">Itachi</option>
							<option value="190">Killer Bee</option>
							<option value="200">Kakashi</option>
							<option value="620">Yamato</option>
							<option value="220">Tobi</option>
							<option value="580">Kakuzu</option>
							<option value="550">Hidan</option>
							<option value="520">Raikage</option>
							<option value="235">Minato</option>
							<option value="500">Kisame</option>
							<option value="600">Madara</option>
							<option value="210">Temari</option>
							<option value="251">Sasori</option>

						</select>
					</li>
					<li class="odd">
						<select name="city" id="city">
							<?php 
	foreach($config['cities'] as $city => $name)  
		echo '<option value="'.$city.'">'.$name.'</option>'; ?>
						</select>
					</li>
					<li class="even">
						<?php 
if(sizeof($config['worlds']) > 1) { ?>
						<select name="world" id="world">
							<?php
	foreach($config['worlds'] as $world => $name)  
		echo '<option value="'.$world.'">'.$name.'</option>'; ?>
						</select>
						<?php }else{ ?>
						<input type="hidden" name="world" value="0" />
						<?php echo $config['worlds'][0]; ?>
						<?php } ?>
					</li>
				</ul>
			</div>
		</fieldset>
		<fieldset>
			<legend>Security image</legend>
			<div class="table">
				<ul style="width: 30%">
					<li class="even">
						
					</li>
					<li class="even">
						<label>Captcha World</label>
					</li>
				</ul>
				<ul style="width: 70%">
					<li class="even">
						<?php echo $captcha;?>
					</li>
					<li class="even">
						 <input type='text' name='captcha'/> 
					</li>
				</ul>
			</div>
		</fieldset>
		<br/>
		<label>&nbsp;</label>
		<input class='sub' type="submit" value="Register"/>
		<?php echo loader(); ?>
		</form>
	</div>
	<div class='bar'>If you create an account you accept to our <a href='#' onClick='$("#rules").toggle(500);'>Rules</a>.</div>
</div>
<div id='rules' style='margin-top: 10px; width: 100%; height: 300px; overflow: auto; display: none;'><?php echo nl2br(getContent("system/rules.php")); ?></div>
