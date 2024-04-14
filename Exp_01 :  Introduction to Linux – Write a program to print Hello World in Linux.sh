#To open a file with nano, you simply type ‘nano’ followed by the file’s name. If the file doesn’t exist, nano will create a new one for you. Here’s an example:
nano test.c++

# now we will write the code for our program test.c++

:'int main(){
    cout<<"Hello World";
    return 0;
}'
 # exit nano using Ctrl+X

#now run the file
 g++ test.cpp -o test

# OUTPUT is => Hello World 

