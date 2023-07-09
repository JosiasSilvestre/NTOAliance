function  onUse(cid, item, frompos, item2, tops)
local voc = 1070 -- id da vocation que ele vai ser promovido
local outfit = 122 -- looktype
if item.itemid == 11664 then -- id do item q ele vai ter q clicar
	doCreatureChangeOutfit(cid, {lookType = outfit})
	doPlayerSetVocation(cid, voc)
	doRemoveItem(item.uid,1)
	doPlayerSendTextMessage(cid, 22, "Parabens voce trocou de Skin!")
	setPlayerStorageValue(cid, 9518, 1070)
end
return true
end