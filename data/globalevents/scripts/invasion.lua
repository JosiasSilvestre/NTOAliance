local i = {
["7:00"] = {nome = "Invasao nukenin", pos = {x=1033, y=918, z=7}, monster = {"500 Nukenin", "1 Renegade"}},
["10:00"] = {nome = "Invasao nukenin", pos = {x=1033, y=918, z=7}, monster = {"500 Nukenin", "1 Renegade"}},
["15:00"] = {nome = "Invasao nukenin", pos = {x=1033, y=918, z=7}, monster = {"500 Nukenin", "1 Renegade"}},
["19:00"] = {nome = "Invasao nukenin", pos = {x=1033, y=918, z=7}, monster = {"500 Nukenin", "1 Renegade"}},
["22:00"] = {nome = "Invasao nukenin", pos = {x=1033, y=918, z=7}, monster = {"500 Nukenin", "1 Renegade"}},
}
function onThink(interval, lastExecution)
hours = tostring(os.date("%X")):sub(1, 5)
tb = i[hours]

if tb then
doBroadcastMessage(hours .. " - " .. tb.nome .. " iniciou.")
for _,x in pairs(tb.monster) do
for s = 1, tonumber(x:match("%d+")) do
doSummonCreature(x:match("%s(.+)"), tb.pos)
end

end

end

return true

end
