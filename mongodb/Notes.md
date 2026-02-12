# getting started
each database needs a mock server to try things out
127.0.0.1 default local host
mongodb protocol tcp/ip

mongo uses bson
robo3t
27017 port number for mongo

# mongo setup 

download mongo commuinty server the desired version of your os

for ubuntu
download mongodb-org-server_8.2.3_amd64.debP
sudo dpkg -i  mongodb-org-server_8.2.3_amd64.deb	//installs the pkg
sudo systemctl status mongod.service //tells you the current service which
              you will find inactive
sudo systemctl start mongod.serivce //starts mongo server

download monosh client
sudo dpkg -i mongodb-mongosh_2.6.0_amd64.deb 
mongosh
will run the mongo shell

show dbs;     //shows you the current data bases
use mydb;       //creates a db
//if you type show dbs you will not see your created db because it is empty

# side notes
remember that by default the _id is projected , if you dont want the _id you will have to specifiecly say _id:0