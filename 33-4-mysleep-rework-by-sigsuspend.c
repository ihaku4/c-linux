unsigned int mysleep(unsigned int nsecs)
{
  /* init new & save old: handler, mask */
    /* block SIGALRM, save old signal mask */
  /* alarm */
  /* sigsuspend */
  /* reset: alarm, sigaction, sigprocmask */
    
  // handler: sigaction(struct), sigaction(function)
  // mask:    sigset_t(struct), sigprocmask(function); sigemptyset, sigaddset, sigdelset
}
