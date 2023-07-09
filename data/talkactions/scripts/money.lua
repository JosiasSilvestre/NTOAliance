function onSay(cid, words, param, channel)
	doPlayerSendTextMessage(cid, MESSAGE_STATUS_CONSOLE_BLUE, "Voce possui " .. getPlayerMoney(cid) .. " gold.")
	return true
end
