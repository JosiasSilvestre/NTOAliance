function  onUse(cid, item, frompos, item2, tops)
local voc = 1083 -- id da vocation que ele vai ser promovido
local outfit = 157 -- looktype
if item.itemid == 11670 then -- id do item q ele vai ter q clicar
	doCreatureChangeOutfit(cid, {lookType = outfit})
	doPlayerSetVocation(cid, voc)
	doRemoveItem(item.uid,1)
	doPlayerSendTextMessage(cid, 22, "Parabens voce trocou de Skin!")
	setPlayerStorageValue(cid, 9531, 1083)
end
return true
end