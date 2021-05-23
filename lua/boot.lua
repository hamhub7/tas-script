rootpath = "sdmc:/script/" --DO NOT EDIT THIS LINE

logpath = rootpath .. "tas-script.log" --Edit this to change the log file's name and/or directory

SetupLog(logpath) --DO NOT EDIT THIS LINE

package.path = rootpath .. "?.lua;" .. package.path --DO NOT EDIT THIS LINE

dofile(rootpath .. "main.lua") --Edit this to change which file is executed after bootup