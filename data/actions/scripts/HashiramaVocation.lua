function  onUse(cid, item, frompos, item2, tops)
local voc = 781 -- id da vocation que ele vai ser promovido
local outfit = 578 -- looktype
if item.itemid == 11410 then -- id do item q ele vai ter q clicar
	doCreatureChangeOutfit(cid, {lookType = outfit})
	doPlayerSetVocation(cid, voc)
	doRemoveItem(item.uid,1)
	doPlayerSendTextMessage(cid, 22, "Parabens voce trocou de Vocacao!")
	setPlayerStorageValue(cid, 9510, 781)
end
return true
end