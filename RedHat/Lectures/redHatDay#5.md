# redhat day5 

# Inode
    linux sees all files as numbers called inodes or index nodes
    inode number is unique per partion meaning , if in differnt partion it may duplilcate
    and thats why we cant make hardlink for files in differnt partions
    if inodes numbers runout you wont be able to add anything on the disk

# Comands
    ls -i                           //gets the file inode number
    soft link(SL)   (shortcut)
        ln -s       [file path] [shortcut path]
            default permissions is 777
            if the file is removed it will output an error no such file or dir
            inaddition it takes a new inode number 
            soft link doesnt increase the number of links
    hard link(HL)
            ln
            hard link works only on files not dir
            it doesnt take a new inode table
            any changes that happen in either is seen in the other
    df -h /
            size of the partition
    locate fileName
            searches for the file inside a database
                                                    **PS: the files must be updated in the db 
                                                    or you wouldnt see it
    updatedb
            updates the db
    find
            searches the live file system 
            -size               
            -iname              //Like -name, but the match is case  insensitive
            -inum n             //File has inode number smaller than, greater than or
                                      exactly n.  
    tar     [archive]   [the file you want to archive] 
            used to archive: tape archive
            -c                  //create   
            -v                  //verbose tells you what the terminal put in the archive
            -f                  //creates tape
            -x                  //extracts
    compress                    //to compress
            -v                  
    uncompress                  //to uncompress
    zcat                        //content of a compressed file
    gzip -v [file name]
    gunzip -v [file name]       //unzip
    bzip2 -v [file name]        //zip
    bunzip                      //unzip
    bzcat                       //view
    zip                         //archive + compress
    unzip                       //uncompress
                                                                //extensions doesnt matter
# FAQ
    any dir you create has 2 links one for itself and one for the "." that represents it
    ".." is also created as the parent dir
    and that is the reason you cant hard link a dir because of the possiblity of recursion
    MEANING: a hard link has all the files in a dir including the . and .. , if you create a
    hard link inside a dir who is the parent ? 

    tar.Z                       means that the file or folder is compressed