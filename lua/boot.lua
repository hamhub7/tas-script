rootpath = "sdmc:/script/"

package.path = rootpath .. "?.lua;" .. package.path

dofile(rootpath .. "main.lua")