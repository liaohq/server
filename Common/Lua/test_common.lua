local c = require "test"

local test_common={}
test_common.__index = test_common


function test_common:init()

end

function test_common:local_var()
   local i = 0
   return function()
	   i=i+1
	   return i
   end
end

function test_common:show_error()
	error("hello world")
end

function test_common:show_assert()
	assert(false,"assert test")
end

function test_common:show_traceback()
	print(debug.traceback())
end

function test_common:show_debug()
	print(debug.debug())
end

function test_common:show_pcall()
	if pcall(test_common:show_assert()) then
		print("show pcall right")
	else
		print("show pcall error")
	end
end

function test_common:call_c_function()
	local a=MyTest()
	print("a=",a)

end
return test_common
