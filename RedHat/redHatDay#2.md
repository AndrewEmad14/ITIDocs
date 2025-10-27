# red hat day 2#

>bin is for binaries where the user commands resides
>boot is for anything boot related like grub
>/root home dir for the root
>/dev device files, which are special files that provide an interface to hardware devices and system resources
>/etc config files
>/sbin super user command 
>/home dir for the usrs dir
>/temp files that their size change dramatically

# commands
    >metacharacters:
        *  match zero or more character
        ?  match only one character
        [] range of characters !it only matches one character for the range! 
        <Example>
        ls [a-f]*
        ls [a-zA-Z]*
        </Example>
    cp  options source target                                       //copies a files
    mv  moves or renames
    useradd
            -u for id
            -g for groups
            -c for comments
            -md creates home dir
        !Dont Forget the username!
    groupadd
            add group
    usermod
            modify user
            -g assign primary group
            -G assign secondary group    you can add multiple groups in the same line with a "," in between
            -D shows the default
            you can use the combination of -D -s to modify the default
            -l change the login name
            -L lock the password use
            -U unlock the password use
    userdel
            delete user
            -r deleted the user with his home dir
    groupdel
            delete group
    newusers filename
            creates users according to the file
    chage  options username
        -m change min days of passwd change
        -M change Max days of passwd change
    gpasswd 
        changes the group password
    id
        display the user full data
    whoami
        displays the user name
    chgrp
        change the group permissions
    newgrp
        change the user primary group temporary
    su 
        change user
        -c "write commands that the user will execute in double qoutes"
    sudo 
        super user do
    chown user  file/dir
        change owner 
    shutdown 
        safe shutdown
        -h time             //shuts down after an amount of time
        -k now              //kicks the user out of the pc
    poweroff 
        risky shutdown


# /etc/passwd file
    loginname:x:uid:gid:comment:home-directory:login-shell
    <username:password:userId:groupId:comments about the user:home-dir:shell>
# /etc/shadow
    username:encrypted passwd:last
    changed:min:max:warn:inactive:expire:future-use
# /etc/group
    the last field the group members some distros mention the primary group the some mention the secondory group
# /etc/skel 
        creates files that are in the user home dir by default when he is created
# FAQ
3 kinds of permisions read, write ,execute rwx for usr group and others
the first number is for file type (- for file and d for dir)
the other are 9 characters are for the permisions for each the user, group and other
the next are the user and the group owners of the file or dir
next a link

files are written normally
dir at the end you will find a /
executable files ends with *
links ends with @
terminal is case senetive in linux



!a program that calculates the number of days form jan 1 1970 to the current date that runs in linux!
                                    <due to the day before the exam>
!what is inactive in /etc/shadow!
<Inactive : The number of days after password expires that account is disabled.>
%wheel is the default group that has all the root commands


useradd usermod userdel
ALL = (ALL)  ALL


first can run on all hostes
secon is all groups and third is the commnads