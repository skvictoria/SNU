//--------------------------------------------------------------------------------------------------
// System Programming                         Shell Lab                                    Fall 2020
//
/// @author <Seulgi Kim>
/// @studid <2016-13692>
//--------------------------------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>
#include <signal.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>

/* Misc manifest constants */
#define MAXLINE    1024   /* max line size */
#define MAXPIPES      8   /* max MAXPIPES */
#define MAXARGS     128   /* max args on a command line */
#define MAXJOBS      16   /* max jobs at any point in time */
#define MAXJID    1<<16   /* max job ID */

/* Job states */
#define UNDEF 0 /* undefined */
#define FG 1    /* running in foreground */
#define BG 2    /* running in background */
#define ST 3    /* stopped */
#define ERROR_ -1

/*
 * Jobs states: FG (foreground), BG (background), ST (stopped)
 * Job state transitions and enabling actions:
 *     FG -> ST  : ctrl-z
 *     ST -> FG  : fg command
 *     ST -> BG  : bg command
 *     BG -> FG  : fg command
 * At most 1 job can be in the FG state.
 */

/* Global variables */
extern char **environ;      /* defined in libc */
char prompt[] = "tsh> ";    /* command line prompt (DO NOT CHANGE) */
int verbose = 0;            /* if true, print additional output */
int nextjid = 1;            /* next job ID to allocate */
char sbuf[MAXLINE];         /* for composing sprintf messages */

struct job_t {              /* The job struct */
  pid_t pid;              /* job PID */
  int jid;                /* job ID [1, 2, ...] */
  int state;              /* UNDEF, BG, FG, or ST */
  char cmdline[MAXLINE];  /* command line */
};
struct job_t jobs[MAXJOBS]; /* The job list */
/* End global variables */


/* Function prototypes */

/*----------------------------------------------------------------------------
 * Functions that you will implement
 */

void eval(char *cmdline);
int builtin_cmd(char *(*argv)[MAXARGS]  );
void do_bgfg(char *(*argv)[MAXARGS]  );
void waitfg(pid_t pid);

void sigchld_handler(int sig);
void sigint_handler(int sig);
void sigtstp_handler(int sig);

/*----------------------------------------------------------------------------*/

/* These functions are already implemented for your convenience */
int parseline(const char *cmdline, char *(*argv)[MAXARGS],  int* pipec);
void sigquit_handler(int sig);

void clearjob(struct job_t *job);
void initjobs(struct job_t *jobs);
int maxjid(struct job_t *jobs);
int addjob(struct job_t *jobs, pid_t pid, int state, char *cmdline);
int deletejob(struct job_t *jobs, pid_t pid);
pid_t fgpid(struct job_t *jobs);
struct job_t *getjobpid(struct job_t *jobs, pid_t pid);
struct job_t *getjobjid(struct job_t *jobs, int jid);
int pid2jid(pid_t pid);
void listjobs(struct job_t *jobs);

void usage(void);
void unix_error(char *msg);
void app_error(char *msg);
typedef void handler_t(int);
handler_t *Signal(int signum, handler_t *handler);

int redirect_in_koo(char **cmd); 
int redirect_out_koo(char **cmd); 


/*
 * main - The shell's main routine
 */
int main(int argc, char **argv)
{
  char c;
  char cmdline[MAXLINE];
  int emit_prompt = 1; /* emit prompt (default) */

  /* Redirect stderr to stdout (so that driver will get all output
   * on the pipe connected to stdout) */
  // Redirect stderr(2) outputs to stdout(1)
  dup2(1, 2);

  /* Parse the command line */
  while ((c = getopt(argc, argv, "hvp")) != EOF) {
    switch (c) {
      case 'h':             /* print help message */
        usage();
        break;
      case 'v':             /* emit additional diagnostic info */
        verbose = 1;
        break;
      case 'p':             /* don't print a prompt */
        emit_prompt = 0;  /* handy for automatic testing */
        break;
      default:
        usage();
    }
  }

  /* Install the signal handlers */

  /* These are the ones you will need to implement */
  Signal(SIGINT,  sigint_handler);   /* ctrl-c */
  Signal(SIGTSTP, sigtstp_handler);  /* ctrl-z */
  Signal(SIGCHLD, sigchld_handler);  /* Terminated or stopped child */

  /* This one provides a clean way to kill the shell */
  Signal(SIGQUIT, sigquit_handler);

  /* Initialize the job list */
  initjobs(jobs);

  /* Execute the shell's read/eval loop */
  while (1) {

    /* Read command line */
    if (emit_prompt) {
      printf("%s", prompt);
      fflush(stdout);
    }
    if ((fgets(cmdline, MAXLINE, stdin) == NULL) && ferror(stdin))
      app_error("fgets error");
    if (feof(stdin)) { /* End of file (ctrl-d) */
      fflush(stdout);
      exit(0);//shell terminates
    }
    //call eval
    eval(cmdline);
    
    fflush(stdout);
    fflush(stdout);
  }

  exit(0); /* control never reaches here */
}


/*
 * eval - Evaluate the command line that the user has just typed in
 *
 * If the user has requested a built-in command (quit, jobs, bg or fg)
 * then execute it immediately. Otherwise, fork a child process and
 * run the job in the context of the child. If the job is running in
 * the foreground, wait for it to terminate and then return.  Note:
 * each child process must have a unique process group ID so that our
 * background children don't receive SIGINT (SIGTSTP) from the kernel
 * when we type ctrl-c (ctrl-z) at the keyboard.
 * When there is redirection(>), it return file name to char** file
 */

void eval(char *cmdline)
{
  char *argv[MAXPIPES][MAXARGS];
  //char buf[MAXLINE];
  int background;
  sigset_t set; //sets of signals
  int pipec;

  //make argv vector
  background = parseline(cmdline, argv, &pipec);
  pid_t pid[pipec];
  int fileds[pipec][2];
  //if first argv is null, execute nothing
  if(argv[0][0] == 0x00) return;

  if(builtin_cmd(&(argv[0]))) return;

  int ri, rj, flag=0, rfd, oldstdo;
  for(ri=0;ri<pipec; ri++){
    for(rj=0; argv[ri][rj]!=NULL; rj++){
      if(!strcmp(argv[ri][rj], ">")){
        //ri = i;
        flag = 1;
        break;
      }
    }
    if(flag) break;
  }

  if(flag){
    if(!argv[ri][rj+1]) return;
    else{
      if((rfd = open(argv[ri][rj+1], O_CREAT|O_TRUNC|O_WRONLY, 0644)) < 0) {
        perror("cannot open redirect file");
        return;
      }
      oldstdo = dup(1);
      dup2(rfd, 1);
      close(rfd);
    }
    argv[ri][rj] = 0x00;
  }

  for(int i=0;i<(pipec-1);i++){
    if(pipe(fileds[i])<0) perror("cannot make pipe");
  }

  for(int i = 0; i < pipec; i++) {
    //check if it is built-in command
    //if it's not, fork child process
    //block SIGCHLD handler
    if(sigemptyset(&set)!=0) perror("signal set not empty");
    if(sigaddset(&set, SIGCHLD) != 0) perror("SIGCHLD hasn't added");
    if(sigaddset(&set, SIGINT) != 0) perror("cannot add SIGINT");
    if(sigaddset(&set, SIGTSTP) != 0) perror("cannot add sigtstp");
    if(sigprocmask(SIG_BLOCK, &set, NULL) !=0) perror("cannot block SIGCHLD");

    if((pid[i]=fork()) == 0){
      //unblock SIGCHLD handler
      if(sigprocmask(SIG_UNBLOCK, &set, NULL)!=0) perror("cannot unblock SIGCHLD");
      //if SIGINT, SIGTSTP, use different process group id from shell
      //so that background child process do not receive the signal
      //alter pgid using its own pid
      if(setpgid(0,0)<0) perror("cannot alter current process's pgid to its own pid");
      //run the job in the context of the child

      if(flag == 1 && pipec == 1) {
        for(int j = 0; j < (pipec-1); j++) {
          close(fileds[j][0]);
          close(fileds[j][1]);
        }
      }
      if(pipec > 1) {
        if(i == 0) {
          dup2(fileds[i][1], STDOUT_FILENO);// make output
        }
        else if(i == pipec-1) {
          dup2(fileds[i-1][0], STDIN_FILENO);//get input
        }
        else {
          dup2(fileds[i-1][0], STDIN_FILENO);
          dup2(fileds[i][1], STDOUT_FILENO);
        }
        for(int j = 0; j < (pipec-1); j++) {
          close(fileds[j][0]);
          close(fileds[j][1]);
        }
      }
      if(execvp(argv[i][0], &(argv[i][0]))<0){
        printf("%s: Command not found\n", *argv[i]);
        //child process terminates
        exit(0);
      }
    }
    else if(pid[i]<0) perror("cannot fork");
  }
  // Parent close all pipes
  for(int i=0; i<(pipec-1); i++){
    close(fileds[i][0]);
    close(fileds[i][1]);
  }
  for (int i=0;i<pipec;i++){
    if(background){
      //add current process to job list
      addjob(jobs, pid[i], BG, *argv[i]);//pid[pipec-1]
    }
    else{//background
      //add current process to job list
      addjob(jobs, pid[i], FG, *argv[i]);//pid[pipec-1]
    }
    //unblock SIGCHLD handler
    if(sigprocmask(SIG_UNBLOCK, &set, NULL)!=0)
      perror("cannot unblock SIGCHLD");
  }

  if(flag == 1) {
    dup2(oldstdo, 1);
  }
  //parent waits for foreground job to terminate
  if(!background){
    //wait while pid[pipec-1] is no longer foreground process
    waitfg(pid[pipec-1]);
  }
  else{
    printf("[%d] (%d) %s", pid2jid(pid[pipec-1]),pid[pipec-1], cmdline);//*argv[i]
  }
}

/*
 * parseline - Parse the command line and build the argv array.
 *
 * Characters enclosed in single quotes are treated as a single
 * argument.  Return true if the user has requested a BG job, false if
 * the user has requested a FG job.
 * argv[MAXPIPES][MAXARGS]
*/


int parseline(const char *cmdline, char *(*argv)[MAXARGS] , int *rpipec)
{
  static char array[MAXLINE]; /* holds local copy of command line */
  char* buf = array;          /* ptr that traverses command line */
  char* delim;                /* points to first space delimiter */
  char* pdelim;               /* points to pipe */
  int argc;                   /* number of args */
  int bg=0;                   /* background job? */
  int pipec;

  strcpy(buf, cmdline);
  buf[strlen(buf)-1] = ' ';  /* replace trailing '\n' with space */

  argc = 0;// How many argv
  pipec = 0;

  // ignore leading spaces
  while (*buf && (*buf == ' ')) buf++;

  if (*buf == '\'') {
    buf++;
    delim = strchr(buf, '\'');//if buf has '\', delim = '\'
  } else {
    delim = strchr(buf, ' ');
  }

  while (delim) {
    argv[pipec ][ argc++] = buf;
    *delim = '\0';
    buf = delim + 1;

    // ignore spaces
    while (*buf && (*buf == ' ')) buf++;

    if (*buf) pdelim = strchr(buf, '|');

    // if there is pipe right on buf pointer
    if (*buf && pdelim  && *buf == *pdelim) {
      pipec++;
      argc=0;
      buf = buf + 1;

      // ignore spaces
      while (*buf && ( *buf == ' ')) buf++;
    }

    if (*buf == '\'') {
      buf++;
      delim = strchr(buf, '\'');
    } else {
      delim = strchr(buf, ' ');
    }
  }
  argv[pipec][ argc] = NULL;
  pipec++;
  *rpipec = pipec;// change pipec value for eval()

  // ignore blank line
  if (argc == 0) return 1;

  // should the job run in the background?
 if ((bg = (strcmp(argv[pipec-1][argc-1] , "&") == 0)) != 0) {
    argv[pipec-1][--argc] = NULL; 
  }
  return bg;
}

/*
 * builtin_cmd - If the user has typed a built-in command then execute
 *    it immediately.
 */
int builtin_cmd(char *(*argv)[MAXARGS] )
{
  //quit
  //printf("%c, %c", *argv[0][0], *argv[0][1]);
  if(!strcmp(*argv[0], "quit")) exit(0);
  else if(!strcmp(*argv[0], "&")) return 1;
  //bg -> call do_bgfg()
  else if(!strcmp(*argv[0], "bg") || !strcmp(*argv[0], "fg")){
    do_bgfg(argv);
    return 1;
  }
  else if(!strcmp(*argv[0], "jobs")){
    //print all jobs
    listjobs(jobs);
    return 1;
  }
  //if normally execute return 1, else return 0
  return 0;
}

/*
 * do_bgfg - Execute the builtin bg and fg commands
 */
void do_bgfg(char *(*argv)[MAXARGS] )
{

  //if wrong arg -> error message
  //error case 1 : argv[1]==null
  //error case 2 : % but no job
  //error case 3 : 2- but cannot find pid at job list
  //error case 4 : doesn't start with % or 2-
  pid_t jid, pid;
  struct job_t *job;
  int flag;
  if(argv[0][1]==NULL){
    printf("%s command requires PID or %%jobid argument\n", *argv[0]);
    return;
  }
  if(!strcmp(*argv[0], "bg")) flag = 0;
  else flag = 1;

  //check atoi(argv[1]) to exclude jid, pid
  if(argv[0][1][0]=='%'){
    char *p = &(argv[0][1][1]);
    jid = atoi(p);
    job = getjobjid(jobs, jid);
    if(job==NULL){
      printf("%s: No such job\n", argv[0][1]);
      return;
    }
  }
  else if(isdigit(&(argv[0][1][0]))){
    pid = atoi(&(argv[0][1][1]));
    job = getjobpid(jobs, pid);
    if(job==NULL){
      printf("(%d): No such process\n", pid);
    }
  }
  else{
    printf("%s: argument must be a PID or %%jobid\n", flag? "fg": "bg");
    return;
  }
  kill(-(job->pid), SIGCONT);
  if(flag){
    job->state =FG;
    waitfg(job->pid);
  }
  else{
    job->state = BG;
    printf("[%d](%d) %s", job->jid, job->pid, job->cmdline);
  }
}

/*
 * waitfg - Block until process pid is no longer the foreground process
 */
void waitfg(pid_t pid)
{
  struct job_t *j = getjobpid(jobs, pid);
  //char buf[MAXLINE];
  //SIGCHLD TODO
  //while(waitpid>0) -> if many child process terminate?TODO

  //if foregroudn job has already completed and reaped by handler -> return
  //TODO
  
  while(j->pid==pid && j-> state==FG) sleep(1);
  if(verbose){
    printf("waitfg : Process (%d) no longer the fg process \n", pid);
    //memset to buf
    //sprintf to buf
  }
  return;
}


/*****************
 * Signal handlers
 *****************/

/*
 * sigchld_handler - The kernel sends a SIGCHLD to the shell whenever
 *     a child job terminates (becomes a zombie), or stops because it
 *     received a SIGSTOP or SIGTSTP signal. The handler reaps all
 *     available zombie children, but doesn't wait for any other
 *     currently running children to terminate.
 */

void sigchld_handler(int sig)
{
  int status;
  pid_t pid;

  //wait child process terminate
  //return terminated process id
  while((pid = waitpid(-1, &status, WNOHANG|WUNTRACED))>0){
    //find the jobs by pid in joblist
    struct job_t *j = getjobpid(jobs, pid);
    //if child process terminated by signal
    if(WIFSIGNALED(status)!=0){//if child process exit
      fprintf(stdout, "Job [%d] (%d) terminated by signal %d\n", pid2jid(pid), pid
          ,WTERMSIG(status));
      //delete job from joblist
      deletejob(jobs, pid);
    }
    //if child has stopped
    else if(WIFSTOPPED(status)){
      //change job state
      j->state = ST;
      fprintf(stdout, "Job [%d] (%d) stopped by signal %d\n", pid2jid(pid), pid, WSTOPSIG(status));
    }
    //if process terminates normally,
    else if(WIFEXITED(status)){
      //delete that process so that not making zombie
      deletejob(jobs, pid);
    }
  }
  return;
}

/*
 * sigint_handler - The kernel sends a SIGINT to the shell whenver the
 *    user types ctrl-c at the keyboard.  Catch it and send it along
 *    to the foreground job.
 */

void sigint_handler(int sig)
{
  pid_t pid;
  //return pid number of current foreground
  pid = fgpid(jobs);
  if(verbose) printf("sigint_handler : entering\n");
  if(pid>0){
    kill(-pid, SIGINT);//send sigint to every process within the process group
    if(verbose) printf("sigint handler : Job (%d) killed\n", pid);
  }
  if(verbose) printf("sigint_handler: exiting\n");
  return;
}

/*
 * sigtstp_handler - The kernel sends a SIGTSTP to the shell whenever
 *     the user types ctrl-z at the keyboard. Catch it and suspend the
 *     foreground job by sending it a SIGTSTP.
 */
//
void sigtstp_handler(int sig)
{
  //deletejob
  pid_t pid;
  pid = fgpid(jobs);//current process value
  if(verbose) printf("sigtstp_hanlder: entering\n");
  if(pid>0){
    kill(-pid, SIGTSTP);//send sigtstp to itself
    if(verbose) printf("sigtstp_hanlder: Job[%d] (%d) stopped\n", pid2jid(pid), pid);
  }
  if(verbose) printf("sigtstp_handler: exiting\n");
  return;
}

/*********************
 * End signal handlers
 *********************/

/***********************************************
 * Helper routines that manipulate the job list
 **********************************************/

/* clearjob - Clear the entries in a job struct */
void clearjob(struct job_t *job) {
  job->pid = 0;
  job->jid = 0;
  job->state = UNDEF;
  job->cmdline[0] = '\0';
}

/* initjobs - Initialize the job list */
void initjobs(struct job_t *jobs) {
  int i;

  for (i = 0; i < MAXJOBS; i++)
    clearjob(&jobs[i]);
}

/* maxjid - Returns largest allocated job ID */
int maxjid(struct job_t *jobs)
{
  int i, max=0;

  for (i = 0; i < MAXJOBS; i++)
    if (jobs[i].jid > max)
      max = jobs[i].jid;
  return max;
}

/* addjob - Add a job to the job list */
int addjob(struct job_t *jobs, pid_t pid, int state, char *cmdline)
{
  int i;

  if (pid < 1)
    return 0;

  for (i = 0; i < MAXJOBS; i++) {
    if (jobs[i].pid == 0) {
      jobs[i].pid = pid;
      jobs[i].state = state;
      jobs[i].jid = nextjid++;
      if (nextjid > MAXJOBS)
        nextjid = 1;
      strcpy(jobs[i].cmdline, cmdline);
      if(verbose){
        printf("Added job [%d] %d %s\n", jobs[i].jid, jobs[i].pid, jobs[i].cmdline);
      }
      return 1;
    }
  }
  printf("Tried to create too many jobs\n");
  return 0;
}

/*
  so that background child process do not receive the signal* deletejob - Delete a job whose PID=pid from the job list */
int deletejob(struct job_t *jobs, pid_t pid)
{
  int i;

  if (pid < 1)
    return 0;

  for (i = 0; i < MAXJOBS; i++) {
    if (jobs[i].pid == pid) {
      clearjob(&jobs[i]);
      nextjid = maxjid(jobs)+1;
      return 1;
    }
  }
  return 0;
}

/* fgpid - Return PID of current foreground job, 0 if no such job */
pid_t fgpid(struct job_t *jobs) {
  int i;

  for (i = 0; i < MAXJOBS; i++)
    if (jobs[i].state == FG)
      return jobs[i].pid;
  return 0;
}

/* getjobpid  - Find a job (by PID) on the job list */
struct job_t *getjobpid(struct job_t *jobs, pid_t pid) {
  int i;

  if (pid < 1)
    return NULL;
  for (i = 0; i < MAXJOBS; i++)
    if (jobs[i].pid == pid)
      return &jobs[i];
  return NULL;
}

/* getjobjid  - Find a job (by JID) on the job list */
struct job_t *getjobjid(struct job_t *jobs, int jid)
{
  int i;

  if (jid < 1)
    return NULL;
  for (i = 0; i < MAXJOBS; i++)
    if (jobs[i].jid == jid)
      return &jobs[i];
  return NULL;
}

/* pid2jid - Map process ID to job ID */
int pid2jid(pid_t pid)
{
  int i;

  if (pid < 1)
    return 0;
  for (i = 0; i < MAXJOBS; i++)
    if (jobs[i].pid == pid) {
      return jobs[i].jid;
    }
  return 0;
}

/* listjobs - Print the job list */
void listjobs(struct job_t *jobs)
{
  int i;

  for (i = 0; i < MAXJOBS; i++) {
    if (jobs[i].pid != 0) {
      printf("[%d] (%d) ", jobs[i].jid, jobs[i].pid);
      switch (jobs[i].state) {
        case BG:
          printf("Running ");
          break;
        case FG:
          printf("Foreground ");
          break;
        case ST:
          printf("Stopped ");
          break;
        default:
          printf("listjobs: Internal error: job[%d].state=%d ",
              i, jobs[i].state);
      }
      printf("%s\n", jobs[i].cmdline);
    }
  }
}
/******************************
 * end job list helper routines
 ******************************/


/***********************
 * Other helper routines
 ***********************/

/*
 * usage - print a help message
 */
void usage(void)
{
  printf("Usage: shell [-hvp]\n");
  printf("   -h   print this message\n");
  printf("   -v   print additional diagnostic information\n");
  printf("   -p   do not emit a command prompt\n");
  exit(1);
}

/*
 * unix_error - unix-style error routine
 */
void unix_error(char *msg)
{
  fprintf(stdout, "%s: %s\n", msg, strerror(errno));
  exit(1);
}

/*
 * app_error - application-style error routine
 */
void app_error(char *msg)
{
  fprintf(stdout, "%s\n", msg);
  exit(1);
}

/*
 * Signal - wrapper for the sigaction function
 */
handler_t *Signal(int signum, handler_t *handler)
{
  struct sigaction action, old_action;

  action.sa_handler = handler;
  sigemptyset(&action.sa_mask); /* block sigs of type being handled */
  action.sa_flags = SA_RESTART; /* restart syscalls if possible */

  if (sigaction(signum, &action, &old_action) < 0)
    unix_error("Signal error");
  return (old_action.sa_handler);
}

/*
 * sigquit_handler - The driver program can gracefully terminate the
 *    child shell by sending it a SIGQUIT signal.
 */
void sigquit_handler(int sig)
{
  printf("Terminating after receipt of SIGQUIT signal\n");
  exit(1);
}

/* $end tshref-ans */
