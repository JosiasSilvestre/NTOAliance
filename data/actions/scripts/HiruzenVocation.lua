function  onUse(cid, item, frompos, item2, tops)
local voc = 891 -- id da vocation que ele vai ser promovido
local outfit = 2 -- looktype
if item.itemid == 11640 then -- id do item q ele vai ter q clicar
	doCreatureChangeOutfit(cid, {lookType = outfit})
	doPlayerSetVocation(cid, voc)
	doRemoveItem(item.uid,1)
	doPlayerSendTextMessage(cid, 22, "Parabens voce trocou de Vocacao!")
	setPlayerStorageValue(cid, 9515, 891)
end
return true
end