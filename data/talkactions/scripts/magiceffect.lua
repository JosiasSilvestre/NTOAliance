function onSay(cid, words, param, channel)
	param = tonumber(param)
	if(not param or param < 0 or param > 9999999) then
		doPlayerSendCancel(cid, "O parametro numerico nao pode ser menor que 0 e maior que 400.")
		return true
	end

	doSendMagicEffect(getCreaturePosition(cid), param)
	return true
end
