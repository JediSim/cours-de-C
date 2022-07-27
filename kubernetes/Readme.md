# Kubernetes

---

## Installation

##### Linux

1. Manjaro :

   - `yay minikube` minikube permet de faire tourner un environnement de développement pour Kubernetes avec un simple Nodes.
   - `yay kubectl` Ca permet de gerer le cluster. C'est pas obligatoire tu peux utiliser `minikube kubectl <le reste de la commande>` mais c'est plus long a écrire.

##### Windows /!\

- installer linux

## Introduction

faut bien lancer la machinerie... `minikube start`

il y a une interface graphique qui peut aider `minikube dashboard`

#### Etape 1 creer un "deployment" et un "service" :

1. creation du deployment :
   `kubectl create deployment <nom du deployment> --image=<image>`

2. creation du service à partir du deployment :
   `kubectl expose deployment <nom du deployment> --type=<type> --port=<port>`
   list de types :
   - LoadBalancer : quand on veut exposer le service en dehors du cluster sur une IP fix
   - NodePort : exposer le service accessible avec <NodeId>:<NodePort>
   - ClusterIP : expose le service sur une IP interne au cluster
   - ExternalName : expose le service sur un nom de domaine externe
