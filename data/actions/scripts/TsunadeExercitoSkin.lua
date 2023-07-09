function  onUse(cid, item, frompos, item2, tops)
local voc = 1073 -- id da vocation que ele vai ser promovido
local outfit = 112 -- looktype
if item.itemid == 11658 then -- id do item q ele vai ter q clicar
	doCreatureChangeOutfit(cid, {lookType = outfit})
	doPlayerSetVocation(cid, voc)
	doRemoveItem(item.uid,1)
	doPlayerSendTextMessage(cid, 22, "Parabens voce trocou de Skin!")
	setPlayerStorageValue(cid, 9521, 1073)
end
return true
end