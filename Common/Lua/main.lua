local test1=require("test_pairs")
local test_common = require("test_common")
local test_coroutine = require("test_coroutine")

test1.print()
local func = test_common.local_var()
print("i=" .. func() )
print("i=" .. func() )

local func1 = test_common.local_var()
print("func1=" .. func1() )
print("func1=" .. func1() )

--test_common.show_error()
--test_common.show_assert()
--test_common.show_pcall()


test_coroutine.begin_test()
