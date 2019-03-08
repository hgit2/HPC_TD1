
faible_prod <- read.table("faible_prod.txt", header = TRUE, sep="\t", dec=",")
plot( faible_prod$taille.vecteur, faible_prod$moy)
