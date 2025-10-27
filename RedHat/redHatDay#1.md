# RedHatDay#1 #

recommend watch: >redhat / ubuntu course marhar tech
                 >history of os 
                1970 first operating system

richard soulman

gnu no unix

# LINUX components
>kernel
>shell 
>apps

# Commands Syntax
    command [options] [arguments]
    **each is separted by a space
# Commands    
      "|" : This operator is used to redirect the standard output (stdout) of one command to the standard input (stdin) of another command 
      ">" :  This operator is used to redirect the standard output (stdout) of a command to a file (overwrite)
      ">>" : same as above but it appends
      history: history of all your commands in the session
      " ` ": used with echo to specify that it is a command
      wc : count new line , words and byte
      man : manual
            >option -K    <search globaly in man>
            >option -l    <List>
            >option -a    <get all man pages>

     cd : change dir
            >".." back to the parent
            >"-"  go back to previous dir
            >"~"  means /home/usr of the current logged in user
     ls: list contents 
            >"R" recursive direcotyr list
            >"a" all    
            >"l" long list format  
            >"f" file type
            >"-r" recurseive
            >"*3" all files in dir 3
            >"*" all files except hidden files (.)
            > meta charcters doesnt match hidden files

     pwd : print working directory
     mkdir: make dir
           >any dir that starts with "." hidden
           >-p for creating a dir inside a folder
     cat: displays whats in the files
     more : displays files but with paginagtion one screen at a time
     head: first lines of your files (by default 10)
        >"-n ${whatever number of lines you want}" 
     tail: last lines of your files () 
              -n last n lines
              +n from the line 
     touch: update the access and modifications of times of each files to the current time 
            IF the file doesnt exsist it creates said file
     rmdir: deletes empty dir FOREVER
     rm: deletes files 
        >"r" delete the directory recursevly (files and folders inside are deleted)

     

# File System
    /    :  the root  is the start of the file hirearchy
    /etc :  dir for configurations of the system with restricted access
    /home:  List of the usrs directories
    /tmp :  cache files
    /var :  log, tmp
    /lib :  libariers
    /usr/sbin: link to sbin
    /var :  any varibale like logs and cache
    /proc:  process direcectory
    /opt :  is a directory for installing optional or add-on software packages that are not part of the core operating system

# Path
    Relative : from where i am standing
    absloute : from the root
# FAQ
        Bugezzela
        kickstart: mode permits automated installation ancebel
        you can do this command like this:
        ls -l -a
        OR
        ls -al
        ASLONG AS the option dosent take arguments
        
        each app is treated as a user inorder to give it permisions

what does + do with tail?(Bouns in the lab)


no

7,8,11