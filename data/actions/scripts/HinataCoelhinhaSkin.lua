function  onUse(cid, item, frompos, item2, tops)
local voc = 1074 -- id da vocation que ele vai ser promovido
local outfit = 115 -- looktype
if item.itemid == 11659 then -- id do item q ele vai ter q clicar
	doCreatureChangeOutfit(cid, {lookType = outfit})
	doPlayerSetVocation(cid, voc)
	doRemoveItem(item.uid,1)
	doPlayerSendTextMessage(cid, 22, "Parabens voce trocou de Skin!")
	setPlayerStorageValue(cid, 9522, 1074)
end
return true
end