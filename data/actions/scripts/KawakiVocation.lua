function  onUse(cid, item, frompos, item2, tops)
local voc = 1061 -- id da vocation que ele vai ser promovido
local outfit = 107 -- looktype
if item.itemid == 11656 then -- id do item q ele vai ter q clicar
	doCreatureChangeOutfit(cid, {lookType = outfit})
	doPlayerSetVocation(cid, voc)
	doRemoveItem(item.uid,1)
	doPlayerSendTextMessage(cid, 22, "Parabens voce trocou de Vocacao!")
	setPlayerStorageValue(cid, 9503, 1061)
end
return true
end