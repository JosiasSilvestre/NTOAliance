function onUse(cid, item, fromPosition, itemEX, toPosition)

quest = 12301
if getPlayerStorageValue(cid,12301) == -1 then
doPlayerSendTextMessage(cid,25,"Voce recebeu a vocacao Kakuzo!")
doSendMagicEffect(getCreaturePosition(cid),12)
doPlayerAddItem(cid, 2110, 1)
setPlayerStorageValue(cid,12301, 1)
return true
end

if getPlayerStorageValue(cid,12301) == 1 then
doPlayerSendTextMessage(cid,25,"Voce ja recebeu esse item!")
doSendMagicEffect(getCreaturePosition(cid),2)
end

end