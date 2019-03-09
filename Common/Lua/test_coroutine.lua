local test_coroutine = {}
test_coroutine.__index = test_coroutine


function test_coroutine:init()

end

function test_coroutine:begin_test()
	--test_coroutine:test_param()
	test_coroutine:test_consume()
end

function test_coroutine:test()
	
	local co=coroutine.create(function()
		for i=1,10 do
			print("i=" .. i)
			if i==9 then
				coroutine.yield()
			end
		end
	end)
	
	print("coroutine status = " .. coroutine.status(co) )

	coroutine.resume(co)
	print("coroutine status = " .. coroutine.status(co) )
	
	coroutine.resume(co)
	print("coroutine status = " .. coroutine.status(co) )
    print(coroutine.resume(co) )
end

function test_coroutine:test_param()
	local co = coroutine.create( function(a,b,c)
			coroutine.yield(a,b,c)
		end)

	print( coroutine.resume(co,1,2,3) )

	local co1 = coroutine.create( function()
		print("co",coroutine.yield(88))
	end)

	coroutine.resume(co1,1,2,3)
	coroutine.resume(co1,555)


end

function test_coroutine:test_consume()
	function send(x)
		coroutine.yield(x)
	end

	local producer = coroutine.create( function()
		while true do
			local value = io.read()
			send(value)
		end
	end)


	function receive()
		local status,value = coroutine.resume( producer )
		if value then
			io.write(value,"\n")
		end
	end
	for i=1,10 do
		receive()
	end
end


return test_coroutine
