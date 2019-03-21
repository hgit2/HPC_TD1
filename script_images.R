####################################" faible ##############################################

# faible prod 
faible_prod <- read.table("faible_prod.txt", header = TRUE, sep="\t", dec=",")
plot( faible_prod$nb.coeurs, faible_prod$moy, type = "b", col="darkcyan")

# faible sum2vect 
faible_sum2 <- read.table("faible_sum2vect.txt", header = TRUE, sep="\t")
faible_sum2 <- na.omit(faible_sum2) # supprime les lignes avec des NA
plot( faible_sum2$nb_coeur, faible_sum2$moy)

# faible sumvect 
faible_sum <- read.table("faible_sumvect.txt", header = TRUE, sep="\t")
faible_sum <- na.omit(faible_sum)
plot( faible_sum$nb.coeurs, faible_sum$moy)

### plot des trois fonctions
plot( faible_sum2$nb_coeur, faible_sum2$moy, type = "b", pch=4, col="darkorange1", main = "Temps d'exécution en fonction du nombre de coeurs pour un passage à l'échelle faible", xlab="Nombre de coeurs", ylab="Temps d'exécution moyen")
points( faible_prod$nb.coeurs, faible_prod$moy, type = "b", col="brown", pch=17)
points( faible_sum$nb.coeurs, faible_sum$moy, type = "b", col="darkcyan", pch=19)
legend("topleft", c("Addition de 2 vecteurs", "Produit d'un vecteur par un double","Somme des éléments d'un vecteur"), col=c("darkorange1","brown", "darkcyan"), lty=c(1,1,1), pch=c(4,17,19))

############################ fort ################################################

#### fort prod (recupération des moyennes pour chaque taille)
fort_prod <- read.table("fort_prod.txt", header = TRUE, sep="\t")
fort_prod_t1 <- fort_prod[fort_prod$taille.vecteur==1000000,]
fort_prod_t1 <- na.omit(fort_prod_t1)
fort_prod_t2 <- fort_prod[fort_prod$taille.vecteur==10000000,]
fort_prod_t2 <- na.omit(fort_prod_t2)
fort_prod_t3 <- fort_prod[fort_prod$taille.vecteur==100000000,]
fort_prod_t3 <- na.omit(fort_prod_t3)
#plot prod pour les différentes tailles
plot( fort_prod_t3$nb.coeurs, fort_prod_t3$moy, type = "b", pch=15, col="darkgoldenrod4", main = "Temps d'exécution en fonction du nombre de coeurs pour un passage à l'échelle forte (Produit dun vecteur par un double)", xlab="Nombre de coeurs", ylab="Temps d'exécution moyen", ylim=c(2,600))
points( fort_prod_t2$nb.coeurs, fort_prod_t2$moy, type = "b", col="darkgreen", pch=15)
points( fort_prod_t1$nb.coeurs, fort_prod_t1$moy, type = "b", col="darkred", pch=15)
legend("topleft", c(expression(paste("Taille=", 10^8)), expression(paste("Taille=", 10^7)),expression(paste("Taille=", 10^6))), col=c("darkgoldenrod4", "darkgreen", "darkred"), lty=c(1,1,1), pch=c(15,15,15))


#### fort sum2 (recupération des moyennes pour chaque taille)
fort_sum2 <- read.table("fort_sum2vect.txt", header = TRUE, sep="\t")
fort_sum2_t1 <- fort_sum2[fort_sum2$taille.vecteur==1000000,]
fort_sum2_t1 <- na.omit(fort_sum2_t1)
fort_sum2_t2 <- fort_sum2[fort_sum2$taille.vecteur==10000000,]
fort_sum2_t2 <- na.omit(fort_sum2_t2)
fort_sum2_t3 <- fort_sum2[fort_sum2$taille.vecteur==100000000,]
fort_sum2_t3 <- na.omit(fort_sum2_t3)
#plot
plot( fort_sum2_t3$nb_coeur, fort_sum2_t3$moy, type = "b", pch=7, col="darkgoldenrod4", main = "Temps d'exécution en fonction du nombre de coeurs pour un passage à l'échelle forte (Addition de 2 vecteurs)", xlab="Nombre de coeurs", ylab="Temps d'exécution moyen", ylim = c(0,800))
points( fort_sum2_t2$nb_coeur, fort_sum2_t2$moy, type = "b", col="darkgreen", pch=7)
points( fort_sum2_t1$nb_coeur, fort_sum2_t1$moy, type = "b", col="darkred", pch=7)
legend("topleft", c(expression(paste("Taille=", 10^8)), expression(paste("Taille=", 10^7)),expression(paste("Taille=", 10^6))), col=c("darkgoldenrod4", "darkgreen", "darkred"), lty=c(1,1,1), pch=c(7,7,7))


#### fort sum (recupération des moyennes pour chaque taille)
fort_sum <- read.table("fort_sumvect.txt", header = TRUE, sep="\t")
fort_sum_t1 <- fort_sum[fort_sum$taille.vecteur==1000000,]
fort_sum_t1 <- na.omit(fort_sum_t1)
fort_sum_t2 <- fort_sum[fort_sum$taille.vecteur==10000000,]
fort_sum_t2 <- na.omit(fort_sum_t2)
fort_sum_t3 <- fort_sum[fort_sum$taille.vecteur==100000000,]
fort_sum_t3 <- na.omit(fort_sum_t3)
#plot
plot( fort_sum_t3$nb.coeurs, fort_sum_t3$moy, type = "b", pch=12, col="darkgoldenrod4", main = "Temps d'exécution en fonction du nombre de coeurs pour un passage à l'échelle forte (Somme des éléments d'un vecteur)", xlab="Nombre de coeurs", ylab="Temps d'exécution moyen", ylim=c(2,300))
points( fort_sum_t2$nb.coeurs, fort_sum_t2$moy, type = "b", col="darkgreen", pch=12)
points( fort_sum_t1$nb.coeurs, fort_sum_t1$moy, type = "b", col="darkred", pch=12)
legend("topleft", c(expression(paste("Taille=", 10^8)), expression(paste("Taille=", 10^7)),expression(paste("Taille=", 10^6))), col=c("darkgoldenrod4", "darkgreen", "darkred"), lty=c(1,1,1), pch=c(12,12,12))


## Plot t1 (taille =10^6) pour les trois fonctions
plot( fort_prod_t1$nb.coeurs, fort_prod_t1$moy, type = "b", col="brown", pch=17,main = expression(paste("Temps d'exécution en fonction du nombre de coeurs pour un passage à l'échelle forte (taille=",10^6,")")), xlab="Nombre de coeurs", ylab="Temps d'exécution moyen", xlim=c(1,4), ylim=c(1,9))
points( fort_sum_t1$nb.coeurs, fort_sum_t1$moy, type = "b", col="darkcyan", pch=19)
points( fort_sum2_t1$nb_coeur, fort_sum2_t1$moy, type = "b", col="darkorange1", pch=4)
legend("topleft", c("Produit d'un vecteur par un double","Somme des éléments d'un vecteur", "Addition de 2 vecteurs"), col=c("brown", "darkcyan", "darkorange1"), lty=c(1,1,1), pch=c(17,19,4))

## Plot t2 (taille=10^7) pour les trois fonctions
plot( fort_prod_t2$nb.coeurs, fort_prod_t2$moy, type = "b", col="brown", pch=17,main = expression(paste("Temps d'exécution en fonction du nombre de coeurs pour un passage à l'échelle forte (taille=",10^7,")")), xlab="Nombre de coeurs", ylab="Temps d'exécution moyen", xlim=c(1,4), ylim=c(20,80))
points( fort_sum_t2$nb.coeurs, fort_sum_t2$moy, type = "b", col="darkcyan", pch=19)
points( fort_sum2_t2$nb_coeur, fort_sum2_t2$moy, type = "b", col="darkorange1", pch=4)
legend("topleft", c("Produit d'un vecteur par un double","Somme des éléments d'un vecteur", "Addition de 2 vecteurs"), col=c("brown", "darkcyan", "darkorange1"), lty=c(1,1,1), pch=c(17,19,4))

## Plot t3 (taille=10^8) pour les trois fonctions
plot( fort_prod_t3$nb.coeurs, fort_prod_t3$moy, type = "b", col="brown", pch=17,main = expression(paste("Temps d'exécution en fonction du nombre de coeurs pour un passage à l'échelle forte (taille=",10^8,")")), xlab="Nombre de coeurs", ylab="Temps d'exécution moyen", xlim=c(1,4), ylim=c(240,800))
points( fort_sum_t3$nb.coeurs, fort_sum_t3$moy, type = "b", col="darkcyan", pch=19)
points( fort_sum2_t3$nb_coeur, fort_sum2_t3$moy, type = "b", col="darkorange1", pch=4)
legend("topleft", c("Produit d'un vecteur par un double","Somme des éléments d'un vecteur", "Addition de 2 vecteurs"), col=c("brown", "darkcyan", "darkorange1"), lty=c(1,1,1), pch=c(17,19,4))
