function onSay(cid, words, param, channel)
	param = tonumber(param)
	if(not param or param < 0 or param > 999999) then
		doPlayerSendCancel(cid, "O parametro numerico nao pode ser menor que 0 e maior que 41.")
		return true
	end

	local position = getCreaturePosition(cid)
	for i = 1, 30 do
		doSendDistanceShoot(position, {x = position.x + math.random(-7, 7), y = position.y + math.random(-5, 5), z = position.z}, param)
	end

	return true
end
