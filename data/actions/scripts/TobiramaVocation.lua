function  onUse(cid, item, frompos, item2, tops)
local voc = 801 -- id da vocation que ele vai ser promovido
local outfit = 637 -- looktype
if item.itemid == 11417 then -- id do item q ele vai ter q clicar
	doCreatureChangeOutfit(cid, {lookType = outfit})
	doPlayerSetVocation(cid, voc)
	doRemoveItem(item.uid,1)
	doPlayerSendTextMessage(cid, 22, "Parabens voce trocou de Vocacao!")
	setPlayerStorageValue(cid, 9511, 801)
end
return true
end