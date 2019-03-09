local stu = 
{
	[1]="1",
	[2]="2",
	[3]="3",
	[4]="4",
	[5]="5",
	[6]="6",
	[8]="8",
}

local test_pairs={}
test_pairs.__index = test_pairs

function test_pairs:init()
	local num = -1
end

function test_pairs:show()
	print("this ipairs table list")

	for i,v in ipairs(stu) do
		print( v)
	end

	print("this pairs table list")

	for i,v in pairs(stu) do
		print( v)
	end
end

function test_pairs:print()
	--print(self.num)
end

return test_pairs

