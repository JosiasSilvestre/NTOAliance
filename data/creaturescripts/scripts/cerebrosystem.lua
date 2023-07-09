function onDeath(cid, corpse, deathList)

local heart = doPlayerAddItem(deathList[1],5808, 1)

if isPlayer(cid) and isPlayer(deathList[1]) then

doItemSetAttribute(heart, "name", "" ..getPlayerName(cid).. " Brain's")
doItemSetAttribute(heart, "description", "Morto no Level "..getPlayerLevel(cid).." por "..getPlayerName(deathList[1])..". " .. (getCreatureSkullType(cid) <= SKULL_GREEN and "(Assassinado)" or "(Legitima defesa)"))
end
return true
end