function  onUse(cid, item, frompos, item2, tops)
local voc = 1087 -- id da vocation que ele vai ser promovido
local outfit = 1334 -- looktype
if item.itemid == 11674 then -- id do item q ele vai ter q clicar
	doCreatureChangeOutfit(cid, {lookType = outfit})
	doPlayerSetVocation(cid, voc)
	doRemoveItem(item.uid,1)
	doPlayerSendTextMessage(cid, 22, "Parabens voce trocou de Skin!")
	setPlayerStorageValue(cid, 9535, 1087)
end
return true
end