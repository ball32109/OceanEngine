

local function dispatcher(source,session)
	--print("call lua",source,session)
	Finish.Log(string.format("fuck you,%d",source))
end

Finish.SetCallBack(dispatcher)