each database needs a mock server to try things out
127.0.0.1 default local host
mongodb protocol tcp/ip

mongo uses bson

wild tiger
robo3t
27017 port number for mongo



mongo setup 

download mongo commuinty server the desired version of your os

for ubuntu

sudo dpk -i mongopkg

sudo systemctl status mongod.service      //check the servic status

sudo systemctl start mongod.service       //start service

sudo systemctl killall mongod.service     //kills service


next install mongosh and depackage it
now run the mongodb and run the sh

show dbs;     //shows you the current data bases
use mydb;       //creates a db
//if you type show dbs you will not see your created db because it is empty


remember that by default the _id is projected , if you dont want the _id you will have to specifiecly say _id:0