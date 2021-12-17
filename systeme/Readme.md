
# Compiler le mini shell

```
gcc --std=c99 -Wall -Wextra -Werror -o minishell ./minishell.c
```

# 6 Exécuter un programme

### Expliquez le fonctionnement de fork() vu en cours, ce nouveau processus s'exécute t'il immédiatement ?
à l'appel de fork, on duplique le contexte d'execution actuel dans un nouveau processus. Il s'exécute immédiatement.

### Quels sont les éléments communs au père et au fils?
le contexte au moment de l'appel fork()

### Quels sont les éléments conservés du processus après un appel à exec ?

## 6.1 Utilisation de la redirection >

### Expliquez le fonctionnement de cet appel système "dup2 ( fd , STDOUT_FILENO) ;"

### Compiler le garbage collector

```
gcc -Wall -Werror --std=c99 -Wno-unused-parameters tinygc.c -o tinygc
```