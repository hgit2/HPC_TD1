####################################" faible ##############################################

# faible matprod 
faible_prod <- read.table("faible_matprod.txt", header = TRUE, sep="\t", dec=",")
plot( faible_prod$nb_coeurs, faible_prod$moy, type = "b", col="darkcyan")

# faible sum2mat
faible_sum2 <- read.table("faible_addmat.txt", header = TRUE, sep="\t")
faible_sum2 <- na.omit(faible_sum2) # supprime les lignes avec des NA
plot( faible_sum2$nb_coeurs, faible_sum2$moy)

# faible summat
faible_sum <- read.table("faible_summat.txt", header = TRUE, sep="\t")
faible_sum <- na.omit(faible_sum)
plot( faible_sum$nb_coeurs, faible_sum$moy)

### plot des trois fonctions
plot( faible_sum2$nb_coeurs, faible_sum2$moy, type = "b", pch=4, col="darkorange1", main = "Temps d'exécution en fonction du nombre de coeurs pour un passage à l'échelle faible (matrices)", xlab="Nombre de coeurs", ylab="Temps d'exécution moyen")
points( faible_prod$nb_coeurs, faible_prod$moy, type = "b", col="brown", pch=17)
points( faible_sum$nb_coeurs, faible_sum$moy, type = "b", col="darkcyan", pch=19)
legend("topleft", c("Addition de 2 matrices", "Produit d'une matrice par un double","Somme des éléments d'une matrice"), col=c("darkorange1","brown", "darkcyan"), lty=c(1,1,1), pch=c(4,17,19))

############################ fort ################################################

#### fort prod (recupération des moyennes pour chaque taille)
fort_prod <- read.table("fort_matprod.txt", header = TRUE, sep="\t")
#plot prod pour les différentes tailles
fort_prod_t1 <- fort_prod[fort_prod$taille_vecteur==50,]
fort_prod_t2 <- fort_prod[fort_prod$taille_vecteur==500,]
fort_prod_t3 <- fort_prod[fort_prod$taille_vecteur==5000,]
plot( fort_prod_t3$nb_coeurs, fort_prod_t3$moy, type = "b", pch=15, col="darkgoldenrod4", main = "Temps d'exécution en fonction du nombre de coeurs pour un passage à l'échelle forte (Produit d'une matrice par un double)", xlab="Nombre de coeurs", ylab="Temps d'exécution moyen", ylim=c(2,350))
points( fort_prod_t2$nb_coeurs, fort_prod_t2$moy, type = "b", col="darkgreen", pch=15)
points( fort_prod_t1$nb_coeurs, fort_prod_t1$moy, type = "b", col="darkred", pch=15)
legend("topleft", c(expression(paste("Taille=", 10^8)), expression(paste("Taille=", 10^7)),expression(paste("Taille=", 10^6))), col=c("darkgoldenrod4", "darkgreen", "darkred"), lty=c(1,1,1), pch=c(15,15,15))


#### fort sum2 (recupération des moyennes pour chaque taille)
fort_sum2 <- read.table("fort_addmat.txt", header = TRUE, sep="\t")
fort_sum2_t1 <- fort_sum2[fort_sum2$taille_vecteur==50,]
fort_sum2_t2 <- fort_sum2[fort_sum2$taille_vecteur==500,]
fort_sum2_t3 <- fort_sum2[fort_sum2$taille_vecteur==5000,]

#plot
plot( fort_sum2_t3$nb_coeur, fort_sum2_t3$moy, type = "b", pch=7, col="darkgoldenrod4", main = "Temps d'exécution en fonction du nombre de coeurs pour un passage à l'échelle forte (Addition de 2 matrices)", xlab="Nombre de coeurs", ylab="Temps d'exécution moyen", ylim = c(0,400))
points( fort_sum2_t2$nb_coeur, fort_sum2_t2$moy, type = "b", col="darkgreen", pch=7)
points( fort_sum2_t1$nb_coeur, fort_sum2_t1$moy, type = "b", col="darkred", pch=7)
legend("topleft", c(expression(paste("Taille=", 10^8)), expression(paste("Taille=", 10^7)),expression(paste("Taille=", 10^6))), col=c("darkgoldenrod4", "darkgreen", "darkred"), lty=c(1,1,1), pch=c(7,7,7))


#### fort sum (recupération des moyennes pour chaque taille)
fort_sum <- read.table("fort_summat.txt", header = TRUE, sep="\t")
fort_sum_t1 <- fort_sum[fort_sum$taille_vecteur==50,]
fort_sum_t2 <- fort_sum[fort_sum$taille_vecteur==500,]
fort_sum_t3 <- fort_sum[fort_sum$taille_vecteur==5000,]

#plot
plot( fort_sum_t3$nb_coeurs, fort_sum_t3$moy, type = "b", pch=12, col="darkgoldenrod4", main = "Temps d'exécution en fonction du nombre de coeurs pour un passage à l'échelle forte (Somme des éléments d'une matrice)", xlab="Nombre de coeurs", ylab="Temps d'exécution moyen", ylim=c(0,100))
points( fort_sum_t2$nb_coeurs, fort_sum_t2$moy, type = "b", col="darkgreen", pch=12)
points( fort_sum_t1$nb_coeurs, fort_sum_t1$moy, type = "b", col="darkred", pch=12)
legend("topleft", c(expression(paste("Taille=", 10^8)), expression(paste("Taille=", 10^7)),expression(paste("Taille=", 10^6))), col=c("darkgoldenrod4", "darkgreen", "darkred"), lty=c(1,1,1), pch=c(12,12,12))


## Plot t1 (taille =10^6) pour les trois fonctions
plot( fort_prod_t1$nb_coeurs, fort_prod_t1$moy, type = "b", col="brown", pch=17,main = expression(paste("Temps d'exécution en fonction du nombre de coeurs pour un passage à l'échelle forte (taille=",50,") : matrices")), xlab="Nombre de coeurs", ylab="Temps d'exécution moyen", xlim=c(1,4), ylim=c(0,6))
points( fort_sum_t1$nb_coeurs, fort_sum_t1$moy, type = "b", col="darkcyan", pch=19)
points( fort_sum2_t1$nb_coeur, fort_sum2_t1$moy, type = "b", col="darkorange1", pch=4)
legend("topleft", c("Produit d'une matrice par un double","Somme des éléments d'une matrice", "Addition de 2 matrices"), col=c("brown", "darkcyan", "darkorange1"), lty=c(1,1,1), pch=c(17,19,4))

## Plot t2 (taille=10^7) pour les trois fonctions
plot( fort_prod_t2$nb_coeurs, fort_prod_t2$moy, type = "b", col="brown", pch=17,main = expression(paste("Temps d'exécution en fonction du nombre de coeurs pour un passage à l'échelle forte (taille=",500,") : matrices")), xlab="Nombre de coeurs", ylab="Temps d'exécution moyen", xlim=c(1,4), ylim=c(0,4))
points( fort_sum_t2$nb_coeurs, fort_sum_t2$moy, type = "b", col="darkcyan", pch=19)
points( fort_sum2_t2$nb_coeur, fort_sum2_t2$moy, type = "b", col="darkorange1", pch=4)
legend("topleft", c("Produit d'une matrice par un double","Somme des éléments d'une matrices", "Addition de 2 matrices"), col=c("brown", "darkcyan", "darkorange1"), lty=c(1,1,1), pch=c(17,19,4))

## Plot t3 (taille=10^8) pour les trois fonctions
plot( fort_prod_t3$nb_coeurs, fort_prod_t3$moy, type = "b", col="brown", pch=17,main = expression(paste("Temps d'exécution en fonction du nombre de coeurs pour un passage à l'échelle forte (taille=",5000,") : matrices")), xlab="Nombre de coeurs", ylab="Temps d'exécution moyen", xlim=c(1,4), ylim=c(50,350))
points( fort_sum_t3$nb_coeurs, fort_sum_t3$moy, type = "b", col="darkcyan", pch=19)
points( fort_sum2_t3$nb_coeur, fort_sum2_t3$moy, type = "b", col="darkorange1", pch=4)
legend("topleft", c("Produit d'une matrice par un double","Somme des éléments d'une matrice", "Addition de 2 matrices"), col=c("brown", "darkcyan", "darkorange1"), lty=c(1,1,1), pch=c(17,19,4))
