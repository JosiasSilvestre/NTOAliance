function onUse(cid, item, fromPosition, itemEx, toPosition)
	local value = math.random(5792, 5797)
	doTransformItem(item.uid, value)
	doCreatureSay(cid, getCreatureName(cid) .. ' sorteou um ' .. value - 5791 .. '.', TALKTYPE_MONSTER)
	return true
end
