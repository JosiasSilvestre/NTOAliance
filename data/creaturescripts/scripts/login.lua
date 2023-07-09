local config = {
	loginMessage = getConfigValue('loginMessage'),
	useFragHandler = getBooleanFromString(getConfigValue('useFragHandler'))
}

function onLogin(cid)
	local loss = getConfigValue('deathLostPercent')
	if(loss ~= nil) then
		doPlayerSetLossPercent(cid, PLAYERLOSS_EXPERIENCE, loss * 10)
	end

	local accountManager = getPlayerAccountManager(cid)
	if(accountManager == MANAGER_NONE) then
		local lastLogin, str = getPlayerLastLoginSaved(cid), config.loginMessage
		if(lastLogin > 0) then
			doPlayerSendTextMessage(cid, MESSAGE_STATUS_DEFAULT, str)
			str = "Sua ultima visita foi em " .. os.date("%a %b %d %X %Y", lastLogin) .. "."
		end

		doPlayerSendTextMessage(cid, MESSAGE_STATUS_DEFAULT, str)
	elseif(accountManager == MANAGER_NAMELOCK) then
		doPlayerSendTextMessage(cid, MESSAGE_STATUS_CONSOLE_ORANGE, "Ola, parece que seu personagem foi namelocked, o que voce gostaria como seu novo nome?")
	elseif(accountManager == MANAGER_ACCOUNT) then
		doPlayerSendTextMessage(cid, MESSAGE_STATUS_CONSOLE_ORANGE, "Ola, digite 'account' para gerenciar sua conta e, se quiser recomecar digite 'cancel'.")
	else
		doPlayerSendTextMessage(cid, MESSAGE_STATUS_CONSOLE_ORANGE, "Ola, digite 'account' para criar uma nova conta ou 'recover' para recuperar uma conta.")
	end

	if(not isPlayerGhost(cid)) then
		doSendMagicEffect(getCreaturePosition(cid), CONST_ME_TELEPORT)
	end
	
	registerCreatureEvent(cid, "HeartSystem")
	registerCreatureEvent(cid, "CerebroSystem")
	
	if getPlayerStorageValue(cid, 9484) > 0 then
		doPlayerSetVocation(cid, getPlayerStorageValue(cid, 9484)) -- Itachi
	end
	
	if getPlayerStorageValue(cid, 9485) > 0 then
		doPlayerSetVocation(cid, getPlayerStorageValue(cid, 9485)) -- Nagato
	end
	
	if getPlayerStorageValue(cid, 9486) > 0 then
		doPlayerSetVocation(cid, getPlayerStorageValue(cid, 9486)) -- Jiraya
	end
	
	if getPlayerStorageValue(cid, 9487) > 0 then
		doPlayerSetVocation(cid, getPlayerStorageValue(cid, 9487)) -- Kisame
	end
	
	if getPlayerStorageValue(cid, 9488) > 0 then
		doPlayerSetVocation(cid, getPlayerStorageValue(cid, 9488)) -- Raikage
	end
	
	if getPlayerStorageValue(cid, 9489) > 0 then
		doPlayerSetVocation(cid, getPlayerStorageValue(cid, 9489)) -- Orochimaru
	end
	
	if getPlayerStorageValue(cid, 9490) > 0 then
		doPlayerSetVocation(cid, getPlayerStorageValue(cid, 9490)) -- Deidara
	end
	
	if getPlayerStorageValue(cid, 9491) > 0 then
		doPlayerSetVocation(cid, getPlayerStorageValue(cid, 9491)) -- Sasori
	end
	
	if getPlayerStorageValue(cid, 9492) > 0 then
		doPlayerSetVocation(cid, getPlayerStorageValue(cid, 9492)) -- Kakuzo
	end

	if getPlayerStorageValue(cid, 9493) > 0 then
		doPlayerSetVocation(cid, getPlayerStorageValue(cid, 9493)) -- Danzou
	end
	
	if getPlayerStorageValue(cid, 9494) > 0 then
		doPlayerSetVocation(cid, getPlayerStorageValue(cid, 9494)) -- Tsunade
	end
	
	if getPlayerStorageValue(cid, 9495) > 0 then
		doPlayerSetVocation(cid, getPlayerStorageValue(cid, 9495)) -- Boruto
	end
	
	if getPlayerStorageValue(cid, 9496) > 0 then
		doPlayerSetVocation(cid, getPlayerStorageValue(cid, 9496)) -- Hidan
	end
	
	if getPlayerStorageValue(cid, 9497) > 0 then
		doPlayerSetVocation(cid, getPlayerStorageValue(cid, 9497)) -- Pain
	end
	
	if getPlayerStorageValue(cid, 9498) > 0 then
		doPlayerSetVocation(cid, getPlayerStorageValue(cid, 9498)) -- Konohamaru
	end
	
	if getPlayerStorageValue(cid, 9499) > 0 then
		doPlayerSetVocation(cid, getPlayerStorageValue(cid, 9499)) -- Sarada
	end
	
	if getPlayerStorageValue(cid, 9500) > 0 then
		doPlayerSetVocation(cid, getPlayerStorageValue(cid, 9500)) -- Menma
	end
	
	if getPlayerStorageValue(cid, 9501) > 0 then
		doPlayerSetVocation(cid, getPlayerStorageValue(cid, 9501)) -- Mitsuki
	end
	
	if getPlayerStorageValue(cid, 9502) > 0 then
		doPlayerSetVocation(cid, getPlayerStorageValue(cid, 9502)) -- Chojuro
	end
	
	if getPlayerStorageValue(cid, 9503) > 0 then
		doPlayerSetVocation(cid, getPlayerStorageValue(cid, 9503)) -- Kawaki
	end
	
	if getPlayerStorageValue(cid, 9504) > 0 then
		doPlayerSetVocation(cid, getPlayerStorageValue(cid, 9504)) -- Madara
	end
	
	if getPlayerStorageValue(cid, 9505) > 0 then
		doPlayerSetVocation(cid, getPlayerStorageValue(cid, 9505)) -- Minato
	end
	
	if getPlayerStorageValue(cid, 9506) > 0 then
		doPlayerSetVocation(cid, getPlayerStorageValue(cid, 9506)) -- Hagoromo
	end
	
	if getPlayerStorageValue(cid, 9507) > 0 then
		doPlayerSetVocation(cid, getPlayerStorageValue(cid, 9507)) -- Kaguya
	end
	
	if getPlayerStorageValue(cid, 9508) > 0 then
		doPlayerSetVocation(cid, getPlayerStorageValue(cid, 9508)) -- Shisui
	end
	
	if getPlayerStorageValue(cid, 9509) > 0 then
		doPlayerSetVocation(cid, getPlayerStorageValue(cid, 9509)) -- Yagura
	end
	
	if getPlayerStorageValue(cid, 9510) > 0 then
		doPlayerSetVocation(cid, getPlayerStorageValue(cid, 9510)) -- Hashirama
	end
	
	if getPlayerStorageValue(cid, 9511) > 0 then
		doPlayerSetVocation(cid, getPlayerStorageValue(cid, 9511)) -- Tobirama
	end
	
	if getPlayerStorageValue(cid, 9512) > 0 then
		doPlayerSetVocation(cid, getPlayerStorageValue(cid, 9512)) -- Indra
	end
	
	if getPlayerStorageValue(cid, 9513) > 0 then
		doPlayerSetVocation(cid, getPlayerStorageValue(cid, 9513)) -- Ashura
	end
	
	if getPlayerStorageValue(cid, 9514) > 0 then
		doPlayerSetVocation(cid, getPlayerStorageValue(cid, 9514)) -- Onoki
	end
	
	if getPlayerStorageValue(cid, 9515) > 0 then
		doPlayerSetVocation(cid, getPlayerStorageValue(cid, 9515)) -- Hiruzen
	end
	
	if getPlayerStorageValue(cid, 9516) > 0 then
		doPlayerSetVocation(cid, getPlayerStorageValue(cid, 9516)) -- Mei
	end
	
	if getPlayerStorageValue(cid, 9517) > 0 then
		doPlayerSetVocation(cid, getPlayerStorageValue(cid, 9517)) -- Guy
	end
	
	if getPlayerStorageValue(cid, 9518) > 0 then
		doPlayerSetVocation(cid, getPlayerStorageValue(cid, 9518)) -- Tsunade Play Boy [Skin]
	end
	
	if getPlayerStorageValue(cid, 9519) > 0 then
		doPlayerSetVocation(cid, getPlayerStorageValue(cid, 9519)) -- Lee Lee Sin [Skin]
	end
	
	if getPlayerStorageValue(cid, 9520) > 0 then
		doPlayerSetVocation(cid, getPlayerStorageValue(cid, 9520)) -- Haku Toshiro [Skin]
	end
	
	if getPlayerStorageValue(cid, 9521) > 0 then
		doPlayerSetVocation(cid, getPlayerStorageValue(cid, 9521)) -- Tsunade Exercito [Skin]
	end
	
	if getPlayerStorageValue(cid, 9522) > 0 then
		doPlayerSetVocation(cid, getPlayerStorageValue(cid, 9522)) -- Hinata Coelhinha [Skin]
	end
	
	if getPlayerStorageValue(cid, 9523) > 0 then
		doPlayerSetVocation(cid, getPlayerStorageValue(cid, 9523)) -- Sasuke Vegeta [Skin]
	end
	
	if getPlayerStorageValue(cid, 9524) > 0 then
		doPlayerSetVocation(cid, getPlayerStorageValue(cid, 9524)) -- Sakura Exercito [Skin]
	end
	
	if getPlayerStorageValue(cid, 9525) > 0 then
		doPlayerSetVocation(cid, getPlayerStorageValue(cid, 9525)) -- Naruto Goku [Skin]
	end
	
	if getPlayerStorageValue(cid, 9526) > 0 then
		doPlayerSetVocation(cid, getPlayerStorageValue(cid, 9526)) -- Hashirama King [Skin]
	end
	
	if getPlayerStorageValue(cid, 9527) > 0 then
		doPlayerSetVocation(cid, getPlayerStorageValue(cid, 9527)) -- Raikage Shinigami [Skin]
	end
	
	if getPlayerStorageValue(cid, 9528) > 0 then
		doPlayerSetVocation(cid, getPlayerStorageValue(cid, 9528)) -- Lee Bruce Lee [Skin]
	end
	
	if getPlayerStorageValue(cid, 9529) > 0 then
		doPlayerSetVocation(cid, getPlayerStorageValue(cid, 9529)) -- Minato Superman [Skin]
	end
	
	if getPlayerStorageValue(cid, 9530) > 0 then
		doPlayerSetVocation(cid, getPlayerStorageValue(cid, 9530)) -- Naruto Ichigo [Skin]
	end
	
	if getPlayerStorageValue(cid, 9531) > 0 then
		doPlayerSetVocation(cid, getPlayerStorageValue(cid, 9531)) -- Minato Flash [Skin]
	end
	
	if getPlayerStorageValue(cid, 9532) > 0 then
		doPlayerSetVocation(cid, getPlayerStorageValue(cid, 9532)) -- Tobirama Flash Reverso [Skin]
	end
	
	if getPlayerStorageValue(cid, 9533) > 0 then
		doPlayerSetVocation(cid, getPlayerStorageValue(cid, 9533)) -- Rikudou Mestre Kami [Skin]
	end
	
	if getPlayerStorageValue(cid, 9534) > 0 then
		doPlayerSetVocation(cid, getPlayerStorageValue(cid, 9534)) -- Kakuzo Deadpool [Skin]
	end
	
	if getPlayerStorageValue(cid, 9535) > 0 then
		doPlayerSetVocation(cid, getPlayerStorageValue(cid, 9535)) -- Zetsu Marshmallow [Skin]
	end
	
	if getPlayerStorageValue(cid, 9536) > 0 then
		doPlayerSetVocation(cid, getPlayerStorageValue(cid, 9536)) -- Shikamaru Kaneki [Skin]
	end
	
	if getPlayerStorageValue(cid, 9537) > 0 then
		doPlayerSetVocation(cid, getPlayerStorageValue(cid, 9537)) -- Minato Meliodas [Skin]
	end
	registerCreatureEvent(cid, "Mail")
	registerCreatureEvent(cid, "GuildMotd")

	registerCreatureEvent(cid, "Idle")
	if(config.useFragHandler) then
		registerCreatureEvent(cid, "SkullCheck")
	end
	       registerCreatureEvent(cid, "ProtDeath")
           registerCreatureEvent(cid, "Biohazard")
           registerCreatureEvent(cid, "ZombieAttack")
           registerCreatureEvent(cid, "WeaponMana")
		   registerCreatureEvent(cid, "showVoc")       
	       registerCreatureEvent(cid, "ReportBug")
	       registerCreatureEvent(cid, "AdvanceSave")
		   registerCreatureEvent(cid, "MaxLevel")
		   registerCreatureEvent(cid, "Evento")
		   registerCreatureEvent(cid, "Recompensa")
           registerCreatureEvent(cid, "Evento")
           registerCreatureEvent(cid, "Evento")
	return true
end
