--Lua script to save time/ value pair to MySQL server
require "luasql.mysql"

local current_time=os.date("%Y-%m-%d %H:%M:%S")
env = assert (luasql.mysql())
con = assert (env:connect('aquarium', 'root', 'ja175524', '192.168.0.5'))
res = assert (con:execute('INSERT INTO config(Timestamp,Temp,Salinity,PH) VALUES("'..current_time..'",'..temp..'",'..sal..'",'..ph..')'))
