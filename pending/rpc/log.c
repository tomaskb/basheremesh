
#include <stuff.h>
#include <debug.h>

/* Read log file and return the value. */
int read_log (void)
{
  FILE *fp;
  int n;
  
  fp = fopen (LOGFILE, "r");
  
  /* If file does not exist, initialize it. */
  if (!fp)
    {
      fp = fopen (LOGFILE, "w");
      sysfault (!fp, -1);
      fprintf (fp, "%d\n", 0); 
      fclose (fp);
      return 0;
    }	

  sysfault (!fp, -1);
  
  fscanf (fp, "%d", &n);
  
  fclose (fp);
  return n;
  
}

/* Increment the value on the log file. */
int write_log (void)
{
  FILE *fp;
  int n;
  
  n = read_log ();
  sysfault (n<0, -1);
  
  fp = fopen (LOGFILE, "w");
  sysfault (!fp, -1);
  
  n++;
  fprintf (fp, "%d\n", n); 
  
  fclose (fp);

  return n;
}
