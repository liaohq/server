package.cpath = package.cpath .. ";../../Common/Luaclib/?.so;"
local c_test = require "libmylua.test"
local c_other = require "libmylua.other"
print(c_test.MyTest())
print(c_test.BaseOperate())
--print(c_test.ErrorTest())

local a ={11,22,33}
print(table.concat(a,",") )

print("lua_newtable test....\n")
local my_table = c_test.NewtableTest()
for i,v in pairs(my_table) do
	print("key=",i,"value=",v)
end

print("my_table size=",#my_table)



print("lua_gettable test....\n")


student = 
{
	name = "lhq",
	age  = 28,
}

c_test.GettableTest()


print("lua_getfield test....\n")
local menpai,level,world_id = c_test.GetfieldTest()

print("menpai=",menpai,",level=",level,",world_id=",world_id)

print("lua_newuserdata test....\n")

local user_data = c_test.NewUserData(100)
print(user_data)
c_test.SetUserData(user_data,0,12)
print("userdata 0 = ",c_test.GetUserData(user_data,0) )

assert(true,"helllll")
