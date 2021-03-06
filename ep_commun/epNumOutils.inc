/* version 0.2 du                                                         */
/*  derni�re modification :                                               */
/*         01 10 2013 (SD)                                                */
/*  auteur :                                                              */
/*         SD Samuel D�om (sdeom@epadesa.fr)                              */
/*         VD Vianney Dugrain (vdugrain@epadesa.fr)                       */

/* Pour fonctionner il faut inclure pr�alablement la boite � outils       */
/*  epTexteOutils                                                         */

/* Liste des routines                                                     */
/*	Tronc(�prc_entree,�prc_sortie) Tronque la valeur d'un nombre � 		  */
/*		   l'entier inf�rieur											  */
/*         derni�re modification : 14 12 2012 (SD-VD)                     */
/*	FormateEntier(�prc_entree,prc_sortie) Formate une valeur num�rique	  */
/*		   � l'entier inf�rieur											  */
/*         derni�re modification : 01 10 2013 (SD)                        */

rout,Tronc(�prc_entree,�prc_sortie)
/*	Tronque la valeur stock�e dans la proc�dure �prc_entree � l'entier 	*/	
/*	 inf�rieur et la renvoie dans �prc_sortie							*/
{
  var,�int
  �int=[[�prc_entree]%0]
  if,"�int>[�prc_entree]"
  {
    �int=[�int-1]
  }
  [�prc_sortie]=[�int]
}

rout,FormateEntier(�prc_entree,�prc_sortie)
/*	Formate la valeur du nombre contenue dans la proc�dure �prc_entier	*/
/*	 en renvoie un entier stock� dans la proc�dure �prc_sortie			*/
{
  var,�int,�temp
  run,DelChr34([�prc_entree],�temp)
  if,"valnum(�temp)"
  {
    run,Tronc(�temp,�int)
  }
  else
  {
	�int=0
  }
  [�prc_sortie]=[�int]
}