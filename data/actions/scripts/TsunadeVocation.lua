function  onUse(cid, item, frompos, item2, tops)
local voc = 731 -- id da vocation que ele vai ser promovido
local outfit = 534 -- looktype
if item.itemid == 11478 then -- id do item q ele vai ter q clicar
	doCreatureChangeOutfit(cid, {lookType = outfit})
	doPlayerSetVocation(cid, voc)
	doRemoveItem(item.uid,1)
	doPlayerSendTextMessage(cid, 22, "Parabens voce trocou de Vocacao!")
	setPlayerStorageValue(cid, 9494, 731)
end
return true
end