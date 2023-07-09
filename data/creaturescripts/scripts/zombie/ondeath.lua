function onDeath(cid)
	setZombiesToSpawnCount(getZombiesToSpawnCount() + 2)
	doCreatureSay(cid, "Eu voltei!", 19)
	return true
end