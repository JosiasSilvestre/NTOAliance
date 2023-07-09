function  onUse(cid, item, frompos, item2, tops)
local voc = 521 -- id da vocation que ele vai ser promovido
local outfit = 880 -- looktype
if item.itemid == 11646 then -- id do item q ele vai ter q clicar
	doCreatureChangeOutfit(cid, {lookType = outfit})
	doPlayerSetVocation(cid, voc)
	doRemoveItem(item.uid,1)
	doPlayerSendTextMessage(cid, 22, "Parabens voce trocou de Vocacao!")
	setPlayerStorageValue(cid, 9488, 781)
end
return true
end