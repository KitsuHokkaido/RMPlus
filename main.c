#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <dirent.h>
#include <unistd.h>

#define BUFFER_SIZE 60

int erase_all(const char* exception);
int get_dir(char* dir, int size);

int main(int argc, char* argv[])
{
  if(argc > 1)
  {
    if(strcmp(argv[1],"--help") == 0)
    {
      printf("Command : rm+ [command] [flag1] [param] [flag2] [param]\n\n[command]\n * : to delete all the files\n files : specify the name of the files\n[flags]\n -x : exception of\n -s : to delete several files\n -*f : to delete all the files\n -*d to delete all the directories\n -*fd : to delete all the files and directories\n[param]\n name : you can specify a filename\n extension : you can specify a file extension\n\nExample:\n > rm+ -*f -x file1 file2 : delete all the files excepted file1 and file2\n > rm+ -*f -x .txt : delete all the files excepted the files with extension.txt\n");
    }
    else if(strcmp(argv[1], "-*f") == 0)
    {
      if(argc > 2 && strcmp(argv[2], "-x") == 0)
      {
        if(argc > 3)
        {        
          if(erase_all(argv[3]) != 0)
          {
            fprintf(stderr, "Error : %s\n", strerror(errno));
          }
        }
        else 
        {
          fprintf(stderr, "Error [flag -x] : You must specify a file or an extension\n");
        }
      }
      else 
      {
        if(erase_all("") != 0)
        {
          fprintf(stderr, "Error : %s\n", strerror(errno));
        }
      }
    }
    else 
    {
      if(remove(argv[1]) != 0)
      {
        fprintf(stderr, "Error : %s\n", strerror(errno));
        exit(1);
      }
    }
  }
  else  
  {
    printf("You must specify an argument\nFor help, write : rm+ --help\n");
  }
  return 0;
}

int erase_all(const char* exception)
{
  struct dirent *dir;
  
  char current_dir[BUFFER_SIZE];
  
  if(get_dir(current_dir, BUFFER_SIZE) == 0)
  {
    DIR*d = opendir(current_dir);
    if(d)
    {
      while((dir = readdir(d)) != NULL)
      {
        if(dir->d_type != DT_DIR && strcmp(dir->d_name, exception) != 0) 
        {
          remove(dir->d_name);
        }
      }
      closedir(d);
    }
  }

  return 0;
}

int get_dir(char* dir, int size)
{
  char buffer[BUFFER_SIZE];
  if ( getcwd( buffer, BUFFER_SIZE ) == NULL ) 
  {
    fprintf( stderr, "Cannot get current working directory path\n" );
    if ( errno == ERANGE )
    {
      fprintf( stderr, "Buffer size is too small.\n" );
    }
    return -1;
  }

  strcpy(dir, buffer);

  return 0;
}
