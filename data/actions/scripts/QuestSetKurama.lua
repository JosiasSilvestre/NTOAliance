function onUse(cid, item, fromPosition, itemEX, toPosition)

quest = 9445
if getPlayerStorageValue(cid, 9445) == -1 then
doPlayerSendTextMessage(cid,25,"Parabens, Aqui Esta Seu Set Kurama!")
doSendMagicEffect(getCreaturePosition(cid),12)
local bag = doPlayerAddItem(cid, 11500, 1)
doPlayerAddItem(cid, 11499, 1)
doPlayerAddItem(cid, 11498, 1)
doPlayerAddItem(cid, 11497, 1)
setPlayerStorageValue(cid,9445, 1)
return true
end

if getPlayerStorageValue(cid,9445) == 1 then
doPlayerSendTextMessage(cid,25,"Voce ja recebeu esse item!")
doSendMagicEffect(getCreaturePosition(cid),2)
end

end