# red hat day 3 #

# permisions and acces for files and Dir4

permission      file        dir

read        display/cp      ls
write       modify content  with excute you have add and delete and rename
Execute     execute file    cd and ls-l


# Commands

    >chmod              //change permission filename
        u:owner g:group  o:other a:all
        +: add permision -: remove permision =:Assign permissions 
        r:read  w:write x:execute
                        <Example> chmod u+x,go+r file1
        OCTAL mode
            r = 4
            w = 2
            x = 1
                        <Example> chmod 760
    >umask             //default permisions that i dont want
        umask only affect the user using it not other users

    >vi                 //file editor
    u:              undo
    ctrl+r          redo
    i               inserts mode
    esc             command mode
    o opens         new blank line
    a apends        text after the cursor
    shift+a         append at the end of the line
    shift+i         insert text at the beginig of the line
    shift+O         opens a new line above the cursor
    h:              left
    l:              right
    j:              down
    k:              up
    w:              forward one word
    b:              back one word
    e:              to the end of the current word
    0:              to the begining of the line
    esc+:           last line mode
        :w          save
        :wq         save and quit
        :q          quit
        :q!         force quit without saving
        :n          goes to line N
    ctrl+F      pages forward one screen
    ctrl+B      pages back one screen
    setnu       numbers the lines
    set ic      ignore case sensitivty
    set showmode  shows mode
        
                >vi -i   read only
    >enviorment variables           
            the enviorment variables start with a $
                <Examples>
                        $HOME           //home dir 
                        $PWD   
        man bash to get all env vars
        /somthing                   //to search in the man 
                    /<something>\b
        PATH=$PATH:/whatever dir you want
    >ALIAS  // another name for a comand
             <EXample> alias c=clear</Example>
            unalias your alias
    >/etc/profile
        profile for all user
        .profile or .bash_profile  the profile file of the user
    .bashrc     runs every time a shell i opened
    
                

# FAQ
            by default the files doesnt have excutable permision
            vi is the only editor that works if the system crashes
