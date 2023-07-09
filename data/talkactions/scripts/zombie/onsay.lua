function onSay(cid, words, param, channel)
	if(getStorage(ZE_STATUS) ~= 2) then
		local players_on_arena_count = #getZombiesEventPlayers()
		if(param == 'force') then
			if(players_on_arena_count > 0) then
				setZombiesEventPlayersLimit(players_on_arena_count  )
				addZombiesEventBlockEnterPosition()
				doSetStorage(ZE_STATUS, 2)
				doBroadcastMessage("O evento assassino comecou.")
				doPlayerSendTextMessage(cid, MESSAGE_STATUS_CONSOLE_BLUE, "O evento assassino comecou.")
			else
				doPlayerSendTextMessage(cid, MESSAGE_STATUS_CONSOLE_BLUE, "Evento assassino cancelado. Nao teve participantes.")
			end
		else
			if(param ~= '' and tonumber(param) > 0) then
				setZombiesEventPlayersLimit(tonumber(param))
			end
			removeZombiesEventBlockEnterPosition()
			doSetStorage(ZE_STATUS, 1)
			doPlayerSendTextMessage(cid, MESSAGE_STATUS_CONSOLE_BLUE, "O evento comecou.")
			doBroadcastMessage("[Evento automatico] Foi aberto o teleporte para o Evento Assassino. Esperando " .. getZombiesEventPlayersLimit() - players_on_arena_count .. " jogadores para dar inicio ao evento.")
		end
	else
		doPlayerSendTextMessage(cid, MESSAGE_STATUS_CONSOLE_BLUE, "O Evento Assassino ja esta aberto.")
	end
	return true
end