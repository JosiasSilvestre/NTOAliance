function onUse(cid, item, fromPosition, itemEX, toPosition)

quest = 7449
if getPlayerStorageValue(cid,7449) == -1 then
doPlayerSendTextMessage(cid,25,"Voce recebeu a vocacao Sasori!")
doSendMagicEffect(getCreaturePosition(cid),12)
doPlayerAddItem(cid, 2108, 1)
setPlayerStorageValue(cid,7449, 1)
return true
end

if getPlayerStorageValue(cid,7449) == 1 then
doPlayerSendTextMessage(cid,25,"Voce ja recebeu esse item!")
doSendMagicEffect(getCreaturePosition(cid),2)
end

end