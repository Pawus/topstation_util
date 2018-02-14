/* version 0.2 du                                                         */
/*  dernière modification :                                               */
/*         01 10 2013 (SD)                                                */
/*  auteur :                                                              */
/*         SD Samuel Déom (sdeom@epadesa.fr)                              */
/*         VD Vianney Dugrain (vdugrain@epadesa.fr)                       */

/* Pour fonctionner il faut inclure préalablement la boite à outils       */
/*  epTexteOutils                                                         */

/* Liste des routines                                                     */
/*	Tronc(§prc_entree,§prc_sortie) Tronque la valeur d'un nombre à 		  */
/*		   l'entier inférieur											  */
/*         dernière modification : 14 12 2012 (SD-VD)                     */
/*	FormateEntier(§prc_entree,prc_sortie) Formate une valeur numérique	  */
/*		   à l'entier inférieur											  */
/*         dernière modification : 01 10 2013 (SD)                        */

rout,Tronc(§prc_entree,§prc_sortie)
/*	Tronque la valeur stockée dans la procédure §prc_entree à l'entier 	*/	
/*	 inférieur et la renvoie dans §prc_sortie							*/
{
  var,§int
  §int=[[§prc_entree]%0]
  if,"§int>[§prc_entree]"
  {
    §int=[§int-1]
  }
  [§prc_sortie]=[§int]
}

rout,FormateEntier(§prc_entree,§prc_sortie)
/*	Formate la valeur du nombre contenue dans la procédure §prc_entier	*/
/*	 en renvoie un entier stocké dans la procédure §prc_sortie			*/
{
  var,§int,§temp
  run,DelChr34([§prc_entree],§temp)
  if,"valnum(§temp)"
  {
    run,Tronc(§temp,§int)
  }
  else
  {
	§int=0
  }
  [§prc_sortie]=[§int]
}