rootpath = "sdmc:/script/"

logpath = "sdmc:/test.log"

package.path = rootpath .. "?.lua;" .. package.path

SetupLog(logpath)

dofile(rootpath .. "main.lua")