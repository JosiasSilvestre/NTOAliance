function onUse(cid, item, fromPosition, itemEx, toPosition)
	if item.uid > 1000 and item.uid < 13000 then
		local itemWeight = getItemWeightById(item.uid, 1)
		local playerCap = getPlayerFreeCap(cid)
		if getPlayerStorageValue(cid, item.uid) == -1 then
			if playerCap >= itemWeight then
				doPlayerSendTextMessage(cid, MESSAGE_INFO_DESCR, 'Voce encontrou um ' .. getItemNameById(item.uid) .. '.')
				doPlayerAddItem(cid, item.uid ,1)
				setPlayerStorageValue(cid, item.uid, 1)
			else
				doPlayerSendTextMessage(cid, MESSAGE_INFO_DESCR, 'Voce encontrou um ' .. getItemNameById(item.uid) .. ' weighing ' .. itemWeight .. ' oz E pesado demais.')
			end
		else
			doPlayerSendTextMessage(cid, MESSAGE_INFO_DESCR, "Esta vazio.")
		end
	else
		return false
	end
	return true
end