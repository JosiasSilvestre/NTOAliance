function  onUse(cid, item, frompos, item2, tops)
local voc = 971 -- id da vocation que ele vai ser promovido
local outfit = 406 -- looktype
if item.itemid == 11479 then -- id do item q ele vai ter q clicar
	doCreatureChangeOutfit(cid, {lookType = outfit})
	doPlayerSetVocation(cid, voc)
	doRemoveItem(item.uid,1)
	doPlayerSendTextMessage(cid, 22, "Parabens voce trocou de Vocacao!")
	setPlayerStorageValue(cid, 9500, 971)
end
return true
end