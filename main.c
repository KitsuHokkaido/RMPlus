#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <dirent.h>
#include <unistd.h>

#define BUFFER_SIZE 60
typedef enum 
{
  EXC_FILE,
  EXC_EXTENSION
} exception_type;

int erase_all(const char* exception[], exception_type excep_type, int exception_size);
int get_dir(char* dir, int size);
int get_last_files(char* exception[], const char* args[], int begin, int end);

void print_help(void);


int main(int argc, char* argv[])
{
  if(argc > 1)
  {
    if(strcmp(argv[1],"--help") == 0)
    {
      print_help();
    }
    else if(strcmp(argv[1], "-*f") == 0)
    {
      if(argc > 2 && strcmp(argv[2], "-x") == 0)
      {
        if(argc > 3)
        {
          char* exceptions[20];
          get_last_files(exceptions, argv, 3, argc);
          int remaining = argc - 3;
          
          if(argv[3][0] == '.')
          {
            if(erase_all(exceptions, EXC_EXTENSION, remaining) != 0)
            {
              fprintf(stderr, "Error : %s\n", strerror(errno));
            }
          }
          else 
          {
            if(erase_all(exceptions, EXC_FILE, remaining) != 0)
            {
              fprintf(stderr, "Error : %s\n", strerror(errno));
            }
          }
        }
        else 
        {
          fprintf(stderr, "Error [flag -x] : You must specify a file or an extension\n");
        }
      }
      else 
      {
        char* exception[] = {""};
        if(erase_all(exception, 1, 1) != 0)
        {
          fprintf(stderr, "Error : %s\n", strerror(errno));
        }
      }
    }
    else 
    {
      for(int i = 1; i < argc; i++)
      {
        if(remove(argv[i]) != 0)
        {
          if(errno == ENOTEMPTY)
          {
            char command[20];
            strcpy(command, "rm -r ");
            strcat(command, argv[i]);

            if(system(command) != 0)
            {
              fprintf(stderr, "Error : %s\n", strerror(errno));
              exit(1);
            }
          }
          else 
          {
            fprintf(stderr, "Error : %s\n", strerror(errno));
          }
        }
      }
    }
  }
  else  
  {
    printf("You must specify an argument\nFor help, write : rm+ --help\n");
  }
  return 0;
}

int erase_all(const char* exception[], exception_type excep_type, int exception_size)
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
        if(dir->d_type != DT_DIR)
        {
          int destroyable = 0;
          for(int i = 0; i < exception_size; i++)
          {
            if(excep_type == EXC_FILE)
            {
              if (strcmp(dir->d_name, exception[i]) == 0) 
              {
                destroyable = 1;
                break;
              }
            }
            else if(excep_type == EXC_EXTENSION)
            {
              if(strstr(dir->d_name, exception[i]) != NULL) 
              {
                destroyable = 1;
                break;
              }
            }
          }
          if(destroyable == 0)
          {
            remove(dir->d_name);
          }
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

int get_last_files(char* exception[], const char* args[], int begin, int end)
{
  for (int i = 0; i < (end-begin); i++)
  {
    exception[i] = args[begin+i];
  }
  return 0;
}


void print_help()
{
  puts("Command : rm+ [command] [flag1] [param] [flag2] [param]\n"
       "\n"
       "[command]\n"
       "* : to delete all the files\n"
       "files : specify the name of the files\n"
       "\n"
       "[flags]\n"
       " -x : exception of\n"
       "-s : to delete several files\n"
       "-*f : to delete all the files\n"
       "-*d to delete all the directories\n"
       "-*fd : to delete all the files and directories\n"
       "\n"
       "[param]\n"
       "name : you can specify a filename\n"
       "extension : you can specify a file extension\n"
       "\n"
       "Example:\n"
       "> rm+ -*f -x file1 file2 : delete all the files excepted file1 and file2\n"
       "> rm+ -*f -x .txt : delete all the files excepted the files with extension.txt\n");
}

