--[[
    Capture The Flag System 
    Author: Maxwell Denisson(MaXwEllDeN)
    Version: 1.0
]]

_CTF_LIB = {
         redid = 17530,
         greenid = 17531,
                
         Flagsto = 13221,         
         teamssto = 17530,         

         winp = 15,
         recompCTF = {{2160, 2}},
                          
         nopen = true, -- Precisa usar o comando para abrir? false não true sim
         
         CTFSto = 95712,
         TownExit = 1, -- Templo que o player será teletransportado quando acabar o evento ou ele sair dele.

         price = false, -- Preço para entrar no Evento, caso não precise Digite false.
         teamsOUT = {}
}

_CTF_LIB.flags = {
               [_CTF_LIB.redid] = {pos = {x = 1013, y = 707, z = 6},
                                  posEflag = {x = 1011, y = 707, z = 7},
                                  id = 1435, color = 180, na = "Madara",
                                  temple = 5,                                  
                                  color = 180,
                                  out = {          
                                        [1] = {lookType = 244, lookHead = 0, lookBody = 132, lookLegs = 113, lookFeet = 94},
                                        [2] = {lookType = 244, lookHead = 0, lookBody = 94, lookLegs = 113, lookFeet = 113},
                                        [3] = {lookType = 244, lookHead = 0, lookBody = 132, lookLegs = 113, lookFeet = 94, lookAddons = 3}}
                                  },
               [_CTF_LIB.greenid] = {pos = {x = 1012, y = 735, z = 6},
                                    posEflag = {x = 1010, y = 734, z = 7},
                                    id = 1437, color = 30, na = "Hashirama",
                                    temple = 6,
                                    color = 31,
                                    out = {
                                          [1] = {lookType = 370, lookHead = 0, lookBody = 121, lookLegs = 101, lookFeet = 101},                                        
                                          [2] = {lookType = 370, lookHead = 0, lookBody = 121, lookLegs = 101, lookFeet = 101, lookAddons = 1},
                                          [3] = {lookType = 370, lookHead = 0, lookBody = 121, lookLegs = 101, lookFeet = 101, lookAddons = 3}}
                                    }          
         }           



for a, b in pairs(_CTF_LIB.flags) do

    local condition = createConditionObject(CONDITION_OUTFIT)
    setConditionParam(condition, CONDITION_PARAM_TICKS, 180000*1000)
    addOutfitCondition(condition, b.out[1])

    local condition2 = createConditionObject(CONDITION_OUTFIT)
    setConditionParam(condition2, CONDITION_PARAM_TICKS, 180000*1000)
    addOutfitCondition(condition2, b.out[2])              

    local other = createConditionObject(CONDITION_OUTFIT)
    setConditionParam(other, CONDITION_PARAM_TICKS, 180000*1000)
    addOutfitCondition(other, b.out[3])
            
    _CTF_LIB.teamsOUT[a] = {}
    _CTF_LIB.teamsOUT[a][0] = condition2
    _CTF_LIB.teamsOUT[a][1] = condition
    _CTF_LIB.teamsOUT[a][2] = other            
    
end

function MsgToCTFM(class, msg)
   for _, b in pairs (getOnlinePlayers()) do       
       local b = getPlayerByNameWildcard(b)
       if (getPlayerStorageValue(b, _CTF_LIB.teamssto) > 0) then
          doPlayerSendTextMessage(b, class, msg)
       end
   end       
end

function getTeamLivre()
   local teams = {}
   for a, b in pairs(_CTF_LIB.flags) do
       table.insert(teams, {getGlobalStorageValue(a), a})
   end        
      
   if (teams[1][1] < teams[2][1]) then
      return teams[1][2]
   elseif (teams[1][1] > teams[2][1]) then      
      return teams[2][2]
   end

   local team = teams[math.random(#teams)][2] 
   return team   
end

function doFindItemInPos(ids,pos) -- By Undead Slayer
   local results = {}
   
   for _ = 0, 255 do
       local findPos = {x = pos.x, y = pos.y, z = pos.z, stackpos = _}
       if isInArray(ids, getThingFromPos(findPos).itemid) then
          table.insert(results, getThingFromPos(findPos))
       end
   end
   
   return results
end

function CTF_createFlags()
   for a, b in pairs(_CTF_LIB.flags) do
      local item = doCreateItem(b.id, 1, b.pos)
      doItemSetAttribute(item, "uid", a)
      doItemSetAttribute(item, "aid", 67189)

      b.posEflag.stackpos = 0
      local item = getThingFromPos(b.posEflag).uid

      doItemSetAttribute(item, "uid", a)
      doItemSetAttribute(item, "aid", 15312)
            
      setGlobalStorageValue(a-15, 0)
      setGlobalStorageValue(a, 0)                           
   end
end

function ComparePosition(pos1, pos2)   
   if (((pos1.x ~= pos2.x) or (pos1.y ~= pos2.y) or (pos1.z ~= pos2.z))) then
      return false
   end
   return true
end

function CreateFlag(pos, id)
   if (#doFindItemInPos({id}, pos) < 1) then    
      return doCreateItem(id, 1, pos)
   end       
   return true   
end

function RemoveFlag(pos, id)
local iteims = doFindItemInPos({id}, pos)
   if (#iteims > 0) then    
      for _, b in pairs(iteims) do
         doRemoveItem(b.uid, 1)
      end
   end
   return true
end

function WalkFlag(uid, team, pos, bant)
   local function Alert(pos)      
      if (isCreature(uid)) then  

         if (getPlayerStorageValue(uid, _CTF_LIB.Flagsto) < 1) or (getPlayerStorageValue(uid, _CTF_LIB.teamssto) < 1) then                        
            return RemoveFlag(getPPos(uid), _CTF_LIB.flags[bant].id)  
         end

         if (getPlayerStorageValue(uid, _CTF_LIB.Flagsto) == 17001) then
            RemoveFlag(getPPos(uid), _CTF_LIB.flags[bant].id)
            return setPlayerStorageValue(uid, _CTF_LIB.Flagsto, -1)                        
         end        
                              
         if not(ComparePosition(getThingPos(uid), getPPos(uid))) then
            RemoveFlag(getPPos(uid), _CTF_LIB.flags[bant].id)
            setPPos(uid, getThingPos(uid))         
            CreateFlag(getThingPos(uid), _CTF_LIB.flags[bant].id)
         end         
         
         addEvent(Alert, 250, pos)
      end   
   end
   Alert(pos)
   return true
end


function setPPos(uid, pos)
   return setPlayerStorageValue(uid, 50117, "{x = ".. pos.x ..", y = ".. pos.y ..", z = ".. pos.z .."}")      
end

function getPPos(uid)      
   return loadstring('return ' .. getPlayerStorageValue(uid, 50117))()
end

function getFlag(uid, team, bant)
   setPPos(uid, getThingPos(uid))
   CreateFlag(getThingPos(uid), _CTF_LIB.flags[bant].id)      
   setPlayerStorageValue(uid, _CTF_LIB.Flagsto, bant)

   MsgToCTFM(22, getCreatureName(uid) .. " roubou a bandeira do time ".. _CTF_LIB.flags[bant].na .. "!")
   return WalkFlag(uid, team, getThingPos(uid), bant)       
end

function devolverFlag(uid, team)
   if (#doFindItemInPos({_CTF_LIB.flags[team].id}, _CTF_LIB.flags[team].pos) < 1) then    
      local item = doCreateItem(_CTF_LIB.flags[team].id, 1, _CTF_LIB.flags[team].pos)
      doItemSetAttribute(item, "uid", team)
      doItemSetAttribute(item, "aid", 67189)      
   end             
   return setPlayerStorageValue(uid, _CTF_LIB.Flagsto, 17001)
end

function addPoint(uid, team, bant)
   if (getGlobalStorageValue(team-15) < 0) then
      setGlobalStorageValue(team-15, 0) 
   end                                 
   
   RemoveFlag(getPPos(uid), _CTF_LIB.flags[bant].id)
   addEvent(devolverFlag, 2000, uid, bant)      
   setGlobalStorageValue(team-15, getGlobalStorageValue(team-15)+1)
   msgi = "Capture The Flag by MaXwellDeN:\n"   

   doSendAnimatedText(getThingPos(uid), "+POINT+", _CTF_LIB.flags[bant].color)
   for a, b in pairs (_CTF_LIB.flags) do
       if (getGlobalStorageValue(a-15) < 0) then
          setGlobalStorageValue(a-15, 0)
       end
       msgi = msgi .. "\n Time ".. b.na .." -> ".. getGlobalStorageValue(a-15) .. " point(s)."
   end   
    
   for _, b in pairs (getOnlinePlayers()) do       
       local b = getPlayerByNameWildcard(b)
       if (getPlayerStorageValue(b, _CTF_LIB.teamssto) > 0) then
          doPlayerSendTextMessage(b, 22, getCreatureName(uid) .. " entregou a bandeira do time ".. _CTF_LIB.flags[bant].na .. " e obteve 1 ponto para seu time!")
          doPlayerSendTextMessage(b, 27, msgi)
       end
   end
   
   for a, b in pairs(_CTF_LIB.flags) do
      if (getGlobalStorageValue(a-15) >= _CTF_LIB.winp) then
         for c, _ in pairs(_CTF_LIB.flags) do
            setGlobalStorageValue(c-15, 0) 
         end

         for _, cid in pairs (getOnlinePlayers()) do
             local cid = getPlayerByNameWildcard(cid)
             if (getPlayerStorageValue(cid, _CTF_LIB.teamssto) > 0) then
                doPlayerSendTextMessage(cid, 27, "O Time ".. _CTF_LIB.flags[team].na .." venceu o Capture a bandeira, por tanto, todos os membros dessa equipa ganharam uma recompensa. Parabéns!")
                if (getPlayerStorageValue(cid, _CTF_LIB.teamssto) == a) then
                   for _, y in pairs(_CTF_LIB.recompCTF) do
                      doPlayerAddItem(cid, y[1], y[2])
                   end
                end
                
                doCreatureAddHealth(cid, getCreatureMaxHealth(cid))
                doCreatureAddMana(cid, getCreatureMaxMana(cid))
                doPlayerSetTown(cid, _CTF_LIB.TownExit);
                doTeleportThing(cid, getTownTemplePosition(_CTF_LIB.TownExit))
                doCreatureSetSkullType(cid, 0)
                doRemoveCondition(cid, CONDITION_PARAM_OUTFIT)                
                setPlayerStorageValue(cid, _CTF_LIB.teamssto, -1)
             end         
         end                          
         break
      end
   end
   
   return true
end